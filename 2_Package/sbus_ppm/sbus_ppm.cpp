/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: sbus_ppm_driver.cpp
* Contact:  QQ Exchange Group -- 521037187
* Version:  V2.0
*
* LICENSING TERMS:
* The Hands Free is licensed generally under a permissive 3-clause BSD license.
* Contributions are requiredto be made under the same license.
*
* History:
* <author>      <time>      <version>      <desc>
* mawenke       2015.10.1    V1.0          creat this file
*
* Description:  this file include decoding functions of sbus and ppm remote signal
*               one sbus message continued 3ms  and two sbus message's interval is 4ms，so 7ms a frame
*               and we can decoding it base this information
*
*
***********************************************************************************************************************/

#include "sbus_ppm.h"

SBUS sbus ;
PPM ppm ;

//extern "C" void USART2_IRQHandler(void)
//{
//    unsigned char data;
//#if SYSTEM_SUPPORT_OS == 1
//    OSIntEnter();
//#endif
//    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
//    {
//        data = USART_ReceiveData(USART2);
//        sbus.receiveByteAnl(data);
//        USART_ClearITPendingBit(USART2, USART_IT_RXNE);  // clear interrupt flag
//    }
//#if SYSTEM_SUPPORT_OS == 1
//    OSIntExit();
//#endif
//}

/***********************************************************************************************************************
* Function:    void SBUS::Sbus_IRQ(unsigned int Data)    put this function in serial port interrupt func
*
* Scope:       public
*
* Description:
*
* Arguments:
*
* Return:
*
* Cpu_Time:    stm32f4+fpu(3 us)
*
* History:
***********************************************************************************************************************/
void SBUS::receiveByteAnl(unsigned char receive_byte)
{

    this_time_ = HF_Get_System_Time();
    d_time_ = this_time_ - last_time_ ;
    last_time_ = this_time_ ;
    sbus_bufi_++;
    if( d_time_ > 	SBUS_D_TIME)          //if right , This bytes is the first of sbus message
    {
        sbus_bufi_=0;
    }
    if( sbus_bufi_ < 25){
        sbus_rx_buffer_[sbus_bufi_]  = receive_byte ;
        if( sbus_bufi_ == 24 && ( sbus_rx_buffer_[0] == 0x0f ) )
        {
            sbus_mes_count_++;
            sbus_frequency=sbusFrequencyMeasure();   //Measure the sbus message's Frequency , about 100hz
            sbus_rx_update = 1 ;                      //renew a sbus message and wait main func to use
            sbus_mes_i_++;
            if(sbus_mes_i_ >= 20)
            {
                sbus_mes_i_=0;
                sbusDataAnl();
            }
        }
    }
    else {
        sbus_bufi_=0;
    }
}

/***********************************************************************************************************************
* Function:    void SBUS::sbusDataAnl(void)
*
* Scope:       private  
*
* Description: 
*
* Arguments:
*
* Return:
*
* Cpu_Time:    stm32f4+fpu(2 us)
*
* History:
***********************************************************************************************************************/
void SBUS::sbusDataAnl(void)
{
    sbus_channel[0] = (sbus_rx_buffer_[2] & 0x7) << 8 | sbus_rx_buffer_[1];
    sbus_channel[8] = (sbus_rx_buffer_[13] & 0x7) << 8 | sbus_rx_buffer_[12];
    sbus_channel[1] = (sbus_rx_buffer_[3] & 0x3F) << 5 | sbus_rx_buffer_[2] >> 3;
    sbus_channel[9] = (sbus_rx_buffer_[14] & 0x3F) << 5 | sbus_rx_buffer_[13] >> 3;
    sbus_channel[2] = (sbus_rx_buffer_[5] & 0x1) << 10 | sbus_rx_buffer_[4] << 2 | sbus_rx_buffer_[3] >> 6;
    sbus_channel[10] = (sbus_rx_buffer_[16] & 0x1) << 10 | sbus_rx_buffer_[15] << 2 | sbus_rx_buffer_[14] >> 6;
    sbus_channel[3] = (sbus_rx_buffer_[6] & 0xF) << 7 | sbus_rx_buffer_[5] >> 1;
    sbus_channel[11] = (sbus_rx_buffer_[17] & 0xF) << 7 | sbus_rx_buffer_[16] >> 1;
    sbus_channel[4] = (sbus_rx_buffer_[7] & 0x7F) << 4 | sbus_rx_buffer_[6] >> 4;
    sbus_channel[12] = (sbus_rx_buffer_[18] & 0x7F) << 4 | sbus_rx_buffer_[17] >> 4;
    sbus_channel[5] = (sbus_rx_buffer_[9] & 0x3) << 9 | sbus_rx_buffer_[8] << 1 | sbus_rx_buffer_[7] >> 7;
    sbus_channel[13] = (sbus_rx_buffer_[20] & 0x3) << 9 | sbus_rx_buffer_[19] << 1 | sbus_rx_buffer_[18] >> 7;
    sbus_channel[6] = (sbus_rx_buffer_[10] & 0x1F) << 6 | sbus_rx_buffer_[9] >> 2;
    sbus_channel[14] = (sbus_rx_buffer_[21] & 0x1F) << 6 | sbus_rx_buffer_[20] >> 2;
    sbus_channel[7] = sbus_rx_buffer_[11] << 3 | sbus_rx_buffer_[10] >> 5;
    sbus_channel[15] = sbus_rx_buffer_[22] << 3 | sbus_rx_buffer_[21] >> 5;
    sbus_flag = sbus_rx_buffer_[23];
    if( sbus_flag == 0 ) sbus_state = 1;    
}

/***********************************************************************************************************************
* Function:    float SBUS::sbusFrequencyMeasure(void)
*
* Scope:       private  
*
* Description: Measure the sbus message's Frequency , about 100hz
*
* Arguments:
*
* Return:
*
* Cpu_Time:    stm32f4+fpu(1 us)
*
* History:
***********************************************************************************************************************/
float SBUS::sbusFrequencyMeasure(void)
{
    this_time = HF_Get_System_Time();
    d_time_new = this_time - last_time ;
    last_time = this_time ;
    d_time = 0.9f*d_time+0.1f*d_time_new  ;   //Low pass filter
    return (1000000/d_time);
}	

/***********************************************************************************************************************
* Function:      void PPM::PPM_IRQ(float pwm_value)
*
* Scope:         public
*
* Description:   pwm_value is the Sample of ppm's Pulse width , unit:us
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
void PPM::receiveFloatAnl(float pwm_value)
{
    ch_++;
    if( pwm_value > 3000)
    {
        ch_ = 0;         //if right , This value is the first of ppm message
    }
    ppm_rc_value[ch_] = pwm_value;
}

