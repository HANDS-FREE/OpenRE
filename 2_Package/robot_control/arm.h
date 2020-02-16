#ifndef ARM_H
#define ARM_H

#include "board.h"
#include "robot_abstract.h"

class Arm
{
public:
    Arm()
    {
        robot = NULL;
        para = NULL;
        degree_to_radian = 0.017453f;
        radian_to_degree = 57.2958f;
        memset(&filter , 0 , sizeof(filter));
        memset(&expect_head , 0 , sizeof(expect_head));
    }
    void init(RobotAbstract *robot_)
    {
        robot = robot_;
        setParameters(&robot->para.arm_para);
    }
    void loopCall(void){ }

    void setParameters(ArmParameters *para_){
        para = para_;
    }
    void updataArmPose(void)
    {
        expect_head = robot->arm.expect_arm_state;  //radian
    }

private:
    RobotAbstract *robot;
    ArmParameters *para;
    ArmDOFVector filter , expect_head; //radian
    float degree_to_radian ,  radian_to_degree;
};

#endif //ARM_H
