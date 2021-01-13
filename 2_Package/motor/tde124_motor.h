#ifndef TDE124_MOTOR
#define TDE124_MOTOR

#include "motor_abstract.h"
#include "queue.h"

#define SPEED_MODE 0
#define FORCE_MODE 1

class TDE124Motors: public MotorAbstract
{
public:
    TDE124Motors() {
    }
    void init(RobotAbstract *robot_);
    void loopCall(void);

    void setMode(unsigned char motor_id_, unsigned char mode_);

    void controlEnable(unsigned char motor_id_);
    void controlDisable(unsigned char motor_id_);

    void setAngleSpeed(unsigned char motor_id_ , float expect_angle_speed_);
    float getAngleSpeed(unsigned char motor_id_);

    float getDPastAngel(unsigned char motor_id_);
    float getPastTotalAngle(unsigned char motor_id_){
        if(motor_id_ == 1) return motors->m1.past_total_angle;
        if(motor_id_ == 2) return motors->m2.past_total_angle;
        if(motor_id_ == 3) return motors->m3.past_total_angle;
        if(motor_id_ == 4) return motors->m4.past_total_angle;
        return motors->m1.past_total_angle;;
    }
    void clearPastTotaAngle(unsigned char motor_id_){}

    void setParameters(unsigned char motor_id_ , const MotorParameters *para_){
        para = para_;
    }
    const MotorParameters* getParameters(unsigned char motor_id_){
        return para;
    }
    const MotorControlData* getControlData(unsigned char motor_id_){
        if(motor_id_ == 1) return &motors->m1;
        if(motor_id_ == 2) return &motors->m2;
        if(motor_id_ == 3) return &motors->m3;
        if(motor_id_ == 4) return &motors->m4;
        return &motors->m1;
    }

private:
    void clear_the_alarm(unsigned char channel);
    void can_send_tx_data(void);
    unsigned char motor1_mode,motor2_mode;

};

#endif // TDE124_MOTOR


