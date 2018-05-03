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

void Chassis::call(void)
{
    if(robot == NULL || para == NULL || motor_top == NULL || robot_tf == NULL) return;

    datatUpdate();

    control_quality = control_quality - (100.00f / call_frequency);  //control_quality reduce 1 every call
    if(control_quality >= 100){
        control_quality = 100;
    }
    else if(control_quality <= 5){
        control_quality = 5;
    }
    if(control_quality <= 30 || para->control_enable == 0 ){   //ifcontrol_quality is too low
        //motor control disable
        //set motor Expect Speed 0
        motor_top->motor1.setAngleSpeed(0);
        motor_top->motor2.setAngleSpeed(0);
        motor_top->motor3.setAngleSpeed(0);
        motor_top->motor4.setAngleSpeed(0);

        motor_top->motor1.controlDisable();
        motor_top->motor2.controlDisable();
        motor_top->motor3.controlDisable();
        motor_top->motor4.controlDisable();
    }
    else if(control_quality >=70 ){
        motor_top->motor1.controlEnable();
        motor_top->motor2.controlEnable();
        motor_top->motor3.controlEnable();
        motor_top->motor4.controlEnable();

        // speed low filter
        for(unsigned char i = 0 ; i < 4 ; i++)
        {
            speed_filter[i] = (1- para->speed_low_filter) * speed_filter[i]  +  para->speed_low_filter * *( ( (float *)&robot->expect_motor_speed) + i);
        }

        motor_top->motor1.setAngleSpeed(speed_filter[0] * radian_to_degree);
        motor_top->motor2.setAngleSpeed(speed_filter[1] * radian_to_degree);
        motor_top->motor3.setAngleSpeed(speed_filter[2] * radian_to_degree);
        motor_top->motor4.setAngleSpeed(speed_filter[3] * radian_to_degree);
    }

     //   printf("motor_speed:  servo1=%.4f  servo2=%.4f \r\n", robot->measure_motor_speed.servo1 ,  robot->measure_motor_speed.servo2);
    //    printf("robot_speed:  x=%.4f  y=%.4f  z=%.4f  \r\n",
    //           robot->measure_robot_speed.x , robot->measure_robot_speed.y , robot->measure_robot_speed.z);
    //    printf("lobal_coordinate:  x=%.4f  y=%.4f  z=%.4f  \r\n",
    //           robot->measure_global_coordinate.x , robot->measure_global_coordinate.y , robot->measure_global_coordinate.z);
}

void Chassis::chassisTest(void)
{
    if(robot == NULL || para == NULL || motor_top == NULL || robot_tf == NULL) return;

    datatUpdate();

    motor_top->motor1.controlEnable();
    motor_top->motor2.controlEnable();
    motor_top->motor3.controlEnable();
    motor_top->motor4.controlEnable();

    // speed low filter
    for(unsigned char i = 0 ; i < 4 ; i++)
    {
        speed_filter[i] = (1- para->speed_low_filter) * speed_filter[i]  +  para->speed_low_filter * *( ( (float *)&robot->expect_motor_speed) + i);
    }

    if(robot->expect_motor_speed.servo1 == 0)
    {
        motor_top->motor1.setAngleSpeed(20 * radian_to_degree);
        motor_top->motor2.setAngleSpeed(20 * radian_to_degree);
        motor_top->motor3.setAngleSpeed(20 * radian_to_degree);
        motor_top->motor4.setAngleSpeed(20 * radian_to_degree);

        if(robot->measure_motor_speed.servo1 > 1.90 && robot->measure_motor_speed.servo1 < 2.10)
            printf("motor1 is ok.\r\n");
        else
            printf("motor1 is wrong\r\n");
        if(robot->measure_motor_speed.servo2 > 1.90 && robot->measure_motor_speed.servo2 < 2.10)
            printf("motor2 is ok.\r\n");
        else
            printf("motor2 is wrong\r\n");
        if(robot->measure_motor_speed.servo3 > 1.90 && robot->measure_motor_speed.servo3 < 2.10)
            printf("motor3 is ok.\r\n");
        else
            printf("motor3 is wrong\r\n");
        if(robot->measure_motor_speed.servo4 > 1.90 && robot->measure_motor_speed.servo4 < 2.10)
            printf("motor4 is ok.\r\n");
        else
            printf("motor4 is wrong\r\n");
    }
    else
    {
        motor_top->motor1.setAngleSpeed(robot->expect_motor_speed.servo1);
        motor_top->motor2.setAngleSpeed(robot->expect_motor_speed.servo2);
        motor_top->motor3.setAngleSpeed(robot->expect_motor_speed.servo3);
        motor_top->motor4.setAngleSpeed(robot->expect_motor_speed.servo4);
    }

    //    printf("motor_speed:  servo1=%.4f  servo2=%.4f \r\n", robot->measure_motor_speed.servo1 ,  robot->measure_motor_speed.servo2);
    //    printf("robot_speed:  x=%.4f  y=%.4f  z=%.4f  \r\n",
    //           robot->measure_robot_speed.x , robot->measure_robot_speed.y , robot->measure_robot_speed.z);
    //    printf("lobal_coordinate:  x=%.4f  y=%.4f  z=%.4f  \r\n",
    //           robot->measure_global_coordinate.x , robot->measure_global_coordinate.y , robot->measure_global_coordinate.z);
}

void Chassis::datatUpdate(void)
{
    robot->measure_motor_speed.servo1 = motor_top->motor1.getControlData()->measure_angle_speed  *  degree_to_radian;
    robot->measure_motor_speed.servo2 = motor_top->motor2.getControlData()->measure_angle_speed * degree_to_radian;
    robot->measure_motor_speed.servo3 = motor_top->motor3.getControlData()->measure_angle_speed * degree_to_radian;
    robot->measure_motor_speed.servo4 = motor_top->motor4.getControlData()->measure_angle_speed* degree_to_radian;

    robot_tf->getRobotSpeed((float* )&robot->measure_motor_speed , (float* )&robot->measure_robot_speed);
    robot_tf->getGlobalSpeed((float* )&robot->measure_motor_speed , (float* )&robot->measure_global_speed , robot->measure_global_coordinate.z);

    robot->measure_motor_mileage.servo1 = motor_top->motor1.getControlData()->past_total_angle * degree_to_radian;
    robot->measure_motor_mileage.servo2 = motor_top->motor2.getControlData()->past_total_angle * degree_to_radian;
    robot->measure_motor_mileage.servo3 = motor_top->motor3.getControlData()->past_total_angle * degree_to_radian;
    robot->measure_motor_mileage.servo4 = motor_top->motor4.getControlData()->past_total_angle * degree_to_radian;

    float  d_len[4];
    d_len[0]= motor_top->motor1.get_d_past_angel() * degree_to_radian * para->wheel_radius;
    d_len[1]= motor_top->motor2.get_d_past_angel() * degree_to_radian * para->wheel_radius;
    d_len[2] = motor_top->motor3.get_d_past_angel() * degree_to_radian * para->wheel_radius;
    d_len[3] = motor_top->motor4.get_d_past_angel() * degree_to_radian * para->wheel_radius;

    //get global coordinate
    //need time stm32F1 330us  stm32F4+NOFPU 64~80us   stm32F4+FPU 8~16us
    robot_tf->getGlobalCoordinate( d_len , (float* )&robot->measure_global_coordinate);
    //need time stm32F1 20us  stm32F4+FPU 0~2us
    robot_tf->getRobotCoordinate( d_len , (float* )&robot->measure_robot_coordinate);
}
