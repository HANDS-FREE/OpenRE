#ifndef SENSORS
#define SENSORS

class Sensors
{
public:
    Sensors() {

    }
    void init(RobotAbstract *robot_)
    {
        robot=robot_;
        sensors = &robot_->sensors;
    }
    void loopCall(void); //200HZ

private:
    RobotAbstract *robot;
    SensorsData *sensors;

private:
};

#endif // SENSORS

