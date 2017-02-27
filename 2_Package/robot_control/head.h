#ifndef HEAD_H
#define HEAD_H

#include "board.h"
#include "servo_digital.h"
#include "robot_abstract.h"

//the AX digital servo pose be divided into 1024 unit 0~0X3FF
//counterclockwise is positive
//HEAD  Pitch>0 Look up  ; Pitch<0 Look down ; YAW>0 Look left  ; YAW<0 Look right

class Head
{
public:
    Head(){
        robot = NULL;
        para = NULL;
        degree_to_radian = 0.017453f;
        radian_to_degree = 57.2958f;
        servo_digital = ServoDigital();
        memset(&filter , 0 , sizeof(filter));
        memset(&expect_head , 0 , sizeof(expect_head));
    }

    void init(RobotAbstract* robot_)
    {
        robot = robot_;
        setParameters(&robot->para.head_para);
    }
    void setParameters(HeadParameters* para_);
    void updataHeadPose(void)
    {
        expect_head = robot->expect_head_state; // radian
    }
    void call(void);

private:
    void set_head_pose(HeadPose pose);
    void datatUpdate(void);

    RobotAbstract* robot;
    HeadParameters* para;
    ServoDigital servo_digital;
    HeadPose filter , expect_head; // radian
    float degree_to_radian ,  radian_to_degree;
};

#endif // HEAD_H
