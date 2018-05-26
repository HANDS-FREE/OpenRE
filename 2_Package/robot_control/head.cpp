/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* Contact:  QQ Exchange Group -- 521037187
*
* LICENSING TERMS:
* The Hands Free is licensed generally under a permissive 3-clause BSD license.
* Contributions are requiredto be made under the same license.
*
* History:
* <author>      <time>      <version>      <desc>
* mawenke       2015.10.1    V1.0          creat this file
* mawenke       2015.7.1     V2.0          update this file
* Description:
***********************************************************************************************************************/

#include "head.h"

void Head::setParameters(HeadParameters* para_)
{
    para = para_;
    HeadPose pose;
    pose.pitch = 0;
    pose.roll  = 0;
    pose.yaw = 0;
    if(para->type ==  HFANALOG)
    {
       Board::getInstance()->pwmInterfaceInit((unsigned char)para->id.pitch , 1);
       Board::getInstance()->pwmInterfaceInit((unsigned char)para->id.yaw , 1);
    }
    else if(para->type == HFDIGITAL)
    {
        servo_digital.axServoInit();
        servo_digital.getServoConnective();
    }
    set_head_pose(pose);
}

void Head::call(void)
{
    if(robot == NULL ||    para == NULL) return;

    datatUpdate();

    filter.pitch = (1 - para->speed_low_filter) * filter.pitch + para->speed_low_filter * expect_head.pitch;
    filter.roll = (1 - para->speed_low_filter) * filter.roll + para->speed_low_filter * expect_head.roll;
    filter.yaw = (1 - para->speed_low_filter) * filter.yaw + para->speed_low_filter * expect_head.yaw;
    if(filter.pitch >= para->range.pitch) filter.pitch = para->range.pitch;
    if(filter.pitch <= - para->range.pitch) filter.pitch = - para->range.pitch;
    if(filter.roll >= para->range.roll) filter.roll = para->range.roll;
    if(filter.roll <= - para->range.roll) filter.roll = -para->range.roll;
    if(filter.yaw >= para->range.yaw) filter.yaw = para->range.yaw;
    if(filter.yaw <= - para->range.yaw) filter.yaw = -para->range.yaw;

    HeadPose  expect_head_offset;
    expect_head_offset.pitch = filter.pitch + para->offset.pitch;
    expect_head_offset.roll = filter.roll + para->offset.roll;
    expect_head_offset.yaw = filter.yaw + para->offset.yaw;

    set_head_pose(expect_head_offset);

   // printf(" pitch = %f  yaw=%f  \n " , robot->measure_head_state.pitch * 57.2958f  ,  robot->measure_head_state.yaw * 57.2958f);
}


void Head::set_head_pose(HeadPose pose)
{
    HeadPose  value;
    if(para->type ==  HFANALOG)
    {
       value.pitch = 1500 - pose.pitch * radian_to_degree * 11.111f;
       value.yaw = 1500 + pose.yaw * radian_to_degree * 11.111f;
       Board::getInstance()->setPWMInterfaceValue((unsigned char)para->id.pitch , value.pitch);
       Board::getInstance()->setPWMInterfaceValue((unsigned char)para->id.yaw , value.yaw);

    }
    else if(para->type == HFDIGITAL)
    {
        value.pitch=-(pose.pitch * radian_to_degree/300)*1024;
        value.yaw=(pose.yaw * radian_to_degree/300)*1024;
        servo_digital.axSendPosition((unsigned char)para->id.pitch , value.pitch , 0x50);
        servo_digital.axSendPosition((unsigned char)para->id.yaw , value.yaw , 0x50);
    }
}


void Head::datatUpdate(void)
{
    HeadPose  value;
    if(para->type ==  HFANALOG)
    {
        value.pitch =Board::getInstance()->readPWMInterfaceValue((unsigned char)para->id.pitch);
        value.yaw =Board::getInstance()->readPWMInterfaceValue((unsigned char)para->id.yaw);
        robot->measure_head_state.pitch  =  degree_to_radian * (float)(1500 - value.pitch)/11.111f - para->offset.pitch;
        robot->measure_head_state.yaw =   degree_to_radian * (float)(value.yaw -1500)/11.111f  - para->offset.yaw;
    }
    else if(para->type == HFDIGITAL)
    {
        value.pitch = servo_digital.axReadPosition((unsigned char)para->id.pitch) ;
        value.yaw = servo_digital.axReadPosition((unsigned char)para->id.yaw) ;
        robot->measure_head_state.pitch =  degree_to_radian * (float)value.pitch * 300 / 1024 - para->offset.pitch;
        robot->measure_head_state.yaw = degree_to_radian * (float)value.yaw * 300 / 1024 - para->offset.yaw;
    }
}

