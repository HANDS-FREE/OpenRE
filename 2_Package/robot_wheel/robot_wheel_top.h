#ifndef ROBOT_WHEEL_TOP_H
#define ROBOT_WHEEL_TOP_H

#include "robot_wheel_config.h"
#include "hf_link.h"

#if  ROBOT_WHEEL_MODEL==2
#include "tf_2wd.h"
#define TF_CLASS TF_2WD
#endif
#if  ROBOT_WHEEL_MODEL==3
#define TF_CLASS TF_3WD
#include "tf_3wd.h"
#endif
#if  ROBOT_WHEEL_MODEL==4
#define TF_CLASS TF_4WD
#include "tf_4wd.h"
#endif

class RobotWheel:public TF_CLASS
{
public:
    RobotWheel()
    {
        control_command_quality=0;   //0~100  if<30 control_command_quality is bad and Control Disable  , otherwise control enable
        robot_control_en=0;
        call_frequency=20;
        l_filter=0.4;
    }
    void robotWheelTopInit(void);
    void robotWheelTopCall(void);

private:
    struct RobotMotor{
        float  m1;
        float  m2;
        float  m3;
        float  m4;};
    RobotMotor d_motor_len_filter_ , expect_angle_speed_;
    unsigned char robot_wheel_model;
    unsigned char control_command_quality;  // 0~100  if<30 control_command_quality is bad and Control Disable  , otherwise control enable
    unsigned char robot_control_en;         // Whether or not enable motor control
    float call_frequency;
    float l_filter ;

    void robotDataUpdate(void);
    void chassisControl(void);
    void headControl(void);
    void armControl(void);
    void robotCoordCalc(void);
    void remoteAnalysis(void);
};

extern RobotAbstract my_robot;
extern HFLink hf_link_pc_node;
extern HFLink *hf_link_node_pointer;
extern RobotWheel hands_free_robot;

#endif  // #ifndef ROBOT_WHEEL_TOP_H

