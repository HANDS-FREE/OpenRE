#ifndef ROBOT_TOP_H
#define ROBOT_TOP_H

//#include "imu_top.h"
#include "robot_abstract.h"
#include "chassis.h"
#include "head.h"
#include "arm.h"
#include "sbus_ppm.h"
#include "hf_link.h"

class RobotControl
{
private:
    RobotControl()
    {
        robot =NULL;
        sbus_node = NULL;
        hf_link_node = NULL;
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
        motor_top.motorTopInit(robot->para.chassis_para.dof , robot->para.chassis_para.motor_pid_t ,
                               &robot->para.motor_para  ,  robot->para.chassis_para.simulation_model);
        chassis.init(robot , &motor_top);
        head.init(robot);
        arm.init(robot);
    }
    void call(void);

    void setSBUSRemoteNodePointer(SBUS* sbus_node_)
    {
        sbus_node = sbus_node_ ;
        sbus_node_device=sbus_node->device;
    }
    void setHFLinkNodePointer(HFLink* hf_link_node_)
    {
        hf_link_node_device = (DeviceType)hf_link_node_->port_num;
        hf_link_node = hf_link_node_ ;
    }
    void setHFLinkRadioNodePointer(HFLink* hf_link_node_)
    {
        hf_link_radio_node_device = (DeviceType)hf_link_node_->port_num;
        hf_link_radio_node = hf_link_node_ ;
    }

public:
    MotorTop motor_top;
    Chassis chassis;
    Head head;
    Arm arm;
    SBUS *sbus_node;
    DeviceType sbus_node_device;
    HFLink *hf_link_node;
    DeviceType hf_link_node_device;
    HFLink *hf_link_radio_node;
    DeviceType hf_link_radio_node_device;

private:
    RobotAbstract* robot;
    void hfLinkNodeEvent(HFLink* hf_link_node_);
    void sbusEvent(SBUS *sbus_);
    void datatUpdate(void);
    float call_frequency;
    float degree_to_radian ,  radian_to_degree;
};

#endif  // #ifndef ROBOT_TOP_H

