/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: BSP_TOP.c
* Contact:  QQ Exchange Group -- 521037187
* Version:  V2.0
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
    battery_voltage_alarm_ = 10.50 ;
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
    if(PC_INTERFACE == 4){
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

    device_type[USART_GPS] = 0x32;
    device_type[USART_SBUS] = 0x21;
    device_type[USART_DIGITAL_SERVO] = 0x32;
    device_type[USART_IMU] = 0x50;
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
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIOA , &GPIO_InitStruct);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
    GPIO_Init(GPIOC , &GPIO_InitStruct);
}

void Board::setLedState(uint8_t led_id, uint8_t operation)
{
    if ( led_id == 0){
        if(operation == 0) { GPIO_SetBits(GPIOA , GPIO_Pin_2);}
        else if(operation == 1) { GPIO_ResetBits(GPIOA , GPIO_Pin_2);}
        else if(operation == 2){GPIO_ToggleBits(GPIOA , GPIO_Pin_2);}
    }

    if ( led_id == 1){
        if(operation == 0) { GPIO_SetBits(GPIOC , GPIO_Pin_13);}
        else if(operation == 1) { GPIO_ResetBits(GPIOC , GPIO_Pin_13);}
        else if(operation == 2) { GPIO_ToggleBits(GPIOC , GPIO_Pin_13);}
    }

    if ( led_id == 2){
        if(operation == 0) { GPIO_SetBits(GPIOC , GPIO_Pin_14);}
        if(operation == 1) { GPIO_ResetBits(GPIOC , GPIO_Pin_14);}
        else if(operation == 2) { GPIO_ToggleBits(GPIOC , GPIO_Pin_14);}
    }
}

void Board::beepInit(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 ;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA , &GPIO_InitStruct);
}

void Board::setBeepState(uint8_t operation)
{
    if(operation == 0) { GPIO_ResetBits(GPIOA , GPIO_Pin_12);}
    else if(operation == 1) { GPIO_SetBits(GPIOA , GPIO_Pin_12);}
    else if(operation == 2) { GPIO_SetBits(GPIOA , GPIO_Pin_12);}
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
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    if(mode == 0)
    {

    }
    else if(mode == 1)
    {
        if(motor_id == 1 ){
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
            GPIO_Init(GPIOB , &GPIO_InitStructure);
            GPIO_ResetBits(GPIOB , GPIO_Pin_0);
            GPIO_ResetBits(GPIOB , GPIO_Pin_1);//Stop the motor.
            HF_Encoder_Init(TIM4,0);   //encoder init for PID speed control
            // motor_pwm_t = 5000 , TIM1 motor pwm frequency  = (72M) / motor_pwm_t  = 14.4K
            HF_PWMChannel_Init(TIM1 , 1 , 0 , motor_pwm_t  , 0);
        }
        else if(motor_id == 2){
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5| GPIO_Pin_4;
            GPIO_Init(GPIOC , &GPIO_InitStructure);
            GPIO_ResetBits(GPIOC , GPIO_Pin_5);
            GPIO_ResetBits(GPIOC , GPIO_Pin_4);//Stop the motor.
            HF_Encoder_Init(TIM2,1);
            HF_PWMChannel_Init(TIM1 , 2 , 0 , motor_pwm_t  , 0);
        }
        else if(motor_id == 3){
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6| GPIO_Pin_7;
            GPIO_Init(GPIOC , &GPIO_InitStructure);
            GPIO_ResetBits(GPIOC , GPIO_Pin_7);
            GPIO_ResetBits(GPIOC , GPIO_Pin_6);//Stop the motor.
            HF_Encoder_Init(TIM3,0);
            HF_PWMChannel_Init(TIM1 , 3 , 0 , motor_pwm_t  , 0);
        }
        else if(motor_id == 4){
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8| GPIO_Pin_9;
            GPIO_Init(GPIOC , &GPIO_InitStructure);
            GPIO_ResetBits(GPIOC, GPIO_Pin_8);
            GPIO_ResetBits(GPIOC , GPIO_Pin_9);//Stop the motor.
            HF_Encoder_Init(TIM5,0);
            HF_PWMChannel_Init(TIM1 , 4 , 0 , motor_pwm_t  , 0);
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

    }
    else if(mode == 1)
    {

    }
}

void Board::motorDisable(uint8_t mode , uint8_t motor_id)
{
    if(mode == 0)
    {

    }
    else if(mode == 1)
    {
        //The motors are always enable in the first board.
        if(motor_id == 1 ){
            GPIO_ResetBits(GPIOB , GPIO_Pin_0);
            GPIO_ResetBits(GPIOB , GPIO_Pin_1);//Stop the motor.
        }
        else if(motor_id == 2){
            GPIO_ResetBits(GPIOC , GPIO_Pin_5);
            GPIO_ResetBits(GPIOC , GPIO_Pin_4);//Stop the motor.
        }
        else if(motor_id == 3){
            GPIO_ResetBits(GPIOC , GPIO_Pin_7);
            GPIO_ResetBits(GPIOC , GPIO_Pin_6);//Stop the motor.
        }
        else if(motor_id == 4){
            GPIO_ResetBits(GPIOE , GPIO_Pin_8);
            GPIO_ResetBits(GPIOE , GPIO_Pin_9);//Stop the motor.
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

    }
    else if(mode == 1)
    {
        if( motor_id ==1 ){
            if( pwm_value > 5) {
                GPIO_ResetBits(GPIOB , GPIO_Pin_0);
                GPIO_SetBits(GPIOB , GPIO_Pin_1);
                HF_Set_PWM(TIM1 , 1 , (uint16_t)pwm_value);
                return;
            }
            else if(pwm_value < -5){
                GPIO_SetBits(GPIOB , GPIO_Pin_0);
                GPIO_ResetBits(GPIOB , GPIO_Pin_1);
                HF_Set_PWM(TIM1 , 1 , (uint16_t) -pwm_value);
                return;
            }
            else{
                motorDisable(1,1);
                return;
            }
        }
        else if(motor_id == 2 ){
            if( pwm_value > 5) {
                GPIO_ResetBits(GPIOC , GPIO_Pin_5);
                GPIO_SetBits(GPIOC , GPIO_Pin_4);
                HF_Set_PWM(TIM1 , 2 , (uint16_t)pwm_value);
                return;
            }
            else if(pwm_value < -5){
                GPIO_SetBits(GPIOC , GPIO_Pin_5);
                GPIO_ResetBits(GPIOC , GPIO_Pin_4);
                HF_Set_PWM(TIM1 , 2 , (uint16_t)-pwm_value);
                return;
            }
            else{
                motorDisable(1,2);
                return;
            }
        }
        else if(motor_id == 3 ){
            if( pwm_value > 5) {
                GPIO_SetBits(GPIOC , GPIO_Pin_7);
                GPIO_ResetBits(GPIOC , GPIO_Pin_6);
                HF_Set_PWM(TIM1 , 3 , (uint16_t)pwm_value);
                return;
            }
            else if(pwm_value < -5){
                GPIO_ResetBits(GPIOC , GPIO_Pin_7);
                GPIO_SetBits(GPIOC , GPIO_Pin_6);
                HF_Set_PWM(TIM1 , 3 , (uint16_t)pwm_value);
                return;
            }
            else{
                motorDisable(1,3);
                return;
            }
        }
        else if(motor_id == 4 ){
            if( pwm_value > 5) {
                GPIO_ResetBits(GPIOC , GPIO_Pin_8);
                GPIO_SetBits(GPIOC , GPIO_Pin_9);
                HF_Set_PWM(TIM1 , 4 , (uint16_t)pwm_value);
                return;
            }
            else if(pwm_value < -5){
                GPIO_SetBits(GPIOC , GPIO_Pin_8);
                GPIO_ResetBits(GPIOC , GPIO_Pin_9);
                HF_Set_PWM(TIM1 , 4 , (uint16_t)pwm_value);
                return;
            }
            else{
                motorDisable(1,4);
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
float Board::getMotorEncoderCNT(uint8_t motor_id)
{
    if(motor_id == 1 ){
        return HF_Get_Encode_TIM4();
    }
    else if(motor_id == 2){
        return HF_Get_Encode_TIM2();
    }
    else if(motor_id == 3){
        return HF_Get_Encode_TIM3();
    }
    else if(motor_id == 4){
        return HF_Get_Encode_TIM5();
    }
    return 0;
}

float Board::getMotorCurrent(uint8_t motor_id)
{
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

}

void Board::axServoTxModel(void)
{

}

void Board::axServoRxModel(void)
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
void Board::pwmInterfaceInit(uint8_t channel_x , uint8_t mode)
{
    uint16_t motor_pwm_t = 0;

    if(mode == 0)     //motor mode
    {
        motor_pwm_t = 5000;

        if(channel_x == 1){
            // motor_pwm_t = 5000 , TIM1 motor pwm frequency  = (72M) / motor_pwm_t  = 14.4K
            HF_PWMChannel_Init(TIM1 , 1 , 0 , motor_pwm_t , 1);
        }
        else if(channel_x == 2){
            HF_PWMChannel_Init(TIM1 , 2 , 0 , motor_pwm_t , 1);
        }
    }
    else if(mode == 1)  //analog servo mode 50HZ
    {
        motor_pwm_t = 20000;

        if(channel_x == 1){
            //motor_pwm_t = 5000 , TIM1 motor pwm frequency  = (72M/72) / motor_pwm_t  = 50HZ
            HF_PWMChannel_Init(TIM1 , 1 , 72-1 , motor_pwm_t , 1);
        }
        else if(channel_x == 2){
            HF_PWMChannel_Init(TIM1 , 2 , 72-1 , motor_pwm_t , 1);
        }
    }
    return;
}

void Board::setPWMInterfaceValue(uint8_t channel_x , uint16_t pwm_value)
{
    if(pwm_value <0) return;
    else if(channel_x == 1){
        HF_Set_PWM(TIM1 , 1 ,  (uint16_t)pwm_value);
    }
    else if(channel_x == 2){
        HF_Set_PWM(TIM1 , 2 , (uint16_t)pwm_value);
    }
    return;
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
    HF_ADC_Moder_Init(0x0400, 1, 3.3);  //ADC init
}

void Board::timerInit(void)
{
    HF_Timer_Init(TIM6 , 1000);  //timer6 init , 1000us
}

float Board::getBatteryVoltage(void)
{
    //0.33 is the loss voltage of diode
    battery_voltage_ = 0.8f * battery_voltage_+ 0.2f*(float)(0.33f + HF_Get_ADC_Output(1) * battery_proportion_ );
    return battery_voltage_ ;
}

void Board::getCPUInfo(void)
{
    //get ID of CPU and capacity of Flash
    chipUniqueID[0]  = *(__IO u32 *)(0X1FFFF7F0); // MSB
    chipUniqueID[1] = *(__IO u32 *)(0X1FFFF7EC);  //
    chipUniqueID[2] = *(__IO u32 *)(0X1FFFF7E8);  // LSB
    flashSize =  *(__IO u16 *)(0X1FFFF7E0);       //Unit:KB
}
