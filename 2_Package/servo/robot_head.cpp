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
#include "robot_head.h"

RobotHead robot_head;

/***********************************************************************************************************************
* Function:
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
void RobotHead::init(void)
{
    RobotHead();
    if (servo_type == 1)
    {
        axServoInit();
        pitch_range = 30 * angletorad;
        yaw_range = 80 * angletorad;
        pitch_offset = 150 * angletorad;
        yaw_offset = 150 * angletorad;
    }
    else
    {
        board.pwmInterfaceInit(TIM12 , 1);
        pitch_range = 50 * angletorad;
        yaw_range = 70 * angletorad;
        pitch_offset =  - 5 * angletorad;
        yaw_offset = 60  * angletorad;
    }
}

/***********************************************************************************************************************
* Function:
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
void RobotHead::topCall(void)
{

    if(first_call==0)
    {
        first_call=1;
        if(servo_type == 1){
            getServoConnective();
            expect_head_pitch = 0 ;
            expect_head_yaw = 0 ;
            set_head_state();
        }
    }
    else
    {
        if(servo_type == 0) {
            set_head_state_renew = 1;
            read_head_state_renew = 1;
        }
        if(set_head_state_renew == 1 )
        {
            set_head_state_renew = 0;
            set_head_state();
        }
        if(read_head_state_renew == 1 )
        {
            read_head_state_renew = 0;
            read_head_state();
        }
    }
}

/***********************************************************************************************************************
* Function:
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
void RobotHead::set_head_state(void)
{
    unsigned short int set_pitch, set_yaw;
    float expect_head_pitch_filter_ ,  expect_head_yaw_filter_ ;

    if(servo_type == 1){
        expect_head_pitch_filter =  expect_head_pitch  ;
        expect_head_yaw_filter = expect_head_yaw ;
    }
    else{
        expect_head_pitch_filter =  0.2f * expect_head_pitch  + 0.8f * expect_head_pitch_filter;
        expect_head_yaw_filter =  0.2f * expect_head_yaw  + 0.8f * expect_head_yaw_filter;
    }

    if(expect_head_pitch_filter >= pitch_range) expect_head_pitch_filter = pitch_range;
    if(expect_head_pitch_filter <= -pitch_range) expect_head_pitch_filter = -pitch_range;
    if(expect_head_yaw_filter >= yaw_range) expect_head_yaw_filter = yaw_range;
    if(expect_head_yaw_filter <= -yaw_range) expect_head_yaw_filter = -yaw_range;
    expect_head_pitch_filter_  = expect_head_pitch_filter + pitch_offset;
    expect_head_yaw_filter_  = expect_head_yaw_filter + yaw_offset;

    if(servo_type == 1){
        set_pitch=-(expect_head_pitch_filter_ * radtoangle/300)*1024;
        set_yaw=(expect_head_yaw_filter_ * radtoangle/300)*1024;
        axSendPosition(1, set_pitch , 0x50);
        axSendPosition(2, set_yaw , 0x50);
    }
    else {
        set_pitch = 1500 - expect_head_pitch_filter_ * radtoangle * 11.111f;
        set_yaw = 1500 + expect_head_yaw_filter_ * radtoangle * 11.111f;
        board.setPWMValue(9 , set_pitch);
        board.setPWMValue(10, set_yaw);
    }
}

/***********************************************************************************************************************
* Function:
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
void RobotHead::read_head_state(void)
{
    short int read_pitch , read_yaw;
    if(servo_type == 1){
        read_pitch = axReadPosition(1) ;
        read_yaw = axReadPosition(2) ;
        measure_head_pitch =  angletorad * (float)read_pitch * 300 / 1024 - pitch_offset;
        measure_head_yaw = angletorad * (float)read_yaw * 300 / 1024 - yaw_offset;
    }
    else {
        read_pitch = TIM12->CCR1;
        read_yaw = TIM12->CCR2;
        measure_head_pitch =  angletorad * (float)(1500 - read_pitch)/11.111f - pitch_offset ;
        measure_head_yaw =   angletorad * (float)(read_yaw -1500)/11.111f  - yaw_offset  ;
    }
}
