#ifndef TF_3OMNI_H
#define TF_3OMNI_H

#include "tfrobot.h"

//support for 3 wheel omni robots

class TFOmni3 : public TFRobot
{
public:
    TFOmni3(float wheel_radius_ = 0  , float body_radius_ = 0):
      TFRobot(wheel_radius_ , body_radius_  , 3){}

private:
    void robotToMotorTF(const float* robot , float* motor )
    {
        *motor = 0 * (*robot) + 1 * (*(robot+1)) + body_radius * (*(robot+2)) ;
        *(motor + 1) =  -0.866025f * (*robot) - 0.5f * (*(robot+1)) + body_radius * (*(robot+2)) ;
        *(motor + 2) =  0.866025f * (*robot) - 0.5f * (*(robot+1)) + body_radius * (*(robot+2)) ;
    }
    void motorToRobotTF(const float* motor , float* robot)
    {
        *robot = 0 * (*motor) + -0.57735f * (*(motor+1)) + 0.57735f * (*(motor+2)) ;
        *(robot + 1) =  0.666667f* (*motor)  -0.333333f * (*(motor+1)) + -0.333333f * (*(motor+2)) ;
        *(robot + 2) =  ( 0.333333f / body_radius ) * ( (*motor) + (*(motor+1)) +  (*(motor+2)) ) ;
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
        *(global + 1) =  sin(R_theta) * (*robot) + cos(R_theta) * (*(robot+1)) + 0 * (*(robot+2)) ;
        *(global + 2) =  0 * (*robot) + 0 * (*(robot+1)) + 1 * (*(robot+2)) ;
    }
    void globalToMotorTF(const float* global , float* motor ,float R_theta)
    {
        *motor =  -sin(R_theta) * (*global) + cos(R_theta) * (*(global+1)) + body_radius * (*(global+2)) ;
        *(motor + 1) =  -sin(PI_/3 - R_theta) * (*global) - cos(PI_/3 - R_theta) * (*(global+1)) + body_radius * (*(global+2)) ;
        *(motor + 2) =  sin(PI_/3 + R_theta) * (*global) - cos(PI_/3 + R_theta) * (*(global+1)) + body_radius * (*(global+2)) ;
    }
    void motorToGlobalTF(const float* motor , float* global ,float R_theta)
    {
        *global = -0.666667f * sin(R_theta)*(*motor) + (-0.577350f*cos(R_theta) + 0.333333f*sin(R_theta))*(*(motor+1)) + (0.577350f*cos(R_theta) + 0.333333f*sin(R_theta))*(*(motor+2)) ;
        *(global + 1) =  0.666667f * cos(R_theta)*(*motor) + (-0.577350f*sin(R_theta) - 0.333333f*cos(R_theta))*(*(motor+1)) + (0.577350f*sin(R_theta) - 0.333333f*cos(R_theta))*(*(motor+2)) ;
        *(global + 2) =  ( 1 / (3*body_radius) ) * ( (*motor) + (*(motor+1)) +(*(motor+2)) ) ;
    }

};

#endif // TF_3OMNI_H
