#ifndef CHASSIS_H
#define CHASSIS_H

#include "robot_abstract.h"
#include "chassis_parameters.h"
#include "motor_top.h"
#include "tfdifferential.h"
#include "tfomni3.h"
#include "tfomni4.h"
#include "tfmecanum4.h"
#include "tfcarlike.h"

class Chassis
{
public:
    Chassis()
    {
        robot = NULL;
        para = NULL;
        motor_top =NULL;
        robot_tf = NULL;
        degree_to_radian = 0.017453f;
        radian_to_degree = 57.2958f;
        call_frequency = 20;
        memset(&speed_filter , 0 , sizeof(speed_filter));
    }

    void init(RobotAbstract* robot_ ,  MotorTop* motor_top_ )
    {
        robot = robot_;
        motor_top = motor_top_;
        setParameters( &robot_->para.chassis_para );
    }

    void call(void);

    void setParameters(ChassisParameters* para_)
    {
        para = para_;

        if(para_->type == DIFFERENTIAL2){
            differentia_model = TFDifferential(para_->wheel_radius , para_->body_radius , 2);
            robot_tf = &differentia_model;
        }
        else if(para_->type == DIFFERENTIAL4){
            differentia_model = TFDifferential(para_->wheel_radius , para_->body_radius , 4);
            robot_tf = &differentia_model;
        }
        else if(para_->type == OMNI3){
            omni3_model = TFOmni3(para_->wheel_radius , para_->body_radius);
            robot_tf = &omni3_model;
        }
        else if(para_->type == OMINI4){
            omin4_model = TFOmni4(para_->wheel_radius , para_->body_radius);
            robot_tf = &omni3_model;
        }
        else if(para_->type == MECANUM4){
            mecanum_model = TFMecanum(para_->wheel_radius , para_->body_radius);
            robot_tf = &mecanum_model;
        }
        else if(para_->type == CARLIKE){
            carlike_model = TFCarLike(para_->wheel_radius , para_->body_radius);
            robot_tf = &carlike_model;
        }
    }

    void updataGlobalSpeed(void)
    {
        control_quality += 30;   //robot->robot_parameters.control_signal_quality add 30
        robot_tf->globalSpeedSet( (float* )&robot->expect_global_speed , (float* )&robot->expect_motor_speed ,
                                  robot->measure_global_coordinate.z);
    }
    void updataRobotSpeed(void)
    {
        control_quality += 30;
        robot_tf->robotSpeedSet((float* )&robot->expect_robot_speed , (float* )&robot->expect_motor_speed);
    }
    void updataMotorSpeed(void){ return ;}

    void clearCoordData(void)
    {
        robot->measure_global_coordinate.x=0;
        robot->measure_global_coordinate.y=0;
        robot->measure_global_coordinate.z=0;
        robot->measure_robot_coordinate.x=0;
        robot->measure_robot_coordinate.y=0;
        robot->measure_robot_coordinate.z=0;
        motor_top->motor1.clear_past_total_angle();
        motor_top->motor2.clear_past_total_angle();
        motor_top->motor3.clear_past_total_angle();
        motor_top->motor4.clear_past_total_angle();
    }

private:
    void datatUpdate(void);
    RobotAbstract* robot;
    ChassisParameters* para;
    MotorTop* motor_top;
    float degree_to_radian ,  radian_to_degree;
    float call_frequency;
    float control_quality;
    float speed_filter[4];

private:
    TFRobot *robot_tf;
    TFDifferential differentia_model;
    TFOmni3 omni3_model;
    TFOmni4 omin4_model;
    TFMecanum mecanum_model;
    TFCarLike carlike_model;

};

#endif // CHASSIS_H
