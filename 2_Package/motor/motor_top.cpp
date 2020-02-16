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
void MotorTop::init(RobotAbstract *robot_)
{
    if(robot_->para.motor_para.driver_type == MotorDriver_PWM12_AND_IO || robot_->para.motor_para.driver_type == MotorDriver_PWM_AND_IOAB)
    {
        typical_dc_motors = TypicalDCMotors();
        motors = &typical_dc_motors;
    }
    else if(robot_->para.motor_para.driver_type == MotorDriver_ZLAC706)
    {

    }
    else
    {
        return;
    }
    motors->init(robot_);
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
void MotorTop::loopCall(void)
{
    float pid_t = motors->getParameters(0)->pid_t;
    if(loop_cnt >= (unsigned int)(pid_t/d_loop_time)) loop_cnt = 0;
    if(loop_cnt == 0) motors->loopCall();
    loop_cnt++;
}

void MotorTop::motorTest(void)
{
    /* here comments code is for motor test ，you do not include·it in normal unless you need to test the motor*/
    static unsigned short int i = 0 , j = 0;
    i++;
    j++;

    if(i <= 500)
    {
        motors->setAngleSpeed(0,1000);
    }
    else if (i > 500 && i < 1000)
    {
        motors->setAngleSpeed(0,-1000);
    }
    else i = 0;

    if(j >= 25)
    {
        j = 0;
        motors->printInfo(1);
    }
}
