#ifndef TF_DIFFERENTIAL_H
#define TF_DIFFERENTIAL_H

#include "tfrobot.h"

//support for multiple differential robots (2wd , 4wd , 6wd and tank)

class TFDifferential : public TFRobot
{
public:
    TFDifferential(float wheel_radius_  = 0  , float body_radius_ = 0 , unsigned char num_ = 2):
        TFRobot(wheel_radius_ , body_radius_  , num_){}

private:
    void robotToMotorTF(const float* robot , float* motor )
    {
        *motor = -1 * (*robot) + 0 * (*(robot+1)) + body_radius * (*(robot+2)) ;
        *(motor + 1) =  1 * (*robot) + 0 * (*(robot+1)) + body_radius * (*(robot+2)) ;
        if(motor_num >= 4)
        {
            *(motor + 2) = *motor;
            *(motor + 3) = *(motor + 1);
        }
        if(motor_num >= 6)
        {
            *(motor + 4) = *motor;
            *(motor + 5) = *(motor + 1);
        }
    }
    void motorToRobotTF(const float* motor , float* robot)
    {
        *robot = -0.5f * (*motor) + 0.5f* (*(motor+1));
        *(robot + 1) =  0 * (*motor)  + 0 * (*(motor+1));
        *(robot + 2) =  ( 0.5f/ body_radius ) * ( (*motor) + (*(motor+1)) );
    }
    void globalToRobotTF(const float* global , float* robot , float R_theta)
    {
        *robot =  (float)( cos(R_theta) * (*global) + sin(R_theta) * (*(global+1)) + 0 * (*(global+2)) );
        *(robot + 1) = (float)( -sin(R_theta) * (*global) + cos(R_theta) * (*(global+1)) + 0 * (*(global+2)) );
        *(robot + 2) =   0 * (*global) + 0 * (*(global+1)) + 1 * (*(global+2)) ;
    }
    void robotToGlobalTF(const float* robot , float* global ,float R_theta)
    {
        *global = cos(R_theta)*(*robot) - sin(R_theta) * (*(robot+1)) +  0 * (*(robot+2)) ;
        *(global + 1) =  sin(R_theta) * (*robot) + cos(R_theta) * (*(robot+1))  + 0 * (*(robot+2)) ;
        *(global + 2) =  0 * (*robot) + 0 * (*(robot+1)) + 1 * (*(robot+2)) ;
    }
    void globalToMotorTF(const float* global , float* motor ,float R_theta)
    {  // differential robot do not have  global speed
        for(unsigned char i =0 ; i < motor_num ; i++ ){
            *(motor + i) =0;
        }
    }
    void motorToGlobalTF(const float* motor , float* global ,float R_theta)
    {
        *global = (-cos(R_theta)/2)*(*motor) + (cos(R_theta)/2)*(*(motor+1)) ;
        *(global + 1) =  (-sin(R_theta)/2) * (*motor) +  (sin(R_theta)/2) * (*(motor+1)) ;
        *(global + 2) =  (0.5f/body_radius) * (*motor) + (0.5f/body_radius) * (*(motor+1)) ;
    }
};


#endif // TF_DIFFERENTIAL_H
