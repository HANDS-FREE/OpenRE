/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: tf_3wd.cpp
* Contact:  QQ Exchange Group -- 521037187
* Version:  V2.0
*
* LICENSING TERMS:
* The Hands Free is licensed generally under a permissive 3-clause BSD license. 
* Contributions are requiredto be made under the same license.
*
* History:
* <author>      <time>      <version>      <desc>
* mawenke      2015.10.1    V1.0          creat this file
*
* Description:  本文件定义了三轮式 万向轮机器人 底盘运动的坐标变换数学函数  即三个轮的速度 	机器人坐标  世界坐标
*               两两之间的变换公式   该文件在LIB_Robot_3WD package里面  依赖 LIB_Motor_Contorl package
***********************************************************************************************************************/

#include "tf_3wd.h"

#define  PI_   3.141592653f

TF_3WD tf_3wd;

/***********************************************************************************************************************
* Function:     void TF_3WD::robotToMotorTF(float* robot , float* motor , float robot_r)  
*
* Scope:        public
*
* Description:  机器人坐标到三个轮子的变换
*
* Arguments:
* Motor   为输出的三个电机的线速度v1 v2 v3  
* Robot   为机器人坐标的速度向量xyw 
* robot_r 机器人的半径  
* Return:
*
* Cpu_Time:  
*
* History:
* by   mawenke   2015.10.1   creat
***********************************************************************************************************************/

void TF_3WD::robotToMotorTF(const float* robot , float* motor , float robot_r)   
{
    *motor = 0 * (*robot) + 1 * (*(robot+1)) + robot_r * (*(robot+2)) ;
    *(motor + 1) =  -0.866025f * (*robot) - 0.5f * (*(robot+1)) + robot_r * (*(robot+2)) ;
    *(motor + 2) =  0.866025f * (*robot) - 0.5f * (*(robot+1)) + robot_r * (*(robot+2)) ;
}

/***********************************************************************************************************************
* Function:     void TF_3WD::MotorToRobotTF(float* motor , float* global , float robot_r)  
*
* Scope:        public
*
* Description:  三个轮子到机器人坐标的变换
*
* Arguments:
* Motor   为输入的三个电机的线速度v1 v2 v3
* Robot   为机器人坐标的速度向量xyw 
* robot_r 机器人的半径
* Return:
*
* Cpu_Time:  stm32F1 20us   stm32F4+FPU 0~2us
*
* History:
* by   mawenke   2015.10.1   creat
***********************************************************************************************************************/
void TF_3WD::motorToRobotTF(const float* motor , float* robot , float robot_r)
{
    *robot = 0 * (*motor) + -0.57735f * (*(motor+1)) + 0.57735f * (*(motor+2)) ;
    *(robot + 1) =  0.666667f* (*motor)  -0.333333f * (*(motor+1)) + -0.333333f * (*(motor+2)) ;
    *(robot + 2) =  ( 0.333333f/ (float)robot_r ) * ( (*motor) + (*(motor+1)) +  (*(motor+2)) ) ;
}


/***********************************************************************************************************************
* Function:     void TF_3WD::globalToRobotTF( float* global , float* robot , float R_theta) 
*
* Scope:        public
*
* Description:  世界坐标到机器人坐标的变换
*
* Arguments:
* Global为Global坐标的速度向量xyw
* Robot为Robot坐标的速度向量xyw 
* R_theta 为机器人当前方向  即坐标值的Z
* Return:
*
* Cpu_Time:  
*
* History:
* by   mawenke   2015.10.1   creat
***********************************************************************************************************************/
void TF_3WD::globalToRobotTF(const float* global , float* robot , float R_theta)   
{
    *robot =  (float)( cos(R_theta) * (*global) + sin(R_theta) * (*(global+1)) + 0 * (*(global+2)) );
    *(robot + 1) = (float)( -sin(R_theta) * (*global) + cos(R_theta) * (*(global+1)) + 0 * (*(global+2)) );
    *(robot + 2) =   0 * (*global) + 0 * (*(global+1)) + 1 * (*(global+2)) ;
}


/***********************************************************************************************************************
* Function:     void TF_3WD::robotToGlobalTF(float* robot , float* global ,float R_theta) 
*
* Scope:        public
*
* Description:  机器人坐标到世界坐标的变换
*
* Arguments:
* Global为Global坐标的速度向量xyw
* Robot为Robot坐标的速度向量xyw 
* R_theta 为机器人当前方向  即坐标值的Z
* Return:
*
* Cpu_Time:  
*
* History:
* by   mawenke   2015.10.1   creat
***********************************************************************************************************************/
void TF_3WD::robotToGlobalTF(const float* robot , float* global ,float R_theta)   
{
    *global = cos(R_theta)*(*robot) - sin(R_theta) * (*(robot+1)) +  0 * (*(robot+2)) ;
    *(global + 1) =  sin(R_theta) * (*robot) + cos(R_theta) * (*(robot+1)) + 0 * (*(robot+2)) ;
    *(global + 2) =  0 * (*robot) + 0 * (*(robot+1)) + 1 * (*(robot+2)) ;
}


/***********************************************************************************************************************
* Function:     void TF_3WD::robotToGlobalTF(float* robot , float* global ,float R_theta)  
*
* Scope:        public
*
* Description:  世界坐标到三个轮子的变换
*
* Arguments:
* Global为Global坐标的速度向量xyw
* Robot为Robot坐标的速度向量xyw 
* R_theta 为机器人当前方向  即坐标值的Z
* robot_r机器人的半径
* Return:
*
* Cpu_Time:  
*
* History:
* by   mawenke   2015.10.1   creat
***********************************************************************************************************************/
void TF_3WD::globalToMotorTF(const float* global , float* motor ,float R_theta ,float robot_r)   
{
    *motor =  -sin(R_theta) * (*global) + cos(R_theta) * (*(global+1)) + robot_r * (*(global+2)) ;
    *(motor + 1) =  -sin(PI_/3 - R_theta) * (*global) - cos(PI_/3 - R_theta) * (*(global+1)) + robot_r * (*(global+2)) ;
    *(motor + 2) =  sin(PI_/3 + R_theta) * (*global) - cos(PI_/3 + R_theta) * (*(global+1)) + robot_r * (*(global+2)) ;
}

/***********************************************************************************************************************
* Function:     void TF_3WD::robotToGlobalTF(float* robot , float* global ,float R_theta)  
*
* Scope:        public
*
* Description:  三个轮子线速度或者线里程微分到世界坐标的变换 
                                函数  void motorToGlobalTF(float* motor , float* global ,float R_theta)
                                三个万向轮式的机器人坐标到全局坐标的转化

                                输入 机器人坐标的三个变量    全局坐标的三个变量的保存地址   机器人的和全局坐标的夹角
                                Gvx Gvy Gvz  v1 v2 v3
                                Global 为全局坐标的速度x ，y ，z
                                *motor  为三个电机的速度 v1 ， v2 ，v3

                                或者

 Global 为全局坐标的微分  dx ，dy ，dz
 *motor 为三个电机的里程微分 d s1 ， d s2 ，d s3
*
* Arguments:
* Global为Global坐标的速度向量xyw
* Robot为Robot坐标的速度向量xyw 
* R_theta 为机器人当前方向  即坐标值的Z
* robot_r机器人的半径
* Return:
*
* Cpu_Time:  stm32F1 330us   stm32F4+NOFPU 64~80us    stm32F4+FPU 8~16us
*
* History:
* by   mawenke   2015.10.1   creat
***********************************************************************************************************************/
void TF_3WD::motorToGlobalTF(const float* motor , float* global ,float R_theta ,float robot_r)   
{
    *global = -0.666667f * sin(R_theta)*(*motor) + (-0.577350f*cos(R_theta) + 0.333333f*sin(R_theta))*(*(motor+1)) + (0.577350f*cos(R_theta) + 0.333333f*sin(R_theta))*(*(motor+2)) ;
    *(global + 1) =  0.666667f * cos(R_theta)*(*motor) + (-0.577350f*sin(R_theta) - 0.333333f*cos(R_theta))*(*(motor+1)) + (0.577350f*sin(R_theta) - 0.333333f*cos(R_theta))*(*(motor+2)) ;
    *(global + 2) =  ( 1 / (float)(3*robot_r) ) * ( (*motor) + (*(motor+1)) +(*(motor+2)) ) ;
}


/***********************************************************************************************************************
***                                                                                                                  ***
***                                          Code of External Interface                                              ***
***                                                                                                                  ***
***********************************************************************************************************************/

//unit  distances : metres
//angle： radian
void TF_3WD::globalSpeedSet(const float* expect_global_speed , float* expect_motor_speed , 
                            float global_coordinat_z)
{
    float Motor_Line_Speed[3] ;
    globalToMotorTF( expect_global_speed , Motor_Line_Speed , global_coordinat_z , robot_body_radius_);
    *expect_motor_speed  = ( Motor_Line_Speed[0] / robot_wheel_radius_ );
    *(expect_motor_speed+1)  = ( Motor_Line_Speed[1] / robot_wheel_radius_ );
    *(expect_motor_speed+2)  = ( Motor_Line_Speed[2] / robot_wheel_radius_ );
}

void TF_3WD::robotSpeedSet(const float* expect_robot_speed , float* expect_motor_speed)  
{
    float Motor_Line_Speed[3] ;
    robotToMotorTF(expect_robot_speed , Motor_Line_Speed , robot_body_radius_) ;
    *expect_motor_speed  = ( Motor_Line_Speed[0] / robot_wheel_radius_ );
    *(expect_motor_speed+1)  = ( Motor_Line_Speed[1] / robot_wheel_radius_ );
    *(expect_motor_speed+2)  = ( Motor_Line_Speed[2] / robot_wheel_radius_ );
}


void TF_3WD::getGlobalCoordinate(const float* d_motor_len_filter , float* measure_global_coordinate)  
{
    float D_Global_Coordinate[3] ;
    motorToGlobalTF(d_motor_len_filter , D_Global_Coordinate , *(measure_global_coordinate+2) , robot_body_radius_);
    *measure_global_coordinate += D_Global_Coordinate[0];
    *(measure_global_coordinate+1) += D_Global_Coordinate[1];
    *(measure_global_coordinate+2) += D_Global_Coordinate[2];
}	

void TF_3WD::getRobotCoordinate(const float* d_motor_len_filter , float* measure_robot_coordinate)  
{
    float D_Robot_Coordinate[3] ;
    motorToRobotTF( d_motor_len_filter , D_Robot_Coordinate , robot_body_radius_) ;
    *measure_robot_coordinate += D_Robot_Coordinate[0];
    *(measure_robot_coordinate+1) += D_Robot_Coordinate[1];
    *(measure_robot_coordinate+2) += D_Robot_Coordinate[2];
}	

void TF_3WD::getRobotSpeed(const float* measure_motor_speed , float* measure_robot_speed)
{
    float measure_motor_line_speed[3];
    measure_motor_line_speed[0]=*measure_motor_speed * robot_wheel_radius_;
    measure_motor_line_speed[1]=*(measure_motor_speed+1) * robot_wheel_radius_;
    measure_motor_line_speed[2]=*(measure_motor_speed+2) * robot_wheel_radius_;
    motorToRobotTF(measure_motor_line_speed , measure_robot_speed , robot_body_radius_) ;
}

void TF_3WD::getGlobalSpeed(const float* measure_motor_speed , float* measure_global_speed ,float global_coordinat_z )
{
    float measure_motor_line_speed[3];
    measure_motor_line_speed[0]=*measure_motor_speed * robot_wheel_radius_;
    measure_motor_line_speed[1]=*(measure_motor_speed+1) * robot_wheel_radius_;
    measure_motor_line_speed[2]=*(measure_motor_speed+2) * robot_wheel_radius_;
    motorToGlobalTF(measure_motor_line_speed , measure_global_speed , global_coordinat_z , robot_body_radius_);
}
