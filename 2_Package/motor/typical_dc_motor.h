#ifndef TYPICAL_DC_MOTOR
#define TYPICAL_DC_MOTOR

#include "motor_control.h"
#include "motor_abstract.h"

class TypicalDCMotors : public MotorAbstract
{
public:
    TypicalDCMotors() {}
    void init(RobotAbstract *robot_);
    void loopCall(void);

    void setMode(unsigned char motor_id_, unsigned char mode_){ }

    void controlEnable(unsigned char motor_id_);
    void controlDisable(unsigned char motor_id_);

    void setAngleSpeed(unsigned char motor_id_ , float expect_angle_speed_);
    float getAngleSpeed(unsigned char motor_id_);

    float getDPastAngel(unsigned char motor_id_);
    float getPastTotalAngle(unsigned char motor_id_);
    void clearPastTotaAngle(unsigned char motor_id_);

    void setParameters(unsigned char motor_id_ , const MotorParameters *para_);
    const MotorParameters* getParameters(unsigned char motor_id_);
    const MotorControlData* getControlData(unsigned char motor_id_);

private:
    MotorControl motor1 , motor2 , motor3 ,motor4;
};

#endif // TYPICAL_DC_MOTOR

