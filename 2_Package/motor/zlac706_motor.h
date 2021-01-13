#ifndef ZLAC706_MOTOR
#define ZLAC706_MOTOR

#include "motor_abstract.h"
#include "queue.h"

#define SPEED_MODE 0
#define FORCE_MODE 1

class ZLAC706Motors: public MotorAbstract
{
public:
    ZLAC706Motors() {
        l_past_total_angle1 = 0;
        l_past_total_angle2 = 0;
        c_past_total_angle1 = 0;
        c_past_total_angle2 = 0;
        c_past_total_pose1 = 0;
        c_past_total_pose2 = 0;
        motor1_alarm_time = 0;
        motor2_alarm_time = 0;
        motor1_connect_quality = 0;
        motor2_connect_quality = 0;
        motor_error_detect_cnt1_ = 0;
        motor_error_detect_cnt2_ = 0;
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
        if(motor_id_ == 1) return c_past_total_angle1;
        if(motor_id_ == 2) return c_past_total_angle2;
        return c_past_total_angle1;
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
    void usart_set_angle_speed(unsigned char channel ,unsigned char mode,
                               float expect_angle_speed);
    void motor_int_speed_mode(void);
    void setToForceMode(void);
    void setTOSpeedMode(void);

    float l_past_total_angle1 , l_past_total_angle2 , c_past_total_angle1 , c_past_total_angle2;
    int c_past_total_pose1 , c_past_total_pose2;
    Queue *motor1_queue , *motor2_queue;
    unsigned char motor1_mode,motor2_mode;

    unsigned int  motor1_alarm_time,motor2_alarm_time; //safe time
    unsigned char motor1_connect_quality,motor2_connect_quality;
    unsigned char motor_error_detect_cnt1_,motor_error_detect_cnt2_;
    unsigned char m1d[4],m2d[4];
};

#endif // ZLAC706_MOTOR


