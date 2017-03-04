#ifndef TFROBOT_H
#define TFROBOT_H

#include "math.h"

class TFRobot
{
public:
    TFRobot(float wheel_radius_ = 0 , float body_radius_ = 0 ,unsigned char num_ = 0)
    {
        wheel_radius = wheel_radius_;
        body_radius = body_radius_;
        motor_num = num_;
        PI_ = 3.141592653f;
    }

    void set_robot_wheel_radius(float wheel_r){wheel_radius = wheel_r;}
    void set_robot_body_radius(float body_r){body_radius = body_r;}
    float get_robot_wheel_radius(void) const {return wheel_radius;}
    float get_robot_body_radius(void) const {return body_radius ;}

    //expect_global_speed : x , y , z   unit  distances : metres
    //angle： radian
    void globalSpeedSet(const float* expect_global_speed , float* expect_motor_angle_speed ,
                        float global_coordinat_z)
    {
        float Motor_Line_Speed[6] ;
        globalToMotorTF( expect_global_speed , Motor_Line_Speed , global_coordinat_z );
        for (unsigned char i = 0  ; i < motor_num ; i++)
        {
            *(expect_motor_angle_speed + i)  = ( Motor_Line_Speed[i] / wheel_radius );
        }
    }

    void robotSpeedSet(const float* expect_robot_speed , float* expect_motor_angle_speed)
    {
        float Motor_Line_Speed[6] ;
        robotToMotorTF(expect_robot_speed , Motor_Line_Speed) ;
        for (unsigned char i = 0  ; i < motor_num ; i++)
        {
            *(expect_motor_angle_speed + i)  = ( Motor_Line_Speed[i] / wheel_radius );
        }
    }

    //measure_global_coordinate: x , y , z
    void getGlobalCoordinate(const float* d_motor_len  , float* measure_global_coordinate)
    {
        float D_Global_Coordinate[3] ;
        motorToGlobalTF(d_motor_len  , D_Global_Coordinate , *(measure_global_coordinate+2));
        *measure_global_coordinate += D_Global_Coordinate[0];
        *(measure_global_coordinate+1) += D_Global_Coordinate[1];
        *(measure_global_coordinate+2) += D_Global_Coordinate[2];
    }

    void getRobotCoordinate(const float* d_motor_len  , float* measure_robot_coordinate)
    {
        float D_Robot_Coordinate[3] ;
        motorToRobotTF(d_motor_len , D_Robot_Coordinate) ;
        *measure_robot_coordinate += D_Robot_Coordinate[0];
        *(measure_robot_coordinate+1) += D_Robot_Coordinate[1];
        *(measure_robot_coordinate+2) += D_Robot_Coordinate[2];
    }

    void getRobotSpeed(const float* measure_motor_angle_speed , float* measure_robot_speed)
    {
        float measure_motor_line_speed[6];
        for (unsigned char i = 0 ; i < motor_num ; i++  )
        {
            *(measure_motor_line_speed + i)  = *(measure_motor_angle_speed + i) * wheel_radius;
        }
        motorToRobotTF(measure_motor_line_speed , measure_robot_speed ) ;
    }

    void getGlobalSpeed(const float* measure_motor_angle_speed , float* measure_global_speed , float global_coordinat_z)
    {
        float measure_motor_line_speed[6];
        for (unsigned char i = 0 ; i < motor_num ; i++  )
        {
            *(measure_motor_line_speed + i)  = *(measure_motor_angle_speed + i) * wheel_radius;
        }
        motorToGlobalTF(measure_motor_line_speed , measure_global_speed , global_coordinat_z );
    }

public:
    unsigned char motor_num;
    float wheel_radius;
    float body_radius;
     float PI_;

private:
    /***********************************************************************************************************************
    * Function:     robotToMotorTF(const float* robot , float* motor )
    *
    * Scope:
    *
    * Description:  机器人坐标到2个轮子的变换
    *
    * Arguments:
    * Robot   为机器人坐标的速度向量XYZ
    * Motor   为输出的两个电机的线速度v1  v2 ... vn
    *
    * Return:
    *
    * Cpu_Time:
    *
    * History:
    * by   mawenke   2015.10.1   creat
    ***********************************************************************************************************************/
    virtual void robotToMotorTF(const float* robot , float* motor ) = 0;

    /***********************************************************************************************************************
    * Function:     void MotorToRobotTF(const float* motor , float* global)
    *
    * Scope:        public
    *
    * Description:  三个轮子到机器人坐标的变换
    *
    * Arguments:
    * Motor   为输出的三个电机的线速度v1  v2 ... vn
    * Robot   为机器人坐标的速度向量XYZ
    *
    * Return:
    *
    * Cpu_Time:  stm32F1 20~30us   stm32F4+FPU 0~3us
    *
    * History:
    * by   mawenke   2015.10.1   creat
    ***********************************************************************************************************************/
    virtual void motorToRobotTF(const float* motor , float* robot) = 0;

    /***********************************************************************************************************************
    * Function:     void globalToRobotTF(const float* global , float* robot , float R_theta)
    *
    * Scope:
    *
    * Description:  世界坐标到机器人坐标的变换
    *
    * Arguments:
    * Global为Global坐标的速度向量xyw
    * Robot为Robot坐标的速度向量xyw
    * R_theta 为机器人当前方向  即坐标值的Z
    *
    * Return:
    *
    * Cpu_Time:
    *
    * History:
    * by   mawenke   2015.10.1   creat
    ***********************************************************************************************************************/
    virtual void globalToRobotTF(const float* global , float* robot , float R_theta) = 0;

    /***********************************************************************************************************************
    * Function:     void robotToGlobalTF(const float* robot , float* global ,float R_theta)
    *
    * Scope:
    *
    * Description:  机器人坐标到世界坐标的变换
    *
    * Arguments:
    * Global为Global坐标的速度向量xyw
    * Robot为Robot坐标的速度向量xyw
    * R_theta 为机器人当前方向  即坐标值的Z
    *
    * Return:
    *
    * Cpu_Time:
    *
    * History:
    * by   mawenke   2015.10.1   creat
    ***********************************************************************************************************************/
    virtual void robotToGlobalTF(const float* robot , float* global ,float R_theta) = 0;

    /***********************************************************************************************************************
    * Function:     void robotToGlobalTF(const float* robot , float* global ,float R_theta)
    *
    * Scope:        public
    *
    * Description:  世界坐标到三个轮子的变换
    *
    * Arguments:
    * Global为Global坐标的速度向量xyw
    * Robot为Robot坐标的速度向量xyw
    * R_theta 为机器人当前方向  即坐标值的Z
    *
    * Return:
    *
    * Cpu_Time:
    *
    * History:
    * by   mawenke   2015.10.1   creat
    ***********************************************************************************************************************/
    virtual void globalToMotorTF(const float* global , float* motor ,float R_theta)  = 0;

    /***********************************************************************************************************************
    * Function:     void robotToGlobalTF(const float* robot , float* global ,float R_theta)
    *
    * Scope:        public
    *
    * Description:  三个轮子线速度或者线里程微分到世界坐标的变换
                                    函数  void motorToGlobalTF(float* motor , float* global ,float R_theta)
                                    三个万向轮式的机器人坐标到全局坐标的转化

                                    输入 机器人坐标的三个变量    全局坐标的三个变量的保存地址   机器人的和全局坐标的夹角
                                    Gvx Gvy Gvz  v1 v2 ...vn
                                    Global 为全局坐标的速度x ，y ，z
                                    *motor  为三个电机的速度 v1 ， v2 ...vn

                                    或者

     Global 为全局坐标的微分  dx ，dy ，dz
     *motor 为三个电机的里程微分 d s1 ， d s2 ... d sn
    *
    * Arguments:
    * Global为Global坐标的速度向量xyz
    * Robot为Robot坐标的速度向量xyz
    * R_theta 为机器人当前方向  即坐标值的Z
    *
    * Return:
    *
    * Cpu_Time:  stm32F1 300~400us   stm32F4+NOFPU 64~80us    stm32F4+FPU 8~16us
    *
    * History:
    * by   mawenke   2015.10.1   creat
    ***********************************************************************************************************************/
    virtual void motorToGlobalTF(const float* motor , float* global ,float R_theta)  =0;
};

#endif // TFROBOT_H
