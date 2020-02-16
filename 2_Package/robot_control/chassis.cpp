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

#include "chassis.h"

//20HZ
void Chassis::loopCall(void)
{
    if(robot == NULL || para == NULL || motor_top == NULL || robot_tf == NULL) return;

    datatUpdate();
    safetyDetection();

    if(system_info->chassis_online == 0 || system_info->col_drop_alarm == 1)
    {
        //ifcontrol_quality is too low or unsafe
        //set motor Expect Speed 0 , motor_id_ = 0 means for all motors
        motor_top->motors->setAngleSpeed(0,0);
        motor_top->motors->controlDisable(0);
    }
    else if(system_info->chassis_online == 1){
        //motor_id_ = 0 means for all motors
        motor_top->motors->controlEnable(0);

        //speed low filter
        for(unsigned char i = 0 ; i < 4 ; i++)
        {
            speed_filter[i] = (1- para->speed_low_filter) * speed_filter[i]  +
                    para->speed_low_filter * *( ( (float *)&robot->chassis.expect_motor_speed) + i);
        }

        motor_top->motors->setAngleSpeed(1, speed_filter[0] * radian_to_degree);
        motor_top->motors->setAngleSpeed(2, speed_filter[1] * radian_to_degree);
        motor_top->motors->setAngleSpeed(3, speed_filter[2] * radian_to_degree);
        motor_top->motors->setAngleSpeed(4, speed_filter[3] * radian_to_degree);
    }
    //printInfo(1);
}

void Chassis::setParameters(ChassisParameters *para_)
{
    para = para_;

    if(para_->type == DIFFERENTIAL2){
        differentia_model = TFDifferential(para_->wheel_radius , para_->body_radius , 2);
        robot_tf = &differentia_model;
    }
    else if(para_->type == DIFFERENTIAL4){
        differentia_model = TFDifferential(para_->wheel_radius , para_->body_radius , 4);
        robot_tf = &differentia_model;
    }
    else if(para_->type == OMNI3){
        omni3_model = TFOmni3(para_->wheel_radius , para_->body_radius);
        robot_tf = &omni3_model;
    }
    else if(para_->type == OMINI4){
        omni4_model = TFOmni4(para_->wheel_radius , para_->body_radius);
        robot_tf = &omni4_model;
    }
    else if(para_->type == MECANUM4){
        mecanum_model = TFMecanum(para_->wheel_radius , para_->body_radius);
        robot_tf = &mecanum_model;
    }
    else if(para_->type == CARLIKE){
        carlike_model = TFCarLike(para_->wheel_radius , para_->body_radius);
        robot_tf = &carlike_model;
    }
}

void Chassis::updataGlobalSpeed(void)
{
    system_info->control_quality += 30;   //robot->robot_parameters.control_signal_quality add 30
    robot_tf->globalSpeedSet( (float* )&robot->chassis.expect_global_speed , (float* )&robot->chassis.expect_motor_speed ,
                              robot->chassis.measure_global_coordinate.z);
}
void Chassis::updataRobotSpeed(void)
{
    system_info->control_quality += 30;
    robot_tf->robotSpeedSet((float* )&robot->chassis.expect_robot_speed , (float* )&robot->chassis.expect_motor_speed);
}

void Chassis::updataMotorSpeed(void)
{
    system_info->control_quality += 30;
}

//20HZ
void Chassis::datatUpdate(void)
{
    robot->chassis.measure_motor_speed.servo1 = motor_top->motors->getAngleSpeed(1) * degree_to_radian;
    robot->chassis.measure_motor_speed.servo2 = motor_top->motors->getAngleSpeed(2) * degree_to_radian;
    robot->chassis.measure_motor_speed.servo3 = motor_top->motors->getAngleSpeed(3) * degree_to_radian;
    robot->chassis.measure_motor_speed.servo4 = motor_top->motors->getAngleSpeed(4) * degree_to_radian;

    robot_tf->getRobotSpeed((float* )&robot->chassis.measure_motor_speed , (float* )&robot->chassis.measure_robot_speed);
    robot_tf->getGlobalSpeed((float* )&robot->chassis.measure_motor_speed , (float* )&robot->chassis.measure_global_speed , robot->chassis.measure_global_coordinate.z);

    robot->chassis.measure_motor_mileage.servo1 = motor_top->motors->getPastTotalAngle(1) * degree_to_radian;
    robot->chassis.measure_motor_mileage.servo2 = motor_top->motors->getPastTotalAngle(2) * degree_to_radian;
    robot->chassis.measure_motor_mileage.servo3 = motor_top->motors->getPastTotalAngle(3) * degree_to_radian;
    robot->chassis.measure_motor_mileage.servo4 = motor_top->motors->getPastTotalAngle(4) * degree_to_radian;

    float d_len[4];
    d_len[0] = motor_top->motors->getDPastAngel(1) * degree_to_radian * para->wheel_radius;
    d_len[1] = motor_top->motors->getDPastAngel(2) * degree_to_radian * para->wheel_radius;
    d_len[2] = motor_top->motors->getDPastAngel(3) * degree_to_radian * para->wheel_radius;
    d_len[3] = motor_top->motors->getDPastAngel(4) * degree_to_radian * para->wheel_radius;

    //get global coordinate
    //need time stm32F1 330us  stm32F4+NOFPU 64~80us   stm32F4+FPU 8~16us
    robot_tf->getGlobalCoordinate(d_len , (float* )&robot->chassis.measure_global_coordinate);
    //need time stm32F1 20us  stm32F4+FPU 0~2us
    robot_tf->getRobotCoordinate(d_len , (float* )&robot->chassis.measure_robot_coordinate);
}

//20HZ
void Chassis::safetyDetection(void)
{
    //control quality detection
    system_info->control_quality = system_info->control_quality - (100.00f / call_frequency); //control_quality reduce 1 every call
    if(system_info->control_quality >= 100) system_info->control_quality = 100;
    else if(system_info->control_quality <= 5) system_info->control_quality = 5;
    if(system_info->control_quality <= 30) system_info->chassis_online = 0;
    else if (system_info->control_quality >=70) system_info->chassis_online = 1;
    else system_info->chassis_online = 2;

    //motor speed limit
    unsigned char over_speed_state = 0;
    for(unsigned char i = 0 ; i < 4 ; i++)
    {
        if(*( ( (float *)&robot->chassis.expect_motor_speed) + i) > (para->max_speed_limit.x/para->wheel_radius))
        {
            *( ( (float *)&robot->chassis.expect_motor_speed) + i) = para->max_speed_limit.x/para->wheel_radius;
            over_speed_state = 1;
        }
        else if(*( ( (float *)&robot->chassis.expect_motor_speed) + i) < -(para->max_speed_limit.x/para->wheel_radius))
        {
            *( ( (float *)&robot->chassis.expect_motor_speed) + i) = - para->max_speed_limit.x/para->wheel_radius;
            over_speed_state = 1;
        }
    }
    system_info->over_speed_state = over_speed_state;
}

void Chassis::clearCoordData(void)
{
    robot->chassis.measure_global_coordinate.x=0;
    robot->chassis.measure_global_coordinate.y=0;
    robot->chassis.measure_global_coordinate.z=0;
    robot->chassis.measure_robot_coordinate.x=0;
    robot->chassis.measure_robot_coordinate.y=0;
    robot->chassis.measure_robot_coordinate.z=0;
    motor_top->motors->clearPastTotaAngle(0);
}

void Chassis::chassisTest(void)
{
    if(robot == NULL || para == NULL || motor_top == NULL || robot_tf == NULL) return;

    datatUpdate();

    //motor_id_ = 0 means for all motors
    motor_top->motors->controlEnable(0);

    // speed low filter
    for(unsigned char i = 0 ; i < 4 ; i++)
    {
        speed_filter[i] = (1- para->speed_low_filter) * speed_filter[i]  +  para->speed_low_filter * *( ( (float *)&robot->chassis.expect_motor_speed) + i);
    }

    motor_top->motors->setAngleSpeed(0 , 10 * radian_to_degree);

    if(robot->chassis.measure_motor_speed.servo1 > 8 && robot->chassis.measure_motor_speed.servo1 < 12)
        printf("motor1 is ok.\r\n");
    else
        printf("motor1 is wrong\r\n");
    if(robot->chassis.measure_motor_speed.servo2 > 8 && robot->chassis.measure_motor_speed.servo2 < 12)
        printf("motor2 is ok.\r\n");
    else
        printf("motor2 is wrong\r\n");
    if(robot->chassis.measure_motor_speed.servo3 > 8 && robot->chassis.measure_motor_speed.servo3 < 12)
        printf("motor3 is ok.\r\n");
    else
        printf("motor3 is wrong\r\n");
    if(robot->chassis.measure_motor_speed.servo4 > 8 && robot->chassis.measure_motor_speed.servo4 < 12)
        printf("motor4 is ok.\r\n");
    else
        printf("motor4 is wrong\r\n");

    printInfo(1);
}

void Chassis::printInfo(unsigned char type_)
{
    if(type_ ==1)
    {
        printf("expect_robot_speed:  x=%.4f  y=%.4f  z=%.4f  \r\n",
               robot->chassis.expect_robot_speed.x , robot->chassis.expect_robot_speed.y , robot->chassis.expect_robot_speed.z);
        printf("measure_robot_speed:  x=%.4f  y=%.4f  z=%.4f  \r\n",
               robot->chassis.measure_robot_speed.x , robot->chassis.measure_robot_speed.y , robot->chassis.measure_robot_speed.z);
        printf("measure_global_coordinate:  x=%.4f  y=%.4f  z=%.4f  \r\n",
               robot->chassis.measure_global_coordinate.x , robot->chassis.measure_global_coordinate.y , robot->chassis.measure_global_coordinate.z);
    }
}
