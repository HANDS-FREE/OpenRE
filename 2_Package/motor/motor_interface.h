#ifndef MOTOR_INTERFACE_H
#define MOTOR_INTERFACE_H

#include "board.h"
#include "virtual_motor.h"

class MotorInterface
{
public:
    MotorInterface(){
        board = Board::getInstance();
        driver_type = 1;
        simulation_model = 0;
    }
    void init(unsigned char driver_type_ , unsigned char simulation_model_){
        driver_type = driver_type_;
        simulation_model =  simulation_model_ ;
    }

public:
    void interfaceInit(unsigned char device_type_id_ , float pwm_max_){
        if(simulation_model == 0){
            board->motorInterfaceInit((uint8_t)driver_type , board->getByteHighFourBit(board->device_type[device_type_id_]) , pwm_max_);
        }
        else{
            virtual_motor.init(pwm_max_);
        }
    }

    void IOEnable(unsigned char device_type_id_)
    {
        if(simulation_model == 0){
            board->motorEnable((uint8_t)driver_type , board->getByteHighFourBit(board->device_type[device_type_id_]));
        }
        else{
            virtual_motor.enable();
        }
    }

    void IODisable(unsigned char device_type_id_ )
    {
        if(simulation_model == 0){
            board->motorDisable((uint8_t)driver_type , board->getByteHighFourBit(board->device_type[device_type_id_]));
        }
        else{
            virtual_motor.disable();
        }
    }

    void setPWM(unsigned char device_type_id_  , float pwm)
    {
        if(simulation_model == 0){
            board->motorSetPWM((uint8_t)driver_type , board->getByteHighFourBit(board->device_type[device_type_id_]) , pwm);
        }
        else{
            virtual_motor.setPWM(pwm);
        }
    }

    float getEncoderdata(unsigned char device_type_id_ )
    {
        if(simulation_model == 0){
            return board->getMotorEncoderCNT(board->getByteHighFourBit(board->device_type[device_type_id_])) ;
        }
        else{
            return virtual_motor.getEncoder();
        }
    }

    float getCurrent(unsigned char device_type_id_)
    {
        if(simulation_model == 0){
            return board->getMotorCurrent(board->getByteHighFourBit(board->device_type[device_type_id_]));
        }
        else{
            return virtual_motor.getCurrent();
        }
    }

private:
    Board *board;
    SimpleVirtualMotor virtual_motor;
    unsigned char simulation_model;
    unsigned char driver_type;
};

#endif // MOTOR_INTERFACE_H
