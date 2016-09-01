#ifndef PAN_TILT_HEAD_AX_H
#define PAN_TILT_HEAD_AX_H

#include "servo_config.h"
#include "servo_digital.h"

class HeadAX:public ServoDigital
{
public:
    HeadAX()
    {
        ServoDigital();
        set_head_state_renew=0;
        read_head_state_renew=0;
        expect_head_pitch=0;
        expect_head_yaw=0;
        measure_head_pitch=0;
        measure_head_yaw=0;
        first_call=0;
    }
    void headInit(void);
    void headTopCall(void);
    void setState(float pitch , float yaw);
    void getState(float* pitch , float* yaw);

private:
    unsigned char first_call;
    unsigned char set_head_state_renew , read_head_state_renew;
    float expect_head_pitch , expect_head_yaw;
    float measure_head_pitch , measure_head_yaw;

    unsigned short int read_pitch , read_yaw;
    unsigned short int set_pitch, set_yaw;
    unsigned short int pitch_offset , pitch_range , yaw_offset , yaw_range;

};

extern HeadAX robot_head;

#endif // #ifndef PAN_TILT_HEAD_AX_H






