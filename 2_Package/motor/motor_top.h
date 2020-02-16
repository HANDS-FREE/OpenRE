#ifndef MOTOR_TOP_H
#define MOTOR_TOP_H

#include "typical_dc_motor.h"

class MotorTop
{
public:
    MotorTop() {
        d_loop_time = 0.005;
        loop_cnt = 0;
    }
    void init(RobotAbstract *robot_);
    void loopCall(void);

    void setMode(unsigned char mode_)
    {
        if(motors == NULL) return;
        motors->setMode(0,mode_);
    }

    void motorTest(void);

public:
    MotorAbstract *motors;
    TypicalDCMotors typical_dc_motors;

private:
    float d_loop_time;
    unsigned int loop_cnt;
};

#endif // #ifndef MOTOR_TOP_H
