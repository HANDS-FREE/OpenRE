#ifndef __bsp_top_H
#define	__bsp_top_H

#ifdef __cplusplus
extern "C" {
#endif 

#define Hardware_Platform    1                  //The value 1 means using STM32F1 Processor,and 4 means using STM32F4 Processor

#include "main_config.h"

#include "stm32f10x.h"
#include "delay.h"
#include "rtc.h"	 	
#include "wdg_wkup.h"	
#include "flash.h"
#include "led_key.h"
#include "usart.h"
#include "adc_dac.h"
#include "timer.h"
#include "pwm_in.h" 
#include "pwm_out.h"
#include "encoder.h"
#include "i2c.h"
#include "can.h"
#include "spi.h"

#include "malloc.h"	 
/************************************************************************************************************************
***                                                                                                                   ***
***                          The underlying hardware abstract information                                             ***
***                                                                                                                   ***
*************************************************************************************************************************/
typedef struct BSP_Data
{
    CPU_Hardware_Data *cpu_hardware_data_r;
    CALENDAR *calendar_r;
    LED_KEY_DATA *led_key_data_r;
    ADC_DAC_Data *adc_dac_data_r;
    PWM_In_Data *pwm_in_data_r;
    PWM_Out_Data *pwm_out_data_r;
    ENCODER_Data *encoder_data_r;
} BSP_Data;
extern BSP_Data bsp_data;

/************************************************************************************************************************
***                                                                                                                   ***
***                                           The System information                                                  ***
***                                                                                                                   ***
*************************************************************************************************************************/

typedef struct System_Data{     // some flags of system
    float System_Time;           //system working time (unit:us), start after power-on
    uint8_t S_Initialize;        //state of system: 0-->not initialize  1-->initialized
    uint16_t cnt_1ms;
    uint16_t cnt_2ms;
    uint16_t cnt_5ms;
    uint16_t cnt_10ms;
    uint16_t cnt_20ms;
    uint16_t cnt_50ms;
}System_Data;

extern System_Data system_data;

void HF_BSP_Init(void);           //The initialization of  most underlying hardware, only calls once
void HF_BSP_Cycle_Call(void);     //update the underlying hardware information: feeding dog, cycle calling. Suggest calling every 10us
// need time stm32f1  35us

#ifdef __cplusplus
}
#endif 

#endif  //bsp_top.h


