#ifndef SENSORS
#define SENSORS

#include "robot_abstract.h"

class Sensors
{
public:
    Sensors() {
        loop_100hz=loop_50hz=loop_20hz=loop_10hz=loop_1hz=0;
    }
    void init(RobotAbstract *robot_)
    {
        robot=robot_;
        sensors = &robot_->sensors;
    }
    void loopCall(void); //200HZ

private:
    void chassisDataUpdate(void); //20HZ

private:
    RobotAbstract *robot;
    SensorsData *sensors;

private:
    unsigned char loop_100hz,loop_50hz,loop_20hz,loop_10hz,loop_1hz;
};

#endif // SENSORS

