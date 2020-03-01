#ifndef SENSORS
#define SENSORS

#include "robot_abstract.h"
#include "imu_top.h"

class Sensors
{
private:
    Sensors() {
        loop_500hz=loop_250hz=loop_100hz=loop_50hz=loop_20hz=loop_10hz=loop_1hz=0;
    }

public:
    static Sensors* getInstance()
    {
        static Sensors instance;
        return &instance;
    }
    void init(RobotAbstract *robot_)
    {
        robot = robot_;
        sensors = &robot_->sensors;
        imu.init(1,0,0,0,0,0);
    }
    void loopCall(void); //1000HZ

private:
    void chassisDataUpdate(void);   //20HZ
    void imuSensorDataUpdate(void); //50HZ

private:
    RobotAbstract *robot;
    SensorsData *sensors;
    IMU imu;

private:
    unsigned short int loop_500hz,loop_250hz,loop_100hz,loop_50hz,loop_20hz,loop_10hz,loop_1hz;
};

#endif // SENSORS

