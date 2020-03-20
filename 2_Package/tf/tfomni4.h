#ifndef TF_OMNI4_H
#define TF_OMNI4_H

#include "tfrobot.h"

//support for 4 wheel omni robots

/*******************************************************************************
4wd (Top view)

1       2
  X   X
    X
  X   X
4       3
*******************************************************************************/

class TFOmni4 : public TFRobot
{
public:
    TFOmni4(float wheel_radius_  = 0 , float body_radius_ = 0) :
        TFRobot(wheel_radius_ , body_radius_  , 4){}

private:
    void robotToMotorTF(const float* robot , float* motor )
    {
        *motor = 0 * (*robot) + 1 * (*(robot+1)) + body_radius * (*(robot+2)) ;
        *(motor + 1) =  -1 * (*robot) + 0 * (*(robot+1)) + body_radius * (*(robot+2)) ;
        *(motor + 2) = 0 * (*robot) + -1 * (*(robot+1)) + body_radius * (*(robot+2)) ;
        *(motor + 3) =  1 * (*robot) + 0 * (*(robot+1)) + body_radius * (*(robot+2)) ;
    }
    void motorToRobotTF(const float* motor , float* robot)
    {
        *robot = 0 * (*motor) - 0.5f* (*(motor+1)) + 0 * (*(motor+2)) + 0.5f * (*(motor+3));
        *(robot + 1) =  0.5f * (*motor) - 0 * (*(motor+1)) - 0.5f * (*(motor+2)) + 0 * (*(motor+3));
        *(robot + 2) =  (0.25f/body_radius) * (*motor) + (0.25f/body_radius) * (*(motor+1)) + (0.25f/body_radius) * (*(motor+2)) + (0.25f/body_radius) * (*(motor+3));
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
    {
        float robot[3]={0};
        globalToRobotTF(global, robot, R_theta);
        robotToMotorTF (robot, motor);
    }
    void motorToGlobalTF(const float* motor , float* global ,float R_theta)
    {
        float robot[3]={0};
        motorToRobotTF(motor , robot);
        robotToGlobalTF(robot , global , R_theta);
    }

};

#endif // TF_OMNI4_H
