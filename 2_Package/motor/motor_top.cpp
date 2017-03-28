/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: motor_top.c
* Contact:  QQ Exchange Group -- 521037187
* Version:  V2.0
*
* LICENSING TERMS:
* The Hands Free is licensed generally under a permissive 3-clause BSD license.
* Contributions are requiredto be made under the same license.
*
* History:
* <author>      <time>      <version>      <desc>
* mawenke      2015.10.1    V1.0          creat this file
*
* Description: The file defined a Class for motor control ， you can use it Conveniently and modify a litter
*              for a different circuit board
***********************************************************************************************************************/

#include "motor_top.h"

/***********************************************************************************************************************
* Function:
*
* Scope:        public
*
* Description:  motor control interface init
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
***********************************************************************************************************************/
void MotorTop::motorTopInit(uint8_t motor_enable_num_   ,  float pid_t_ ,
                            const MotorParameters*  motor_init_structure , uint8_t simulation_model_)
{
    MotorParameters para;
    para = *motor_init_structure;
    motor_enable_num = motor_enable_num_;
    pid_t = pid_t_;
    simulation_model = simulation_model_;

    if(motor_enable_num >= 1)
    {
        para.motor_id = 1;
        motor1 = DCMotor(para.driver_type , simulation_model_);
        motor1.controlInit(pid_t_ , &para);
        motor1.setAngleSpeed(0);
    }
    if(motor_enable_num >= 2)
    {
        para.motor_id = 2;
        motor2 = DCMotor(para.driver_type , simulation_model_);
        motor2.controlInit(pid_t_ , &para);
        motor2.setAngleSpeed(0);
    }
    if(motor_enable_num >= 3)
    {
        para.motor_id = 3;
        motor3 = DCMotor(para.driver_type , simulation_model_);
        motor3.controlInit(pid_t_ , &para);
        motor3.setAngleSpeed(0);
    }
    if(motor_enable_num >= 4)
    {
        para.motor_id = 4;
        motor4 = DCMotor(para.driver_type , simulation_model_);
        motor4.controlInit(pid_t_ , &para);
        motor4.setAngleSpeed(0);
    }
}

/***********************************************************************************************************************
* Function:
*
* Scope:        public
*
* Description:  motor control function ，cycle call it ，and the call frequency is PID frequency
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
***********************************************************************************************************************/
void MotorTop::motorTopCall(void)
{
    if(motor_enable_num >= 1)
    {
        motor1.speedControlCall(  );
    }
    if(motor_enable_num >= 2)
    {
        motor2.speedControlCall();
    }
    if(motor_enable_num >= 3)
    {
        motor3.speedControlCall(  );
    }
    if(motor_enable_num >= 4)
    {
        motor4.speedControlCall( );
    }
}

void MotorTop::motorTest(void)
{
    /* here comments code is for motor test ，you do not include·it in normal unless you need to test the motor*/
    static unsigned short int i = 0 , j = 0;
    i++;
    j++;

    if(i <= 250)
    {
        motor1.setAngleSpeed(500);
        motor2.setAngleSpeed(500);
        motor3.setAngleSpeed(500);
        motor4.setAngleSpeed(500);
    }
    else if (i > 250 && i < 500)
    {
        motor1.setAngleSpeed(-500);
        motor2.setAngleSpeed(-500);
        motor3.setAngleSpeed(-500);
        motor4.setAngleSpeed(-500);
    }
    else i = 0;

    if(j >= 35)
    {
        j = 0;
        printf("measure motor speed:  motor1=%.4f  motor2=%.4f  motor3=%.4f  motor4=%.4f \r\n",
               motor1.getControlData()->measure_angle_speed , motor2.getControlData()->measure_angle_speed,
               motor3.getControlData()->measure_angle_speed , motor4.getControlData()->measure_angle_speed);
    }
}

