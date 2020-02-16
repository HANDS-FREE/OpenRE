#ifndef MOTOR_ABSTRACT
#define MOTOR_ABSTRACT

#include "robot_abstract.h"
#include "stdio.h"

class MotorAbstract
{
public:
    MotorAbstract() {}
    virtual void init(RobotAbstract *robot_)
    {
      para = &robot_->para.motor_para;
      motors = &robot_->motors;
      sensors = &robot_->sensors;
    }
    virtual void loopCall(void) = 0;

    virtual void setMode(unsigned char motor_id_, unsigned char mode_) = 0;

    virtual void controlEnable(unsigned char motor_id_) = 0;
    virtual void controlDisable(unsigned char motor_id_) = 0;

    virtual void setAngleSpeed(unsigned char motor_id_ , float expect_angle_speed_) = 0;
    virtual float getAngleSpeed(unsigned char motor_id_) = 0;

    virtual float getDPastAngel(unsigned char motor_id_) = 0;
    virtual float getPastTotalAngle(unsigned char motor_id_) = 0;
    virtual void clearPastTotaAngle(unsigned char motor_id_) = 0;

    virtual void setParameters(unsigned char motor_id_ , const MotorParameters *para_) = 0;
    virtual const MotorParameters* getParameters(unsigned char motor_id_) = 0;
    virtual const MotorControlData* getControlData(unsigned char motor_id_) = 0;

    inline void printInfo(unsigned char type_)
    {
        if(type_ ==1)
        {
            printf("expect_angle_speed:  motor1=%.4f  motor2=%.4f  motor3=%.4f  motor4=%.4f \r\n",
                   getControlData(1)->expect_angle_speed , getControlData(2)->expect_angle_speed,
                   getControlData(3)->expect_angle_speed , getControlData(4)->expect_angle_speed);
            printf("measure_angle_speed:  motor1=%.4f  motor2=%.4f  motor3=%.4f  motor4=%.4f \r\n",
                   getControlData(1)->measure_angle_speed , getControlData(2)->measure_angle_speed,
                   getControlData(3)->measure_angle_speed , getControlData(4)->measure_angle_speed);
        }
    }

protected:
    const MotorParameters *para;
    MotorsControlData *motors;
    SensorsData *sensors;
};


#endif // MOTOR_ABSTRACT

