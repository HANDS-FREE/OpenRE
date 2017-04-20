#ifndef __imu_top_arithmetic_model_H__
#define __imu_top_arithmetic_model_H__

#include "imu_config.h"
#include "imu_top.h"


class ARITHMETIC_MODEL
{	

public:
    ARITHMETIC_MODEL(void);

    // 用户接口 /////////////////////////////////////////////////////////////////////////////////////////////////////////

    // 状态变量
    unsigned char Fusion_State;												//当前设备是否正常，融合是否正常
    unsigned char Imu_Top_fusion_HavingInitial;								//是否初始化角度
    FUSION_IPType_PRY_DGREE 	Initial_Angle_dgree;						//初始的姿态角 _dgree代表单位为°

    // 输入变量
    unsigned char Fusion_En;												//使能 融合算法 : 建议 在四轴稳定的时候使能 动态机动的时候禁止
    FUSION_IPType_PRY_DGREE		Target_Angle;								//目标姿态角

    // 输出变量
    FUSION_IPType_PRY_DGREE		ControlVector_Position;						//姿态角 位置环 误差控制向量
    FUSION_IPType_PRY_DGREE		ControlVector_Velocity;						//姿态角 速度环 误差控制向量

    IMU_QUATERNION Fus_Quaternion;											//融合的四元数
    FUSION_IPType_PRY_DGREE		Fus_Angle;									//融合的姿态角
    FUSION_IPType_PRY_DGREE 	AccHmcMes_Angle_dgree;						//测量的姿态角

    // 功能函数 接口
    void GetAccHmc_MesAngle_dgree(unsigned char mode);						//获得测量的角度 	AccHmcMes_Angle_dgree

    void Set_ModelInitial(void);											//初始化

    void ModelCommanState_Update(void);										//通用章公共变量更新

    void XState1_Predict(IPType Imu_T);									//X_Pre1预测更新
    void XState2_Predict(IPType Imu_T);									//X_Pre2预测更新

    // 过程1 EXTEND KALMAN : ACC | PITCH ROLL
    void ExtendedKalman_State_Update1(void);							//扩展卡尔曼 状态变量更新
    void XState_KalmanFusionCall_Process1(void);						//基于扩展卡尔曼滤波的pitch roll修正

    // 过程2 针对YAW的误差陀螺仪数据修正：HMC | YAW
    void YawError_Correct_State_Update2(void);							//叉积误差修正 状态变量更新
    void YawError_Correct_Process2(void);								//基于叉积的误差yaw修正

    void UpdateState_to_PortVariable(void);									//将 状态变量 更新到 用户接口 变量

private:
    // 通用 章 *********************************************************************************************************
    // 数学模型 抽象 变量 //////////////////////////////////////////////////////////////////////////////////////////////

    // 公共变量
    IPType										Z_ACCxyz[3];				//观测变量Z(t)：ACC部分
    IPType										Z_Hmcxyz[3];				//观测变量Z(t)：Hmc部分
    IPType 										Ut[3];						//控制变量U(t)的值

    IPType										Cn_Gravity[3];				//参考坐标系 重力向量
    IPType										Cn_Orin_Hmcxyz[3];			//参考坐标系 既参考坐标系的 Hmc数据


    // 过程变量
    IPType 										Cb_Ideal_Acc1[3];			//由重力向量 通过Cn_to_Cb映射的当前姿态对应的 ACCxyz
    IPType 										Cb_Ideal_Acc2[3];

    IPType										Cb_Ideal_Hmc1[3];			//由指北磁向量 通过Cn_to_Cb映射的当前姿态对应的 Hmcxyz
    IPType 										Cb_Ideal_Hmc2[3];

    // 融合变量
    IPType 										X_Fus1[4];					//状态变量X(t)的融合值
    IPType 										X_Fus2[4];

    IPType 										X_Pre1[4];					//状态变量X(t)的预测值
    IPType 										X_Pre2[4];

    // ACC > 卡尔曼滤波 > Pitch Roll 章 ********************************************************************************
    // 数学模型 抽象 变量 //////////////////////////////////////////////////////////////////////////////////////////////
    /* 离散扩展卡尔曼公式
         *	 ^
         *1:X(t) = F(X(t),U(t)) + W(t), W(t) ~ N(0,Pre_Quaternion(t))
         *2:Z(t) = H(X(t)) 			+ V(t), V(t) ~ N(0,Mes_Covariance(t))
         *
         *其中：
         * X(t) = [q0,q1,q2,q3] > 四元数
         * U(t) = [gx,gy,gz]		> 陀螺仪
         * F > 非线性函数矩阵
         * H > 非线性函数矩阵
        */
    // 状态变量 ：
    IPType											F_Jacobian[16];			//F对X求偏导的雅克比矩阵 4×4
    IPType 											H_Jacobian1[12];		//H对X求偏导的雅克比矩阵 3×4

    IPType 											H_Jacobian2[12];		//H对X求偏导的雅克比矩阵 3×4


    // 过程变量 ：融合过程处理变量
    IPType											Pre_Covariance_1[16];	//预测过程协方差 				 4×4
    //IPType											Pre_Covariance_2[16];
    IPType											Mes_Covariance_1[9];	//测量过程协方差				 3×3
    //IPType											Mes_Covariance_2[9];

    // HMC > 向量叉值误差纠正 > Yaw 章 *********************************************************************************
    // 数学模型 抽象 变量 //////////////////////////////////////////////////////////////////////////////////////////////

    // 状态变量 ：

    // 过程变量 ：
    IPType 											Error_Ut[3];			//误差陀螺仪数据

    // 基本计算函数 ////////////////////////////////////////////////////////////////////////////////////////////////////
    // 向量,四元数类
    IPType M_Smart_sqrt(IPType number);										//自定义的一个开方函数

    void Vector3_Norm(IPType *vector_norm);									//单位化向量

    void Vector3CrossProduct(IPType *v_l, IPType *v_r, IPType *v_return);	//3维向量叉积
    IPType Vector3DotProduct(IPType *v_l, IPType *v_r);						//3维向量点积


    IMU_QUATERNION Quaternion_Norm(IMU_QUATERNION q_in);					//单位化四元数
    void QuaternionVector4_Norm(IPType *vector_norm);

    FUSION_IPType_PRY_DGREE Quaternion_to_PRY_dgree(IMU_QUATERNION qq);		// 四元数 > 欧拉角(°)
    void QuaternionVector4_to_PRY_dgree(IPType *qq, IPType *qq_anlge);

    IMU_QUATERNION PRY_dgree_to_Quaternion(FUSION_IPType_PRY_DGREE qq_angle); 	// 欧拉角(°) > 四元数
    void PRY_dgree_Vector3_to_Quaternion(IPType *qq_angle, IPType *qq);

    IMU_QUATERNION Quaternion_SimpleAdd(char fx,IMU_QUATERNION q_left, IMU_QUATERNION q_right);		//四元数数值向量加法
    IMU_QUATERNION Quaternion_Kgain_q(IPType Kgain, IMU_QUATERNION q_in);							//四元数系数乘
    void QuaternionVector4_SimpleAdd(char fx,IPType *q_left, IPType *q_right, IPType *q_result);
    void QuaternionVector4_Kgain_SimpleAdd(char fx, IPType *q_left, IPType Kgain1, IPType *q_right, IPType Kgain2, IPType *q_result);	//四元数系数乘加

    IPType Quaternion_DotMutiply(IMU_QUATERNION q_left, IMU_QUATERNION q_right);									//四元数点乘
    IPType QuaternionVector4_DotMutiply(IPType *q_left, IPType *q_right);

    IMU_QUATERNION Quaternion_CrossMutiply(IMU_QUATERNION q_left, IMU_QUATERNION q_right);				//四元数叉乘
    void QuaternionVector4_CrossMutiply(IPType *q_left, IPType *q_right, IPType *q_result);

    IMU_QUATERNION Quaternion_Rotate(char fx, IMU_QUATERNION q_orin, IMU_QUATERNION q_turn);			//四元数旋转计算
    void QuaternionVector4_Rotate(char fx, IPType *q_orin, IPType *q_turn, IPType *q_result);

    IMU_QUATERNION Quaternion_GlobalInterpolation(IPType t, IPType Theta_dgree, IMU_QUATERNION q_orin, IMU_QUATERNION q_target);	//四元数球形插值
    void QuaternionVector4_GlobalInterpolation(IPType t, IPType Theta_dgree, IPType *q_orin, IPType *q_target, IPType *q_result);

    IMU_QUATERNION Quaternion_Differential(IMU_QUATERNION qq, FLOAT_XYZ Gyro);								//四元数微分方程
    void Quaternion_Differential_Matrix(IPType *qq, IPType *Gyro, IPType *dq);

    // 坐标系类
    FLOAT_XYZ	Cb_to_Cn_XYZ(IMU_QUATERNION qq, FLOAT_XYZ Cb_XYZDta);								//载体坐标系>参考坐标系　XYZ轴数据
    void Cb_to_Cn_XYZ_Matrix(IPType *qq, IPType *Cb_XYZDta, IPType *Cn_XYZDta_Return);		//同上，IPType*形式输入

    FLOAT_XYZ	Cn_to_Cb_XYZ(IMU_QUATERNION qq, FLOAT_XYZ Cn_XYZDta);								//参考坐标系>载体坐标系　XYZ轴数据
    void Cn_to_Cb_XYZ_Matrix(IPType *qq, IPType *Cn_XYZDta, IPType *Cb_XYZDta_Return);						//同上，IPType*形式输入

    // 过程算法函数 ////////////////////////////////////////////////////////////////////////////////////////////////////
    // 四元数微分方程的积分算法
    void XStateUpdate_by_ImplicitEuler(IPType Imu_T, IPType *XUpdate, IPType *InForce);						//隐性欧拉法 积分

};

extern ARITHMETIC_MODEL imu_arithmetic_model;

#endif // __imu_top_fusion_arithmetic_H__

