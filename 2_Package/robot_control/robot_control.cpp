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
//20HZ
void RobotControl::loopCall(void)
{
    datatUpdate();
    if(sbus_node != NULL)
    {
        sbusEvent(sbus_node);
    }
    if(robolink_radio_node != NULL)
    {
        robolinkNodeEvent(robolink_radio_node);
    }
    if(robolink_node != NULL)
    {
        robolinkNodeEvent(robolink_node);
    }
    chassis.loopCall();
    head.loopCall();
    arm.loopCall();
}

void RobotControl::robolinkNodeEvent(RoboLink *node_)
{
    if(node_->receive_package_renew[WRITE_MOTOR_PARAMETERS]==1)
    {
        node_->receive_package_renew[WRITE_MOTOR_PARAMETERS]=0;
        motor_top.motors->setParameters(0, &robot->para.motor_para);
    }
    if(node_->receive_package_renew[SAVE_MOTOR_PARAMETERS]==1)
    {
        node_->receive_package_renew[SAVE_MOTOR_PARAMETERS]=0;

    }
    if(node_->receive_package_renew[WRITE_CHASSIS_PARAMETERS]==1)
    {
        node_->receive_package_renew[WRITE_CHASSIS_PARAMETERS]=0;
        chassis.setParameters(&robot->para.chassis_para);
    }
    if(node_->receive_package_renew[SAVE_CHASSIS_PARAMETERS]==1)
    {
        node_->receive_package_renew[SAVE_CHASSIS_PARAMETERS]=0;

    }
    if(node_->receive_package_renew[WRITE_HEAD_PARAMETERS]==1)
    {
        node_->receive_package_renew[WRITE_HEAD_PARAMETERS]=0;
        head.setParameters(&robot->para.head_para);
    }
    if(node_->receive_package_renew[SAVE_HEAD_PARAMETERS]==1)
    {
        node_->receive_package_renew[SAVE_HEAD_PARAMETERS]=0;

    }
    if(node_->receive_package_renew[WRITE_ARM_PARAMETERS]==1)
    {
        node_->receive_package_renew[WRITE_ARM_PARAMETERS]=0;
        arm.setParameters(&robot->para.arm_para);
    }
    if(node_->receive_package_renew[SAVE_ARM_PARAMETERS]==1)
    {
        node_->receive_package_renew[SAVE_ARM_PARAMETERS]=0;

    }
    if( node_->receive_package_renew[SET_GLOBAL_SPEED]==1 ){
        node_->receive_package_renew[SET_GLOBAL_SPEED]=0;
        chassis.updataGlobalSpeed();
    }
    if( node_->receive_package_renew[SET_ROBOT_SPEED]==1 ){
        node_->receive_package_renew[SET_ROBOT_SPEED ]=0;
        chassis.updataRobotSpeed();
    }
    if( node_->receive_package_renew[SET_MOTOR_SPEED]==1 ){
        node_->receive_package_renew[SET_MOTOR_SPEED] = 0;
        chassis.updataMotorSpeed();
    }
    if(node_->receive_package_renew[CLEAR_COORDINATE_DATA]==1)
    {
        node_->receive_package_renew[CLEAR_COORDINATE_DATA]=0;
        chassis.clearCoordData();
    }
    if(node_->receive_package_renew[SET_HEAD_STATE]==1)
    {
        node_->receive_package_renew[SET_HEAD_STATE]=0;
        head.updataHeadPose();
    }
    if( node_->receive_package_renew[SET_ARM_STATE]==1 ){
        node_->receive_package_renew[SET_ARM_STATE]=0;
        arm.updataArmPose();
    }
    if( node_->receive_package_renew[GET_SENSOR_DIS_DATA]==1 ){
        node_->receive_package_renew[GET_SENSOR_DIS_DATA]=0;
        robot->sensors.disio_data.button1 = Board::getInstance()->getKeyState(1);
        robot->sensors.disio_data.button2 = Board::getInstance()->getKeyState(2);
    }
}

/***********************************************************************************************************************
* Function:     void RobotControl::datatUpdate(void)
*
* Scope:        private
*
* Description:  update the robot RobotAbstract ,only need a low call frequency , 20HZ is recommended
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
    robot->system_info.power_remain = Board::getInstance()->power_remain;

    //printf("robot->system_info.power_remain =%f \r\n", robot->system_info.power_remain);
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
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
***********************************************************************************************************************/
void RobotControl::sbusEvent(SBUS *node_)
{
    if ( node_->sbus_state == 1)
    {
        node_->sbus_state=0;
        if( node_->sbus_channel[5] >= 1000 )
        {
            robot->chassis.expect_robot_speed.x = (-(node_->sbus_channel[1] - 992)*0.001f);
            robot->chassis.expect_robot_speed.y = (-(node_->sbus_channel[0] - 992)*0.001f);
            robot->chassis.expect_robot_speed.z = (-(node_->sbus_channel[3] - 992)*0.001f) * 3;
            robolink_node->receive_package_renew[SET_ROBOT_SPEED]=1;
        }
        else if( node_->sbus_channel[5] <= 200 )
        {
            robot->head.expect_head_state.pitch =(node_->sbus_channel[1] - 992) * 0.05f;
            robot->head.expect_head_state.yaw = -(node_->sbus_channel[0] - 992) * 0.05f;
            robolink_node->receive_package_renew[SET_HEAD_STATE]=1;
        }
        else
        {

        }
    }
}

void RobotControl::printInfo(unsigned char type_)
{
    if(type_ ==1)
    {
        printf("expect speed: %f\r\n", robot->chassis.expect_robot_speed.x);
    }
}
