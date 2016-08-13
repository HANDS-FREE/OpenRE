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

#ifdef CONTROL_UNIT_V2

Board board;

Board::Board(){
    cnt_1ms = 0;
    cnt_2ms = 0;
    cnt_5ms = 0;
    cnt_10ms = 0;
    cnt_20ms = 0;
    cnt_50ms  = 0;
    cnt_500ms = 0 ;
    board_call_i = 0 ;
    board_call_j = 0 ;
    board_call_k = 0 ;
    battery_voltage_  = 0;
    battery_voltage_alarm_ =0 ;
    battery_proportion_ =0 ;
    temperature_ = 0;
    uint16_t beep_alarm_cnt_ ;
    battery_voltage_alarm_ = 10.00 ;
    battery_proportion_ = 11.00 ;
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

    delay_init();
    HF_System_Timer_Init();         //Initialize the measurement systemm
    debugInterfaceInit();

    ledInit();
    //keyInit();
    beepInit();

    //HF_RTC_Init();                //Initialize the RTC, if return 0:failed,else if return 1:succeeded
    //HF_IWDG_Init();               //Initialize the independed watch dog, system will reset if not feeding dog over 1s
    HF_ADC_Moder_Init(0X3E00 , 5);  //ADC init
    HF_Timer_Init(TIM6 , 1000);     //timer6 init , 1000us

    setBeepState(1);
    delay_ms(500);
    setBeepState(0);
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
    board_call_i++;
    board_call_j++;
    board_call_k++;

    keyStateRenew();

    if(board_call_i >= 20) //5HZ
    {
        board_call_i=0;
        //HF_IWDG_Feed(); //Feeding Dog
        system_time = HF_Get_System_Time();  //system working time (unit:us), start after power-on
        if(board_call_k > 500) //wait 5s for a stable battery_voltage
        {
            board_call_k = 500;

            cpu_temperature = getCPUTemperature();
            battery_voltage = getBatteryVoltage();
            if( (battery_voltage > 7) && (battery_voltage < battery_voltage_alarm_) )
            {
                beep_alarm_cnt_++;
                if(beep_alarm_cnt_ >=20)
                {
                    setBeepState(2);
                }
            }
            else if( battery_voltage > (battery_voltage_alarm_+0.2f) )
            {
                beep_alarm_cnt_ =0;
                setBeepState(0);
            }
        }

    }
    if(board_call_j >= 100) //1hz
    {
        board_call_j=0;
        //HF_RTC_Time_Renew(); //updating time
    }


}

void Board::debugInterfaceInit(void)
{
    HF_USART_Init(USART1 , 921600 , 0);  //debug USART init
}

void Board::debugPutChar(uint8_t txbyte_)
{
    USART_SendData(USART1 , txbyte_);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
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
    temperature_ = 0.8f*temperature_ + 0.2f*( (HF_Get_ADC_Output(6) - 0.76f ) / 0.0025f +25 ) ;
    return temperature_;
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
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_3 ;
    GPIO_Init(GPIOE , &GPIO_InitStruct);

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15 ;
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
void Board::setLedState(uint8_t led_id, uint8_t operation){
    if ( led_id == 0){
        if(operation == 0){ GPIO_SetBits(GPIOE , GPIO_Pin_2);}
        else if(operation == 1) { GPIO_ResetBits(GPIOE , GPIO_Pin_2);}
        else if(operation == 2) { GPIO_ToggleBits(GPIOE , GPIO_Pin_2);}
    }
    else if(led_id == 1){
        if(operation == 0){ GPIO_SetBits(GPIOE , GPIO_Pin_3);}
        else if(operation == 1) { GPIO_ResetBits(GPIOE , GPIO_Pin_3);}
        else if(operation == 2) { GPIO_ToggleBits(GPIOE , GPIO_Pin_3);}
    }
    else if(led_id == 2){
        if(operation == 0){ GPIO_SetBits(GPIOC , GPIO_Pin_13);}
        else if(operation == 1) { GPIO_ResetBits(GPIOC , GPIO_Pin_13);}
        else if(operation == 2) { GPIO_ToggleBits(GPIOC , GPIO_Pin_13);}
    }
    else if(led_id == 3){
        if(operation == 0){ GPIO_SetBits(GPIOE , GPIO_Pin_0);}
        else if(operation == 1) { GPIO_ResetBits(GPIOE , GPIO_Pin_0);}
        else if(operation == 2) { GPIO_ToggleBits(GPIOE , GPIO_Pin_0);}
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
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 ;
    GPIO_Init(GPIOE , &GPIO_InitStruct);
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
    if(operation == 0) { GPIO_ResetBits(GPIOE , GPIO_Pin_1);  }
    else if(operation == 1) { GPIO_SetBits(GPIOE , GPIO_Pin_1); }
    else if(operation == 2) { GPIO_ToggleBits(GPIOE , GPIO_Pin_1); }
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
void Board::motorInterfaceInit(uint8_t motor_id , float motor_pwm_T)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;

    if(motor_id == 1 ){
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE , ENABLE);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
        GPIO_Init(GPIOE , &GPIO_InitStructure);
        GPIO_ResetBits(GPIOE , GPIO_Pin_8);
        HF_Encoder_Init(TIM2,1);   //encoder init for PID speed control
    }
    else if(motor_id == 2){
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE , ENABLE);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 ;
        GPIO_Init(GPIOE , &GPIO_InitStructure);
        GPIO_ResetBits(GPIOE , GPIO_Pin_12);
        HF_Encoder_Init(TIM3,1);
    }
    else if(motor_id == 3){
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE , ENABLE);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
        GPIO_Init(GPIOE , &GPIO_InitStructure);
        GPIO_ResetBits(GPIOE , GPIO_Pin_4);
        HF_Encoder_Init(TIM4,1);
    }
    else if(motor_id == 4){
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE , ENABLE);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
        GPIO_Init(GPIOE , &GPIO_InitStructure);
        GPIO_ResetBits(GPIOE , GPIO_Pin_14);
        HF_Encoder_Init(TIM5,0);
    }

    //motor_pwm_T = 5000 , TIM1 motor pwm frequency  = (168M/4) / motor_pwm_T  = 16.8K
    HF_PWMOut_Init(TIM1 , 2-1 , motor_pwm_T , 1);

    //motor_pwm_T = 5000 , TIM9 motor pwm frequency  = (168M/4) / motor_pwm_T = 16.8K
    HF_PWMOut_Init(TIM9 , 2-1 , motor_pwm_T , 0);

    //motor_pwm_T = 5000 , TIM12 motor pwm frequency = (84M/2) / motor_pwm_T  = 16.8K
    HF_PWMOut_Init(TIM12 , 0 , motor_pwm_T , 0);
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
void Board::motorEnable(uint8_t motor_id)
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
        GPIO_SetBits(GPIOE , GPIO_Pin_14);
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
void Board::motorDisable(uint8_t motor_id)
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
        GPIO_ResetBits(GPIOE , GPIO_Pin_14);
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
    float motor_current;

    if(motor_id == 1 ){
        motor_current = HF_Get_ADC_Output(2);
        return motor_current;
    }
    else if(motor_id == 2){
        motor_current = HF_Get_ADC_Output(3);
        return motor_current;
    }
    else if(motor_id == 3){
        motor_current = HF_Get_ADC_Output(4);
        return motor_current;
    }
    else if(motor_id == 4){
        motor_current = HF_Get_ADC_Output(5);
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
void Board::motorSetPWM(uint8_t motor_id , int pwm_value)
{
    if( motor_id ==1 ){
        if( pwm_value > 0) {
            HF_PWM_Set_TIM1_CCR1((unsigned short int)pwm_value);
            HF_PWM_Set_TIM1_CCR2(0);
            return;
        }
        else{
            HF_PWM_Set_TIM1_CCR1(0);
            HF_PWM_Set_TIM1_CCR2((unsigned short int)-pwm_value);
            return;
        }
    }
    else if(motor_id == 2 ){
        if( pwm_value > 0) {
            HF_PWM_Set_TIM1_CCR3((unsigned short int)pwm_value);
            HF_PWM_Set_TIM1_CCR4(0);
            return;
        }
        else{
            HF_PWM_Set_TIM1_CCR3(0);
            HF_PWM_Set_TIM1_CCR4((unsigned short int)-pwm_value);
            return;
        }
    }
    else if(motor_id ==3 ){
        if( pwm_value > 0) {
            HF_PWM_Set_TIM9_CCR1((unsigned short int)pwm_value);
            HF_PWM_Set_TIM9_CCR2(0);
            return;
        }
        else{
            HF_PWM_Set_TIM9_CCR1(0);
            HF_PWM_Set_TIM9_CCR2((unsigned short int)-pwm_value);
            return;
        }
    }
    else if(motor_id ==4 ){
        if( pwm_value > 0) {
            HF_PWM_Set_TIM12_CCR1((unsigned short int)pwm_value);
            HF_PWM_Set_TIM12_CCR2(0);
            return;
        }
        else{
            HF_PWM_Set_TIM12_CCR1(0);
            HF_PWM_Set_TIM12_CCR2((unsigned short int)-pwm_value);
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
void Board::axServoInterfaceInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    HF_USART_Init(USART3 , 1000000 , 2);

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
void Board::axServoSendTxByte(uint8_t tx_byte)
{
    USART_SendData(USART3 , tx_byte);
    while(USART_GetFlagStatus(USART3 , USART_FLAG_TC) == RESET);
}
uint8_t Board::axServoGetRxByte(uint8_t *error)
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
void Board::sbusInterfaceInit(void)
{
    HF_USART_Init(USART2,100000,1);
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
void Board::imuI2CInit(void)
{
    HF_Simulat_I2C_Init(1);
}

void Board::imuI2CWriteByte(uint8_t equipment_address , uint8_t reg_address ,
                            uint8_t reg_data , uint8_t fastmode)
{
    HF_Simulat_I2C_Write_Byte( 1 , equipment_address , reg_address , reg_data , fastmode);
}


uint8_t Board::imuI2CReadByte(uint8_t equipment_address , uint8_t reg_address , uint8_t fastmode)
{
    return HF_Simulat_I2C_Read_Byte( 1 , equipment_address , reg_address , fastmode) ;
}

uint8_t Board::imuI2CWriteBuf(uint8_t equipment_address,uint8_t reg_address,
                           uint8_t* pt_char , uint8_t size , uint8_t fastmode)
{
    uint8_t temp;
    temp = HF_Simulat_I2C_Write_Buf( 1 , equipment_address , reg_address , pt_char , size , fastmode);
    return temp;
}

uint8_t Board::imuI2CReadBuf(uint8_t equipment_address,uint8_t reg_address,
                          uint8_t * pt_char , uint8_t size , uint8_t fastmode)
{
    uint8_t temp;
    temp = HF_Simulat_I2C_Read_Buf( 1 , equipment_address , reg_address , pt_char , size , fastmode);
    return temp;
}

void Board::gpsInterfaceInit(void)
{
    HF_USART_Init(USART3 , 9600 , 2);
}
void Board::gpsSendTxByte(uint8_t tx_byte)
{
    while(USART_GetFlagStatus(USART3 , USART_FLAG_TC)==RESET);
    USART_SendData(USART3 , tx_byte);
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
void Board::eepromI2CInit(void)
{
    HF_Simulat_I2C_Init(1);
}

void Board::eepromI2CWriteByte(uint8_t equipment_address , uint8_t reg_address ,
                               uint8_t reg_data , uint8_t fastmode)
{
    HF_Simulat_I2C_Write_Byte( 1 , equipment_address , reg_address , reg_data , fastmode);
}

uint8_t Board::eepromI2CReadByte(uint8_t equipment_address , uint8_t reg_address , uint8_t fastmode)
{
    return HF_Simulat_I2C_Read_Byte( 1 , equipment_address , reg_address , fastmode) ;
}

uint8_t Board::eepromI2CWriteBuf(uint8_t equipment_address,uint8_t reg_address,
                              uint8_t* pt_char , uint8_t size , uint8_t fastmode)
{
    uint8_t temp;
    temp = HF_Simulat_I2C_Write_Buf( 1 , equipment_address , reg_address , pt_char , size , fastmode);
    return temp;
}

uint8_t Board::eepromI2CReadBuf(uint8_t equipment_address,uint8_t reg_address,
                             uint8_t * pt_char , uint8_t size , uint8_t fastmode)
{
    uint8_t temp;
    temp = HF_Simulat_I2C_Read_Buf( 1 , equipment_address , reg_address , pt_char , size , fastmode);
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
void Board::extendI2CInit(void)
{
    HF_Simulat_I2C_Init(2);
}

void Board::extendI2CWriteByte(uint8_t equipment_address , uint8_t reg_address ,
                               uint8_t reg_data , uint8_t fastmode)
{
    HF_Simulat_I2C_Write_Byte( 2 , equipment_address , reg_address , reg_data , fastmode);
}

uint8_t Board::extendI2CReadByte(uint8_t equipment_address , uint8_t reg_address , uint8_t fastmode)
{
    return HF_Simulat_I2C_Read_Byte( 2 , equipment_address , reg_address , fastmode) ;
}

uint8_t Board::extendI2CWriteBuf(uint8_t equipment_address,uint8_t reg_address,
                              uint8_t* pt_char , uint8_t size , uint8_t fastmode)
{
    uint8_t temp;
    temp = HF_Simulat_I2C_Write_Buf( 2 , equipment_address , reg_address , pt_char , size , fastmode);
    return temp;
}

uint8_t Board::extendI2CReadBuf(uint8_t equipment_address,uint8_t reg_address,
                             uint8_t * pt_char , uint8_t size , uint8_t fastmode)
{
    uint8_t temp;
    temp = HF_Simulat_I2C_Read_Buf( 2 , equipment_address , reg_address , pt_char , size , fastmode);
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
void Board::pwmInterfaceInit(uint8_t mode , float pwm_t)
{
    if(mode == 1)
    {
        //motor_pwm_T = 5000 , TIM1 motor pwm frequency  = (168M/4) / motor_pwm_T  = 16.8K
        HF_PWMOut_Init(TIM1 , 2-1 , pwm_t , 1);

        //motor_pwm_T = 5000 , TIM9 motor pwm frequency  = (168M/4) / motor_pwm_T = 16.8K
        HF_PWMOut_Init(TIM9 , 2-1 , pwm_t , 0);

        //motor_pwm_T = 5000 , TIM12 motor pwm frequency = (84M/2) / motor_pwm_T  = 16.8K
        HF_PWMOut_Init(TIM12 , 0 , pwm_t , 0);
    }
    else if(mode == 2)
    {
        //motor_pwm_T = 5000 , TIM1 motor pwm frequency  = (168M/4) / motor_pwm_T  = 16.8K
        HF_PWMOut_Init(TIM1 , 168-1 , 20000 , 1);

        //motor_pwm_T = 5000 , TIM9 motor pwm frequency  = (168M/4) / motor_pwm_T = 16.8K
        HF_PWMOut_Init(TIM9 , 168-1 , 20000 , 0);

        //motor_pwm_T = 5000 , TIM12 motor pwm frequency = (84M/2) / motor_pwm_T  = 16.8K
        HF_PWMOut_Init(TIM12 , 84-1 , 20000 , 0);
    }
}

void Board::setPWMValue(uint8_t channel_x , float pwm_value)
{
    if(pwm_value <0) return;
    if(channel_x == 1){
        HF_PWM_Set_TIM1_CCR1((unsigned short int)pwm_value);
    }
    if(channel_x == 2){
        HF_PWM_Set_TIM1_CCR2((unsigned short int)pwm_value);
    }
    if(channel_x == 3){
        HF_PWM_Set_TIM1_CCR3((unsigned short int)pwm_value);
    }
    if(channel_x == 4){
        HF_PWM_Set_TIM1_CCR4((unsigned short int)pwm_value);
    }
    if(channel_x == 5){
        HF_PWM_Set_TIM8_CCR1((unsigned short int)pwm_value);
    }
    if(channel_x == 6){
        HF_PWM_Set_TIM8_CCR2((unsigned short int)pwm_value);
    }
    if(channel_x == 7){
        HF_PWM_Set_TIM9_CCR1((unsigned short int)pwm_value);
    }
    if(channel_x == 8){
        HF_PWM_Set_TIM9_CCR2((unsigned short int)pwm_value);
    }
    if(channel_x == 9){
        HF_PWM_Set_TIM12_CCR1((unsigned short int)pwm_value);
    }
    if(channel_x == 10){
        HF_PWM_Set_TIM12_CCR2((unsigned short int)pwm_value);
    }
}

#endif
