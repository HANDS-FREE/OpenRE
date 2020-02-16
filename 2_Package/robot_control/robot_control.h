#ifndef ROBOT_TOP_H
#define ROBOT_TOP_H

//#include "imu_top.h"
#include "robot_abstract.h"
#include "chassis.h"
#include "head.h"
#include "arm.h"
#include "sbus_ppm.h"
#include "robolink.h"

class RobotControl
{
private:
    RobotControl()
    {
        robot =NULL;
        sbus_node = NULL;
        robolink_node = NULL;
        degree_to_radian = 0.017453f;
        radian_to_degree = 57.2958f;
        call_frequency = 20;
    }

public:
    static RobotControl* getInstance()
    {
       static RobotControl instance;
       return &instance;
    }

    void init(RobotAbstract* robot_)
    {
        robot = robot_;
        motor_top.init(robot);
        chassis.init(robot , &motor_top);
        head.init(robot);
        arm.init(robot);
    }
    void loopCall(void); //20HZ

    void setSBUSRemoteNodePointer(SBUS *node_)
    {
        sbus_node = node_;
        sbus_node_device=sbus_node->device;
    }
    void setRobolinkNodePointer(RoboLink *node_)
    {
        robolink_node_device = (DeviceType)node_->port_num;
        robolink_node = node_;
    }
    void setRobolinkRadioNodePointer(RoboLink *node_)
    {
        robolink_radio_node_device = (DeviceType)node_->port_num;
        robolink_radio_node = node_;
    }

public:
    MotorTop motor_top;
    Chassis chassis;
    Head head;
    Arm arm;
    SBUS *sbus_node;
    DeviceType sbus_node_device;
    RoboLink *robolink_node;
    DeviceType robolink_node_device;
    RoboLink *robolink_radio_node;
    DeviceType robolink_radio_node_device;

private:
    RobotAbstract *robot;
    void robolinkNodeEvent(RoboLink *node_);
    void sbusEvent(SBUS *node_);
    void datatUpdate(void);
    void printInfo(unsigned char type_);
    float call_frequency;
    float degree_to_radian , radian_to_degree;
};

#endif  // #ifndef ROBOT_TOP_H

