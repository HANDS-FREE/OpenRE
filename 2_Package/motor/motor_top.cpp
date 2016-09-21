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

MotorTop motor_top;

/***********************************************************************************************************************
* Function:     void MotorTop::motor_set_pwm(uint8_t motor_id , float pwm_value)
*
* Scope:        private
*
* Description:  The underlying interface of motor control，you need to modify it for a different circuit board
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
***********************************************************************************************************************/
void MotorTop::motorPWMRenew(uint8_t motor_id , float pwm_value)
{

    if( motor_id ==1 ){
        if( motor_enable[0] !=1 )
        {
            board.motorDisable(1);
            board.motorSetPWM(1,0);
            return;
        }
        else if( ( pwm_value < motor_dead_zone ) && (pwm_value > -motor_dead_zone) )   // enter dead line
        {
            board.motorDisable(1);
            board.motorSetPWM(1,0);
            return;
        }
        else{
            board.motorEnable(1);
            board.motorSetPWM(1,pwm_value);
            return;
        }
    }
    else if(motor_id == 2 ){
        if( motor_enable[1] !=1 )
        {
            board.motorDisable(2);
            board.motorSetPWM(2,0);
            return;
        }
        else if( ( pwm_value < motor_dead_zone ) && (pwm_value > -motor_dead_zone) )   // enter dead line
        {
            board.motorDisable(2);
            board.motorSetPWM(2,0);
            return;
        }
        else{
            board.motorEnable(2);
            board.motorSetPWM(2,pwm_value);
            return;
        }
    }

    else if(motor_id ==3 ){
        if( motor_enable[2] !=1 )
        {
            board.motorDisable(3);
            board.motorSetPWM(3,0);
            return;
        }
        else if( ( pwm_value < motor_dead_zone ) && (pwm_value > -motor_dead_zone) )  //enter dead line
        {
            board.motorDisable(3);
            board.motorSetPWM(3,0);
            return;
        }
        else{
            board.motorEnable(3);
            board.motorSetPWM(3,pwm_value);
            return;
        }
    }
    
    else if(motor_id ==4 ){
        if( motor_enable[3] !=1 )
        {
            board.motorDisable(4);
            board.motorSetPWM(4,0);
            return;
        }
        else if( ( pwm_value < motor_dead_zone ) && (pwm_value > -motor_dead_zone) )  //enter dead line
        {
            board.motorDisable(4);
            board.motorSetPWM(4,0);
            return;
        }
        else{
            board.motorEnable(4);
            board.motorSetPWM(4,pwm_value);
            return;
        }

    }
    
}

/***********************************************************************************************************************
* Function:     void MotorTop::motorTopInit(void)
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
void MotorTop::motorTopInit(float motor_enable_num_ , float motor_encoder_num_ ,
                            float motor_pid_t_  , unsigned char motor_simulation_model_)
{
    motor_enable_num = motor_enable_num_;
    motor_encoder_num = motor_encoder_num_;
    motor_pid_t = motor_pid_t_;

    board.motorInterfaceInit(1, motor_pwm_max); //motor_x init
    motor1.motorControlInit(motor_pid_t_ , motor_encoder_num_ , motor_pwm_max , motor_simulation_model_);
    motor_enable[0]=1;  //enable motor control
    motorPWMRenew(1,0);

    board.motorInterfaceInit(2, motor_pwm_max);
    motor2.motorControlInit(motor_pid_t_ , motor_encoder_num_ , motor_pwm_max , motor_simulation_model_);
    motor_enable[1]=1;
    motorPWMRenew(2,0);

    if(motor_enable_num >= 3)
    {
        board.motorInterfaceInit(3, motor_pwm_max);
        motor3.motorControlInit(motor_pid_t_ , motor_encoder_num_ , motor_pwm_max , motor_simulation_model_);
        motor_enable[2]=1;
        motorPWMRenew(3,0);
    }

    if(motor_enable_num >= 4)
    {
        board.motorInterfaceInit(4, motor_pwm_max);
        motor4.motorControlInit(motor_pid_t_ , motor_encoder_num_ , motor_pwm_max , motor_simulation_model_);
        motor_enable[3]=1;
        motorPWMRenew(4,0);
    }
}

/***********************************************************************************************************************
* Function:     void MotorTop::motorTopCall(void)
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
    // *Count--the address of encoder D_value   MAX_PWM_OUT--PWM max value
    // need time    stm32f4+nofpu 25us  stm32f4+fpu 5us
    motorPWMRenew( 1 , motor1.speedControl(expect_angle_speed_m[0] , board.getMotorEncoderCNT(1) ) );
    motorPWMRenew( 2 , motor2.speedControl(expect_angle_speed_m[1] , board.getMotorEncoderCNT(2) ) );
    if(motor_enable_num >= 3)
    {
        motorPWMRenew( 3 , motor3.speedControl(expect_angle_speed_m[2] , board.getMotorEncoderCNT(3) ) );
    }
    if(motor_enable_num >= 4)
    {
        motorPWMRenew( 4 , motor4.speedControl(expect_angle_speed_m[3] , board.getMotorEncoderCNT(4) ) );
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
        expect_angle_speed_m[0]=1000;
        expect_angle_speed_m[1]=1000;
        expect_angle_speed_m[2]=1000;
        expect_angle_speed_m[3]=1000;
    }
    else if (i > 250 && i < 500)
    {
        expect_angle_speed_m[0]=-1000;
        expect_angle_speed_m[1]=-1000;
        expect_angle_speed_m[2]=-1000;
        expect_angle_speed_m[3]=-1000;
    }
    else i = 0;

    if(j >= 35)
    {
        j = 0;
        printf("measure motor speed:  motor1=%.4f  motor2=%.4f  motor3=%.4f  motor4=%.4f \r\n" , motor1.get_measure_angle_speed() , motor2.get_measure_angle_speed() , motor3.get_measure_angle_speed() , motor4.get_measure_angle_speed() );
    }
}

