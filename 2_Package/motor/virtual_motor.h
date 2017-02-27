#ifndef VIRTUAL_MOTOR_H
#define VIRTUAL_MOTOR_H

/***********************************************************************************************************************
VirtualMotor : this is a motor simulator of handsfree ,if you don't have real robot or real motor
you can use it and you an use it for :
: practice motor pid control , validation your control algorithm
: established virtual robot model , and connect to ROS, you can see the virtual robot run in the RVIZ
this means you only need a stm32 board like handsfreecontrolunit for practice ros
: use it for establish PC software,debug communications
***********************************************************************************************************************/

class VirtualMotor
{
public:
    VirtualMotor() {}
    void init(void){ }
    void setPWM(float pwm){ }
    void enable(void){ }
    void disable(void){}
    float getSpeed(void){return 0;}
    float getCurrent(void){return 0;}
    float getEncoder(void){return 0;}

private:
    float  angle_speed_ , current_ , encoder_count_;
};

#endif // VIRTUAL_MOTOR_H
