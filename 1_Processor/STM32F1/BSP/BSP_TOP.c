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
* <author>    <time>      <version >       <desc>
* mawenke     2015.10.1   V1.0             creat
* LiuDong     2016.1.8    V1.57            update the name of function
*
* Description:
* TM32F1--------------
* no using Pin source
* BSP Distribution of hardware source
* SysTick(24Bits) used by operation system, nor using to make accurate delay  if no operation system 
* TIM7 used by time measurement system
* TIM2 3 4 reserved for encoder   
* TIM5 6   reserved for interruption of timer
* TIM1 8   reserved for PWM generater
************************************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif 

#include "BSP_TOP.h"

BSP_Data bsp_data={&cpu_hardware_data_r,&calendar_r,&led_key_data_r,&adc_dac_data_r,&pwm_in_data_r,&pwm_out_data_r,&encoder_data_r};  
System_Data system_data;
/***********************************************************************************************************************
* Function:     static void BSP_Data_init(void)
*
* Scope:        private
*
* Description:  defining the structure to packed the data of BSP. If initialized
*               the RAM will distribute some RAM space
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
* by   mawenke   2015.12.1   creat
***********************************************************************************************************************/
static void BSP_Data_init(void)
{
    bsp_data.cpu_hardware_data_r->ChipUniqueID[0] = 0;
    bsp_data.cpu_hardware_data_r->ChipUniqueID[1] = 0;
    bsp_data.cpu_hardware_data_r->ChipUniqueID[2] = 0;
}

/***********************************************************************************************************************
* Function:     void BSP_Cycle_Call(void)
*
* Scope:        public
*
* Description:  update the underlying hardware information: feeding dog, cycle calling. Suggest calling every 10us
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
* by   mawenke   2015.12.1                           creat
* by   LiuDong   2016.1.8       V1.57       update the name of function
***********************************************************************************************************************/
void HF_BSP_Cycle_Call(void)         // need time stm32f1  35us
{
    
#if	BSP_CFG_RTC_EN > 0u              //if using RTC Timer
    static unsigned char BSP_Cycle_i;
    BSP_Cycle_i++;
    if(BSP_Cycle_i >= 50)            //updating every 500ms
    {
        BSP_Cycle_i=0;
        HF_RTC_Time_Renew();	       //updating time
    }
#endif
     
#if	BSP_CFG_WDG_WKUP_EN  > 0u        //if using Watch Dog
    HF_IWDG_Feed();                  //Feeding Dog
#endif
#if	BSP_CFG_LED_KEY_EN > 0u          //if using LED and Key
    HF_Key_Cycle();                  //cycle calling every 10ms, update the LED and Key data
#endif
#if	BSP_CFG_ADC_EN > 0u              //if using ADC
    ADC_Data_Anl();                  //transfering the data of ADC
#endif
    
    system_data.System_Time = GET_System_time();  //system working time (unit:us), start after power-on
    
}

//void RCC_Init(void)
//{  	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	   //must use repeat using
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); 
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE); 
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE); 
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); 
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); 
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);		
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
//}


/***********************************************************************************************************************
* Function:     void BSP_Init(void)
*
* Scope:        public
*
* Description:  BSP init  The initialization of  most underlying hardware, only calls once
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
* by   mawenke   2015.12.1                           creat
* by   LiuDong   2016.1.8       V1.57       update the name of function
***********************************************************************************************************************/
void HF_BSP_Init(void)
{
    
    BSP_Data_init();              // Initialize all BSP data, and distribute RAM space
    delay_init();                 // Initialize the delay system
    Init_Measurement_Timer();     // Initialize the measurement systemm
    Get_CPU_Information() ;       // Get the ID of CPU and the capacity of Flash
    
#if	BSP_CFG_RTC_EN  > 0u
    HF_RTC_Init();                // Initialize the RTC, if return 0:failed,else if return 1:succeeded
#endif
    
#if	BSP_CFG_WDG_WKUP_EN  > 0u
    HF_IWDG_Init();               //  Initialize the independed watch dog, system will reset if not feeding dog over 1.28s
#endif
    
    #if	BSP_CFG_FLASH_EN > 0u
    #endif
    
#if	BSP_CFG_LED_KEY_EN > 0u
    HF_Led_Key_Init();
#endif
    
#if	BSP_CFG_USART_EN > 0u
    HF_Usart_Init(USART1,921600,0);  //Initilaize the debug USART, First Parameter:USARTx
 #endif
    
#if	BSP_CFG_ADC_DAC_EN > 0u
    HF_ADC_Moder_Init();             //Initialize ADC:ADC0--ADC9  PA0--7  PB0,1
    HF_Dac_Init(DAC_Channel_1);      //Initialize DAC:DAC_Channel_x = DAC_Channel_1 PA4 || DAC_Channel_2 PA5
#endif
    
#if	BSP_CFG_TIMER_EN > 0u
    HF_Timer_Init(TIM6 , 1000);   	 //Input parameter :TIMx and delay time(us), *timer2--7     1ms
#endif
    
#if	BSP_CFG_PWMIN_EN > 0u
    HF_PwmIn_Init();                 //Initialize capturing PWM. Using 5 channels maximum.    PC0 PC1 PC2 PC3 PC4
#endif
    
#if	BSP_CFG_PWMOUT_EN > 0u
#endif
    
#if	BSP_CFG_ENCODER_EN > 0u
#endif
    
#if	BSP_CFG_SPI_EN > 0u
#endif
    
#if	BSP_CFG_I2C_EN > 0u
#endif
    
#if	BSP_CFG_CAN_EN > 0u
#endif
    
}


#ifdef __cplusplus
}
#endif 
