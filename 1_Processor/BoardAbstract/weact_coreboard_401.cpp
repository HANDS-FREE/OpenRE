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
    battery_series_ = 3;
    battery_voltage_alarm_ = 10.20 ;
    battery_proportion_ = 11.00 ;

#ifndef DEBUG_PRINTF_INTERFACE
    device_type[USART_DEBUG] = 0x11;
#else
    if(DEBUG_PRINTF_INTERFACE == 1){
        device_type[USART_DEBUG] = 0x11;
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
    device_type[USART_PC] = 0x11;
#else
    if(PC_INTERFACE == 1){
        device_type[USART_PC] = 0x11;
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
        device_type[USART_RADIO] = 0x11;
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

    device_type[USART_GPS] = 0x00;
    device_type[USART_SBUS] = 0x00;
    device_type[USART_DIGITAL_SERVO] = 0x00;
    device_type[USART_IMU] = 0x00;
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
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
    GPIO_Init(GPIOC , &GPIO_InitStruct);

    setLedState(0,0); //set all led
}

void Board::setLedState(uint8_t led_id, uint8_t operation){
    if(led_id == 0){
        if(operation == 0)
        {
            setLedState(1,0);
        }
        else if(operation == 1)
        {
            setLedState(1,1);
        }
        else if(operation == 2)
        {
            setLedState(1,2);
        }
    }
    if ( led_id == 1){
        if(operation == 0){ GPIO_SetBits(GPIOC , GPIO_Pin_13);}
        else if(operation == 1) { GPIO_ResetBits(GPIOC , GPIO_Pin_13);}
        else if(operation == 2) { GPIO_ToggleBits(GPIOC , GPIO_Pin_13);}
    }
}

void Board::beepInit(void)
{

}

void Board::setBeepState(uint8_t operation)
{

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

}

void Board::motorDisable(uint8_t mode , uint8_t motor_id)
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
void Board::motorSetPWM(uint8_t mode , uint8_t motor_id , int pwm_value)
{

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

}

void Board::setPWMInterfaceValue(uint8_t channel_x , uint16_t pwm_value)
{

}

uint16_t Board::readPWMInterfaceValue(uint8_t channel_x)
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
void Board::adcInit(void)
{
    HF_ADC_Moder_Init(0 , 0 , 3.3f);   //ADC init
}

float Board::getADCInterfaceValue(uint8_t channel_x)
{
    return 0;
}

void Board::timerInit(void)
{
    HF_Timer_Init(TIM5 , 1000);  //timer6 init , 1000us
}

float Board::getBatteryVoltage(void)
{
    return 0;
}

void Board::getCPUInfo(void)
{   //get ID of CPU and capacity of Flash
    chipUniqueID[0] = *(__IO u32 *)(0x1FFF7A10); // MSB
    chipUniqueID[1] = *(__IO u32 *)(0x1FFF7A14); //
    chipUniqueID[2] = *(__IO u32 *)(0x1FFF7A18); // LSB
    flashSize =  *(__IO u16 *)(0x1FFF7A22);      //Unit:KB
}
