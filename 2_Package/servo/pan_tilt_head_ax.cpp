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

/***********************************************************************************************************************
* Function:     void HeadAX::headInit(void)
*
* Scope:        public
*
* Description:
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
***********************************************************************************************************************/
void HeadAX::headInit(void)
{
    axServoInit();
}

/***********************************************************************************************************************
* Function:    void HeadAX::headTopCall(void)
*
* Scope:
*
* Description:
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
***********************************************************************************************************************/
void HeadAX::headTopCall(void)
{

    if(first_call==0)
    {
        first_call=1;
        getServoConnective();
        axSendPosition(1, pitch_offset, 0x50);
        axSendPosition(2, yaw_offset , 0x50);
    }
    else
    {
        if(set_head_state_renew == 1 )
        {
            set_head_state_renew = 0;
            if(expect_head_pitch >= pitch_range) expect_head_pitch=pitch_range;
            if(expect_head_pitch <= -pitch_range) expect_head_pitch=-pitch_range;
            if(expect_head_yaw >= yaw_range) expect_head_yaw=yaw_range;
            if(expect_head_yaw <= -yaw_range) expect_head_yaw=-yaw_range;

            set_pitch=-(expect_head_pitch/300)*1024+pitch_offset;
            set_yaw=(expect_head_yaw/300)*1024+yaw_offset;
            axSendPosition(1, set_pitch , 0x50);
            axSendPosition(2, set_yaw , 0x50);
        }
        if(read_head_state_renew == 1 )
        {
            read_head_state_renew = 0;
            read_pitch = axReadPosition(1);
            read_yaw = axReadPosition(2);
            measure_head_pitch = ((float)(pitch_offset - read_pitch)*300)/1024;
            measure_head_yaw = ((float)(set_yaw - yaw_offset)*300)/1024;
        }
    }
}

/***********************************************************************************************************************
* Function:     void HeadAX::setState(float pitch_angle , float yaw_angle)
*
* Scope:
*
* Description:
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
***********************************************************************************************************************/
void HeadAX::setState(float pitch_angle , float yaw_angle)
{
    set_head_state_renew = 1;
    expect_head_pitch =  pitch_angle;
    expect_head_yaw = yaw_angle;
}

/***********************************************************************************************************************
* Function:     void HeadAX::getState(float* pitch , float* yaw)
*
* Scope:
*
* Description:
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
***********************************************************************************************************************/
void HeadAX::getState(float* pitch , float* yaw)
{
    read_head_state_renew = 1;
    *pitch = measure_head_pitch ;
    *yaw = measure_head_yaw;
}
