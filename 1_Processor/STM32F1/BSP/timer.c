/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: timer.c
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
*        STM32F1--------------
*        TIM7 used by time measurement system
*        TIM2 3 4 reserved for encoder   
*        TIM5 6   reserved for interruption of timer
*        TIM1 8   reserved for PWM generater
*******************************8***************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif 

#include "timer.h"
#include "nvic.h"


#if BSP_CFG_TIMER_EN > 0u	

/***********************************************************************************************************************
* Function:     Timer_Init(TIM_TypeDef* TIMx , int Time_us)
*
* Scope:        public
*
* Description: Initialize timer interrupt. Input parameter :TIMx and delay time(us), *timer2--7     1ms
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
* by   mawenke    2015.12.1                            creat
* by   LiuDong    2016.1.8       V1.57       update the name of function
***********************************************************************************************************************/
void HF_Timer_Init(TIM_TypeDef* TIMx , int Time_us)
{
    
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_DeInit(TIMx);
    
    if( TIMx == TIM2){
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE); /* enable clock */
        TIM2_NVIC_Configuration();    //enable interruptation
    }
    else if( TIMx == TIM3){
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE); /* enable clock */
        TIM3_NVIC_Configuration();     //enable interruptation
    }
    else if( TIMx == TIM4){
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 , ENABLE); /* enable clock */
        TIM4_NVIC_Configuration();    //enable interruptation
    }
    else if( TIMx == TIM5){
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5 , ENABLE); /* enable clock */
        TIM5_NVIC_Configuration();    //enable interruptation
    }
    else if( TIMx == TIM6){
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6 , ENABLE); /* enable clock */
        TIM6_NVIC_Configuration();    //enable interruptation
    }
    else if( TIMx == TIM7){
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7 , ENABLE); /* enable clock */
        TIM7_NVIC_Configuration();    //enable interruptation
    }
    
    TIM_TimeBaseStructure.TIM_Period= Time_us-1 ;		 					/* the value of auto reload register  */
    TIM_TimeBaseStructure.TIM_Prescaler= (72 - 1);				    /* prescler : 72M/72 */
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 		/* ClockDivision*/
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; /* count upwards */
    TIM_TimeBaseInit(TIMx , &TIM_TimeBaseStructure);
    TIM_ClearFlag(TIMx , TIM_FLAG_Update);							    		/* clear interrupt flags */
    TIM_ITConfig(TIMx ,TIM_IT_Update,ENABLE);
    TIM_Cmd(TIMx , ENABLE);
}	

#endif  //#if BSP_CFG_TIMER_EN > 0u	

#ifdef __cplusplus
}
#endif 

