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

    void init(RobotAbstract *robot_ , MotorTop *motor_top_)
    {
        robot = robot_;
        system_info = &robot->chassis.system_info;
        motor_top = motor_top_;
        setParameters(&robot_->para.chassis_para);
    }
    void loopCall(void); //20HZ

    void setParameters(ChassisParameters *para_);
    void updataGlobalSpeed(void);
    void updataRobotSpeed(void);
    void updataMotorSpeed(void);

    void setMotorMode(unsigned char mode_)
    {
        if(motor_top == NULL) return;
        motor_top->setMode(mode_);
    }

    void clearCoordData(void);
    void chassisTest(void);
    void printInfo(unsigned char type_);

private:
    void datatUpdate(void); //20HZ
    void safetyDetection(void); //20HZ
    RobotAbstract *robot;
    ChassisSystem *system_info;
    ChassisParameters *para;
    MotorTop *motor_top;
    float degree_to_radian , radian_to_degree;
    float call_frequency;
    float speed_filter[4];
private:
    TFRobot *robot_tf;
    TFDifferential differentia_model;
    TFOmni3 omni3_model;
    TFOmni4 omni4_model;
    TFMecanum mecanum_model;
    TFCarLike carlike_model;
};

#endif // CHASSIS_H
