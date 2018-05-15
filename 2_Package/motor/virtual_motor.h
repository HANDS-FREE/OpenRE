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

class SimpleVirtualMotor
{
public:
    SimpleVirtualMotor() {}
    void init(float pwm_max_){pwm_max=pwm_max_;}
    void setPWM(float pwm_){ pwm = pwm_;}
    void enable(void){ }
    void disable(void){}
    float getSpeed(void){return 0;}
    float getCurrent(void){return 0;}
    float getEncoder(void){
        float simulation_max_angel_speed=3000;
        float pid_t=0.02;
        float encoder_num=1560;
        float measure_unit_encoder = (simulation_max_angel_speed/360.0f)
                *( pwm/pwm_max ) * encoder_num * pid_t;
        return measure_unit_encoder;}

protected:
    float angle_speed_ , current_ , encoder_count_;
    float pwm_max,pwm;
};
#endif // VIRTUAL_MOTOR_H
