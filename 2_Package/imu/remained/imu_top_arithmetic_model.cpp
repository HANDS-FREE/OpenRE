/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: imu_top_arithmetic_model.cpp
* Contact:  QQ Exchange Group -- 521037187
* Version:  V2.0
*
* LICENSING TERMS:
* The Hands Free is licensed generally under a permissive 3-clause BSD license. 
* Contributions are requiredto be made under the same license.
*
* History:
* <author>      <time>      <version>      <desc>
* chenyingbing  2015.12.1   V1.6           creat this file
* Description:  本文件封装了IMU中 姿态角融合的算法所需的 数学模型 状态变量 和算法应用计算函数
*									算法简图：
*
*									#define ARITHMETIC_MPU6050_EXTENDEDKALMAN		1u
*									[MPU6050]	> |FIFO Filter平均滤波| 	> 	|扩展卡尔曼滤波|				<> Pitch Roll	
*
*									#define ARITHMETIC_MPUHMC5883_EGyroCorrect	1u
*									[HMC5883] > |FIFO Filter平均滤波| 	>		|陀螺仪误差叉积法修正|	>		Yaw
*
*									本算法效果说明：
*									能够实现基本的扩展卡尔曼滤波 提供欧拉角，位置向量差，陀螺仪角速度。
*								  但是，因为未在四旋翼上进行测试，可能存在以下不足：
*									1.滞后性太大？
*									2.系数未优化 配置与config.h
***********************************************************************************************************************/

#include "stdlib.h"
#include "imu_top_arithmetic_model.h"

#define degree2radian	0.0174f		
#define radian2degree 57.3f		

ARITHMETIC_MODEL imu_arithmetic_model;

ARITHMETIC_MODEL::ARITHMETIC_MODEL()
{
    // 初始化 - 用户区
    Fusion_En = 1;
    Fusion_State = 0;

    // 初始化 - 内部调用区
    Imu_Top_fusion_HavingInitial = 0;

    Target_Angle.pitch = 0;
    Target_Angle.roll = 0;
    Target_Angle.yaw = 0;

}

/***********************************************************************************************************************
***                                                                                                                  ***
***                                 以下是 基本计算函数                                                  	     ***
***                                                                                                                  ***
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function:     double ARITHMETIC::M_Smart_sqrt(double number)
*
* Scope:        private
*
* Description:	聪明的开方函数 减少一定量的计算时间
*
* Arguments:
*
* Return:
*
* Cpu_Time:     
*
* History:
* chenyingbing  2015.12.1   V1.6      creat
***********************************************************************************************************************/
IPType ARITHMETIC_MODEL::M_Smart_sqrt(IPType number)
{
    static long i;
    static float x2, y;
    const static float threehalfs = 1.5f;
    static IPType deal;

    x2 = number * 0.5f;
    y   = number;
    i   = * ( long * ) &y;
    i   = 0x5f3759df - ( i >> 1 );
    y   = * ( float * ) &i;
    y   = y * ( threehalfs - ( x2 * y * y ) ); 	// 1st iteration
    // y   = y * ( threehalfs - ( x2 * y * y ) ); // 2nd iteration, this can be removed

    deal = 1/y;

    return deal;
}

/***********************************************************************************************************************
* Function:     void ARITHMETIC::Vector3_Norm(double *vector_norm)
*
* Scope:        private
*
* Description:	单位化向量 向量大小：3个长度
*
* Arguments:
*
* Return:
*
* Cpu_Time:     
*
* History:
* chenyingbing  2015.12.1   V1.6      creat
***********************************************************************************************************************/
void ARITHMETIC_MODEL::Vector3_Norm(IPType *vector_norm)
{
    static double norm;
    norm = M_Smart_sqrt(vector_norm[0]*vector_norm[0] +
            vector_norm[1]*vector_norm[1] +
            vector_norm[2]*vector_norm[2]);

    vector_norm[0] /= norm;
    vector_norm[1] /= norm;
    vector_norm[2] /= norm;
}

/***********************************************************************************************************************
* Function:     void ARITHMETIC_MODEL::Vector3CrossProduct3(IPType *v_l, IPType *v_r, IPType *v_return)
*
* Scope:        private
*
* Description:	三维向量叉积 [eax,eay,eaz] = [ax,ay,az]×[vx,vy,vz]
*								eax = (ay*vz - az*vy) ;
*								eay = (az*vx - ax*vz) ;
*								eaz = (ax*vy - ay*vx) ;
*
* Arguments:
*
* Return:
*
* Cpu_Time:     
*
* History:
* chenyingbing  2015.12.1   V1.6      creat
***********************************************************************************************************************/
void ARITHMETIC_MODEL::Vector3CrossProduct(IPType *v_l, IPType *v_r, IPType *v_return)
{
    v_return[0] = v_l[1]*v_r[2] - v_l[2]*v_r[1];
    v_return[1] = v_l[2]*v_r[0] - v_l[0]*v_r[2];
    v_return[2] = v_l[0]*v_r[1] - v_l[1]*v_r[0];
}	

IPType ARITHMETIC_MODEL::Vector3DotProduct(IPType *v_l, IPType *v_r)
{
    return (v_l[0]*v_r[0] + v_l[1]*v_r[1] + v_l[2]*v_r[2]);
}


/***********************************************************************************************************************
* Function:    	FUSION_DOUBLE_PRY_DGREE ARITHMETIC::Quaternion_to_PRY_dgree(IMU_QUATERNION qq)
*
* Scope:        public
*
* Description:	定义四元数到欧拉角(degree)的转换	
*
* Arguments:
*
* Return:
*
* Cpu_Time:     
*
* History:
* chenyingbing  2015.12.1   V1.6      creat
***********************************************************************************************************************/
FUSION_IPType_PRY_DGREE ARITHMETIC_MODEL::Quaternion_to_PRY_dgree(IMU_QUATERNION qq)
{
    FUSION_IPType_PRY_DGREE qq_angle;
    /*
        (w+xi+yj+zk)
        qq_angle->pitch = asin(2*w*y-2*z*x); 									// pitch
        qq_angle->roll  = atan2(2*w*x+2*y*z,-2*x*x-2*y*y+1); 	// roll
        qq_angle->yaw   = atan2(2*w*z+2*x*y,-2*y*y-2*z*z+1); 	// yaw
    */

    qq_angle.pitch = base_math_trigonometic.m_asin(2*qq.q0*qq.q2-2*qq.q3*qq.q1)*radian2degree; 									// pitch
    qq_angle.roll  = base_math_trigonometic.m_atan2(2*qq.q0*qq.q1+2*qq.q2*qq.q3,-2*qq.q1*qq.q1-2*qq.q2*qq.q2+1)*radian2degree; 	// roll
    qq_angle.yaw   = base_math_trigonometic.m_atan2(2*qq.q0*qq.q3+2*qq.q1*qq.q2,-2*qq.q2*qq.q2-2*qq.q3*qq.q3+1)*radian2degree; 	// yaw

    return qq_angle;
}

void ARITHMETIC_MODEL::QuaternionVector4_to_PRY_dgree(IPType *qq, IPType *qq_anlge)
{
    qq_anlge[0] = base_math_trigonometic.m_asin(2*qq[0]*qq[2]-2*qq[3]*qq[1])*radian2degree; 									// pitch
    qq_anlge[1] = base_math_trigonometic.m_atan2(2*qq[0]*qq[1]+2*qq[2]*qq[3],-2*qq[1]*qq[1]-2*qq[2]*qq[2]+1)*radian2degree; 	// roll
    qq_anlge[2] = base_math_trigonometic.m_atan2(2*qq[0]*qq[3]+2*qq[1]*qq[2],-2*qq[2]*qq[2]-2*qq[3]*qq[3]+1)*radian2degree; 	// yaw

}


/***********************************************************************************************************************
* Function:   	IMU_QUATERNION ARITHMETIC::PRY_dgree_to_Quaternion(FUSION_DOUBLE_PRY_DGREE qq_angle)
*
* Scope:        public
*
* Description:	定义欧拉角(degree)到四元数的转换
*
* Arguments:
*
* Return:
*
* Cpu_Time:     
*
* History:
* chenyingbing  2015.12.1   V1.6      creat
***********************************************************************************************************************/
IMU_QUATERNION ARITHMETIC_MODEL::PRY_dgree_to_Quaternion(FUSION_IPType_PRY_DGREE qq_angle)
{
    IMU_QUATERNION qq_return;

    qq_angle.pitch *= degree2radian;
    qq_angle.roll  *= degree2radian;
    qq_angle.yaw   *= degree2radian;

    qq_return.q0 = base_math_trigonometic.m_cos(qq_angle.roll*0.5f)*base_math_trigonometic.m_cos(qq_angle.pitch*0.5f)*base_math_trigonometic.m_cos(qq_angle.yaw*0.5f)
            + base_math_trigonometic.m_sin(qq_angle.roll*0.5f)*base_math_trigonometic.m_sin(qq_angle.pitch*0.5f)*base_math_trigonometic.m_sin(qq_angle.yaw*0.5f);
    qq_return.q1 = base_math_trigonometic.m_sin(qq_angle.roll*0.5f)*base_math_trigonometic.m_cos(qq_angle.pitch*0.5f)*base_math_trigonometic.m_cos(qq_angle.yaw*0.5f)
            - base_math_trigonometic.m_cos(qq_angle.roll*0.5f)*base_math_trigonometic.m_sin(qq_angle.pitch*0.5f)*base_math_trigonometic.m_sin(qq_angle.yaw*0.5f);
    qq_return.q2 = base_math_trigonometic.m_cos(qq_angle.roll*0.5f)*base_math_trigonometic.m_sin(qq_angle.pitch*0.5f)*base_math_trigonometic.m_cos(qq_angle.yaw*0.5f)
            + base_math_trigonometic.m_sin(qq_angle.roll*0.5f)*base_math_trigonometic.m_cos(qq_angle.pitch*0.5f)*base_math_trigonometic.m_sin(qq_angle.yaw*0.5f);
    qq_return.q3 = base_math_trigonometic.m_cos(qq_angle.roll*0.5f)*base_math_trigonometic.m_cos(qq_angle.pitch*0.5f)*base_math_trigonometic.m_sin(qq_angle.yaw*0.5f)
            - base_math_trigonometic.m_sin(qq_angle.roll*0.5f)*base_math_trigonometic.m_sin(qq_angle.pitch*0.5f)*base_math_trigonometic.m_cos(qq_angle.yaw*0.5f);

    return Quaternion_Norm(qq_return);
}

void ARITHMETIC_MODEL::PRY_dgree_Vector3_to_Quaternion(IPType *qq_angle, IPType *qq)
{
    static IPType qq_deal[3];

    qq_deal[0] = qq_angle[0] * degree2radian;
    qq_deal[1] = qq_angle[1] * degree2radian;
    qq_deal[2] = qq_angle[2] * degree2radian;

    qq[0] = base_math_trigonometic.m_cos(qq_deal[1]*0.5f)*base_math_trigonometic.m_cos(qq_deal[0]*0.5f)*base_math_trigonometic.m_cos(qq_deal[2]*0.5f)
            + base_math_trigonometic.m_sin(qq_deal[1]*0.5f)*base_math_trigonometic.m_sin(qq_deal[0]*0.5f)*base_math_trigonometic.m_sin(qq_deal[2]*0.5f);
    qq[1] = base_math_trigonometic.m_sin(qq_deal[1]*0.5f)*base_math_trigonometic.m_cos(qq_deal[0]*0.5f)*base_math_trigonometic.m_cos(qq_deal[2]*0.5f)
            - base_math_trigonometic.m_cos(qq_deal[1]*0.5f)*base_math_trigonometic.m_sin(qq_deal[0]*0.5f)*base_math_trigonometic.m_sin(qq_deal[2]*0.5f);
    qq[2] = base_math_trigonometic.m_cos(qq_deal[1]*0.5f)*base_math_trigonometic.m_sin(qq_deal[0]*0.5f)*base_math_trigonometic.m_cos(qq_deal[2]*0.5f)
            + base_math_trigonometic.m_sin(qq_deal[1]*0.5f)*base_math_trigonometic.m_cos(qq_deal[0]*0.5f)*base_math_trigonometic.m_sin(qq_deal[2]*0.5f);
    qq[3] = base_math_trigonometic.m_cos(qq_deal[1]*0.5f)*base_math_trigonometic.m_cos(qq_deal[0]*0.5f)*base_math_trigonometic.m_sin(qq_deal[2]*0.5f)
            - base_math_trigonometic.m_sin(qq_deal[1]*0.5f)*base_math_trigonometic.m_sin(qq_deal[0]*0.5f)*base_math_trigonometic.m_cos(qq_deal[2]*0.5f);
}

/***********************************************************************************************************************
* Function:   	IMU_QUATERNION ARITHMETIC::Quaternion_Norm(IMU_QUATERNION q_in)	
*
* Scope:        private
*
* Description:	定义四元数正常化 q_return = norm(q_in) 
*
* Arguments:
*
* Return:
*
* Cpu_Time:     
*
* History:
* chenyingbing  2015.12.1   V1.6      creat
***********************************************************************************************************************/
IMU_QUATERNION ARITHMETIC_MODEL::Quaternion_Norm(IMU_QUATERNION q_in)
{
    static IPType norm;
    IMU_QUATERNION q_return;

    norm = M_Smart_sqrt(q_in.q0*q_in.q0 + q_in.q1*q_in.q1 + q_in.q2*q_in.q2 + q_in.q3*q_in.q3);
    q_return.q0 = q_in.q0 / norm;
    q_return.q1 = q_in.q1 / norm;
    q_return.q2 = q_in.q2 / norm;
    q_return.q3 = q_in.q3 / norm;

    return q_return;
}

void ARITHMETIC_MODEL::QuaternionVector4_Norm(IPType *vector_norm)
{
    static IPType norm;
    norm = M_Smart_sqrt(vector_norm[0]*vector_norm[0] +
            vector_norm[1]*vector_norm[1] +
            vector_norm[2]*vector_norm[2] +
            vector_norm[3]*vector_norm[3]);

    vector_norm[0] /= norm;
    vector_norm[1] /= norm;
    vector_norm[2] /= norm;
    vector_norm[3] /= norm;
}

/***********************************************************************************************************************
* Function:   	IMU_QUATERNION ARITHMETIC::Quaternion_SimpleAdd(char fx,IMU_QUATERNION q_left, IMU_QUATERNION q_right)
*
* Scope:        private
*
* Description:	定义四元数加法 q_return = q_left + q_right 
*               fx = 其他  加法
*								fx = 0		 减法
* Arguments:
*
* Return:
*
* Cpu_Time:     
*
* History:
* chenyingbing  2015.12.1   V1.6      creat
***********************************************************************************************************************/
IMU_QUATERNION ARITHMETIC_MODEL::Quaternion_SimpleAdd(char fx,IMU_QUATERNION q_left, IMU_QUATERNION q_right)
{
    IMU_QUATERNION q_return;
    if(fx==0)
    {
        q_right.q0 = -q_right.q0;
        q_right.q1 = -q_right.q1;
        q_right.q2 = -q_right.q2;
        q_right.q3 = -q_right.q3;
    }
    q_return.q0 = q_left.q0 + q_right.q0;
    q_return.q1 = q_left.q1 + q_right.q1;
    q_return.q2 = q_left.q2 + q_right.q2;
    q_return.q3 = q_left.q3 + q_right.q3;

    return q_return;
}

void ARITHMETIC_MODEL::QuaternionVector4_SimpleAdd(char fx,IPType *q_left, IPType *q_right, IPType *q_result)
{
    if(fx==0){
        q_result[0] = q_left[0] - q_right[0];
        q_result[1] = q_left[1] - q_right[1];
        q_result[2] = q_left[2] - q_right[2];
        q_result[3] = q_left[3] - q_right[3];
    }else{
        q_result[0] = q_left[0] + q_right[0];
        q_result[1] = q_left[1] + q_right[1];
        q_result[2] = q_left[2] + q_right[2];
        q_result[3] = q_left[3] + q_right[3];
    }
}

void ARITHMETIC_MODEL::QuaternionVector4_Kgain_SimpleAdd(char fx, IPType *q_left, IPType Kgain1, IPType *q_right, IPType Kgain2, IPType *q_result)
{
    if(fx==0){
        q_result[0] = Kgain1*q_left[0] - Kgain2*q_right[0];
        q_result[1] = Kgain1*q_left[1] - Kgain2*q_right[1];
        q_result[2] = Kgain1*q_left[2] - Kgain2*q_right[2];
        q_result[3] = Kgain1*q_left[3] - Kgain2*q_right[3];
    }else{
        q_result[0] = Kgain1*q_left[0] + Kgain2*q_right[0];
        q_result[1] = Kgain1*q_left[1] + Kgain2*q_right[1];
        q_result[2] = Kgain1*q_left[2] + Kgain2*q_right[2];
        q_result[3] = Kgain1*q_left[3] + Kgain2*q_right[3];
    }
}

/***********************************************************************************************************************
* Function:   	IMU_QUATERNION ARITHMETIC::Quaternion_Kgain_q(IPType Kgain, IMU_QUATERNION q_in)
*
* Scope:        private
*
* Description:	定义四元数 各个值的系数放大 
*
* Arguments:
*
* Return:
*
* Cpu_Time:     
*
* History:
* chenyingbing  2015.12.1   V1.6      creat
***********************************************************************************************************************/
IMU_QUATERNION ARITHMETIC_MODEL::Quaternion_Kgain_q(IPType Kgain, IMU_QUATERNION q_in)
{
    IMU_QUATERNION q_return;
    q_return.q0 = Kgain*q_in.q0;
    q_return.q1 = Kgain*q_in.q1;
    q_return.q2 = Kgain*q_in.q2;
    q_return.q3 = Kgain*q_in.q3;

    return q_return;
}

/***********************************************************************************************************************
* Function:   	double ARITHMETIC::Quaternion_DotMutiply(IMU_QUATERNION q_left, IMU_QUATERNION q_right)
*
* Scope:        private
*
* Description:	定义四元数点积
*								PS: 两个单位四元数向量 越接近，点积越大  <= 1
*
* Arguments:
*
* Return:
*
* Cpu_Time:     
*
* History:
* chenyingbing  2015.12.1   V1.6      creat
***********************************************************************************************************************/
IPType ARITHMETIC_MODEL::Quaternion_DotMutiply(IMU_QUATERNION q_left, IMU_QUATERNION q_right)
{
    double return_value;
    return_value = q_left.q0*q_right.q0 + q_left.q1*q_right.q1 + q_left.q2*q_right.q2 + q_left.q3*q_right.q3;

    return return_value;
}

IPType ARITHMETIC_MODEL::QuaternionVector4_DotMutiply(IPType *q_left, IPType *q_right)
{
    double return_value;
    return_value = q_left[0]*q_right[0] + q_left[1]*q_right[1] + q_left[2]*q_right[2] + q_left[3]*q_right[3];

    return return_value;
}


/***********************************************************************************************************************
* Function:   	IMU_QUATERNION ARITHMETIC::Quaternion_CrossMutiply(IMU_QUATERNION q_left, IMU_QUATERNION q_right)
*
* Scope:        private
*
* Description:	定义四元数叉乘法 q_return = q_left × q_right
*
* Arguments:
*
* Return:
*
* Cpu_Time:     
*
* History:
* chenyingbing  2015.12.1   V1.6      creat
***********************************************************************************************************************/
IMU_QUATERNION ARITHMETIC_MODEL::Quaternion_CrossMutiply(IMU_QUATERNION q_left, IMU_QUATERNION q_right)
{
    IMU_QUATERNION q_return;
    /*
        (d+ai+bj+ck)*(w+xi+yj+zk)
        q_return->q0 = d*w - a*x - b*y - c*z;
        q_return->q1 = a*w + d*x + b*z - c*y;
        q_return->q2 = b*w + d*y + c*x - a*z;
        q_return->q3 = c*w + d*z + a*y - b*x;
    */
    q_return.q0 = q_left.q0*q_right.q0 - q_left.q1*q_right.q1 - q_left.q2*q_right.q2 - q_left.q3*q_right.q3;
    q_return.q1 = q_left.q1*q_right.q0 + q_left.q0*q_right.q1 + q_left.q2*q_right.q3 - q_left.q3*q_right.q2;
    q_return.q2 = q_left.q2*q_right.q0 + q_left.q0*q_right.q2 + q_left.q3*q_right.q1 - q_left.q1*q_right.q3;
    q_return.q3 = q_left.q3*q_right.q0 + q_left.q0*q_right.q3 + q_left.q1*q_right.q2 - q_left.q2*q_right.q1;

    return Quaternion_Norm(q_return);
}

void ARITHMETIC_MODEL::QuaternionVector4_CrossMutiply(IPType *q_left, IPType *q_right, IPType *q_result)
{
    q_result[0] = q_left[0]*q_right[0] - q_left[1]*q_right[1] - q_left[2]*q_right[2] - q_left[3]*q_right[3];
    q_result[1] = q_left[1]*q_right[0] + q_left[0]*q_right[1] + q_left[2]*q_right[3] - q_left[3]*q_right[2];
    q_result[2] = q_left[2]*q_right[0] + q_left[0]*q_right[2] + q_left[3]*q_right[1] - q_left[1]*q_right[3];
    q_result[3] = q_left[3]*q_right[0] + q_left[0]*q_right[3] + q_left[1]*q_right[2] - q_left[2]*q_right[1];

    QuaternionVector4_Norm(q_result);
}

/***********************************************************************************************************************
* Function:   	IMU_QUATERNION ARITHMETIC::Quaternion_Rotate(char fx, IMU_QUATERNION q_orin, IMU_QUATERNION q_turn)
*
* Scope:        private
*
* Description:	定义四元数旋转 Q = q_turn*q_orin 表示先做q_orin旋转，再做q_turn旋转。
*								PS: 第一次旋转是基于B坐标系的旋转轴，第二次旋转是基于B_NEW的，所以，欧拉角转四元数旋转，代表的意义要清楚
*										由于两次旋转轴不同，所以不能简单逆旋转啊啊啊啊啊！！！！！！！
*
*								*** 用欧拉角转换成的四元数的旋转轴是基于B坐标系的，此时B坐标系 = N坐标系！！！
*										所以如果要将此时欧拉角的四元数逆旋转 “相应的欧拉角” 应将相应欧拉角得到的四元数的旋转轴
*										映射到当前B坐标系，再进行逆旋转
*               fx = 其他  正向
*								fx = 0		 逆向	: 
*
* Arguments:
*
* Return:
*
* Cpu_Time:     
*
* History:
* chenyingbing  2015.12.1   V1.6      creat
***********************************************************************************************************************/
IMU_QUATERNION ARITHMETIC_MODEL::Quaternion_Rotate(char fx, IMU_QUATERNION q_orin, IMU_QUATERNION q_turn)
{
    IMU_QUATERNION q_return;

    if(fx==0){
        q_turn.q0 = q_turn.q0;
        q_turn.q1 = -q_turn.q1;
        q_turn.q2 = -q_turn.q2;
        q_turn.q3 = -q_turn.q3;
    }
    q_return  = Quaternion_CrossMutiply(q_turn,q_orin);

    return q_return;
}

void ARITHMETIC_MODEL::QuaternionVector4_Rotate(char fx, IPType *q_orin, IPType *q_turn, IPType *q_result)
{
    static IPType q_deal[4];
    q_deal[0] = q_turn[0];
    q_deal[1] = q_turn[1];
    q_deal[2] = q_turn[2];
    q_deal[3] = q_turn[3];

    if(fx==0){
        q_deal[0] =  q_deal[0];
        q_deal[1] = -q_deal[1];
        q_deal[2] = -q_deal[2];
        q_deal[3] = -q_deal[3];
    }

    QuaternionVector4_CrossMutiply(q_deal,q_orin,q_result);
}


/***********************************************************************************************************************
* Function:   	IMU_QUATERNION ARITHMETIC_MODEL::Quaternion_GlobalInterpolation(IPType t, IPType Theta_dgree, 
                                                                IMU_QUATERNION q_orin, IMU_QUATERNION q_target)
*
* Scope:        private
*
* Description:	四元数球形插值
*								t = 0 > q_return = q0
*								t = 1 > q_return = q1
*								q(t)=q1 * sin?(1-t)/sin? + q2 * sin?t/sin?
*								它是非线性的，且 Theta_dgree<=90 才可行
*
* Arguments:
*
* Return:
*
* Cpu_Time:     
*
* History:
* chenyingbing  2015.12.1   V1.6      creat
***********************************************************************************************************************/
IMU_QUATERNION ARITHMETIC_MODEL::Quaternion_GlobalInterpolation(IPType t, IPType Theta_dgree, 
                                                                IMU_QUATERNION q_orin, IMU_QUATERNION q_target)
{
    IMU_QUATERNION q_return;
    double d1,d2,d3;

    //一定不能大于90
    //q_orin 和 q_target 随意：会存在非线性误差
    if(Theta_dgree>=90)Theta_dgree = 90;

    Theta_dgree *= degree2radian;
    d3 = base_math_trigonometic.m_sin(Theta_dgree);
    d1 = base_math_trigonometic.m_sin(Theta_dgree*(1-t))/d3;
    d2 = base_math_trigonometic.m_sin(Theta_dgree*t)/d3;

    q_return = Quaternion_SimpleAdd(1,Quaternion_Kgain_q(d1,q_orin),Quaternion_Kgain_q(d2,q_target));

    return Quaternion_Norm(q_return);
}

void ARITHMETIC_MODEL::QuaternionVector4_GlobalInterpolation(IPType t, IPType Theta_dgree, IPType *q_orin, IPType *q_target, IPType *q_result)
{
    double d1,d2,d3;

    //一定不能大于90
    //q_orin 和 q_target 随意：会存在非线性误差
    if(Theta_dgree>=90)Theta_dgree = 90;

    Theta_dgree *= degree2radian;
    d3 = base_math_trigonometic.m_sin(Theta_dgree);
    d1 = base_math_trigonometic.m_sin(Theta_dgree*(1-t))/d3;
    d2 = base_math_trigonometic.m_sin(Theta_dgree*t)/d3;

    QuaternionVector4_Kgain_SimpleAdd(1,q_orin,d1,q_target,d2,q_result);

    QuaternionVector4_Norm(q_result);
}

/***********************************************************************************************************************
* Function:   	IMU_QUATERNION ARITHMETIC::Quaternion_Differential(IMU_QUATERNION qq, FLOAT_XYZ Gyro)
*
* Scope:        private
*
* Description:	四元数微分
*
* Arguments: 当前状态四元数	当前GYRO_NORMAL数据
* 
* Return: 四元数微分值
*
* Cpu_Time:     
*
* History:
* chenyingbing  2015.12.1   V1.6      creat
***********************************************************************************************************************/
IMU_QUATERNION ARITHMETIC_MODEL::Quaternion_Differential(IMU_QUATERNION qq, FLOAT_XYZ Gyro)
{
    IMU_QUATERNION dq_return;

    //转化为弧度制
    Gyro.x *= degree2radian;
    Gyro.y *= degree2radian;
    Gyro.z *= degree2radian;

    dq_return.q0 = (-qq.q1*Gyro.x - qq.q2*Gyro.y - qq.q3*Gyro.z);
    dq_return.q1 = ( qq.q0*Gyro.x + qq.q2*Gyro.z - qq.q3*Gyro.y);
    dq_return.q2 = ( qq.q0*Gyro.y - qq.q1*Gyro.z + qq.q3*Gyro.x);
    dq_return.q3 = ( qq.q0*Gyro.z + qq.q1*Gyro.y - qq.q2*Gyro.x);

    return dq_return;
}

void ARITHMETIC_MODEL::Quaternion_Differential_Matrix(IPType *qq, IPType *Gyro, IPType *dq)
{	
    static double Gyro_Deal[3];
    //转化为弧度制
    Gyro_Deal[0] = Gyro[0] * degree2radian;
    Gyro_Deal[1] = Gyro[1] * degree2radian;
    Gyro_Deal[2] = Gyro[2] * degree2radian;

    dq[0] = (-qq[1]*Gyro_Deal[0] - qq[2]*Gyro_Deal[1] - qq[3]*Gyro_Deal[2]);
    dq[1] = ( qq[0]*Gyro_Deal[0] + qq[2]*Gyro_Deal[2] - qq[3]*Gyro_Deal[1]);
    dq[2] = ( qq[0]*Gyro_Deal[1] - qq[1]*Gyro_Deal[2] + qq[3]*Gyro_Deal[0]);
    dq[3] = ( qq[0]*Gyro_Deal[2] + qq[1]*Gyro_Deal[1] - qq[2]*Gyro_Deal[0]);
}

/************************************************************************************************************************
***                                                                                                                   ***
***                                 以下是 坐标系类函数                                          											***
***                                                                                                                   ***
*************************************************************************************************************************/

/***********************************************************************************************************************
* Function:     FLOAT_XYZ	ARITHMETIC::Cb_to_n_XYZ(IMU_QUATERNION qq, FLOAT_XYZ Cb_XYZDta)
*
* Scope:        private
*
* Description:	将载体坐标系的XYZ > 参考坐标系的XYZ
*
* Arguments: 
* 
* Return: 
*
* Cpu_Time:     
*
* History:
* chenyingbing  2015.12.1   V1.6      creat
***********************************************************************************************************************/
FLOAT_XYZ	ARITHMETIC_MODEL::Cb_to_Cn_XYZ(IMU_QUATERNION qq, FLOAT_XYZ Cb_XYZDta)
{
    FLOAT_XYZ XYZ_Return;

    IPType q0q1 = qq.q0*qq.q1;
    IPType q0q2 = qq.q0*qq.q2;
    IPType q0q3 = qq.q0*qq.q3;
    IPType q1q1 = qq.q1*qq.q1;
    IPType q1q2 = qq.q1*qq.q2;
    IPType q1q3 = qq.q1*qq.q3;
    IPType q2q2 = qq.q2*qq.q2;
    IPType q2q3 = qq.q2*qq.q3;
    IPType q3q3 = qq.q3*qq.q3;

    IPType dealx = (IPType)Cb_XYZDta.x;
    IPType dealy = (IPType)Cb_XYZDta.y;
    IPType dealz = (IPType)Cb_XYZDta.z;

    XYZ_Return.x = (2*dealx*(0.5f - q2q2 - q3q3) + 2*dealy*(q1q2 - q0q3) + 2*dealz*(q1q3 + q0q2));
    XYZ_Return.y = (2*dealx*(q1q2 + q0q3) + 2*dealy*(0.5f - q1q1 - q3q3) + 2*dealz*(q2q3 - q0q1));
    XYZ_Return.z = (2*dealx*(q1q3 - q0q2) + 2*dealy*(q2q3 + q0q1) + 2*dealz*(0.5f - q1q1 - q2q2));

    return XYZ_Return;
}

void ARITHMETIC_MODEL::Cb_to_Cn_XYZ_Matrix(IPType *qq, IPType *Cb_XYZDta, IPType *Cn_XYZDta_Return)
{
    static IPType q0q1,q0q2,q0q3,q1q1,q1q2,q1q3,q2q2,q2q3,q3q3;
    static IPType dealx,dealy,dealz;

    q0q1 = qq[0]*qq[1];
    q0q2 = qq[0]*qq[2];
    q0q3 = qq[0]*qq[3];
    q1q1 = qq[1]*qq[1];
    q1q2 = qq[1]*qq[2];
    q1q3 = qq[1]*qq[3];
    q2q2 = qq[2]*qq[2];
    q2q3 = qq[2]*qq[3];
    q3q3 = qq[3]*qq[3];

    dealx = Cb_XYZDta[0];
    dealy = Cb_XYZDta[1];
    dealz = Cb_XYZDta[2];

    Cn_XYZDta_Return[0] = (2*dealx*(0.5f - q2q2 - q3q3) + 2*dealy*(q1q2 - q0q3) + 2*dealz*(q1q3 + q0q2));
    Cn_XYZDta_Return[1] = (2*dealx*(q1q2 + q0q3) + 2*dealy*(0.5f - q1q1 - q3q3) + 2*dealz*(q2q3 - q0q1));
    Cn_XYZDta_Return[2] = (2*dealx*(q1q3 - q0q2) + 2*dealy*(q2q3 + q0q1) + 2*dealz*(0.5f - q1q1 - q2q2));

}

/***********************************************************************************************************************
* Function:     FLOAT_XYZ	ARITHMETIC::Cn_to_b_XYZ(IMU_QUATERNION qq, FLOAT_XYZ Cn_XYZDta)
*
* Scope:        private
*
* Description:	将参考坐标系的XYZ > 载体坐标系的XYZ
*
* Arguments: 
* 
* Return: 
*
* Cpu_Time:     
*
* History:
* chenyingbing  2015.12.1   V1.6      creat
***********************************************************************************************************************/
FLOAT_XYZ	ARITHMETIC_MODEL::Cn_to_Cb_XYZ(IMU_QUATERNION qq, FLOAT_XYZ Cn_XYZDta)
{
    FLOAT_XYZ XYZ_Return;

    IPType q0q1 = qq.q0*qq.q1;
    IPType q0q2 = qq.q0*qq.q2;
    IPType q0q3 = qq.q0*qq.q3;
    IPType q1q1 = qq.q1*qq.q1;
    IPType q1q2 = qq.q1*qq.q2;
    IPType q1q3 = qq.q1*qq.q3;
    IPType q2q2 = qq.q2*qq.q2;
    IPType q2q3 = qq.q2*qq.q3;
    IPType q3q3 = qq.q3*qq.q3;

    IPType dealx = (IPType)Cn_XYZDta.x;
    IPType dealy = (IPType)Cn_XYZDta.y;
    IPType dealz = (IPType)Cn_XYZDta.z;

    XYZ_Return.x = (2*dealx*(0.5f - q2q2 - q3q3) + 2*dealy*(q1q2 + q0q3) + 2*dealz*(q1q3 - q0q2));
    XYZ_Return.y = (2*dealx*(q1q2 - q0q3) + 2*dealy*(0.5f - q1q1 - q3q3) + 2*dealz*(q2q3 + q0q1));
    XYZ_Return.z = (2*dealx*(q1q3 + q0q2) + 2*dealy*(q2q3 - q0q1) + 2*dealz*(0.5f - q1q1 - q2q2));

    return XYZ_Return;
}

void ARITHMETIC_MODEL::Cn_to_Cb_XYZ_Matrix(IPType *qq, IPType *Cn_XYZDta, IPType *Cb_XYZDta_Return)
{
    static IPType q0q1,q0q2,q0q3,q1q1,q1q2,q1q3,q2q2,q2q3,q3q3;
    static IPType dealx,dealy,dealz;

    q0q1 = qq[0]*qq[1];
    q0q2 = qq[0]*qq[2];
    q0q3 = qq[0]*qq[3];
    q1q1 = qq[1]*qq[1];
    q1q2 = qq[1]*qq[2];
    q1q3 = qq[1]*qq[3];
    q2q2 = qq[2]*qq[2];
    q2q3 = qq[2]*qq[3];
    q3q3 = qq[3]*qq[3];

    dealx = Cn_XYZDta[0];
    dealy = Cn_XYZDta[1];
    dealz = Cn_XYZDta[2];

    Cb_XYZDta_Return[0] = (2*dealx*(0.5f - q2q2 - q3q3) + 2*dealy*(q1q2 + q0q3) + 2*dealz*(q1q3 - q0q2));
    Cb_XYZDta_Return[1] = (2*dealx*(q1q2 - q0q3) + 2*dealy*(0.5f - q1q1 - q3q3) + 2*dealz*(q2q3 + q0q1));
    Cb_XYZDta_Return[2] = (2*dealx*(q1q3 + q0q2) + 2*dealy*(q2q3 - q0q1) + 2*dealz*(0.5f - q1q1 - q2q2));

}

/************************************************************************************************************************
***                                                                                                                   ***
***                                       其他过程算法类函数                                              						***
***                                                                                                                   ***
*************************************************************************************************************************/

/***********************************************************************************************************************
* Function:   	ARITHMETIC::XStateUpdate_by_ImplicitEuler(double Imu_T, double *XUpdate)
*
* Scope:        private
*
* Description:	隐性欧拉法：
                                Yn+1' = Yn + h*f(Xn,Yn)
                                Yn+1 	= Yn + h*f(Xn,Yn+1')
*               更新周期 Imu_T, 需要更新的四元数状态变量 XUpdate, 激励值InForce：这里是角速度
* Arguments: 
* 
* Return: 
*
* Cpu_Time:     
*
* History:
* chenyingbing  2015.12.1   V1.6      creat
***********************************************************************************************************************/
void ARITHMETIC_MODEL::XStateUpdate_by_ImplicitEuler(IPType Imu_T, IPType *XUpdate, IPType *InForce)
{
    //更新周期
    IPType IMU_T_2 = Imu_T * 0.5f;

    //计算用临时变量
    static IPType qq_Deal1[4],qq_Deal2[4];

    //>> h*f(Xn,Yn) := qq_Deal1[4]
    Quaternion_Differential_Matrix(XUpdate, InForce, qq_Deal1);
    //>> Yn+1' = Yn + h*f(Xn,Yn) := qq_Deal2[4]
    QuaternionVector4_Kgain_SimpleAdd(1,XUpdate,1.0,qq_Deal1,IMU_T_2,qq_Deal2);

    //>> h*f(Xn,Yn+1') := qq_Deal1[4]
    Quaternion_Differential_Matrix(qq_Deal2, InForce, qq_Deal1);
    //>> Yn+1 = Yn + h*f(Xn,Yn+1')  := XUpdate
    QuaternionVector4_Kgain_SimpleAdd(1,XUpdate,1.0,qq_Deal1,IMU_T_2,XUpdate);

    QuaternionVector4_Norm(XUpdate);
}

/************************************************************************************************************************
***                                                                                                                   ***
***                                 以下用户接口功能函数    
***
***  B坐标系定义：	pitch绕Y轴,roll绕X轴,yaw绕Z轴
***	 |------→ Y		
***	 | Z朝上
***	 |
***  ↓
***  X
*************************************************************************************************************************/

/***********************************************************************************************************************
* Function:   	void ARITHMETIC::Set_FusionInitial(void)
*
* Scope:        public
*
* Description:	初始化 Fusion
*
* Arguments: 
* 
* Return: 
*
* Cpu_Time:     stm32f4 -- 2us(fpu) instantly 45us(fpu)
*
* History:
* chenyingbing  2015.12.1   V1.6      creat
***********************************************************************************************************************/
void ARITHMETIC_MODEL::Set_ModelInitial(void)
{
    static unsigned int Initial_cord = 100;
    IMU_QUATERNION qq_deal;

    if(mpu6050.gyro_offset_flag == 1){									//已经矫正完GYRO零漂
        if(!Initial_cord)
        {
            if(!Imu_Top_fusion_HavingInitial)
            {
                GetAccHmc_MesAngle_dgree(2);

                Initial_Angle_dgree = AccHmcMes_Angle_dgree;

                Initial_Angle_dgree.yaw = 0;								//以初始位置作为yaw 0 角
                Cn_Orin_Hmcxyz[0] = Z_Hmcxyz[0];						//得到参考坐标系 既 初始位置的 Hmc数据
                Cn_Orin_Hmcxyz[1] = Z_Hmcxyz[1];
                Cn_Orin_Hmcxyz[2] = Z_Hmcxyz[2];
                Vector3_Norm(Cn_Orin_Hmcxyz);

                qq_deal = PRY_dgree_to_Quaternion(Initial_Angle_dgree);

                X_Fus1[0] = qq_deal.q0;
                X_Fus1[1] = qq_deal.q1;
                X_Fus1[2] = qq_deal.q2;
                X_Fus1[3] = qq_deal.q3;
                X_Pre1[0] = qq_deal.q0;
                X_Pre1[1] = qq_deal.q1;
                X_Pre1[2] = qq_deal.q2;
                X_Pre1[3] = qq_deal.q3;

                X_Fus2[0] = qq_deal.q0;
                X_Fus2[1] = qq_deal.q1;
                X_Fus2[2] = qq_deal.q2;
                X_Fus2[3] = qq_deal.q3;
                X_Pre2[0] = qq_deal.q0;
                X_Pre2[1] = qq_deal.q1;
                X_Pre2[2] = qq_deal.q2;
                X_Pre2[3] = qq_deal.q3;

                Imu_Top_fusion_HavingInitial = 1;
            }
        }else{
            Initial_cord--;
        }
    }
}


/***********************************************************************************************************************
* Function:   	void ARITHMETIC_MODEL::ModelCommanState_Update(void)
*
* Scope:        public
*
* Description:	公共变量赋值更新: ACC HMC单位化等
*
* Arguments: 
* 
* Return: 
*
* Cpu_Time:     stm32f4 -- 35us(fpu)
*
* History:
* chenyingbing  2015.12.1   V1.6      creat
***********************************************************************************************************************/
void ARITHMETIC_MODEL::ModelCommanState_Update(void)
{
    //公共变量
    Z_ACCxyz[0] = mpu6050.acc_normal_long_filter.x;
    Z_ACCxyz[1] = mpu6050.acc_normal_long_filter.y;
    Z_ACCxyz[2] = mpu6050.acc_normal_long_filter.z;

    Vector3_Norm(Z_ACCxyz);						//单位化 Z_ACCxyz

    Z_Hmcxyz[0] = hmc5883l.hmc_normal.x;
    Z_Hmcxyz[1] = hmc5883l.hmc_normal.y;
    Z_Hmcxyz[2] = hmc5883l.hmc_normal.z;

    Vector3_Norm(Z_Hmcxyz);						//单位化 Z_Hmcxyz

    Ut[0] = mpu6050.gyro_normal_long_filter.x;
    Ut[1]= 	mpu6050.gyro_normal_long_filter.y;
    Ut[2] = mpu6050.gyro_normal_long_filter.z;

    Cn_Gravity[0] = 0;
    Cn_Gravity[1] = 0;
    Cn_Gravity[2] = 1;
}


/***********************************************************************************************************************
* Function:   	void ARITHMETIC_MODEL::XState1_Predict(double Imu_T)
*
* Scope:        public
*
* Description:	Xstate1积分更新
*
* Arguments: 
* 
* Return: 
*
* Cpu_Time:     stm32f4 -- 54us(fpu)
*
* History:
* chenyingbing  2015.12.1   V1.6      creat
***********************************************************************************************************************/
void ARITHMETIC_MODEL::XState1_Predict(IPType Imu_T)
{

    XStateUpdate_by_ImplicitEuler(Imu_T, X_Pre1, Ut);

}

/***********************************************************************************************************************
* Function:   	void ARITHMETIC_MODEL::XState2_Predict(double Imu_T)
*
* Scope:        public
*
* Description:	Xstate2积分更新
*
* Arguments: 
* 
* Return: 
*
* Cpu_Time:     stm32f4 -- 54us(fpu)
*
* History:
* chenyingbing  2015.12.1   V1.6      creat
***********************************************************************************************************************/
void ARITHMETIC_MODEL::XState2_Predict(IPType Imu_T)
{
    static IPType Utdeal[3];
    Utdeal[0] = Ut[0] + Error_Ut[0];
    Utdeal[1] = Ut[1] + Error_Ut[1];
    Utdeal[2] = Ut[2] + Error_Ut[2];

    XStateUpdate_by_ImplicitEuler(Imu_T, X_Pre2, Utdeal);

}


/***********************************************************************************************************************
* Function:   	FUSION_DOUBLE_PRY_DGREE ARITHMETIC::GetMes_Angle(void)
*
* Scope:        public
*
* Description:	获得 加速度计 磁罗盘 测量的pith,roll,yaw角
*               mode = 1: 由ACC_NORMAL的数据进行测量
*								mode = 2: 由acc_normal_long_filter的数据进行测量
* Arguments: 
* 
* Return: 
*
* Cpu_Time:     stm32f4 -- 10us(fpu)
*
* History:
* chenyingbing  2015.12.1   V1.6      creat
***********************************************************************************************************************/
void ARITHMETIC_MODEL::GetAccHmc_MesAngle_dgree(unsigned char mode)
{
    IPType GG;
    IPType ax,ay,az;
    IPType mx = hmc5883l.hmc_normal.x;
    IPType my = hmc5883l.hmc_normal.y;
    IPType mz = hmc5883l.hmc_normal.z;
    IPType p,r,y,d1,d2;

    //如果输入错误，则按mode = 2使用
    if(mode != 1){
        mode = 2;
    }

    if(mode == 1)
    {
        ax = mpu6050.acc_normal.x;
        ay = mpu6050.acc_normal.y;
        az = mpu6050.acc_normal.z;
    }
    if(mode == 2)
    {
        ax = mpu6050.acc_normal_long_filter.x;
        ay = mpu6050.acc_normal_long_filter.y;
        az = mpu6050.acc_normal_long_filter.z;
    }
    GG = M_Smart_sqrt(ax*ax + ay*ay + az*az);
    p  = -base_math_trigonometic.m_asin(ax/GG);
    r  = base_math_trigonometic.m_atan2(ay,az);

    d1 = my*base_math_trigonometic.m_cos(r)  - mz*base_math_trigonometic.m_sin(r);
    d2 = mx*base_math_trigonometic.m_cos(p) + my*base_math_trigonometic.m_sin(p)*base_math_trigonometic.m_sin(r) + mz*base_math_trigonometic.m_sin(p)*base_math_trigonometic.m_cos(r);
    y =  -base_math_trigonometic.m_atan2(d1,d2);

    AccHmcMes_Angle_dgree.pitch = p * radian2degree;
    AccHmcMes_Angle_dgree.roll = r * radian2degree;
    AccHmcMes_Angle_dgree.yaw = y * radian2degree;
}

/***********************************************************************************************************************
* Function:   	void ARITHMETIC::UpdateState_to_PortVariable(void)
*
* Scope:        public
*
* Description:	将状态变量更新到用户接口变量
*
* Arguments: 
* 
* Return: 
*
* Cpu_Time:     stm32f4 -- 35us(fpu)
*
* History:
* chenyingbing  2015.12.1   V1.6      creat
***********************************************************************************************************************/
void ARITHMETIC_MODEL::UpdateState_to_PortVariable(void)
{
    static IPType Angle_Deal[3];

    static IPType Q_TargetAngle[4];
    static IPType Target_Vector1[3];
    static IPType Deal_Vector1[3];

    if(Fusion_State){
        //设备正常时
        //Pitch, Roll =================================>
        QuaternionVector4_to_PRY_dgree(X_Pre1, Angle_Deal);
        Fus_Angle.pitch = Angle_Deal[0];
        Fus_Angle.roll  = Angle_Deal[1];
        //Fus_Angle.yaw	  = Angle_Deal[2];

        //Yaw	=========================================>
        QuaternionVector4_to_PRY_dgree(X_Pre2, Angle_Deal);
        //Fus_Angle.pitch = Angle_Deal[0];
        //Fus_Angle.roll  = Angle_Deal[1];
        Fus_Angle.yaw	  = Angle_Deal[2];

        // The Data used for control :
        Angle_Deal[0] = Target_Angle.pitch;
        Angle_Deal[1] = Target_Angle.roll;
        Angle_Deal[2] = Target_Angle.yaw;
        PRY_dgree_Vector3_to_Quaternion(Angle_Deal, Q_TargetAngle);

        Cn_to_Cb_XYZ_Matrix(Q_TargetAngle, Cn_Gravity, Target_Vector1);

        Vector3CrossProduct(Target_Vector1, Cb_Ideal_Acc1, Deal_Vector1);

        //Deal_Num1 = Vector3DotProduct(Target_Vector1,Cb_Ideal_Acc1);

        ControlVector_Position.pitch = Deal_Vector1[1];		// √	超过90°未解决
        ControlVector_Position.roll = Deal_Vector1[0];		// √	超过90°未解决

        ControlVector_Position.yaw = (Target_Angle.yaw - Fus_Angle.yaw);
        if(ControlVector_Position.yaw > 180) {ControlVector_Position.yaw = ControlVector_Position.yaw - 360;}
        if(ControlVector_Position.yaw < -180) {ControlVector_Position.yaw = 360 + ControlVector_Position.yaw;}
        ControlVector_Position.yaw *= degree2radian;			// √

        ControlVector_Velocity.pitch = Ut[1];
        ControlVector_Velocity.roll = Ut[0];
        ControlVector_Velocity.yaw = Ut[2];

        //quaternion=====================================>
        Fus_Quaternion = PRY_dgree_to_Quaternion(Fus_Angle);

    }else{
        //设备不正常时
        Fus_Angle.pitch = 0;
        Fus_Angle.roll  = 0;
        Fus_Angle.yaw	  = 0;

        ControlVector_Position.pitch = 0;
        ControlVector_Position.roll = 0;
        ControlVector_Position.yaw = 0;

        ControlVector_Velocity.pitch = 0;
        ControlVector_Velocity.roll = 0;
        ControlVector_Velocity.yaw = 0;
    }

}


/***********************************************************************************************************************
* Function:   	void ARITHMETIC::ExtendedKalman_State_Update1(void)
*
* Scope:        public
*
* Description:  更新扩展卡尔曼滤波的一些状态变量
*
*								文献1 ：Application of Quaternion-Based Extended Kalman Filter for 
*												MAV Attitude Estimation Using MEMS Sensors
*								------- 用于微小型飞行器姿态估计的四元数扩展卡尔曼滤波算法 薛亮 
*								
*								文献2 : Quaternion-Based Kalman Filter for Micro-machined Strapdown
*												Attitude Heading Reference System
*								------- 用于微机械捷联式航姿系统的四元素算法卡尔曼滤波器 高钟毓(yu')
*								PS:			(文献2为文献1的引用文献)
*
* Arguments: 
* 
* Return: 
*
* Cpu_Time:     stm32f4 -- 37us(fpu)
*
* History:
* chenyingbing  2015.12.1   V1.6      creat
***********************************************************************************************************************/
void ARITHMETIC_MODEL::ExtendedKalman_State_Update1(void)
{
    /*
        // 过程变量
        double 										Cb_Ideal_Acc1[3];										//由重力向量 通过Cn_to_Cb映射的当前姿态对应的 ACCxyz
        double 										Cb_Ideal_Acc2[3];

        // 状态变量 ：
        double										F_Jacobian[16];											//F对X求偏导的雅克比矩阵 4×4
        double 										H_Jacobian[12];											//H对X求偏导的雅克比矩阵 3×4

        // 过程变量 ：融合过程处理变量
        double										Pre_Covariance_1[16];								//预测过程协方差 				 4×4
        double										Mes_Covariance_1[9];								//测量过程协方差				 3×3

    */

    //用于计算的变量
    static IPType gxyz[3];																				//弧度制的 陀螺仪数据

    // 过程1变量
    Cn_to_Cb_XYZ_Matrix(X_Fus1,Cn_Gravity,Cb_Ideal_Acc1);
    Vector3_Norm(Cb_Ideal_Acc1);

    Cn_to_Cb_XYZ_Matrix(X_Fus1,Cn_Orin_Hmcxyz,Cb_Ideal_Hmc1);
    Vector3_Norm(Cb_Ideal_Hmc1);

    // 卡尔曼滤波章
    gxyz[0] = Ut[0] * degree2radian;
    gxyz[1] = Ut[1] * degree2radian;
    gxyz[2] = Ut[2] * degree2radian;

    //F_Jacobian 4×4
    F_Jacobian[0]  = 1;			F_Jacobian[1]  = -gxyz[0];	F_Jacobian[2]  = -gxyz[1];	F_Jacobian[3]  = -gxyz[2];
    F_Jacobian[4]  = gxyz[0];	F_Jacobian[5]  = 1;			F_Jacobian[6]  = gxyz[1];	F_Jacobian[7]  = -gxyz[2];
    F_Jacobian[8]  = gxyz[0];	F_Jacobian[9]  = -gxyz[1];	F_Jacobian[10] = 1;			F_Jacobian[11] = gxyz[2];
    F_Jacobian[12] = gxyz[0];	F_Jacobian[13] = gxyz[1];	F_Jacobian[14] = -gxyz[2];	F_Jacobian[15] = 1;

    //H_Jacobian 3×4
    //1-3×4
    H_Jacobian1[0] = -2*Cn_Gravity[2]*X_Fus1[2];	H_Jacobian1[1] = 2*Cn_Gravity[2]*X_Fus1[3];		H_Jacobian1[2] = -2*Cn_Gravity[2]*X_Fus1[0];		H_Jacobian1[3] = 2*Cn_Gravity[2]*X_Fus1[1];
    H_Jacobian1[4] = 2*Cn_Gravity[2]*X_Fus1[1];		H_Jacobian1[5] = 2*Cn_Gravity[2]*X_Fus1[0];		H_Jacobian1[6] = 2*Cn_Gravity[2]*X_Fus1[3];			H_Jacobian1[7] = 2*Cn_Gravity[2]*X_Fus1[2];
    H_Jacobian1[8] = 2*Cn_Gravity[2]*X_Fus1[0];		H_Jacobian1[9] = -2*Cn_Gravity[2]*X_Fus1[1];	H_Jacobian1[10] = -2*Cn_Gravity[2]*X_Fus1[2];		H_Jacobian1[11] = 2*Cn_Gravity[2]*X_Fus1[3];

}

/***********************************************************************************************************************
* Function:   	void ARITHMETIC::ExtendedKalman_State_Update(void)
*
* Scope:        public
*
* Description:  更新YAW角 叉积修正过程中的一些变量
*
* Arguments: 
* 
* Return: 
*
* Cpu_Time:     stm32f4 -- 55us(fpu)
*
* History:
* chenyingbing  2015.12.1   V1.6      creat
***********************************************************************************************************************/
void ARITHMETIC_MODEL::YawError_Correct_State_Update2(void)
{
    // 过程2变量
    Cn_to_Cb_XYZ_Matrix(X_Fus2,Cn_Gravity,Cb_Ideal_Acc2);
    Vector3_Norm(Cb_Ideal_Acc2);

    Cn_to_Cb_XYZ_Matrix(X_Fus2,Cn_Orin_Hmcxyz,Cb_Ideal_Hmc2);
    Vector3_Norm(Cb_Ideal_Hmc2);

    // 卡尔曼滤波章
    //gxyz[0] = Ut[0] * degree2radian;
    //gxyz[1] = Ut[1] * degree2radian;
    //gxyz[2] = Ut[2] * degree2radian;

    /*F_Jacobian 4×4
    F_Jacobian[0]  = 1;				F_Jacobian[1]  = -gxyz[0];	F_Jacobian[2]  = -gxyz[1];	F_Jacobian[3]  = -gxyz[2];
    F_Jacobian[4]  = gxyz[0];	F_Jacobian[5]  = 1;					F_Jacobian[6]  = gxyz[1];		F_Jacobian[7]  = -gxyz[2];
    F_Jacobian[8]  = gxyz[0];	F_Jacobian[9]  = -gxyz[1];	F_Jacobian[10] = 1;					F_Jacobian[11] = gxyz[2];
    F_Jacobian[12] = gxyz[0];	F_Jacobian[13] = gxyz[1];		F_Jacobian[14] = -gxyz[2];	F_Jacobian[15] = 1;

    //H_Jacobian 3×4
    //1-3×4
    H_Jacobian2[0] = 2*Cn_Orin_Hmcxyz[0]*X_Fus2[0]+2*Cn_Orin_Hmcxyz[1]*X_Fus2[3]-2*Cn_Orin_Hmcxyz[2]*X_Fus2[2];
        H_Jacobian2[1] = 2*Cn_Orin_Hmcxyz[0]*X_Fus2[1]+2*Cn_Orin_Hmcxyz[1]*X_Fus2[2]+2*Cn_Orin_Hmcxyz[2]*X_Fus2[3];
            H_Jacobian2[2] = -2*Cn_Orin_Hmcxyz[0]*X_Fus2[2]+2*Cn_Orin_Hmcxyz[1]*X_Fus2[1]-2*Cn_Orin_Hmcxyz[2]*X_Fus2[0];
                H_Jacobian2[3] = -2*Cn_Orin_Hmcxyz[0]*X_Fus2[3]+2*Cn_Orin_Hmcxyz[1]*X_Fus2[0]+2*Cn_Orin_Hmcxyz[2]*X_Fus2[1];
    H_Jacobian2[4] = -2*Cn_Orin_Hmcxyz[0]*X_Fus2[3]+2*Cn_Orin_Hmcxyz[1]*X_Fus2[0]+2*Cn_Orin_Hmcxyz[2]*X_Fus2[1];
        H_Jacobian2[5] = 2*Cn_Orin_Hmcxyz[0]*X_Fus2[2]-2*Cn_Orin_Hmcxyz[1]*X_Fus2[1]+2*Cn_Orin_Hmcxyz[2]*X_Fus2[0];
            H_Jacobian2[6] = 2*Cn_Orin_Hmcxyz[0]*X_Fus2[1]+2*Cn_Orin_Hmcxyz[1]*X_Fus2[2]+2*Cn_Orin_Hmcxyz[2]*X_Fus2[3];
                H_Jacobian2[7] = -2*Cn_Orin_Hmcxyz[0]*X_Fus2[0]-2*Cn_Orin_Hmcxyz[1]*X_Fus2[3]+2*Cn_Orin_Hmcxyz[2]*X_Fus2[2];
    H_Jacobian2[8] = 2*Cn_Orin_Hmcxyz[0]*X_Fus2[2]-2*Cn_Orin_Hmcxyz[1]*X_Fus2[1]+2*Cn_Orin_Hmcxyz[2]*X_Fus2[0];
        H_Jacobian2[9] = 2*Cn_Orin_Hmcxyz[0]*X_Fus2[3]-2*Cn_Orin_Hmcxyz[1]*X_Fus2[0]-2*Cn_Orin_Hmcxyz[2]*X_Fus2[1];
            H_Jacobian2[10] = 2*Cn_Orin_Hmcxyz[0]*X_Fus2[0]+2*Cn_Orin_Hmcxyz[1]*X_Fus2[3]-2*Cn_Orin_Hmcxyz[2]*X_Fus2[2];
                H_Jacobian2[11] = 2*Cn_Orin_Hmcxyz[0]*X_Fus2[1]+2*Cn_Orin_Hmcxyz[1]*X_Fus2[2]+2*Cn_Orin_Hmcxyz[2]*X_Fus2[3];
    */
}


/***********************************************************************************************************************
* Function:   	void ARITHMETIC::XState_KalmanFusionCall_Process1(double Imu_T)
*
* Scope:        public
*
* Description:  扩展卡尔曼滤波
*
* Arguments: 
* 
* Return: 
*
* Cpu_Time:     stm32f4 -- 52us(fpu)
*
* History:
* chenyingbing  2015.12.1   V1.6      creat
***********************************************************************************************************************/
void ARITHMETIC_MODEL::XState_KalmanFusionCall_Process1(void)
{
    static unsigned char once = 2;
    static unsigned char i;

#define 	K2_Amplify_Gate0		0.5f
#define 	K2_Amplify_Gate1		1.5f
#define 	K2_Amplify_Gate2		5.0f

    static IPType Gradient_ZAxyz[3];		// 梯度步进 处理变量XYZ
    static IPType K2_Amplify_AccCov[2];		// 放大系数2处理变量

    if(Fusion_En)
    {
        //Mes_Covariance
        if(once){
            for(i=0;i<9;i++){
                Mes_Covariance_1[i] = 0;
            }
            once--;
        }

        K2_Amplify_AccCov[0] = abs(Target_Angle.pitch - Fus_Angle.pitch);
        K2_Amplify_AccCov[1] = abs(Target_Angle.roll - Fus_Angle.roll);

        for(i=0;i<2;i++){
            // 当目标角和当前姿态角 的 残差较大时， 既 四轴即将做 机动动作 -> 放大ACC测量值的方差 -> 融合效果削弱： 仅仅为陀螺仪积分。
            if(K2_Amplify_AccCov[i]<K2_Amplify_Gate2){
                K2_Amplify_AccCov[i] = 4;

                if(K2_Amplify_AccCov[i]<K2_Amplify_Gate1){
                    K2_Amplify_AccCov[i] = 2;

                    if(K2_Amplify_AccCov[i]<K2_Amplify_Gate0){
                        K2_Amplify_AccCov[i] = 1;
                    }
                }
            }else{
                K2_Amplify_AccCov[i] = 8;
            }
        }

        Mes_Covariance_1[0] = 	mpu6050.acc_covariance_long_fliter.x * K_Amplify_AccCov * K2_Amplify_AccCov[1];
        Mes_Covariance_1[4] = 	mpu6050.acc_covariance_long_fliter.y * K_Amplify_AccCov * K2_Amplify_AccCov[0];
        Mes_Covariance_1[8] = 	mpu6050.acc_covariance_long_fliter.z * K_Amplify_AccCov * 2.5f;

        //Pre_Covariance
        if(once){
            for(i=0;i<16;i++){
                Pre_Covariance_1[i] = 0;
            }
            once = 0;
        }
        Pre_Covariance_1[0] = 	1.0f * K_Amplify_GyroCov;
        Pre_Covariance_1[5] = 	1.0f * K_Amplify_GyroCov;
        Pre_Covariance_1[10] = 	1.0f * K_Amplify_GyroCov;
        Pre_Covariance_1[15] = 	1.0f * K_Amplify_GyroCov;

        //Fusion//////
        //Gradient
        Gradient_ZAxyz[0] = Cb_Ideal_Acc1[0] + (Z_ACCxyz[0] - Cb_Ideal_Acc1[0])*0.125f;
        Gradient_ZAxyz[1] = Cb_Ideal_Acc1[1] + (Z_ACCxyz[1] - Cb_Ideal_Acc1[1])*0.125f;
        Gradient_ZAxyz[2] = Cb_Ideal_Acc1[2] + (Z_ACCxyz[2] - Cb_Ideal_Acc1[2])*0.125f;

#if ARITHMETIC_MPU6050_EXTENDEDKALMAN > 0u
        kalman_filter1.Kalman_Update(F_Jacobian, H_Jacobian1,
                                     Pre_Covariance_1, Mes_Covariance_1,
                                     Gradient_ZAxyz, Cb_Ideal_Acc1,
                                     X_Pre1, X_Fus1);
#endif

        QuaternionVector4_Norm(X_Fus1);
        X_Pre1[0] = X_Fus1[0];
        X_Pre1[1] = X_Fus1[1];
        X_Pre1[2] = X_Fus1[2];
        X_Pre1[3] = X_Fus1[3];

    }
}	


/***********************************************************************************************************************
* Function:   	void ARITHMETIC_MODEL::YawError_Correct_Process(double Imu_T)
*
* Scope:        public
*
* Description:  
*
* Arguments: 
* 
* Return: 
*
* Cpu_Time:     stm32f4 -- 3us(fpu)
*
* History:
* chenyingbing  2015.12.1   V1.6      creat
***********************************************************************************************************************/
void ARITHMETIC_MODEL::YawError_Correct_Process2(void)
{
#define	IMU_Kp_acc		1.0f
#define IMU_Kp_hmc 		5.0f

    static IPType EAxyz[3],EHxyz[3];

    Vector3CrossProduct(Z_ACCxyz,Cb_Ideal_Acc2,EAxyz);
    Vector3CrossProduct(Z_Hmcxyz,Cb_Ideal_Hmc2,EHxyz);

    Error_Ut[0] = IMU_Kp_acc*EAxyz[0] + 0*EHxyz[0];
    Error_Ut[1] = IMU_Kp_acc*EAxyz[1] + 0*EHxyz[1];
    Error_Ut[2] = 0*EAxyz[2] + IMU_Kp_hmc*EHxyz[2];

    X_Fus2[0] = X_Pre2[0];
    X_Fus2[1] = X_Pre2[1];
    X_Fus2[2] = X_Pre2[2];
    X_Fus2[3] = X_Pre2[3];
}



