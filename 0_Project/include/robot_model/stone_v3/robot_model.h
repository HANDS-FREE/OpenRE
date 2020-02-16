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
*
* Description:
***********************************************************************************************************************/

#ifndef ROBOT_MODEL_H
#define ROBOT_MODEL_H

#include "robot_abstract.h"

class RobotModel : public RobotParameters
{
public:
    RobotModel() : RobotParameters()
    {

        strcpy(robot_info.robot_name, "stone_v3");
        strcpy(robot_info.robot_description ,  "this is a differential2 robot of handsfree");

        motor_para.driver_type = MotorDriver_PWM12_AND_IO;
        motor_para.motor_enable_num = 2;
        motor_para.simulation_model = 0;
        motor_para.pid_t = 0.02;
        motor_para.encoder_num  = 1560;
        motor_para.pwm_max = 5000;
        motor_para.pwm_dead_zone = 10;
        motor_para.speed_low_filter = 0.3;
        motor_para.protect_current = 200;  // 200A means disable current  protect
        motor_para.pid =  {0.0f  , 0.0f , 0.0f , 100.0f , 300.0f , 0.2f , 0.0f  , 0.0f , 0.0f};

        chassis_para.type = DIFFERENTIAL2;
        chassis_para.wheel_radius = 0.0320;
        chassis_para.body_radius = 0.1592;
        chassis_para.speed_low_filter = 0.4;
        chassis_para.imu_fusion_enalbe = 0;
        chassis_para.control_enable = 1;

        head_para.type = HFANALOG;
        head_para.speed_low_filter = 0.3;
        head_para.range.pitch = 50 * degree_to_radian;
        head_para.range.yaw = 70 * degree_to_radian;
        head_para.offset.pitch = 0 *degree_to_radian;
        head_para.offset.yaw = 0 * degree_to_radian;
        head_para.id.pitch = 7;
        head_para.id.yaw = 8;
        head_para.control_enable = 1;

        arm_para.type = DOBOT2;
        arm_para.speed_low_filter = 1;
        arm_para.dof = 4;
        arm_para.control_enable = 1;
    }
};

#endif
