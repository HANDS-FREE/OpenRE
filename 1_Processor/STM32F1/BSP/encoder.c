/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: encoder.c
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
*        occupy hardware source : timer2 timer3 timer4
*        TIM2 CHI1 CHI2---PA0 PA1;
*        TIM3 CHI1 CHI2---PA6 PA7;  || TIM3 CHI1 CHI2---PB4 PB5;
*        TIM4 CHI1 CHI2---PB6 PB7; 
***********************************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif 

#include "encoder.h"
#include "nvic.h"

ENCODER_Data encoder_data_r;

#if BSP_CFG_ENCODER_EN > 0u 

#define ENCODER_PPR           (u16)(1)    // number of pulses per revolution 
#define ICx_FILTER            (u8)1       // 6<-> 670nsec

/***********************************************************************************************************************
* Function:     void Encoder_Init(TIM_TypeDef* TIMx)
*
* Scope:        public
*
* Description:  Initialize encoder mode, input parameter TIM1 TIM2 TIM3
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
* by   mawenke    2015.12.1     creat
***********************************************************************************************************************/
void HF_Encoder_Init(TIM_TypeDef* TIMx , unsigned char GPIO_AF)	      //Initialize encoder mode, input parameter TIM1 TIM2 TIM3
{
    
    TIM_ICInitTypeDef TIM_ICInitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    
    if( TIMx == TIM2){
        
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB , ENABLE); /* enable clock */
        if(GPIO_AF == 0){
            //---------------------------------------------------------------TIM2 CHI1 CHI2---PA0 PA1;
            GPIO_StructInit(&GPIO_InitStructure);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
        else if(GPIO_AF == 1){
            //---------------------------------------------------------------TIM2 CHI1 CHI2---PA15 PB3;
            GPIO_PinRemapConfig(GPIO_FullRemap_TIM2,ENABLE);
            GPIO_StructInit(&GPIO_InitStructure);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
            
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
        }
        TIM2_NVIC_Configuration();    //enable interrupt
        
    }
    
    else if( TIMx == TIM3){
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA , ENABLE); /* enable clock */
        if(GPIO_AF == 0){
            //---------------------------------------------------------------TIM3 CHI1 CHI2---PA6 PA7;
            GPIO_StructInit(&GPIO_InitStructure);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
        else if (GPIO_AF == 1){
            //---------------------------------------------------------------TIM3 CHI1 CHI2---PB4 PB5;
            GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);
            GPIO_StructInit(&GPIO_InitStructure);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
            
        }
        TIM3_NVIC_Configuration();                            //enable interrupt
        
    }
    
    else if( TIMx == TIM4){
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD , ENABLE); /* enable clock */
        if(GPIO_AF == 0){
            //---------------------------------------------------------------TIM4 CHI1 CHI2---PB6 PB7;
            GPIO_StructInit(&GPIO_InitStructure);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
        }
        else if (GPIO_AF == 1){
            //---------------------------------------------------------------TIM4 CHI1 CHI2---PD12 PD13;
            GPIO_PinRemapConfig(GPIO_Remap_TIM4,ENABLE);
            GPIO_StructInit(&GPIO_InitStructure);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            GPIO_Init(GPIOD, &GPIO_InitStructure);
            
        }
        TIM4_NVIC_Configuration();
        
    }
    
    
    TIM_DeInit(TIMx);
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Prescaler = 0x0;
    TIM_TimeBaseStructure.TIM_Period = (4*ENCODER_PPR)-1   ;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);
    TIM_EncoderInterfaceConfig(TIMx, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = ICx_FILTER;
    TIM_ICInit(TIMx, &TIM_ICInitStructure);
    TIM_ClearFlag(TIMx, TIM_FLAG_Update);
    TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIMx, ENABLE);
    
}


/************************************************************************************************************************
***                                                                                                                   ***
***                                           Interrupt Function                                                      ***
***                                                                                                                   ***
*************************************************************************************************************************/


void TIM2_IRQHandler(void)	                           //---TIM2 PA0 , PA1
{ 
    
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
    
    if( TIM_GetCounter(TIM2) == 0 )
        encoder_data_r.TIM2_Count--;
    else
        encoder_data_r.TIM2_Count++;
    
}

void TIM3_IRQHandler(void)	                           //---TIM3 PA6,7   ||   ---PB4 PB5;
{ 
    
    TIM_ClearFlag(TIM3, TIM_FLAG_Update);
    
    if( TIM_GetCounter(TIM3) == 0 )
        encoder_data_r.TIM3_Count--;
    else
        encoder_data_r.TIM3_Count++;
    
}

void TIM4_IRQHandler(void)	                           // TIM4 CHI1 CHI2---PB6 PB7;  
{ 
    
    TIM_ClearFlag(TIM4, TIM_FLAG_Update);
    if( TIM_GetCounter(TIM4) == 0 )
        encoder_data_r.TIM4_Count--;
    else
        encoder_data_r.TIM4_Count++;
    
}

#endif  //#if BSP_CFG_ENCODER_EN > 0u 

#ifdef __cplusplus
}
#endif 
