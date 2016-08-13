/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: pwm_in.c
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
* Description:  capturing PWM can be realized by timer or external interrupt
*               this file take external interrupt to realize capturing, and define 5 channels
*               STM32F1--------------
*               PC0 PC1 PC2 PC3 PC4
***********************************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif 

#include "pwm_in.h"
#include "nvic.h"
#include "delay.h"


PWM_In_Data pwm_in_data_r; //current input value of PWM (Unit:us)

#if BSP_CFG_PWMIN_EN > 0u	

/***********************************************************************************************************************
* Function:     void HF_PwmIn_Init(void)
*
* Scope:        public
*
* Description:  configure input of PWM,and capture the time of high level.
*                PC0 PC1 PC2 PC3 PC4  external interrupt line of Pin.
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
* by   mawenke    2015.12.1                          creat
* by   LiuDong    2016.1.8       V1.57       update the name of function
***********************************************************************************************************************/
void HF_PwmIn_Init(void)
{
    
    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO,ENABLE);
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    
#if PWM_Input_CH0_ENABLE ==1        //if enable this channel
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	 // input  pull down
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource0); /* EXTI line(PC0) mode config */
    EXTI_InitStructure.EXTI_Line = EXTI_Line0;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	//interrupt mode
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //enable interrupt of posedge and negedge
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;           //enable interrupt
    EXTI_Init(&EXTI_InitStructure);
    
    EXTI0_NVIC_Configuration() ;
#endif
    
#if PWM_Input_CH1_ENABLE ==1        //if enable this channel
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	 //input  pull down
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource1); /* EXTI line(PC0) mode config */
    EXTI_InitStructure.EXTI_Line = EXTI_Line1;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	//interrupt mode
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //enable interrupt of posedge and negedge
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;           //enable interrupt
    EXTI_Init(&EXTI_InitStructure);
    
    EXTI1_NVIC_Configuration() ;
#endif
    
#if PWM_Input_CH2_ENABLE ==1        //if enable this channel
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	 // input  pull down
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource2); /* EXTI line(PC0) mode config */
    EXTI_InitStructure.EXTI_Line = EXTI_Line2;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	//interrupt mode
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //enable interrupt of posedge and negedge
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;           //enable interrupt
    EXTI_Init(&EXTI_InitStructure);
    
    EXTI2_NVIC_Configuration() ;
#endif
    
#if PWM_Input_CH3_ENABLE ==1        //if enable this channel
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	     // input  pull down
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource3); /* EXTI line(PC0) mode config */
    EXTI_InitStructure.EXTI_Line = EXTI_Line3;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	//interrupt mode
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //enable interrupt of posedge and negedge
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;           //enable interrupt
    EXTI_Init(&EXTI_InitStructure);
    
    EXTI3_NVIC_Configuration() ;
#endif	
    
    
#if PWM_Input_CH4_ENABLE ==1        //if enable this channel
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	   // input  pull down
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource4); /* EXTI line(PC0) mode config */
    EXTI_InitStructure.EXTI_Line = EXTI_Line4;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	//interrupt mode
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //enable interrupt of posedge and negedge
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;           //enable interrupt
    EXTI_Init(&EXTI_InitStructure);
    
    EXTI4_NVIC_Configuration() ;
#endif
    
}

/***********************************************************************************************************************
* Function:     void EXTIx_IRQHandler(void)
*
* Scope:        public
*
* Description:  realization function of capturing PWM by external interrupt
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
#if PWM_Input_CH1_ENABLE ==1        //if enable this channel
//interrupt program of interrupt line1
void EXTI1_IRQHandler(void)
{
    static float FallingTime=0 , RisingTime =0;
    if( GPIOC->IDR & 0x0002)
    {
        RisingTime = GET_System_time();
    }
    else
    {
        FallingTime = GET_System_time();
        if(FallingTime < RisingTime){ return ;}
        else
        {
            pwm_in_data_r.PWM_Input_CH1 = FallingTime - RisingTime;
        }
    }
    EXTI->PR=1<<1;  //clear interrupt flag
}

#endif


#if PWM_Input_CH2_ENABLE ==1        //if enable this channel
//interrupt program of interrupt line2
void EXTI2_IRQHandler(void)
{
    static float FallingTime=0 , RisingTime =0;
    if( GPIOC->IDR & 0x0004)
    {
        RisingTime = GET_System_time();
    }
    else
    {
        FallingTime = GET_System_time();
        if(FallingTime < RisingTime){return ;}
        else
        {
            pwm_in_data_r.PWM_Input_CH2 = FallingTime - RisingTime;
        }
    }
    EXTI->PR=1<<2;  //clear interrupt flag
}
#endif



#if PWM_Input_CH3_ENABLE ==1        //if enable this channel
//interrupt program of interrupt line3
void EXTI3_IRQHandler(void)
{
    static float FallingTime=0 , RisingTime =0;
    if( GPIOC->IDR & 0x0008)
    {
        RisingTime = GET_System_time();
    }
    else
    {
        FallingTime = GET_System_time();
        if(FallingTime < RisingTime){ return ;}
        else
        {
            pwm_in_data_r.PWM_Input_CH3 = FallingTime - RisingTime;
        }
    }
    EXTI->PR=1<<3;  //clear interrupt flag
}

#endif



#if PWM_Input_CH4_ENABLE ==1        //if enable this channel
//interrupt program of interrupt line4
void EXTI4_IRQHandler(void)
{
    static float FallingTime=0 , RisingTime =0;
    if( GPIOC->IDR & 0x0010)
    {
        RisingTime = GET_System_time();
    }
    else
    {
        FallingTime = GET_System_time();
        if(FallingTime < RisingTime){ return ;}
        else
        {
            pwm_in_data_r.PWM_Input_CH4 = FallingTime - RisingTime;
        }
        
    }
    EXTI->PR=1<<4;  //clear interrupt flag
}

#endif

#endif  //#if BSP_CFG_PWMIN_EN > 0u	

#ifdef __cplusplus
}
#endif

