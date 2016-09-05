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
* Description:  本文件定义了2轮差速底盘运动的坐标变换数学函数  即轮的速度 	机器人坐标  世界坐标
*               两两之间的变换公式
*               适用车型1： 后面两个动力轮，前面一个脚轮或者钢珠的车，例如turtlebot
*               适用车型2： 2轮平衡车
*               适用车型3： 4驱车实际上和2轮车一个模式

* !! 这种车型  速度只有前后和旋转，也就是X和Z   不能全向走
* !! 定义左边为电机1  右边为电机2
***********************************************************************************************************************/

#include "tf_2wd.h"

TF_2WD tf_2w;

/***********************************************************************************************************************
* Function:     void TF_3WD::robotToMotorTF(float* robot , float* motor , float robot_r)  
*
* Scope:        public
*
* Description:  机器人坐标到2个轮子的变换
*
* Arguments:
* Robot   为机器人坐标的速度向量XYZ   Y=0  
* Motor   为输出的两个电机的线速度v1  v2   
* robot_r 机器人的半径  
* Return:
*
* Cpu_Time:  
*
* History:
* by   mawenke   2015.10.1   creat
***********************************************************************************************************************/
void TF_2WD::robotToMotorTF(const float* robot , float* motor , float robot_r)   
{
    *motor = -1 * (*robot) + 0 * (*(robot+1)) + robot_r * (*(robot+2)) ;
    *(motor + 1) =  1 * (*robot) + 0 * (*(robot+1)) + robot_r * (*(robot+2)) ;
}


/***********************************************************************************************************************
* Function:     void TF_3WD::MotorToRobotTF(float* motor , float* global , float robot_r)  
*
* Scope:        public
*
* Description:  三个轮子到机器人坐标的变换
*
* Arguments:
* Motor   为输出的三个电机的线速度v1 v2   
* Robot   为机器人坐标的速度向量XYZ   Y=0 
* robot_r 机器人的半径
* Return:
*
* Cpu_Time:  stm32F1 20us   stm32F4+FPU 0~2us
*
* History:
* by   mawenke   2015.10.1   creat
***********************************************************************************************************************/
void TF_2WD::motorToRobotTF(const float* motor , float* robot , float robot_r)
{
    *robot = -0.5f * (*motor) + 0.5f* (*(motor+1));
    *(robot + 1) =  0 * (*motor)  + 0 * (*(motor+1));
    *(robot + 2) =  ( 0.5f/ (float)robot_r ) * ( (*motor) + (*(motor+1)) );
}



/***********************************************************************************************************************
* Function:     void TF_2WD::globalToRobotTF( float* global , float* robot , float R_theta)    
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
void TF_2WD::globalToRobotTF(const float* global , float* robot , float R_theta)   
{
    *robot =  (float)( cos(R_theta) * (*global) + sin(R_theta) * (*(global+1)) + 0 * (*(global+2)) );
    *(robot + 1) = (float)( -sin(R_theta) * (*global) + cos(R_theta) * (*(global+1)) + 0 * (*(global+2)) );
    *(robot + 2) =   0 * (*global) + 0 * (*(global+1)) + 1 * (*(global+2)) ;
}


/***********************************************************************************************************************
* Function:     void TF_2WD::robotToGlobalTF(float* robot , float* global ,float R_theta)  
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
void TF_2WD::robotToGlobalTF(const float* robot , float* global ,float R_theta)   
{
    *global = cos(R_theta)*(*robot) - sin(R_theta) * (*(robot+1)) +  0 * (*(robot+2)) ;
    *(global + 1) =  sin(R_theta) * (*robot) + cos(R_theta) * (*(robot+1))  + 0 * (*(robot+2)) ;
    *(global + 2) =  0 * (*robot) + 0 * (*(robot+1)) + 1 * (*(robot+2)) ;
}



void TF_2WD::globalToMotorTF(const float* global , float* motor ,float R_theta ,float robot_r)   
{


}


void TF_2WD::motorToGlobalTF(const float* motor , float* global ,float R_theta ,float robot_r)   
{
    *global = (-cos(R_theta)/2)*(*motor) + (cos(R_theta)/2)*(*(motor+1)) ;
    *(global + 1) =  (-sin(R_theta)/2) * (*motor) +  (sin(R_theta)/2) * (*(motor+1)) ;
    *(global + 2) =  (0.5f/robot_r) * (*motor) + (0.5f/robot_r) * (*(motor+1)) ;
}



/***********************************************************************************************************************
***                                                                                                                  ***
***                                          Code of External Interface                                              ***
***                                                                                                                  ***
***********************************************************************************************************************/

//unit  distances : metres
//angle： radian
//2WD 无法走全局速度
void TF_2WD::globalSpeedSet(const float* expect_global_speed , float* expect_motor_speed , 
                            float global_coordinat_z)
{


}

void TF_2WD::robotSpeedSet(const float* expect_robot_speed , float* expect_motor_speed)  
{
    float Motor_Line_Speed[3] ;
    robotToMotorTF(expect_robot_speed , Motor_Line_Speed , robot_body_radius_) ;
    *expect_motor_speed  = ( Motor_Line_Speed[0] / robot_wheel_radius_ );
    *(expect_motor_speed+1)  = ( Motor_Line_Speed[1] / robot_wheel_radius_ );
}

void TF_2WD::getGlobalCoordinate(const float* d_motor_len_filter , float* measure_global_coordinate)  
{
    float D_Global_Coordinate[3] ;
    motorToGlobalTF(d_motor_len_filter , D_Global_Coordinate , *(measure_global_coordinate+2) , robot_body_radius_);
    *measure_global_coordinate += D_Global_Coordinate[0];
    *(measure_global_coordinate+1) += D_Global_Coordinate[1];
    *(measure_global_coordinate+2) += D_Global_Coordinate[2];
}	

void TF_2WD::getRobotCoordinate(const float* d_motor_len_filter , float* measure_robot_coordinate)  
{
    float D_Robot_Coordinate[3] ;
    motorToRobotTF( d_motor_len_filter , D_Robot_Coordinate , robot_body_radius_) ;
    *measure_robot_coordinate += D_Robot_Coordinate[0];
    *(measure_robot_coordinate+1) += D_Robot_Coordinate[1];
    *(measure_robot_coordinate+2) += D_Robot_Coordinate[2];
}	

void TF_2WD::getRobotSpeed(const float* measure_motor_speed , float* measure_robot_speed)
{
    float measure_motor_line_speed[3];
    measure_motor_line_speed[0]=*measure_motor_speed * robot_wheel_radius_;
    measure_motor_line_speed[1]=*(measure_motor_speed+1) * robot_wheel_radius_;
    motorToRobotTF(measure_motor_line_speed , measure_robot_speed , robot_body_radius_) ;
}

void TF_2WD::getGlobalSpeed(const float* measure_motor_speed , float* measure_global_speed ,float global_coordinat_z )
{
    float measure_motor_line_speed[3];
    measure_motor_line_speed[0]=*measure_motor_speed * robot_wheel_radius_;
    measure_motor_line_speed[1]=*(measure_motor_speed+1) * robot_wheel_radius_;
    motorToGlobalTF(measure_motor_line_speed , measure_global_speed , global_coordinat_z , robot_body_radius_);
}
