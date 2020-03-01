/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* Contact:  QQ Exchange Group -- 521037187
* LICENSING TERMS:
* History:
* <author>      <time>       <desc>
* mawenke       2019.4.20    creat this file
***********************************************************************************************************************/
#include "sensors.h"

//1000HZ
void Sensors::loopCall(void)
{
    loop_500hz++;
    loop_250hz++;
    loop_100hz++;
    loop_50hz++;
    loop_20hz++;
    loop_10hz++;
    loop_1hz++;

    imu.loopCall();

    if(loop_500hz >= 2) //500HZ
    {
        loop_500hz = 0;
    }

    if(loop_250hz >= 4) //250HZ
    {
        loop_250hz = 0;
    }

    if(loop_100hz >= 10) //100HZ
    {
        loop_100hz = 0;
    }

    if(loop_50hz >= 20) //50HZ
    {
        loop_50hz = 0;
        imuSensorDataUpdate();
    }

    if(loop_20hz >= 50) //20HZ
    {
        loop_20hz = 0;
        chassisDataUpdate();
    }

    if(loop_10hz >= 100) //10HZ
    {
        loop_10hz = 0;
    }

    if(loop_1hz >= 1000) //1HZ
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

void Sensors::imuSensorDataUpdate(void)
{
    sensors->imu_data.angular_velocity.x = mpu6050.gyro_normal.x; //rad/sec
    sensors->imu_data.angular_velocity.y = mpu6050.gyro_normal.y;
    sensors->imu_data.angular_velocity.z = mpu6050.gyro_normal.z;

    sensors->imu_data.linear_acceleration.x = mpu6050.acc_normal.x;
    sensors->imu_data.linear_acceleration.y = mpu6050.acc_normal.y;
    sensors->imu_data.linear_acceleration.z = mpu6050.acc_normal.z;

    sensors->imu_data.orientation_quaternion.x = imu.imu_fmodel_frame.q_x;
    sensors->imu_data.orientation_quaternion.y = imu.imu_fmodel_frame.q_y;
    sensors->imu_data.orientation_quaternion.z = imu.imu_fmodel_frame.q_z;
    sensors->imu_data.orientation_quaternion.w = imu.imu_fmodel_frame.q_w;

    sensors->imu_data.orientation_euler_rpy.pitch = imu.imu_fmodel_frame.s_pryaw.pitch * 0.017453f ; //rad
    sensors->imu_data.orientation_euler_rpy.roll = imu.imu_fmodel_frame.s_pryaw.roll * 0.017453f;
    sensors->imu_data.orientation_euler_rpy.yaw = imu.imu_fmodel_frame.s_pryaw.yaw * 0.017453f;
}
