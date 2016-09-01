/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: pwm_out.c
* Contact:  QQ Exchange Group -- 521037187
* Version:  V2.0
*
* LICENSING TERMS:  
* The Hands Free is licensed generally under a permissive 3-clause BSD license. 
* Contributions are requiredto be made under the same license.
*
* History: 
* <author>      <time>      <version>      <desc>
* mawenke       2015.10.1   V1.0           creat this file
*
* Description: 
*        STM32F4--------------
*        occupy hardware source : timer1 timer8
*        TIM1_CCR1 -- PA8
*        TIM1_CCR2 -- PA9
*        TIM1_CCR3 -- PA10
*        TIM1_CCR4 -- PA11
*        TIM8_CCR1 -- PC6
*        TIM8_CCR2 -- PC7
*        TIM8_CCR3 -- PC8
*        TIM8_CCR4 -- PC9
***********************************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif 

#include "pwm_out.h"

typedef struct PWM_Out_Data{
    uint16_t TIM1_PWM_Period;
    uint16_t TIM8_PWM_Period;
    uint16_t TIM9_PWM_Period;
    uint16_t TIM12_PWM_Period;

    uint16_t TIM1_PWM1;
    uint16_t TIM1_PWM2;
    uint16_t TIM1_PWM3;
    uint16_t TIM1_PWM4;
    uint16_t TIM8_PWM1;
    uint16_t TIM8_PWM2;
    uint16_t TIM8_PWM3;
    uint16_t TIM8_PWM4;
    uint16_t TIM9_PWM1;
    uint16_t TIM9_PWM2;
    uint16_t TIM12_PWM1;
    uint16_t TIM12_PWM2;
}PWM_Out_Data;

PWM_Out_Data pwm_out_data_r;

/***********************************************************************************************************************
* Function:      void HF_PwmOut_Init(TIM_TypeDef* TIMx)
*
* Scope:         public
*
* Description:   TIM1 PWM initialization
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
void HF_PWMOut_Init(TIM_TypeDef* TIMx , uint16_t Prescaler
                    , uint16_t Period , uint8_t GPIO_AF)
{
    
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    /******************************GPIO Multiplexing Push-pull output*********************************************/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
    
    if(TIMx == TIM1)
    {
        pwm_out_data_r.TIM1_PWM_Period = Period;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
        
        if( GPIO_AF == 0 )
        {
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
            GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_8 |GPIO_Pin_9|GPIO_Pin_10 |GPIO_Pin_11;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
            
            GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM1);
            GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_TIM1);
            GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_TIM1);
            GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_TIM1);
        }
        else if( GPIO_AF == 1 )
        {
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_14;
            GPIO_Init(GPIOE, &GPIO_InitStructure);
            
            GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_TIM1);
            GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_TIM1);
            GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_TIM1);
            GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF_TIM1);
        }
    }
    else if(TIMx == TIM8)
    {
        pwm_out_data_r.TIM8_PWM_Period = Period;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);

        if( GPIO_AF == 0 )
        {
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
            GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_6 |GPIO_Pin_7|GPIO_Pin_8 |GPIO_Pin_9;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
            
            GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM8);
            GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM8);
            GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_TIM8);
            GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_TIM8);
        }
    }
    else if(TIMx == TIM9)
    {
        pwm_out_data_r.TIM9_PWM_Period = Period;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE);

        if( GPIO_AF == 0 )
        {
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
            GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_5 |GPIO_Pin_6;
            GPIO_Init(GPIOE, &GPIO_InitStructure);

            GPIO_PinAFConfig(GPIOE, GPIO_PinSource5, GPIO_AF_TIM9);
            GPIO_PinAFConfig(GPIOE, GPIO_PinSource6, GPIO_AF_TIM9);
        }
    }
    else if(TIMx == TIM12)
    {
        pwm_out_data_r.TIM12_PWM_Period = Period;
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12,ENABLE);
        
        if( GPIO_AF == 0 )
        {
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
            GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_14 |GPIO_Pin_15;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
            
            GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_TIM12);
            GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_TIM12);
        }
    }
    TIM_TimeBaseStructure.TIM_Prescaler = Prescaler;    //Prescaler
    TIM_TimeBaseStructure.TIM_Period = Period;          //count period
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);
    
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
    TIM_OC1Init(TIMx, &TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OC2Init(TIMx, &TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OC3Init(TIMx, &TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OC4Init(TIMx, &TIM_OCInitStructure);
    
    TIM_Cmd(TIMx, ENABLE);
    TIM_ARRPreloadConfig(TIMx, ENABLE);
    TIM_CtrlPWMOutputs(TIMx, ENABLE);
}

/***********************************************************************************************************************
* Function:      HF_PWM_Set_TIMx_CCRx(uint16_t Pwm_Value)
*
* Scope:         public
*
* Description:   set Pulse Width of TIM
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
//set Pulse Width of TIM1
void HF_PWM_Set_TIM1_CCR1(uint16_t Pwm_Value)
{
    if( Pwm_Value <= 0 ) Pwm_Value = 0;
    if( Pwm_Value >= pwm_out_data_r.TIM1_PWM_Period  ) Pwm_Value = pwm_out_data_r.TIM1_PWM_Period;
    TIM_SetCompare1(TIM1,Pwm_Value);
    pwm_out_data_r.TIM1_PWM1 = Pwm_Value;
}
void HF_PWM_Set_TIM1_CCR2(uint16_t Pwm_Value)
{
    if( Pwm_Value <= 0 ) Pwm_Value = 0;
    if( Pwm_Value >= pwm_out_data_r.TIM1_PWM_Period  ) Pwm_Value = pwm_out_data_r.TIM1_PWM_Period;
    TIM_SetCompare2(TIM1,Pwm_Value);
    pwm_out_data_r.TIM1_PWM2 = Pwm_Value;
}
void HF_PWM_Set_TIM1_CCR3(uint16_t Pwm_Value)
{
    if( Pwm_Value <= 0 ) Pwm_Value = 0 ;
    if( Pwm_Value >= pwm_out_data_r.TIM1_PWM_Period  ) Pwm_Value = pwm_out_data_r.TIM1_PWM_Period;
    TIM_SetCompare3(TIM1,Pwm_Value);
    pwm_out_data_r.TIM1_PWM3 = Pwm_Value;
}
void HF_PWM_Set_TIM1_CCR4(uint16_t Pwm_Value)
{
    if( Pwm_Value <= 0 ) Pwm_Value = 0 ;
    if( Pwm_Value >= pwm_out_data_r.TIM1_PWM_Period  ) Pwm_Value = pwm_out_data_r.TIM1_PWM_Period;
    TIM_SetCompare4(TIM1,Pwm_Value);
    pwm_out_data_r.TIM1_PWM4 = Pwm_Value;
}

//set Pulse Width of TIM8
void HF_PWM_Set_TIM8_CCR1(uint16_t Pwm_Value)
{
    if( Pwm_Value <= 0 ) Pwm_Value = 0;
    if( Pwm_Value >= pwm_out_data_r.TIM8_PWM_Period  ) Pwm_Value = pwm_out_data_r.TIM8_PWM_Period;
    TIM_SetCompare1(TIM8,Pwm_Value);
    pwm_out_data_r.TIM8_PWM1 = Pwm_Value;
}
void HF_PWM_Set_TIM8_CCR2(uint16_t Pwm_Value)
{
    if( Pwm_Value <= 0 ) Pwm_Value = 0;
    if( Pwm_Value >= pwm_out_data_r.TIM8_PWM_Period  ) Pwm_Value = pwm_out_data_r.TIM8_PWM_Period;
    TIM_SetCompare2(TIM8,Pwm_Value);
    pwm_out_data_r.TIM8_PWM2 = Pwm_Value;
}
void HF_PWM_Set_TIM8_CCR3(uint16_t Pwm_Value)
{
    if( Pwm_Value <= 0 ) Pwm_Value = 0;
    if( Pwm_Value >= pwm_out_data_r.TIM8_PWM_Period  ) Pwm_Value = pwm_out_data_r.TIM8_PWM_Period;
    TIM_SetCompare3(TIM8,Pwm_Value);
    pwm_out_data_r.TIM8_PWM3 = Pwm_Value;
}
void HF_PWM_Set_TIM8_CCR4(uint16_t Pwm_Value)
{
    if( Pwm_Value <= 0 ) Pwm_Value = 0;
    if( Pwm_Value >= pwm_out_data_r.TIM8_PWM_Period  ) Pwm_Value = pwm_out_data_r.TIM8_PWM_Period;
    TIM_SetCompare4(TIM8,Pwm_Value);
    pwm_out_data_r.TIM8_PWM4 = Pwm_Value;
}

//set Pulse Width of TIM9
void HF_PWM_Set_TIM9_CCR1(uint16_t Pwm_Value)
{
    if( Pwm_Value <= 0 ) Pwm_Value = 0;
    if( Pwm_Value >= pwm_out_data_r.TIM9_PWM_Period  ) Pwm_Value = pwm_out_data_r.TIM9_PWM_Period;
    TIM_SetCompare1(TIM9,Pwm_Value);
    pwm_out_data_r.TIM9_PWM1 = Pwm_Value;
}
void HF_PWM_Set_TIM9_CCR2(uint16_t Pwm_Value)
{
    if( Pwm_Value <= 0 ) Pwm_Value = 0;
    if( Pwm_Value >= pwm_out_data_r.TIM9_PWM_Period  ) Pwm_Value = pwm_out_data_r.TIM9_PWM_Period;
    TIM_SetCompare2(TIM9,Pwm_Value);
    pwm_out_data_r.TIM9_PWM2 = Pwm_Value;
}

//set Pulse Width of TIM12
void HF_PWM_Set_TIM12_CCR1(uint16_t Pwm_Value)
{
    if( Pwm_Value <= 0 ) Pwm_Value = 0 ;
    if( Pwm_Value >= pwm_out_data_r.TIM12_PWM_Period  ) Pwm_Value = pwm_out_data_r.TIM12_PWM_Period;
    TIM_SetCompare1(TIM12,Pwm_Value);
    pwm_out_data_r.TIM12_PWM1 = Pwm_Value;
}
void HF_PWM_Set_TIM12_CCR2(uint16_t Pwm_Value)
{
    if( Pwm_Value <= 0 ) Pwm_Value = 0 ;
    if( Pwm_Value >= pwm_out_data_r.TIM12_PWM_Period  ) Pwm_Value = pwm_out_data_r.TIM12_PWM_Period;
    TIM_SetCompare2(TIM12,Pwm_Value);
    pwm_out_data_r.TIM12_PWM2 = Pwm_Value;
}

#ifdef __cplusplus
}
#endif 
