/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: robot_wheel_config.h
* Contact:  QQ Exchange Group -- 521037187
* Version:  V2.0
*
* LICENSING TERMS:
* The Hands Free is licensed generally under a permissive 3-clause BSD license.
* Contributions are requiredto be made under the same license.
*
* History:
* <author>      <time>      <version>      <desc>
* mawenke       2015.10.1   V1.0           creat this file
* Description:
*
***********************************************************************************************************************/
#include "pan_tilt_head_ax.h"

HeadAX robot_head;

#define PITCH_OFFSET  512
#define PITCH_RANGE  30
#define YAW_OFFSET    512
#define YAW_RANGE  80

void HeadAX::headInit(void)
{
    axServoInit();
}

void HeadAX::headTopCall(void)
{

    if(first_call==0)
    {
        first_call=1;
        getServoConnective();
        axSendPosition(1, PITCH_OFFSET, 0x50);
        axSendPosition(2, YAW_OFFSET , 0x50);
    }
    else
    {
        if(set_head_state_renew == 1 )
        {
            set_head_state_renew = 0;
            if(expect_head_pitch >= PITCH_RANGE) expect_head_pitch=PITCH_RANGE;
            if(expect_head_pitch <= -PITCH_RANGE) expect_head_pitch=-PITCH_RANGE;
            if(expect_head_yaw >= YAW_RANGE) expect_head_yaw=YAW_RANGE;
            if(expect_head_yaw <= -YAW_RANGE) expect_head_yaw=-YAW_RANGE;

            set_pitch=-(expect_head_pitch/300)*1024+PITCH_OFFSET;
            set_yaw=(expect_head_yaw/300)*1024+YAW_OFFSET;
            axSendPosition(1, set_pitch , 0x50);
            axSendPosition(2, set_yaw , 0x50);
        }
        if(read_head_state_renew == 1 )
        {
            read_head_state_renew = 0;
            read_pitch = axReadPosition(1);
            read_yaw = axReadPosition(2);
            measure_head_pitch = ((float)(PITCH_OFFSET - read_pitch)*300)/1024;
            measure_head_yaw = ((float)(set_yaw - YAW_OFFSET)*300)/1024;
        }
    }
}

void HeadAX::setState(float pitch_angle , float yaw_angle)
{
    set_head_state_renew = 1;
    expect_head_pitch =  pitch_angle;
    expect_head_yaw = yaw_angle;
}

void HeadAX::getState(float* pitch , float* yaw)
{
    read_head_state_renew = 1;
    *pitch = measure_head_pitch ;
    *yaw = measure_head_yaw;
}
