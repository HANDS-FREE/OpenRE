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

Board board;

Board::Board(){
    cpu_temperature = cpu_usage = battery_voltage = system_time = 0;
    date_year = date_month = date_day = date_week = 0;
    time_hour = time_min = time_sec = time_ampm = 0;
    system_init = 0;
    cnt_1ms = cnt_2ms = cnt_10ms = cnt_20ms = cnt_50ms = cnt_500ms = 0;
    flashSize = 0;
    usart1_queue=Queue();
    usart2_queue=Queue();
    usart3_queue=Queue();
    usart4_queue=Queue();
    usart5_queue=Queue();

    battery_voltage_ = cpu_temperature_ = 0;
    battery_voltage_alarm_ = 10.50 ;
    battery_proportion_ = 11.00 ;
    cpu_temperature_alarm_ = 0;
    beep_model = beep_alarm_cnt_ = 0;
    board_call_5ms = board_call_20ms = board_call_1s = board_call_2s =  0 ;

#ifndef DEBUG_PRINTF_INTERFACE
    usart_debug = 0x10;
#else
    if(DEBUG_PRINTF_INTERFACE == 1){
        usart_debug = 0x10;
    }
    else if(DEBUG_PRINTF_INTERFACE == 2){
        usart_debug = 0x20;
    }
    else if(DEBUG_PRINTF_INTERFACE == 3){
        usart_debug = 0x30;
    }
    else if(DEBUG_PRINTF_INTERFACE == 4){
        usart_debug = 0x40;
    }
    else if(DEBUG_PRINTF_INTERFACE == 5){
        usart_debug = 0x50;
    }
    else if(DEBUG_PRINTF_INTERFACE == 6){
        usart_debug = 0x60;
    }
    else { usart_debug = 0x10;}
#endif

#ifndef PC_INTERFACE
    usart_pc = 0x10;
#else
    if(PC_INTERFACE == 1){
        usart_pc = 0x10;
    }
    else if(PC_INTERFACE == 2){
        usart_pc = 0x20;
    }
    else if(PC_INTERFACE == 3){
        usart_pc = 0x30;
    }
    else if(PC_INTERFACE == 4){
        usart_pc = 0x40;
    }
    else if(PC_INTERFACE == 5){
        usart_pc = 0x50;
    }
    else if(PC_INTERFACE == 6){
        usart_pc = 0x60;
    }
    else { usart_pc = 0x10;}
#endif

#ifndef RADIO_INTERFACE
    usart_radio = 0x40;
#else
    if(RADIO_INTERFACE == 1){
        usart_radio = 0x10;
    }
    else if(RADIO_INTERFACE == 2){
        usart_radio = 0x20;
    }
    else if(RADIO_INTERFACE == 3){
        usart_radio = 0x30;
    }
    else if(RADIO_INTERFACE == 4){
        usart_radio = 0x40;
    }
    else if(RADIO_INTERFACE == 5){
        usart_radio = 0x50;
    }
    else if(RADIO_INTERFACE == 6){
        usart_radio = 0x60;
    }
    else { usart_radio = 0x40;}
#endif

    usart_gps = 0x32;
    usart_sbus = 0x21;
    usart_digital_servo = 0x32;
    usart_imu = 0x60;
    iic_dev_imu = 0x10;
    iic_dev_at24cxx = 0x10;
    iic_dev_oled = 0x00;
    spi_dev_imu = 0x00;
    spi_dev_nrf24l01 = 0x00;
    spi_dev_lcd = 0x00;
    can_dev_imu = 0x00;
    can_dev_pan_and_tilt = 0x00;
}

/***********************************************************************************************************************
* Function:     void Board::boardBasicInit(void)
*
* Scope:        public
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
void Board::boardBasicInit(void)
{
    int i;
    for(i=0;i<0x8fff;i++);

    HF_System_Timer_Init();         //Initialize the measurement system
    ledInit();
    debugInterfaceInit();

    //keyInit();
    beepInit();

    //HF_RTC_Init();                //Initialize the RTC, if return 0:failed,else if return 1:succeeded
    HF_IWDG_Init();               //Initialize the independed watch dog, system will reset if not feeding dog over 1s
    HF_ADC_Moder_Init(0x0400, 1, 3.3);
    HF_Timer_Init(TIM6 , 1000);     //timer3 init , 1000us

    board.setBeepState(1);
    delay_ms(500);
    board.setBeepState(0);
    board.setLedState(0,0);
    board.setLedState(1,0);
    board.setLedState(2,0);
}

/***********************************************************************************************************************
* Function:     void Board::boardBasicCall(void)
*
* Scope:        public
*
* Description:  update the underlying hardware information,Suggest calling every 10us
*
* Arguments:
*
* Return:
*
* Cpu_Time:  stm32f1(35 us)  stm32f4+nofpu(unknow us) stm32f4+fpu(unknow us)
*
* History:
***********************************************************************************************************************/
void Board::boardBasicCall(void)   //100HZ
{
    board_call_5ms++;
    board_call_20ms++;
    board_call_1s++;
    board_call_2s++;

    keyStateRenew();
    beepStateRenew();

    if(board_call_5ms >= 5) //20HZ
    {
        board_call_5ms = 0;
        HF_IWDG_Feed(); //Feeding Dog
        system_time = HF_Get_System_Time();  //system working time (unit:us), start after power-on
        battery_voltage = getBatteryVoltage();
        cpu_usage = getCPUUsage();
        cpu_temperature = getCPUTemperature();
    }
    if(board_call_20ms >= 20) //5HZ
    {
        board_call_20ms = 0;

    }
    if(board_call_1s >= 100) //1hz
    {
        board_call_1s=0;
        //HF_Get_RTC_Time(&date_year , &date_month , &date_day , &date_week,
        //&time_hour , &time_min , &time_sec , &time_ampm);    //updating time
    }
    if(board_call_2s >= 200) //wait 2s for a stable battery_voltage
    {
        board_call_2s = 0;
        //        if( (battery_voltage > 7) && (battery_voltage < battery_voltage_alarm_) )
        //        {
        //            if(beep_model != 4)
        //            {
        //                setBeepModel(4);
        //            }
        //        }
        //        else if( battery_voltage > (battery_voltage_alarm_+0.2f) )
        //        {
        //            if(beep_model == 4)  setBeepModel(0);
        //        }
    }
}

void Board::writeFlash(uint32_t WriteAddr , uint16_t *pData_in , uint16_t NumToWrite)
{
    uint32_t  Address = FLASH_SAVE_ADDR + 2 * WriteAddr;
    STMFLASH_Write( Address , pData_in , NumToWrite);
}

void Board::readFlash(uint32_t ReadAddr , uint16_t *pData_out , uint16_t NumToRead)
{
    uint32_t  Address = FLASH_SAVE_ADDR + 2 * ReadAddr;
    STMFLASH_Read_Buf(Address, pData_out , NumToRead);
}

void Board::debugInterfaceInit(void)
{
    usartDeviceInit(USART_DEBUG , 921600);  //debug USART init
}

void Board::debugPutChar(uint8_t tx_byte)
{
    usartDeviceWriteByte(USART_DEBUG , tx_byte);
}

float Board::getBatteryVoltage(void)
{
    //0.33 is the loss voltage of diode
    battery_voltage_ = 0.8f * battery_voltage_+ 0.2f*(float)( 0.33f + HF_Get_ADC_Output(1) * battery_proportion_ ) ;
    return battery_voltage_ ;
}

float Board::getCPUUsage(void)
{
#if  SYSTEM_SUPPORT_OS > 0u

#ifdef 	OS_CRITICAL_METHOD        //support UCOSII
    cpu_usage = OSCPUUsage;
    return cpu_usage;
#endif

#ifdef 	CPU_CFG_CRITICAL_METHOD   //support UCOSIII
    cpu_usage = OSStatTaskCPUUsage;
    return cpu_usage;
#endif

#endif
    return 0;
}

float Board::getCPUTemperature(void)
{
    cpu_temperature_ = 0.8 * HF_Get_CPU_Temperature() + 0.2 * cpu_temperature_;
    return cpu_temperature_;
}

void Board::getCPUInfo(void)
{   //get ID of CPU and capacity of Flash
    chipUniqueID[0] = *(__IO u32 *)(0x1FFF7A10); // MSB
    chipUniqueID[1] = *(__IO u32 *)(0x1FFF7A14); //
    chipUniqueID[2] = *(__IO u32 *)(0x1FFF7A18); // LSB
    flashSize =  *(__IO u16 *)(0x1FFF7A22);      //Unit:KB
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
    //LED1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA , &GPIO_InitStruct);
    //LED2
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC , &GPIO_InitStruct);
    //LED3
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC , &GPIO_InitStruct);
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
void Board::setLedState(uint8_t led_id, uint8_t operation)
{
    static uint8_t flag1 = 0 , flag2 = 0 ;
    if ( led_id == 0){
        if(operation == 0) { GPIO_SetBits(GPIOA , GPIO_Pin_2);flag1 = 0;}
        if(operation == 1) { GPIO_ResetBits(GPIOA , GPIO_Pin_2);flag1 = 1;}
        else if(operation == 2) {
            flag1 = ! flag1 ;
            if (flag1 == 0)   GPIO_SetBits(GPIOA , GPIO_Pin_2);
            if (flag1 == 1)   GPIO_ResetBits(GPIOA , GPIO_Pin_2);
        }
    }

    if ( led_id == 1){
        if(operation == 0) { GPIO_SetBits(GPIOC , GPIO_Pin_13);flag2 = 0;}
        if(operation == 1) { GPIO_ResetBits(GPIOC , GPIO_Pin_13);flag2 = 1;}
        else if(operation == 2) {
            flag2 = ! flag2 ;
            if (flag2 == 0)   GPIO_SetBits(GPIOC , GPIO_Pin_13);
            if (flag2 == 1)   GPIO_ResetBits(GPIOC, GPIO_Pin_13);
        }
    }

    if ( led_id == 2){
        if(operation == 0) { GPIO_SetBits(GPIOC , GPIO_Pin_14);flag2 = 0;}
        if(operation == 1) { GPIO_ResetBits(GPIOC , GPIO_Pin_14);flag2 = 1;}
        else if(operation == 2) {
            flag2 = ! flag2 ;
            if (flag2 == 0)   GPIO_SetBits(GPIOC , GPIO_Pin_14);
            if (flag2 == 1)   GPIO_ResetBits(GPIOC, GPIO_Pin_14);
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
void Board::keyInit(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOA, ENABLE);

    //key1
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15 ;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA , &GPIO_InitStruct);
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
void Board::keyStateRenew(void){

}

uint8_t Board::getKeyState(uint8_t key_id){
    return key_state[key_id] ;
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
void Board::beepInit(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 ;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA , &GPIO_InitStruct);
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
void Board::setBeepState(uint8_t operation)
{
    static uint8_t flag = 0 ;
    if(operation == 0) { GPIO_ResetBits(GPIOA , GPIO_Pin_12);flag = 0;}
    if(operation == 1) { GPIO_SetBits(GPIOA , GPIO_Pin_12);flag = 1;}
    else if(operation == 2) {
        flag = ! flag ;
        if (flag == 0)   GPIO_ResetBits(GPIOA , GPIO_Pin_12);
        if (flag == 1)   GPIO_SetBits(GPIOA , GPIO_Pin_12);
    }
}

//model : 0 off , 1 on , 2 toggle , 3 -- 10hz , 4 -- 2hz , 5 -- 0.5hz , 6 -- 0hz
void Board::setBeepModel(uint8_t model){
    beep_model = model;
}

//100HZ
void Board::beepStateRenew(void){
    uint16_t toggle_cnt_;
    beep_alarm_cnt_ ++ ;

    if(beep_model <= 2){
        setBeepState(beep_model);
        return;
    }
    else if(beep_model == 3) toggle_cnt_ = 5;
    else if(beep_model == 4) toggle_cnt_ = 25;
    else if (beep_model == 5) toggle_cnt_ = 100;
    else if(beep_model == 6){
        setBeepState(1);
        return;
    }
    else return;

    if(beep_alarm_cnt_ >= toggle_cnt_)
    {
        beep_alarm_cnt_ = 0;
        setBeepState(2);
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
void Board::motorInterfaceInit(uint8_t mode , uint8_t motor_id , float motor_pwm_t)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    if(motor_id == 1 ){
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
        GPIO_Init(GPIOB , &GPIO_InitStructure);
        GPIO_ResetBits(GPIOB , GPIO_Pin_0);
        GPIO_ResetBits(GPIOB , GPIO_Pin_1);//Stop the motor.
        HF_Encoder_Init(TIM4,0);   //encoder init for PID speed control
        HF_PWMChannel_Init(TIM1 , 1 , 2-1 , motor_pwm_t  , 0);
    }
    else if(motor_id == 2){
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5| GPIO_Pin_4;
        GPIO_Init(GPIOC , &GPIO_InitStructure);
        GPIO_ResetBits(GPIOC , GPIO_Pin_5);
        GPIO_ResetBits(GPIOC , GPIO_Pin_4);//Stop the motor.
        HF_Encoder_Init(TIM2,1);
        HF_PWMChannel_Init(TIM1 , 2 , 2-1 , motor_pwm_t  , 0);
    }
    else if(motor_id == 3){
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6| GPIO_Pin_7;
        GPIO_Init(GPIOC , &GPIO_InitStructure);
        GPIO_ResetBits(GPIOC , GPIO_Pin_7);
        GPIO_ResetBits(GPIOC , GPIO_Pin_6);//Stop the motor.
        HF_Encoder_Init(TIM3,0);
        HF_PWMChannel_Init(TIM1 , 3 , 2-1 , motor_pwm_t  , 0);
    }
    else if(motor_id == 4){
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8| GPIO_Pin_9;
        GPIO_Init(GPIOC , &GPIO_InitStructure);
        GPIO_ResetBits(GPIOC, GPIO_Pin_8);
        GPIO_ResetBits(GPIOC , GPIO_Pin_9);//Stop the motor.
        HF_Encoder_Init(TIM5,0);
        HF_PWMChannel_Init(TIM1 , 4 , 2-1 , motor_pwm_t  , 0);
    }
    //motor_pwm_t = 5000 , TIM1 motor pwm frequency  = (168M/4) / motor_pwm_t  = 16.8K
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
    //No need to enable in the first board.
    //    if(motor_id == 1 ){
    //        GPIO_SetBits(GPIOE , GPIO_Pin_8);
    //    }
    //    else if(motor_id == 2){
    //        GPIO_SetBits(GPIOE , GPIO_Pin_12);
    //    }
    //    else if(motor_id == 3){
    //        GPIO_SetBits(GPIOE , GPIO_Pin_4);
    //    }
    //    else if(motor_id == 4){
    //        GPIO_SetBits(GPIOE , GPIO_Pin_15);
    //    }
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
void Board::motorDisable(uint8_t mode , uint8_t motor_id)
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
    if( motor_id ==1 ){
        if( pwm_value > 0) {
            GPIO_ResetBits(GPIOB , GPIO_Pin_0);
            GPIO_SetBits(GPIOB , GPIO_Pin_1);
            HF_Set_PWM(TIM1 , 1 , (uint16_t)pwm_value);
            return;
        }
        else{
            GPIO_SetBits(GPIOB , GPIO_Pin_0);
            GPIO_ResetBits(GPIOB , GPIO_Pin_1);
            HF_Set_PWM(TIM1 , 1 , (uint16_t) -pwm_value);
            return;
        }
    }
    else if(motor_id == 2 ){
        if( pwm_value > 0) {
            GPIO_ResetBits(GPIOC , GPIO_Pin_5);
            GPIO_SetBits(GPIOC , GPIO_Pin_4);
            HF_Set_PWM(TIM1 , 2 , (uint16_t)pwm_value);
            return;
        }
        else{
            GPIO_SetBits(GPIOC , GPIO_Pin_5);
            GPIO_ResetBits(GPIOC , GPIO_Pin_4);
            HF_Set_PWM(TIM1 , 2 , (uint16_t)-pwm_value);
            return;
        }
    }
    else if(motor_id == 3 ){
        if( pwm_value > 0) {
            GPIO_SetBits(GPIOC , GPIO_Pin_7);
            GPIO_ResetBits(GPIOC , GPIO_Pin_6);
            HF_Set_PWM(TIM1 , 3 , (uint16_t)pwm_value);
            return;
        }
        else{
            GPIO_ResetBits(GPIOC , GPIO_Pin_7);
            GPIO_SetBits(GPIOC , GPIO_Pin_6);
            HF_Set_PWM(TIM1 , 3 , (uint16_t)pwm_value);
            return;
        }
    }
    else if(motor_id == 4 ){
        if( pwm_value > 0) {
            GPIO_ResetBits(GPIOC , GPIO_Pin_8);
            GPIO_SetBits(GPIOC , GPIO_Pin_9);
            HF_Set_PWM(TIM1 , 4 , (uint16_t)pwm_value);
            return;
        }
        else{
            GPIO_SetBits(GPIOC , GPIO_Pin_8);
            GPIO_ResetBits(GPIOC , GPIO_Pin_9);
            HF_Set_PWM(TIM1 , 4 , (uint16_t)pwm_value);
            return;
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
float Board::getMotorCurrent(uint8_t motor_id)
{
    //    float motor_current;

    //    if(motor_id == 1 ){
    //        motor_current = 2.94f * HF_Get_ADC_Output(2);
    //        return motor_current;
    //    }
    //    else if(motor_id == 2){
    //        motor_current = 2.94f * HF_Get_ADC_Output(3);
    //        return motor_current;
    //    }
    //    else if(motor_id == 3){
    //        motor_current = 2.94f * HF_Get_ADC_Output(4);
    //        return motor_current;
    //    }
    //    else if(motor_id == 4){
    //        motor_current = 2.94f * HF_Get_ADC_Output(5);
    //        return motor_current;
    //    }

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
/*void Board::axServoInterfaceInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    HF_USART_Init(USART3 , 1000000 , 2);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOD , &GPIO_InitStructure);
}*/
void Board::axServoTxModel(void)
{
    GPIO_SetBits(GPIOD , GPIO_Pin_10);
}
void Board::axServoRxModel(void)
{
    GPIO_ResetBits(GPIOD , GPIO_Pin_10);
}
/*
void Board::axServoSendTxByte(uint8_t tx_byte)
{
    USART_SendData(USART3 , tx_byte);
    while(USART_GetFlagStatus(USART3 , USART_FLAG_TC) == RESET);
}
uint8_t Board::axServoGetRxByte(uint8_t *error)
{
    return 0;
}
*/
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
            //HF_PWMChannel_Init(TIM8 , 1 , 168-1 , motor_pwm_t , 1);
        }
        else if(channel_x == 6){
            //HF_PWMChannel_Init(TIM8 , 2 , 168-1 , motor_pwm_t , 1);
        }
        else return;
    }

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
    else if(channel_x == 3){
        HF_Set_PWM(TIM1 , 3 , (uint16_t)pwm_value);
    }
    else if(channel_x == 4){
        HF_Set_PWM(TIM1 , 4  , (uint16_t)pwm_value);
    }
    else if(channel_x == 5){
        //HF_Set_PWM(TIM8 , 1 , (uint16_t)pwm_value);
    }
    else if(channel_x == 6){
        //  HF_Set_PWM(TIM8 , 2 , (uint16_t)pwm_value);
    }
    else return;

}

uint16_t Board::readPWMInterfaceValue(uint8_t channel_x)
{
    uint16_t pwm_value;

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
        //   pwm_value = TIM8->CCR1;
    }
    else if(channel_x == 6){
        //   pwm_value = TIM8->CCR2;
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
Queue* Board::getUsartQueue(uint8_t channel)
{
    if(channel ==1) return &usart1_queue;
    else if(channel ==2)return &usart2_queue;
    else if(channel ==3)return &usart3_queue;
    else if(channel ==4)return &usart4_queue;
    else if(channel ==5)return &usart5_queue;
    else if(channel ==6)return &usart6_queue;
    else return NULL;
}

void Board::usartDeviceInit(DeviceType usart_device_type ,  uint32_t baudrate)
{
    uint8_t device_channel , device_mapping;

    if(usart_device_type == USART_DEBUG){
        device_channel = getByteHighFourBit(usart_debug);
        device_mapping = getByteLowFourBit(usart_debug);
        if(baudrate == 0) baudrate=921600;
    }
    if(usart_device_type == USART_PC){
        device_channel = getByteHighFourBit(usart_pc);
        device_mapping = getByteLowFourBit(usart_pc);
        if(baudrate == 0) baudrate=921600;
    }
    else if(usart_device_type == USART_RADIO){
        device_channel = getByteHighFourBit(usart_radio);
        device_mapping = getByteLowFourBit(usart_radio);
        if(baudrate == 0) baudrate=921600;
    }
    else if(usart_device_type == USART_GPS){
        device_channel = getByteHighFourBit(usart_gps);
        device_mapping = getByteLowFourBit(usart_gps);
        if(baudrate == 0) baudrate=9600;
    }
    else if(usart_device_type == USART_SBUS){
        device_channel = getByteHighFourBit(usart_sbus);
        device_mapping = getByteLowFourBit(usart_sbus);
        if(baudrate == 0) baudrate=100000;
    }
    else if(usart_device_type == USART_DIGITAL_SERVO){
        GPIO_InitTypeDef GPIO_InitStructure;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
        GPIO_Init(GPIOD , &GPIO_InitStructure);

        device_channel = getByteHighFourBit(usart_digital_servo);
        device_mapping = getByteLowFourBit(usart_digital_servo);
        if(baudrate == 0) baudrate=1000000;
    }
    else if(usart_device_type == USART_IMU){
        device_channel = getByteHighFourBit(usart_imu);
        device_mapping = getByteLowFourBit(usart_imu);
        if(baudrate == 0) baudrate=115200;
    }
    else {
        return;
    }

    HF_USART_Init(device_channel , baudrate , device_mapping);
}

void Board::usartDeviceWriteByte(DeviceType usart_device_type , uint8_t reg_data)
{
    uint8_t device_channel = 0 , device_mapping = 0;

    device_mapping = device_mapping;  // avoid not use warning

    if(usart_device_type == USART_PC){
        device_channel = getByteHighFourBit(usart_pc);
        device_mapping = getByteLowFourBit(usart_pc);
    }
    else if(usart_device_type == USART_RADIO){
        device_channel = getByteHighFourBit(usart_radio);
        device_mapping = getByteLowFourBit(usart_radio);
    }
    else if(usart_device_type == USART_GPS){
        device_channel = getByteHighFourBit(usart_gps);
        device_mapping = getByteLowFourBit(usart_gps);
    }
    else if(usart_device_type == USART_SBUS){
        device_channel = getByteHighFourBit(usart_sbus);
        device_mapping = getByteLowFourBit(usart_sbus);

    }
    else if(usart_device_type == USART_DIGITAL_SERVO){
        device_channel = getByteHighFourBit(usart_digital_servo);
        device_mapping = getByteLowFourBit(usart_digital_servo);
    }
    else if(usart_device_type == USART_IMU){
        device_channel = getByteHighFourBit(usart_imu);
        device_mapping = getByteLowFourBit(usart_imu);
    }
    else {
        return;
    }

    HF_USART_Put_Char(device_channel , reg_data);
}

Queue* Board::usartDeviceReadData(DeviceType usart_device_type)
{
    Queue* temp;
    uint8_t device_channel=0 , device_mapping=0;

    device_mapping = device_mapping;  // avoid not use warning

    if(usart_device_type == USART_PC){
        device_channel = getByteHighFourBit(usart_pc);
        device_mapping = getByteLowFourBit(usart_pc);
    }
    else if(usart_device_type == USART_RADIO){
        device_channel = getByteHighFourBit(usart_radio);
        device_mapping = getByteLowFourBit(usart_radio);
    }
    else if(usart_device_type == USART_GPS){
        device_channel = getByteHighFourBit(usart_gps);
        device_mapping = getByteLowFourBit(usart_gps);
    }
    else if(usart_device_type == USART_SBUS){
        device_channel = getByteHighFourBit(usart_sbus);
        device_mapping = getByteLowFourBit(usart_sbus);
    }
    else if(usart_device_type == USART_DIGITAL_SERVO){
        device_channel = getByteHighFourBit(usart_digital_servo);
        device_mapping = getByteLowFourBit(usart_digital_servo);
    }
    else if(usart_device_type == USART_IMU){
        device_channel = getByteHighFourBit(usart_imu);
        device_mapping = getByteLowFourBit(usart_imu);
    }
    else{
        temp = NULL;
    }

    temp = getUsartQueue(device_channel);
    return temp;
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
void Board::iicDeviceInit(DeviceType iic_device_type)
{
    uint8_t device_channel=0 , device_mapping=0;

    device_mapping = device_mapping; // avoid not use warning

    if(iic_device_type == IIC_IMU){
        device_channel = getByteHighFourBit(iic_dev_imu);
        device_mapping = getByteLowFourBit(iic_dev_imu);
    }
    else if(iic_device_type == IIC_AT24CXX){
        device_channel = getByteHighFourBit(iic_dev_at24cxx);
        device_mapping = getByteLowFourBit(iic_dev_at24cxx);
    }
    else if(iic_device_type == IIC_OLED){
        device_channel = getByteHighFourBit(iic_dev_oled);
        device_mapping = getByteLowFourBit(iic_dev_oled);
    }
    else {
        return;
    }

    HF_Simulat_I2C_Init( device_channel ) ;
}

void Board::iicDeviceWriteByte(DeviceType iic_device_type , uint8_t equipment_address,
                               uint8_t reg_address , uint8_t reg_data , uint8_t fastmode)
{
    uint8_t device_channel=0 , device_mapping=0;

    device_mapping = device_mapping; // avoid not use warning

    if(iic_device_type == IIC_IMU){
        device_channel = getByteHighFourBit(iic_dev_imu);
        device_mapping = getByteLowFourBit(iic_dev_imu);
    }
    else if(iic_device_type == IIC_AT24CXX){
        device_channel = getByteHighFourBit(iic_dev_at24cxx);
        device_mapping = getByteLowFourBit(iic_dev_at24cxx);
    }
    else if(iic_device_type == IIC_OLED){
        device_channel = getByteHighFourBit(iic_dev_oled);
        device_mapping = getByteLowFourBit(iic_dev_oled);
    }
    else {
        return;
    }

    HF_Simulat_I2C_Write_Byte( device_channel , equipment_address , reg_address,
                               reg_data , fastmode);
}

uint8_t Board::iicDeviceReadByte(DeviceType iic_device_type , uint8_t equipment_address,
                                 uint8_t reg_address , uint8_t fastmode)
{
    uint8_t device_channel=0 , device_mapping=0;
    uint8_t temp = 0;

    device_mapping = device_mapping; // avoid not use warning

    if(iic_device_type == IIC_IMU){
        device_channel = getByteHighFourBit(iic_dev_imu);
        device_mapping = getByteLowFourBit(iic_dev_imu);
    }
    else if(iic_device_type == IIC_AT24CXX){
        device_channel = getByteHighFourBit(iic_dev_at24cxx);
        device_mapping = getByteLowFourBit(iic_dev_at24cxx);
    }
    else if(iic_device_type == IIC_OLED){
        device_channel = getByteHighFourBit(iic_dev_oled);
        device_mapping = getByteLowFourBit(iic_dev_oled);
    }
    else {
        return 0;
    }

    temp = HF_Simulat_I2C_Read_Byte( device_channel , equipment_address,
                                     reg_address , fastmode) ;
    return temp;
}

uint8_t Board::iicDeviceWriteBuf(DeviceType iic_device_type , uint8_t equipment_address,
                                 uint8_t reg_address , uint8_t* pt_char , uint8_t size , uint8_t fastmode)
{
    uint8_t device_channel=0 , device_mapping=0;
    uint8_t temp = 0;

    device_mapping = device_mapping; // avoid not use warning

    if(iic_device_type == IIC_IMU){
        device_channel = getByteHighFourBit(iic_dev_imu);
        device_mapping = getByteLowFourBit(iic_dev_imu);
    }
    else if(iic_device_type == IIC_AT24CXX){
        device_channel = getByteHighFourBit(iic_dev_at24cxx);
        device_mapping = getByteLowFourBit(iic_dev_at24cxx);
    }
    else if(iic_device_type == IIC_OLED){
        device_channel = getByteHighFourBit(iic_dev_oled);
        device_mapping = getByteLowFourBit(iic_dev_oled);
    }
    else {
        return 0;
    }

    temp = HF_Simulat_I2C_Write_Buf( device_channel , equipment_address , reg_address , pt_char , size , fastmode);
    return temp;
}

uint8_t Board::iicDeviceReadBuf(DeviceType iic_device_type , uint8_t equipment_address,
                                uint8_t reg_address , uint8_t* pt_char , uint8_t size , uint8_t fastmode)
{
    uint8_t device_channel=0 , device_mapping=0;
    uint8_t temp = 0;

    device_mapping = device_mapping; // avoid not use warning

    if(iic_device_type == IIC_IMU){
        device_channel = getByteHighFourBit(iic_dev_imu);
        device_mapping = getByteLowFourBit(iic_dev_imu);
    }
    else if(iic_device_type == IIC_AT24CXX){
        device_channel = getByteHighFourBit(iic_dev_at24cxx);
        device_mapping = getByteLowFourBit(iic_dev_at24cxx);
    }
    else if(iic_device_type == IIC_OLED){
        device_channel = getByteHighFourBit(iic_dev_oled);
        device_mapping = getByteLowFourBit(iic_dev_oled);
    }
    else {
        return 0;
    }

    temp = HF_Simulat_I2C_Read_Buf( device_channel , equipment_address , reg_address,
                                    pt_char , size , fastmode);
    return temp;
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

void Board::spiDeviceInit(DeviceType spi_device_type)
{
    uint8_t device_channel=0 , device_mapping=0;

    if(spi_device_type == SPI_IMU){
        device_channel = getByteHighFourBit(spi_dev_imu);
        device_mapping = getByteLowFourBit(spi_dev_imu);
    }
    else if(spi_device_type == SPI_NRF24L01){
        device_channel = getByteHighFourBit(spi_dev_nrf24l01);
        device_mapping = getByteLowFourBit(spi_dev_nrf24l01);
    }
    else if(spi_device_type == SPI_LCD){
        device_channel = getByteHighFourBit(spi_dev_lcd);
        device_mapping = getByteLowFourBit(spi_dev_lcd);
    }
    else {
        return;
    }

    HF_SPI_Init(device_channel , device_mapping);
}

uint8_t Board::spiDeviceReadWriteByte(DeviceType spi_device_type , uint8_t byte)
{
    uint8_t device_channel = 0 , device_mapping = 0;

    device_mapping = device_mapping; // avoid not use warning

    if(spi_device_type == SPI_IMU){
        device_channel = getByteHighFourBit(spi_dev_imu);
        device_mapping = getByteLowFourBit(spi_dev_imu);
    }
    else if(spi_device_type == SPI_NRF24L01){
        device_channel = getByteHighFourBit(spi_dev_nrf24l01);
        device_mapping = getByteLowFourBit(spi_dev_nrf24l01);
    }
    else if(spi_device_type == SPI_LCD){
        device_channel = getByteHighFourBit(spi_dev_lcd);
        device_mapping = getByteLowFourBit(spi_dev_lcd);
    }
    else {
        return 0;
    }

    return  HF_SPI_ReadWriteByte(device_channel ,  byte);
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
void Board::canDeviceInit(DeviceType can_device_type)
{
    uint8_t device_channel=0 , device_mapping=0;

    if(can_device_type == CAN_IMU){
        device_channel = getByteHighFourBit(can_dev_imu);
        device_mapping = getByteLowFourBit(can_dev_imu);
    }
    if(can_device_type == CAN_PAN_AND_TILT){
        device_channel = getByteHighFourBit(can_dev_pan_and_tilt);
        device_mapping = getByteLowFourBit(can_dev_pan_and_tilt);
    }
    else{
        return;
    }

    HF_CAN_Init(device_channel , device_mapping);
}

void Board::canDeviceSendMessage(DeviceType can_device_type , uint8_t sender_id, uint8_t receiver_id,
                                 uint8_t *txbuf, uint8_t length)
{
    uint8_t device_channel = 0 , device_mapping = 0;

    device_mapping = device_mapping; // avoid not use warning

    if(can_device_type == CAN_IMU){
        device_channel = getByteHighFourBit(can_dev_imu);
        device_mapping = getByteLowFourBit(can_dev_imu);
    }
    if(can_device_type == CAN_PAN_AND_TILT){
        device_channel = getByteHighFourBit(can_dev_pan_and_tilt);
        device_mapping = getByteLowFourBit(can_dev_pan_and_tilt);
    }
    else{
        return;
    }

    HF_CANTX_Message(device_channel , sender_id , receiver_id , txbuf , length);
}

