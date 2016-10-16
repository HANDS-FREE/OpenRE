#ifndef ROBOT_HEAD_H
#define ROBOT_HEAD_H

#include "servo_config.h"
#include "servo_digital.h"

class RobotHead:public ServoDigital
{
public:
    RobotHead(){
        servo_type = 0;
        first_call=0;
        set_head_state_renew=0;
        read_head_state_renew=0;
        radtoangle = 57.295779513 ;
        angletorad = 0.01745329252;
        expect_head_pitch=0;
        expect_head_yaw=0;
        measure_head_pitch=0;
        measure_head_yaw=0;
        expect_head_pitch_filter = 0;
        expect_head_yaw_filter =0;
    }
    void init(void);
    void topCall(void);

    void setState(float pitch , float yaw){ //radian
        set_head_state_renew = 1;
        expect_head_pitch =  pitch;
        expect_head_yaw = yaw;
    }
    void getState(float* pitch , float* yaw){ //radian
        read_head_state_renew = 1;
        *pitch = measure_head_pitch ;
        *yaw = measure_head_yaw;
    }

private:
    void set_head_state(void);
    void read_head_state(void);

    unsigned char  servo_type;  // 1 :  digital servo  0: analog servo
    unsigned char first_call;
    unsigned char set_head_state_renew , read_head_state_renew;
    float radtoangle , angletorad ;    //radian to angle
    float expect_head_pitch , expect_head_yaw ,  expect_head_pitch_filter , expect_head_yaw_filter; //radian
    float measure_head_pitch , measure_head_yaw; //radian
    float pitch_offset , pitch_range , yaw_offset , yaw_range; //radian

};

extern RobotHead robot_head;

#endif // #ifndef ROBOT_HEAD_H






