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
* mawenke       2016.7.1    V2.0           creat this file
*
***********************************************************************************************************************/

#include "board.h"

Board::Board() : BoardAbstract()
{
    battery_voltage_alarm_ = 10.20 ;
    battery_proportion_ = 11.00 ;

#ifndef DEBUG_PRINTF_INTERFACE
    device_type[USART_DEBUG] = 0x10;
#else
    if(DEBUG_PRINTF_INTERFACE == 1){
        device_type[USART_DEBUG] = 0x10;
    }
    else if(DEBUG_PRINTF_INTERFACE == 2){
        device_type[USART_DEBUG] = 0x20;
    }
    else if(DEBUG_PRINTF_INTERFACE == 3){
        device_type[USART_DEBUG] = 0x30;
    }
    else if(DEBUG_PRINTF_INTERFACE == 4){
        device_type[USART_DEBUG] = 0x40;
    }
    else if(DEBUG_PRINTF_INTERFACE == 5){
        device_type[USART_DEBUG] = 0x50;
    }
    else if(DEBUG_PRINTF_INTERFACE == 6){
        device_type[USART_DEBUG] = 0x60;
    }
    else { device_type[USART_DEBUG] = 0x10;}
#endif

#ifndef PC_INTERFACE
    device_type[USART_PC] = 0x10;
#else
    if(PC_INTERFACE == 1){
        device_type[USART_PC] = 0x10;
    }
    else if(PC_INTERFACE == 2){
        device_type[USART_PC] = 0x20;
    }
    else if(PC_INTERFACE == 3){
        device_type[USART_PC] = 0x30;
    }
    else if(PC_INTERFACE == 4){
        device_type[USART_PC] = 0x40;
    }
    else if(PC_INTERFACE == 5){
        device_type[USART_PC] = 0x50;
    }
    else if(PC_INTERFACE == 6){
        device_type[USART_PC] = 0x60;
    }
    else { device_type[USART_PC] = 0x10;}
#endif

#ifndef RADIO_INTERFACE
    device_type[USART_RADIO] = 0x40;
#else
    if(RADIO_INTERFACE == 1){
        device_type[USART_RADIO] = 0x10;
    }
    else if(RADIO_INTERFACE == 2){
        device_type[USART_RADIO] = 0x20;
    }
    else if(RADIO_INTERFACE == 3){
        device_type[USART_RADIO] = 0x30;
    }
    else if(RADIO_INTERFACE == 4){
        device_type[USART_RADIO] = 0x40;
    }
    else if(RADIO_INTERFACE == 5){
        device_type[USART_RADIO] = 0x50;
    }
    else if(RADIO_INTERFACE == 6){
        device_type[USART_RADIO] = 0x60;
    }
    else { device_type[USART_RADIO] = 0x40;}
#endif

#ifndef ROBOT_MOTOR1
    device_type[MOTOR1] = 0x10;
#else
    if(ROBOT_MOTOR1 == 1){
        device_type[MOTOR1] = 0x10;
    }
    else if(ROBOT_MOTOR1 == 2){
        device_type[MOTOR1] = 0x20;
    }
    else if(ROBOT_MOTOR1 == 3){
        device_type[MOTOR1] = 0x30;
    }
    else if(ROBOT_MOTOR1 == 4){
        device_type[MOTOR1] = 0x40;
    }
    else { device_type[MOTOR1] = 0x10;}
#endif

#ifndef ROBOT_MOTOR2
    device_type[MOTOR2] = 0x20;
#else
    if(ROBOT_MOTOR2 == 1){
        device_type[MOTOR2] = 0x10;
    }
    else if(ROBOT_MOTOR2 == 2){
        device_type[MOTOR2] = 0x20;
    }
    else if(ROBOT_MOTOR2 == 3){
        device_type[MOTOR2] = 0x30;
    }
    else if(ROBOT_MOTOR2 == 4){
        device_type[MOTOR2] = 0x40;
    }
    else { device_type[MOTOR2] = 0x20;}
#endif

#ifndef ROBOT_MOTOR3
    device_type[MOTOR3] = 0x30;
#else
    if(ROBOT_MOTOR3 == 1){
        device_type[MOTOR3] = 0x10;
    }
    else if(ROBOT_MOTOR3 == 2){
        device_type[MOTOR3] = 0x20;
    }
    else if(ROBOT_MOTOR3 == 3){
        device_type[MOTOR3] = 0x30;
    }
    else if(ROBOT_MOTOR3 == 4){
        device_type[MOTOR3] = 0x40;
    }
    else { device_type[MOTOR3] = 0x30;}
#endif

#ifndef ROBOT_MOTOR4
    device_type[MOTOR4] = 0x40;
#else
    if(ROBOT_MOTOR4 == 1){
        device_type[MOTOR4] = 0x10;
    }
    else if(ROBOT_MOTOR4 == 2){
        device_type[MOTOR4] = 0x20;
    }
    else if(ROBOT_MOTOR4 == 3){
        device_type[MOTOR4] = 0x30;
    }
    else if(ROBOT_MOTOR4 == 4){
        device_type[MOTOR4] = 0x40;
    }
    else { device_type[MOTOR4] = 0x40;}
#endif

    device_type[USART_GPS] = 0x32;
    device_type[USART_SBUS] = 0x21;
    device_type[USART_DIGITAL_SERVO] = 0x32;
    device_type[USART_IMU] = 0x60;
    device_type[IIC_IMU] = 0x10;
    device_type[IIC_AT24CXX] = 0x10;
    device_type[IIC_OLED] = 0x00;
    device_type[SPI_IMU] = 0x00;
    device_type[SPI_NRF24L01] = 0x00;
    device_type[SPI_LCD] = 0x00;
    device_type[CAN_IMU] = 0x00;
    device_type[CAN_PAN_AND_TILT] = 0x00;
}

/***********************************************************************************************************************
* Function:
*
* Scope:
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
void Board::ledInit(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_3 ;
    GPIO_Init(GPIOE , &GPIO_InitStruct);

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
    GPIO_Init(GPIOC , &GPIO_InitStruct);

    setLedState(0,0); //set all led
}

void Board::setLedState(uint8_t led_id, uint8_t operation){
    if(led_id == 0){
        if(operation == 0)
        {
            setLedState(1,0);setLedState(2,0);setLedState(3,0);setLedState(4,0);
        }
        else if(operation == 1)
        {
            setLedState(1,1);setLedState(2,1);setLedState(3,1);setLedState(4,1);
        }
        else if(operation == 2)
        {
            setLedState(1,2);setLedState(2,2);setLedState(3,2);setLedState(4,2);
        }
    }
    if ( led_id == 1){
        if(operation == 0){ GPIO_SetBits(GPIOE , GPIO_Pin_2);}
        else if(operation == 1) { GPIO_ResetBits(GPIOE , GPIO_Pin_2);}
        else if(operation == 2) { GPIO_ToggleBits(GPIOE , GPIO_Pin_2);}
    }
    else if(led_id == 2){
        if(operation == 0){ GPIO_SetBits(GPIOE , GPIO_Pin_3);}
        else if(operation == 1) { GPIO_ResetBits(GPIOE , GPIO_Pin_3);}
        else if(operation == 2) { GPIO_ToggleBits(GPIOE , GPIO_Pin_3);}
    }
    else if(led_id == 3){
        if(operation == 0){ GPIO_SetBits(GPIOC , GPIO_Pin_13);}
        else if(operation == 1) { GPIO_ResetBits(GPIOC , GPIO_Pin_13);}
        else if(operation == 2) { GPIO_ToggleBits(GPIOC , GPIO_Pin_13);}
    }
    else if(led_id == 4){
        if(operation == 0){ GPIO_SetBits(GPIOE , GPIO_Pin_0);}
        else if(operation == 1) { GPIO_ResetBits(GPIOE , GPIO_Pin_0);}
        else if(operation == 2) { GPIO_ToggleBits(GPIOE , GPIO_Pin_0);}
    }
}

void Board::beepInit(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 ;
    GPIO_Init(GPIOE , &GPIO_InitStruct);
}

void Board::setBeepState(uint8_t operation)
{
    if(operation == 0) { GPIO_ResetBits(GPIOE , GPIO_Pin_1);  }
    else if(operation == 1) { GPIO_SetBits(GPIOE , GPIO_Pin_1); }
    else if(operation == 2) { GPIO_ToggleBits(GPIOE , GPIO_Pin_1); }
}

void Board::keyInit(void)
{

}

void Board::keyStateRenew(void)
{

}


/***********************************************************************************************************************
* Function:
*
* Scope:
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
void Board::motorInterfaceInit(uint8_t mode , uint8_t motor_id , float motor_pwm_t)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;

    if(mode == 0)
    {
        if( motor_id == 1 ){
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE , ENABLE);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
            GPIO_Init(GPIOE , &GPIO_InitStructure);
            GPIO_ResetBits(GPIOE , GPIO_Pin_8);
            HF_Encoder_Init(TIM2,1);   //encoder init for PID speed control
            //motor_pwm_t = 5000 , TIM1 motor pwm frequency  = (168M/2) / motor_pwm_t  = 16.8K
            HF_PWMChannel_Init(TIM1 , 1 , 2-1 , motor_pwm_t , 1);
            HF_PWMChannel_Init(TIM1 , 2 , 2-1 , motor_pwm_t , 1);
        }
        else if(motor_id == 2){
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE , ENABLE);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 ;
            GPIO_Init(GPIOE , &GPIO_InitStructure);
            GPIO_ResetBits(GPIOE , GPIO_Pin_12);
            HF_Encoder_Init(TIM3,1);
            //motor_pwm_t = 5000 , TIM1 motor pwm frequency  = (168M/2) / motor_pwm_t  = 16.8K
            HF_PWMChannel_Init(TIM1 , 3 , 2-1 , motor_pwm_t , 1);
            HF_PWMChannel_Init(TIM1 , 4 , 2-1 , motor_pwm_t , 1);
        }
        else if(motor_id == 3){
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE , ENABLE);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
            GPIO_Init(GPIOE , &GPIO_InitStructure);
            GPIO_ResetBits(GPIOE , GPIO_Pin_4);
            HF_Encoder_Init(TIM4,1);
            //motor_pwm_t = 5000 , TIM9 motor pwm frequency  = (168M/2) / motor_pwm_t = 16.8K
            HF_PWMChannel_Init(TIM9 , 1 , 2-1 , motor_pwm_t , 0);
            HF_PWMChannel_Init(TIM9 , 2 , 2-1 , motor_pwm_t , 0);
        }
        else if(motor_id == 4){
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE , ENABLE);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
            GPIO_Init(GPIOE , &GPIO_InitStructure);
            GPIO_ResetBits(GPIOE , GPIO_Pin_15);
            HF_Encoder_Init(TIM5,0);
            //motor_pwm_t = 5000 , TIM12 motor pwm frequency = (84M) / motor_pwm_t  = 16.8K
            HF_PWMChannel_Init(TIM12 , 1 , 0 , motor_pwm_t , 0);
            HF_PWMChannel_Init(TIM12 , 2 , 0 , motor_pwm_t , 0);
        }
    }
    else if (mode == 1)
    {
        if(motor_id == 1 ){
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE , ENABLE);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_11;
            GPIO_Init(GPIOE , &GPIO_InitStructure);
            GPIO_ResetBits(GPIOE , GPIO_Pin_8);
            GPIO_ResetBits(GPIOE , GPIO_Pin_11);
            HF_Encoder_Init(TIM2,1);   //encoder init for PID speed control
            //motor_pwm_t = 5000 , TIM1 motor pwm frequency  = (168M/2) / motor_pwm_t  = 16.8K
            HF_PWMChannel_Init(TIM1 , 1 , 2-1 , motor_pwm_t , 1);
        }
        else if(motor_id == 2){
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE , ENABLE);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_14 ;
            GPIO_Init(GPIOE , &GPIO_InitStructure);
            GPIO_ResetBits(GPIOE , GPIO_Pin_12);
            GPIO_ResetBits(GPIOE , GPIO_Pin_14);
            HF_Encoder_Init(TIM3,1);
            //motor_pwm_t = 5000 , TIM1 motor pwm frequency  = (168M/2) / motor_pwm_t  = 16.8K
            HF_PWMChannel_Init(TIM1 , 3 , 2-1 , motor_pwm_t , 1);
        }
        else if(motor_id == 3){
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE , ENABLE);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_6;
            GPIO_Init(GPIOE , &GPIO_InitStructure);
            GPIO_ResetBits(GPIOE , GPIO_Pin_4);
            GPIO_ResetBits(GPIOE, GPIO_Pin_6);
            HF_Encoder_Init(TIM4,1);
            //motor_pwm_t = 5000 , TIM9 motor pwm frequency  = (168M/2) / motor_pwm_t = 16.8K
            HF_PWMChannel_Init(TIM9 , 1 , 2-1 , motor_pwm_t , 0);
        }
        else if(motor_id == 4){
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE , ENABLE);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
            GPIO_Init(GPIOE , &GPIO_InitStructure);
            GPIO_ResetBits(GPIOE , GPIO_Pin_15);
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB , ENABLE);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
            GPIO_Init(GPIOB , &GPIO_InitStructure);
            GPIO_ResetBits(GPIOB , GPIO_Pin_15);
            HF_Encoder_Init(TIM5,0);
            //motor_pwm_t = 5000 , TIM12 motor pwm frequency = (84M) / motor_pwm_t  = 16.8K
            HF_PWMChannel_Init(TIM12 , 1 , 0 , motor_pwm_t , 0);
        }
    }
}


/***********************************************************************************************************************
* Function:
*
* Scope:
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
void Board::motorEnable(uint8_t mode , uint8_t motor_id)
{
    if(mode == 0)
    {
        if(motor_id == 1 ){
            GPIO_SetBits(GPIOE , GPIO_Pin_8);
        }
        else if(motor_id == 2){
            GPIO_SetBits(GPIOE , GPIO_Pin_12);
        }
        else if(motor_id == 3){
            GPIO_SetBits(GPIOE , GPIO_Pin_4);
        }
        else if(motor_id == 4){
            GPIO_SetBits(GPIOE , GPIO_Pin_15);
        }
    }
    else if(mode == 1)
    {

    }
}

void Board::motorDisable(uint8_t mode , uint8_t motor_id)
{
    if(mode == 0)
    {
        if(motor_id == 1 ){
            GPIO_ResetBits(GPIOE , GPIO_Pin_8);
        }
        else if(motor_id == 2){
            GPIO_ResetBits(GPIOE , GPIO_Pin_12);
        }
        else if(motor_id == 3){
            GPIO_ResetBits(GPIOE , GPIO_Pin_4);
        }
        else if(motor_id == 4){
            GPIO_ResetBits(GPIOE , GPIO_Pin_15);
        }
    }
    else if(mode == 1)
    {
        if(motor_id == 1 ){
            GPIO_ResetBits(GPIOE , GPIO_Pin_8);
            GPIO_ResetBits(GPIOE , GPIO_Pin_11);
        }
        else if(motor_id == 2){
            GPIO_ResetBits(GPIOE , GPIO_Pin_12);
            GPIO_ResetBits(GPIOE , GPIO_Pin_14);
        }
        else if(motor_id == 3){
            GPIO_ResetBits(GPIOE , GPIO_Pin_4);
            GPIO_ResetBits(GPIOE , GPIO_Pin_6);
        }
        else if(motor_id == 4){
            GPIO_ResetBits(GPIOE , GPIO_Pin_15);
            GPIO_ResetBits(GPIOB , GPIO_Pin_15);
        }
    }
}


/***********************************************************************************************************************
* Function:
*
* Scope:
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
void Board::motorSetPWM(uint8_t mode , uint8_t motor_id , int pwm_value)
{
    if(mode == 0)
    {
        if( motor_id ==1 ){
            if( pwm_value > 5) {
                HF_Set_PWM(TIM1 , 1 , (uint16_t)pwm_value);
                HF_Set_PWM(TIM1 , 2 , 0);
                return;
            }
            else if(pwm_value < -5){
                HF_Set_PWM(TIM1 , 1 , 0);
                HF_Set_PWM(TIM1 , 2 , (uint16_t)-pwm_value);
                return;
            }
            else{
                HF_Set_PWM(TIM1 , 1 , 0);
                HF_Set_PWM(TIM1 , 2 , 0);
                return;
            }
        }
        else if(motor_id == 2 ){
            if( pwm_value > 5) {
                HF_Set_PWM(TIM1 , 3 , (uint16_t)pwm_value);
                HF_Set_PWM(TIM1 , 4 , 0);
                return;
            }
            else if(pwm_value < -5){
                HF_Set_PWM(TIM1 , 3 , 0);
                HF_Set_PWM(TIM1 , 4 , (uint16_t)-pwm_value);
                return;
            }
            else {
                HF_Set_PWM(TIM1 , 3 , 0);
                HF_Set_PWM(TIM1 , 4 , 0);
                return;
            }
        }
        else if(motor_id ==3 ){
            if( pwm_value > 5) {
                HF_Set_PWM(TIM9 , 1 , (uint16_t)pwm_value);
                HF_Set_PWM(TIM9 , 2 , 0);
                return;
            }
            else if(pwm_value < -5){
                HF_Set_PWM(TIM9 , 1 , 0);
                HF_Set_PWM(TIM9 , 2 , (uint16_t)-pwm_value);
                return;
            }
            else{
                HF_Set_PWM(TIM9 , 1 , 0);
                HF_Set_PWM(TIM9 , 2 , 0);
                return;
            }
        }
        else if(motor_id ==4 ){
            if( pwm_value > 5) {
                HF_Set_PWM(TIM12 , 1 , (uint16_t)pwm_value);
                HF_Set_PWM(TIM12 , 2 , 0);
                return;
            }
            else if(pwm_value < -5){
                HF_Set_PWM(TIM12 , 1 , 0);
                HF_Set_PWM(TIM12 , 2 , (uint16_t)-pwm_value);
                return;
            }
            else{
                HF_Set_PWM(TIM12 , 1 , 0);
                HF_Set_PWM(TIM12 , 2 , 0);
                return;
            }
        }
    }
    else if (mode == 1)
    {
        if( motor_id ==1 ){
            if( pwm_value > 5) {
                GPIO_SetBits(GPIOE , GPIO_Pin_11);
                GPIO_ResetBits(GPIOE , GPIO_Pin_8);
                HF_Set_PWM(TIM1 , 1 , (uint16_t)pwm_value);
                return;
            }
            else if(pwm_value < -5){
                GPIO_ResetBits(GPIOE, GPIO_Pin_11);
                GPIO_SetBits(GPIOE , GPIO_Pin_8);
                HF_Set_PWM(TIM1 , 1 , (uint16_t)-pwm_value);
                return;
            }
            else{
                HF_Set_PWM(TIM1 , 1 , 0);
                return;
            }
        }
        else if(motor_id == 2 ){
            if( pwm_value > 5) {
                GPIO_ResetBits(GPIOE , GPIO_Pin_12);
                GPIO_SetBits(GPIOE , GPIO_Pin_14);
                HF_Set_PWM(TIM1 , 3 , (uint16_t)pwm_value);
                return;
            }
            else if(pwm_value < -5){
                GPIO_SetBits(GPIOE , GPIO_Pin_12);
                GPIO_ResetBits(GPIOE , GPIO_Pin_14);
                HF_Set_PWM(TIM1 , 3, (uint16_t)-pwm_value);
                return;
            }
            else {
                HF_Set_PWM(TIM1 , 3 , 0);
                return;
            }
        }

        else if(motor_id ==3 ){
            if( pwm_value > 5) {
                GPIO_ResetBits(GPIOE , GPIO_Pin_4);
                GPIO_SetBits(GPIOE , GPIO_Pin_6);
                HF_Set_PWM(TIM9 , 1 , (uint16_t)pwm_value);
                return;
            }
            else if(pwm_value < -5){
                GPIO_SetBits(GPIOE , GPIO_Pin_4);
                GPIO_ResetBits(GPIOE , GPIO_Pin_6);
                HF_Set_PWM(TIM9 , 1 , (uint16_t)-pwm_value);
                return;
            }
            else{
                HF_Set_PWM(TIM9 , 1 , 0);
                return;
            }
        }
        else if(motor_id ==4 ){
            if( pwm_value > 5) {
                GPIO_ResetBits(GPIOE , GPIO_Pin_15);
                GPIO_SetBits(GPIOB , GPIO_Pin_15);
                HF_Set_PWM(TIM12 , 1 , (uint16_t)pwm_value);
                return;
            }
            else if(pwm_value < -5){
                GPIO_SetBits(GPIOE , GPIO_Pin_15);
                GPIO_ResetBits(GPIOB , GPIO_Pin_15);
                HF_Set_PWM(TIM12 , 1 , (uint16_t)-pwm_value);
                return;
            }
            else{
                HF_Set_PWM(TIM12 , 1 , 0);
                return;
            }
        }
    }
}


/***********************************************************************************************************************
* Function:
*
* Scope:
*
* Description: sensor data
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
***********************************************************************************************************************/
float Board::getMotorEncoderCNT(uint8_t motor_id)
{
    if(motor_id == 1 ){
        return HF_Get_Encode_TIM2();
    }
    else if(motor_id == 2){
        return HF_Get_Encode_TIM3();
    }
    else if(motor_id == 3){
        return HF_Get_Encode_TIM4();
    }
    else if(motor_id == 4){
        return HF_Get_Encode_TIM5();
    }
    return 0;
}

float Board::getMotorCurrent(uint8_t motor_id)
{
    float motor_current;

    if(motor_id == 1 ){
        motor_current = 2.94f * HF_Get_ADC_Output(2);
        return motor_current;
    }
    else if(motor_id == 2){
        motor_current = 2.94f * HF_Get_ADC_Output(3);
        return motor_current;
    }
    else if(motor_id == 3){
        motor_current = 2.94f * HF_Get_ADC_Output(4);
        return motor_current;
    }
    else if(motor_id == 4){
        motor_current = 2.94f * HF_Get_ADC_Output(5);
        return motor_current;
    }
    return 0;
}


/***********************************************************************************************************************
* Function:
*
* Scope:
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
void Board::axServoInterfaceInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD , ENABLE);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOD , &GPIO_InitStructure);
}

void Board::axServoTxModel(void)
{
    GPIO_SetBits(GPIOD , GPIO_Pin_10);
}

void Board::axServoRxModel(void)
{
    GPIO_ResetBits(GPIOD , GPIO_Pin_10);
}


/***********************************************************************************************************************
* Function:
*
* Scope:
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
void Board::pwmInterfaceInit(uint8_t channel_x , uint8_t mode)
{
    uint16_t motor_pwm_t = 0;

    if(mode == 0)     //motor mode
    {
        motor_pwm_t = 5000;

        if(channel_x == 1){  //TIM1 , 8 ,9 is 168M , others is 84M
            //motor_pwm_t = 5000 , TIM1 motor pwm frequency  = (168M/2) / motor_pwm_t  = 16.8K
            HF_PWMChannel_Init(TIM1 , 1 , 2-1 , motor_pwm_t , 1);
        }
        else if(channel_x == 2){
            HF_PWMChannel_Init(TIM1 , 2 , 2-1 , motor_pwm_t , 1);
        }
        else if(channel_x == 3){
            HF_PWMChannel_Init(TIM1 , 3  , 2-1 , motor_pwm_t , 1);
        }
        else if(channel_x == 4){
            HF_PWMChannel_Init(TIM1 , 4 , 2-1 , motor_pwm_t , 1);
        }
        else if(channel_x == 5){
            HF_PWMChannel_Init(TIM9 , 1 , 2-1 , motor_pwm_t , 0);
        }
        else if(channel_x == 6){
            HF_PWMChannel_Init(TIM9 , 2 , 2-1 , motor_pwm_t , 0);
        }
        else if(channel_x == 7){
            HF_PWMChannel_Init(TIM8 , 1 , 2-1 , motor_pwm_t , 0);
        }
        else if(channel_x == 8){
            HF_PWMChannel_Init(TIM8 , 2 , 2-1 , motor_pwm_t , 0);
        }
        else if(channel_x == 9){
            //motor_pwm_t = 5000 , TIM12 motor pwm frequency = (84M) / motor_pwm_t  = 16.8K
            HF_PWMChannel_Init(TIM12 , 1 , 1-1 , motor_pwm_t , 0);
        }
        else if(channel_x == 10){
            HF_PWMChannel_Init(TIM12 , 2 , 1-1 , motor_pwm_t , 0);
        }
        else return;
    }
    else if(mode == 1)  //analog servo mode 50HZ
    {
        motor_pwm_t = 20000;

        if(channel_x == 1){   //TIM1 , 8 ,9 is 168M , others is 84M
            //motor_pwm_t = 5000 , TIM1 motor pwm frequency  = (168M/168) / motor_pwm_t  = 50HZ
            HF_PWMChannel_Init(TIM1 , 1 , 168-1 , motor_pwm_t , 1);
        }
        else if(channel_x == 2){
            HF_PWMChannel_Init(TIM1 , 2 , 168-1 , motor_pwm_t , 1);
        }
        else if(channel_x == 3){
            HF_PWMChannel_Init(TIM1 , 3  , 168-1 , motor_pwm_t , 1);
        }
        else if(channel_x == 4){
            HF_PWMChannel_Init(TIM1 , 4 , 168-1 , motor_pwm_t , 1);
        }
        else if(channel_x == 5){
            HF_PWMChannel_Init(TIM9 , 1 , 168-1 , motor_pwm_t , 0);
        }
        else if(channel_x == 6){
            HF_PWMChannel_Init(TIM9 , 2 , 168-1 , motor_pwm_t , 0);
        }
        else if(channel_x == 7){
            HF_PWMChannel_Init(TIM8 , 1 , 168-1 , motor_pwm_t , 0);
        }
        else if(channel_x == 8){
            HF_PWMChannel_Init(TIM8 , 2 , 168-1 , motor_pwm_t , 0);
        }
        else if(channel_x == 9){
            //motor_pwm_t = 5000 , TIM12 motor pwm frequency = (84M/84) / motor_pwm_t  = 50HZ
            HF_PWMChannel_Init(TIM12 , 1 , 84-1 , motor_pwm_t , 0);
        }
        else if(channel_x == 10){
            HF_PWMChannel_Init(TIM12 , 2 , 84-1 , motor_pwm_t , 0);
        }
        else return;
    }

}

void Board::setPWMInterfaceValue(uint8_t channel_x , uint16_t pwm_value)
{
    if(pwm_value <0) return;
    if(channel_x == 1){
        HF_Set_PWM(TIM1 , 1 ,  pwm_value);
    }
    else if(channel_x == 2){
        HF_Set_PWM(TIM1 , 2 , pwm_value);
    }
    else if(channel_x == 3){
        HF_Set_PWM(TIM1 , 3 , pwm_value);
    }
    else if(channel_x == 4){
        HF_Set_PWM(TIM1 , 4  , pwm_value);
    }
    else if(channel_x == 5){
        HF_Set_PWM(TIM9 , 1 , pwm_value);
    }
    else if(channel_x == 6){
        HF_Set_PWM(TIM9 , 2 , pwm_value);
    }
    else if(channel_x == 7){
        HF_Set_PWM(TIM8 , 1 , pwm_value);
    }
    else if(channel_x == 8){
        HF_Set_PWM(TIM8 , 2 , pwm_value);
    }
    else if(channel_x == 9){
        HF_Set_PWM(TIM12 , 1 , pwm_value);
    }
    else if(channel_x == 10){
        HF_Set_PWM(TIM12 , 2 , pwm_value);
    }
    else return;

}

uint16_t Board::readPWMInterfaceValue(uint8_t channel_x)
{
    uint16_t pwm_value = 0;

    if(channel_x == 1){
        pwm_value = TIM1->CCR1;
    }
    else if(channel_x == 2){
        pwm_value = TIM1->CCR2;
    }
    else if(channel_x == 3){
        pwm_value = TIM1->CCR3;
    }
    else if(channel_x == 4){
        pwm_value = TIM1->CCR4;
    }
    else if(channel_x == 5){
        pwm_value = TIM9->CCR1;
    }
    else if(channel_x == 6){
        pwm_value = TIM9->CCR2;
    }
    else if(channel_x == 7){
        pwm_value = TIM8->CCR1;
    }
    else if(channel_x == 8){
        pwm_value = TIM8->CCR2;
    }
    else if(channel_x == 9){
        pwm_value = TIM12->CCR1;
    }
    else if(channel_x == 10){
        pwm_value = TIM12->CCR2;
    }
    else return 0;

    return pwm_value;
}


/***********************************************************************************************************************
* Function:
*
* Scope:
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
void Board::adcInit(void)
{
    HF_ADC_Moder_Init(0X3E00 , 5 , 2.5f);   //ADC init
}

float Board::getADCInterfaceValue(uint8_t channel_x)
{
    return 0;
}

void Board::timerInit(void)
{
    HF_Timer_Init(TIM6 , 1000);  //timer6 init , 1000us
}

float Board::getBatteryVoltage(void)
{
    //0.33 is the loss voltage of diode
    battery_voltage_ = 0.8f * battery_voltage_+ 0.2f*(float)(0.33f + HF_Get_ADC_Output(1) * battery_proportion_);
    return battery_voltage_ ;
}

void Board::getCPUInfo(void)
{   //get ID of CPU and capacity of Flash
    chipUniqueID[0] = *(__IO u32 *)(0x1FFF7A10); // MSB
    chipUniqueID[1] = *(__IO u32 *)(0x1FFF7A14); //
    chipUniqueID[2] = *(__IO u32 *)(0x1FFF7A18); // LSB
    flashSize =  *(__IO u16 *)(0x1FFF7A22);      //Unit:KB
}
