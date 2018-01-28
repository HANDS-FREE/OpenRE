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
#include "robot_control.h"

/***********************************************************************************************************************
* Function:     void RobotControl::RobotControlCall(void)
*
* Scope:        public
*
* Description:  robot control interface, you must call it in a frequency , generaly  can set
*               be a half of pid frequency
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
***********************************************************************************************************************/
void RobotControl::call(void)
{
    datatUpdate();
    if(sbus_node != NULL)
    {
        sbusEvent(sbus_node);
    }
    if(hf_link_radio_node != NULL)
    {
        hfLinkNodeEvent(hf_link_radio_node);
    }
    if(hf_link_node != NULL)
    {
        hfLinkNodeEvent(hf_link_node);
    }
    chassis.call();
    head.call();
    arm.call();
    //printf("expect speed: %f\r\n", robot->expect_robot_speed.x);
}

void RobotControl::hfLinkNodeEvent(HFLink* hf_link_node_)
{

    if(hf_link_node_->receive_package_renew[SET_MOTOR_PARAMETERS]==1)
    {
        hf_link_node_->receive_package_renew[SET_MOTOR_PARAMETERS]=0;
        motor_top.setParameters(&robot->para.motor_para);
    }
    if(hf_link_node_->receive_package_renew[SAVE_MOTOR_PARAMETERS]==1)
    {
        hf_link_node_->receive_package_renew[SAVE_MOTOR_PARAMETERS]=0;

    }
    if(hf_link_node_->receive_package_renew[SET_CHASSIS_PARAMETERS]==1)
    {
        hf_link_node_->receive_package_renew[SET_CHASSIS_PARAMETERS]=0;
        chassis.setParameters(&robot->para.chassis_para);
    }
    if(hf_link_node_->receive_package_renew[SAVE_CHASSIS_PARAMETERS]==1)
    {
        hf_link_node_->receive_package_renew[SAVE_CHASSIS_PARAMETERS]=0;

    }
    if(hf_link_node_->receive_package_renew[SET_HEAD_PARAMETERS]==1)
    {
        hf_link_node_->receive_package_renew[SET_HEAD_PARAMETERS]=0;
        head.setParameters(&robot->para.head_para);
    }
    if(hf_link_node_->receive_package_renew[SAVE_HEAD_PARAMETERS]==1)
    {
        hf_link_node_->receive_package_renew[SAVE_HEAD_PARAMETERS]=0;

    }
    if(hf_link_node_->receive_package_renew[SET_ARM_PARAMETERS]==1)
    {
        hf_link_node_->receive_package_renew[SET_ARM_PARAMETERS]=0;
        arm.setParameters(&robot->para.arm_para);
    }
    if(hf_link_node_->receive_package_renew[SAVE_ARM_PARAMETERS]==1)
    {
        hf_link_node_->receive_package_renew[SAVE_ARM_PARAMETERS]=0;

    }
    if( hf_link_node_->receive_package_renew[SET_GLOBAL_SPEED]==1 ){
        hf_link_node_->receive_package_renew[SET_GLOBAL_SPEED]=0;
        chassis.updataGlobalSpeed();
    }
    if( hf_link_node_->receive_package_renew[SET_ROBOT_SPEED]==1 ){
        hf_link_node_->receive_package_renew[SET_ROBOT_SPEED ]=0;
        chassis.updataRobotSpeed();
    }
    if( hf_link_node_->receive_package_renew[SET_MOTOR_SPEED]==1 ){
        hf_link_node_->receive_package_renew[SET_MOTOR_SPEED] = 0;
        chassis.updataMotorSpeed();
    }
    if(hf_link_node_->receive_package_renew[CLEAR_COORDINATE_DATA]==1)
    {
        hf_link_node_->receive_package_renew[CLEAR_COORDINATE_DATA]=0;
        chassis.clearCoordData();
    }
    if(hf_link_node_->receive_package_renew[SET_HEAD_STATE]==1)
    {
        hf_link_node_->receive_package_renew[SET_HEAD_STATE]=0;
        head.updataHeadPose();
    }
    if( hf_link_node_->receive_package_renew[SET_ARM_STATE]==1 ){
        hf_link_node_->receive_package_renew[SET_ARM_STATE]=0;
        arm.updataHeadPose();
    }
}

/***********************************************************************************************************************
* Function:     void RobotControl::datatUpdate(void)
*
* Scope:        private
*
* Description:  update the robot RobotAbstract ,only need a low call frequency , 20HZ is recommended
*
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
***********************************************************************************************************************/
void RobotControl::datatUpdate(void)
{
    //system info
    robot->system_info.battery_voltage = Board::getInstance()->battery_voltage;
    robot->system_info.cpu_temperature = Board::getInstance()->cpu_temperature;
    robot->system_info.cpu_usage = Board::getInstance()->cpu_usage;
    robot->system_info.system_time = Board::getInstance()->system_time;
    robot->system_info.power_remain = 1;

    //    //IMU
    //    //    robot->measure_imu_euler_angle.pitch = imu_arithmetic_model.Fus_Angle.pitch * degree_to_radian;
    //    //    robot->measure_imu_euler_angle.roll = imu_arithmetic_model.Fus_Angle.roll * degree_to_radian;
    //    //    robot->measure_imu_euler_angle.yaw = imu_arithmetic_model.Fus_Angle.yaw * degree_to_radian;
    //    if(robot->robot_parameters.imu_enable == 1)
    //    {   //
    //        //measure_global_coordinate.Z=imu_arithmetic_model.Fus_Angle.yaw ;   //use the IMU data to calculating coordinates
    //        //measure_robot_coordinate.Z=imu_arithmetic_model.Fus_Angle.yaw ;
    //    }

    //GPS
}

/***********************************************************************************************************************
* Function:     void RobotControl::sbusControl(void)
*
* Scope:        private
*
* Description:
*
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
***********************************************************************************************************************/
void RobotControl::sbusEvent(SBUS *sbus_)
{
    if ( sbus_->sbus_state == 1)
    {
        sbus_->sbus_state=0;
        if( sbus_->sbus_channel[5] >= 1000 )
        {
            robot->expect_robot_speed.x = (-(sbus_->sbus_channel[1] - 992)*0.001f);
            robot->expect_robot_speed.y = (-(sbus_->sbus_channel[0] - 992)*0.001f);
            robot->expect_robot_speed.z = (-(sbus_->sbus_channel[3] - 992)*0.001f) * 3;
            hf_link_node->receive_package_renew[SET_ROBOT_SPEED]=1;
        }
        else if( sbus_->sbus_channel[5] <= 200 )
        {
            robot->expect_head_state.pitch =(sbus_->sbus_channel[1] - 992) * 0.05f;
            robot->expect_head_state.yaw = -(sbus_->sbus_channel[0] - 992) * 0.05f;
            hf_link_node->receive_package_renew[SET_HEAD_STATE]=1;
        }
        else
        {

        }
    }
}
