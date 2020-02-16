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

#include "typical_dc_motor.h"

void TypicalDCMotors::init(RobotAbstract *robot_)
{
    para = &robot_->para.motor_para;
    motors = &robot_->motors;

    motor1 = MotorControl(para,&motors->m1,(unsigned char)MOTOR1);
    motor1.setAngleSpeed(0);

    motor2 = MotorControl(para,&motors->m2,(unsigned char)MOTOR2);
    motor2.setAngleSpeed(0);

    motor3 = MotorControl(para,&motors->m3,(unsigned char)MOTOR3);
    motor3.setAngleSpeed(0);

    motor4 = MotorControl(para,&motors->m4,(unsigned char)MOTOR4);
    motor4.setAngleSpeed(0);
}

void TypicalDCMotors::loopCall(void)
{
    if(para->motor_enable_num >= 1)
    {
        motor1.loopCall();
    }
    if(para->motor_enable_num >= 2)
    {
        motor2.loopCall();
    }
    if(para->motor_enable_num >= 3)
    {
        motor3.loopCall();
    }
    if(para->motor_enable_num >= 4)
    {
        motor4.loopCall();
    }
}

void TypicalDCMotors::controlEnable(unsigned char motor_id_)
{
    if(motor_id_ == 0)
    {
        motor1.controlEnable();
        motor2.controlEnable();
        motor3.controlEnable();
        motor4.controlEnable();

    }
    if(motor_id_ == 1) motor1.controlEnable();
    if(motor_id_ == 2) motor2.controlEnable();
    if(motor_id_ == 3) motor3.controlEnable();
    if(motor_id_ == 4) motor4.controlEnable();
}

void TypicalDCMotors::controlDisable(unsigned char motor_id_)
{
    if(motor_id_ == 0)
    {
        motor1.controlDisable();
        motor2.controlDisable();
        motor3.controlDisable();
        motor4.controlDisable();

    }
    if(motor_id_ == 1) motor1.controlDisable();
    if(motor_id_ == 2) motor2.controlDisable();
    if(motor_id_ == 3) motor3.controlDisable();
    if(motor_id_ == 4) motor4.controlDisable();
}

void TypicalDCMotors::setAngleSpeed(unsigned char motor_id_ , float expect_angle_speed_)
{
    if(motor_id_ == 0)
    {
        motor1.setAngleSpeed(expect_angle_speed_);
        motor2.setAngleSpeed(expect_angle_speed_);
        motor3.setAngleSpeed(expect_angle_speed_);
        motor4.setAngleSpeed(expect_angle_speed_);

    }
    if(motor_id_ == 1) motor1.setAngleSpeed(expect_angle_speed_);
    if(motor_id_ == 2) motor2.setAngleSpeed(expect_angle_speed_);
    if(motor_id_ == 3) motor3.setAngleSpeed(expect_angle_speed_);
    if(motor_id_ == 4) motor4.setAngleSpeed(expect_angle_speed_);
}

float TypicalDCMotors::getAngleSpeed(unsigned char motor_id_)
{
    if(motor_id_ == 1) return motor1.getControlData()->measure_angle_speed;
    if(motor_id_ == 2) return motor2.getControlData()->measure_angle_speed;
    if(motor_id_ == 3) return motor3.getControlData()->measure_angle_speed;
    if(motor_id_ == 4) return motor4.getControlData()->measure_angle_speed;
    return 0;
}

float TypicalDCMotors::getDPastAngel(unsigned char motor_id_)
{
    if(motor_id_ == 1) return motor1.get_d_past_angel();
    if(motor_id_ == 2) return motor2.get_d_past_angel();
    if(motor_id_ == 3) return motor3.get_d_past_angel();
    if(motor_id_ == 4) return motor4.get_d_past_angel();
    return 0;
}


float TypicalDCMotors::getPastTotalAngle(unsigned char motor_id_)
{
    if(motor_id_ == 1) return motor1.getControlData()->past_total_angle;
    if(motor_id_ == 2) return motor2.getControlData()->past_total_angle;
    if(motor_id_ == 3) return motor3.getControlData()->past_total_angle;
    if(motor_id_ == 4) return motor4.getControlData()->past_total_angle;
    return 0;
}

void TypicalDCMotors::clearPastTotaAngle(unsigned char motor_id_)
{
    if(motor_id_ == 0)
    {
        motor1.clear_past_total_odom();
        motor2.clear_past_total_odom();
        motor3.clear_past_total_odom();
        motor4.clear_past_total_odom();

    }
    if(motor_id_ == 1) motor1.clear_past_total_odom();
    if(motor_id_ == 2) motor2.clear_past_total_odom();
    if(motor_id_ == 3) motor3.clear_past_total_odom();
    if(motor_id_ == 4) motor4.clear_past_total_odom();
}

void TypicalDCMotors::setParameters(unsigned char motor_id_ , const MotorParameters *para_)
{
    para = para_;
    if(motor_id_ == 0)
    {
        motor1.setParameter(para);
        motor2.setParameter(para);
        motor3.setParameter(para);
        motor4.setParameter(para);

    }
    if(motor_id_ == 1) motor1.setParameter(para);
    if(motor_id_ == 2) motor2.setParameter(para);
    if(motor_id_ == 3) motor3.setParameter(para);
    if(motor_id_ == 4) motor4.setParameter(para);
}

const MotorParameters* TypicalDCMotors::getParameters(unsigned char motor_id_)
{
    if(motor_id_ == 1) return motor1.getParameter();
    if(motor_id_ == 2) return motor2.getParameter();
    if(motor_id_ == 3) return motor3.getParameter();
    if(motor_id_ == 4) return motor4.getParameter();
    return motor1.getParameter();
}

const MotorControlData* TypicalDCMotors::getControlData(unsigned char motor_id_)
{
    if(motor_id_ == 1) return motor1.getControlData();
    if(motor_id_ == 2) return motor2.getControlData();
    if(motor_id_ == 3) return motor3.getControlData();
    if(motor_id_ == 4) return motor4.getControlData();
    return motor1.getControlData();
}

