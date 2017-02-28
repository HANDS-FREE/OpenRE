#ifndef MOTOR_TOP_H
#define MOTOR_TOP_H

#include "board.h"
#include "virtual_motor.h"
#include "motor_control.h"

class DCMotor : public MotorControl
{
public:
    DCMotor(MotorDriverType motor_driver_type_ = MotorDriver_PWM12_AND_IO , uint8_t motor_simulation_model_ = 0)
    {
        motor_driver_type = motor_driver_type_;
        motor_simulation_model = motor_simulation_model_;
        board = Board::getInstance();
    }
    void setSimulationModel(uint8_t motor_simulation_model_ ){
        motor_simulation_model =  motor_simulation_model_ ;
    }

public:
    void interfaceInit(unsigned char motor_id_  , float pwm_max){
        if(motor_simulation_model == 0){
            board->motorInterfaceInit((uint8_t)motor_driver_type , motor_id_ , pwm_max);
        }
        else{
            virtual_motor.init();
        }
    }

    void IOEnable(unsigned char motor_id_ )
    {
        if(motor_simulation_model == 0){
            board->motorEnable((uint8_t)motor_driver_type , motor_id_);
        }
        else{
            virtual_motor.enable();
        }
    }

    void IODisable(unsigned char motor_id_ )
    {
        if(motor_simulation_model == 0){
            board->motorDisable((uint8_t)motor_driver_type , motor_id_);
        }
        else{
            virtual_motor.disable();
        }
    }

    void setPWM(unsigned char motor_id_  , float pwm)
    {
        if(motor_simulation_model == 0){
            board->motorSetPWM((uint8_t)motor_driver_type , motor_id_ , pwm);
        }
        else{
            virtual_motor.setPWM(pwm);
        }
    }

    float getEncoderdata(unsigned char motor_id_ )
    {
        if(motor_simulation_model == 0){
            return board->getMotorEncoderCNT(motor_id_) ;
        }
        else{
            return virtual_motor.getEncoder();
        }
    }

    float getCurrent(unsigned char motor_id_)
    {
        if(motor_simulation_model == 0){
            return board->getMotorCurrent(motor_id_);
        }
        else{
            return virtual_motor.getCurrent();
        }
    }

private:
    Board *board;
    VirtualMotor virtual_motor;
    uint8_t motor_simulation_model;
    MotorDriverType motor_driver_type;
};

class MotorTop
{
public:
    MotorTop() { }

    void motorTopInit(uint8_t motor_enable_num_   ,  float pid_t_ ,
                      const MotorParameters*  motor_init_structure , uint8_t simulation_model_ = 0 );
    void motorTopCall(void);
    void setParameters(const MotorParameters*  motor_para)
    {
        if(motor_para->motor_id == 0) //set all motor
        {
            motorTopInit(motor_enable_num  ,  pid_t  , motor_para , simulation_model);
        }
        if(motor_para->motor_id == 1)
        {
            motor1.setParameters(motor_para);
        }
        if(motor_para->motor_id == 2)
        {
            motor2.setParameters(motor_para);
        }
        if(motor_para->motor_id == 3)
        {
            motor3.setParameters(motor_para);
        }
        if(motor_para->motor_id == 4)
        {
            motor4.setParameters(motor_para);
        }
    }
    void motorTest(void);

public:
    DCMotor motor1 , motor2 , motor3 ,motor4;

private:
    MotorPID default_pid;
    uint8_t motor_enable_num;
    uint8_t simulation_model;
    float  pid_t;
};

#endif // #ifndef MOTOR_TOP_H

