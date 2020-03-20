#ifndef TF_CARLIKE_H
#define TF_CARLIKE_H

#include "tfrobot.h"

//support for 4 wheel omni robots

class TFCarLike : public TFRobot
{
public:
    TFCarLike(float wheel_radius_ = 0  , float body_radius_  = 0) :
        TFRobot(wheel_radius_ , body_radius_  , 4){}

private:
    void robotToMotorTF(const float* robot , float* motor )
    {

    }
    void motorToRobotTF(const float* motor , float* robot)
    {

    }
    void globalToRobotTF(const float* global , float* robot , float R_theta)
    {
    }
    void robotToGlobalTF(const float* robot , float* global ,float R_theta)
    {

    }
    void globalToMotorTF(const float* global , float* motor ,float R_theta)
    {

    }
    void motorToGlobalTF(const float* motor , float* global ,float R_theta)
    {

    }

};

#endif // TF_CARLIKE_H
