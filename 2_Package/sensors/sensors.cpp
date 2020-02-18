/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* Contact:  QQ Exchange Group -- 521037187
* LICENSING TERMS:
* History:
* <author>      <time>       <desc>
* mawenke       2019.4.20    creat this file
***********************************************************************************************************************/
#include "sensors.h"

//200HZ
void Sensors::loopCall(void)
{
    loop_100hz++;
    loop_50hz++;
    loop_20hz++;
    loop_10hz++;
    loop_1hz++;

    if(loop_100hz >= 2) //100HZ
    {
        loop_100hz = 0;
    }

    if(loop_50hz >= 4) //50HZ
    {
        loop_50hz = 0;
    }

    if(loop_20hz >= 10) //20HZ
    {
        loop_20hz = 0;
        chassisDataUpdate();
    }

    if(loop_10hz >= 20) //10HZ
    {
        loop_10hz = 0;
    }

    if(loop_1hz >= 200) //1HZ
    {
        loop_1hz = 0;
    }
}

void Sensors::chassisDataUpdate(void)
{
    sensors->disio_data.control_quality = robot->chassis.system_info.control_quality;
    sensors->disio_data.chassis_online = robot->chassis.system_info.chassis_online;
    sensors->disio_data.col_drop_alarm = robot->chassis.system_info.col_drop_alarm;
    sensors->disio_data.over_speed_state = robot->chassis.system_info.over_speed_state;
    sensors->disio_data.motor1_online_state = robot->motors.m1.online_state;
    sensors->disio_data.motor2_online_state = robot->motors.m2.online_state;
    sensors->disio_data.motor1_mode_state = robot->motors.m1.mode_state;
    sensors->disio_data.motor2_mode_state = robot->motors.m2.mode_state;
    sensors->disio_data.motor1_fault_state = robot->motors.m1.fault_state;
    sensors->disio_data.motor2_fault_state = robot->motors.m2.fault_state;
}
