#ifndef MOTOR_TOP_H
#define MOTOR_TOP_H

#include "motor_config.h"
#include "motor_control.h"

/***********************************************************************************************************************
motor_simulation_model_ : this is a motor simulator of handsfree ,if you don't have real robot or real motor
you can use it and you an use it for :
: practice motor pid control , validation your control algorithm
: established virtual robot model , and connect to ROS, you can see the virtual robot run in the RVIZ
this means you only need a stm32 board like handsfreecontrolunit for practice ros
: use it for establish PC software,debug communications
***********************************************************************************************************************/

class MotorTop
{
public:
    MotorTop(){
        motor[0]=MotorControl();
        motor[1]=MotorControl();
        motor[2]=MotorControl();
        motor[3]=MotorControl();
        expect_angle_speed_m[0]=0;
        expect_angle_speed_m[1]=0;
        expect_angle_speed_m[2]=0;
        expect_angle_speed_m[3]=0;
        motor_enable[0]=0;
        motor_enable[1]=0;
        motor_enable[2]=0;
        motor_enable[3]=0;
        motor_pwm_max = 5000;
        motor_dead_zone = 10 ;
    }
    void motorTopInit(float motor_enable_num_ , float motor_encoder_num_ , float motor_pid_t_  , unsigned char motor_simulation_model_);
    void motorTopCall(void);
    void motorStateEnable(int8_t motor_id){ motor_enable[motor_id - 1] = 1 ; }  //motor_id = 1~N
    void motorStateDisable(int8_t motor_id){ motor_enable[motor_id - 1] = 0 ; }
    uint8_t getMotorState(int8_t motor_id) const{ return motor_enable[motor_id - 1];}
    void setMotorAngleSpeed(int8_t motor_id , float speed){   //motor_id = 1~N degree/s
        expect_angle_speed_m[motor_id - 1] = speed ; }
    float getMotorAngleSpeed(int8_t motor_id) const{
        return expect_angle_speed_m[motor_id - 1]; }
public:
    MotorControl motor[4];

private:
    uint8_t motor_enable_num; //the motor's num of yor need to control
    float motor_encoder_num;  //the encoder sensor count when the  motor turning one circle
    float motor_pid_t;        //the interval time of  motor pid control  the unit is second
    float motor_pwm_max;      //set the max value for pwm
    float motor_dead_zone;    //when the pwm in this zone , the motor disable
    uint8_t motor_enable[4];  //Whether or not enable motor control

    float expect_angle_speed_m[4];
    void motorPWMRenew(uint8_t motor_id , float pwm_value);
};

extern MotorTop motor_top;

#endif // #ifndef MOTOR_TOP_H

