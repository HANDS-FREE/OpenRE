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

/***********************************************************************************************************************
* Function:      void HF_PWMChannel_Init(TIM_TypeDef* TIMx, uint8_t Channel , uint16_t Prescaler,
                        uint16_t Period, uint8_t GPIO_AF)
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
void HF_PWMChannel_Init(TIM_TypeDef* TIMx, uint8_t Channel , uint16_t Prescaler,
                        uint16_t Period, uint8_t GPIO_AF)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    /******************************GPIO Multiplexing Push-pull output*********************************************/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

    if(TIMx == TIM1)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);

        if ( GPIO_AF == 0 )
        {
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

            if(Channel == 1){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_8;
                GPIO_Init(GPIOA, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM1);
            }
            else if(Channel == 2){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_9;
                GPIO_Init(GPIOA, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_TIM1);
            }
            else if(Channel == 3){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_10;
                GPIO_Init(GPIOA, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_TIM1);
            }
            else if(Channel == 4){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_11;
                GPIO_Init(GPIOA, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_TIM1);
            }
            else return;
        }
        else if( GPIO_AF == 1 )
        {
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

            if(Channel == 1){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_9;
                GPIO_Init(GPIOE, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_TIM1);
            }
            else if(Channel == 2){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_11;
                GPIO_Init(GPIOE, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_TIM1);
            }
            else if(Channel == 3){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_13;
                GPIO_Init(GPIOE, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_TIM1);
            }
            else if(Channel == 4){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_14;
                GPIO_Init(GPIOE, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF_TIM1);
            }
            else return;
        }

    }
    else if(TIMx == TIM2)
    {
        if( GPIO_AF == 0 ){
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
            if(Channel == 1){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_0;
                GPIO_Init(GPIOA, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM2);
            }
            else if(Channel == 2){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_1;
                GPIO_Init(GPIOA, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM2);
            }
            else if(Channel == 3){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_2;
                GPIO_Init(GPIOA, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_TIM2);
            }
            else if(Channel == 4){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_3;
                GPIO_Init(GPIOA, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_TIM2);
            }
            else return;
        }
        else if( GPIO_AF == 1 ){
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
            if(Channel == 1){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_15;
                GPIO_Init(GPIOA, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOA, GPIO_PinSource15, GPIO_AF_TIM2);
            }
            else if(Channel == 2){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_3;
                GPIO_Init(GPIOB, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_TIM2);
            }
            else if(Channel == 3){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_10;
                GPIO_Init(GPIOB, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_TIM2);
            }
            else if(Channel == 4){
            }
            else return;
        }
        else if( GPIO_AF == 2 ){
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
            if(Channel == 1){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_5;
                GPIO_Init(GPIOA, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_TIM2);
            }
            else return;
        }
    }
    else if(TIMx == TIM3)
    {
        if( GPIO_AF == 0 ){
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
            if(Channel == 1){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_6;
                GPIO_Init(GPIOA, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM3);
            }
            else if(Channel == 2){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_7;
                GPIO_Init(GPIOA, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_TIM3);
            }
            else if(Channel == 3){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_0;
                GPIO_Init(GPIOB, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOB, GPIO_PinSource0, GPIO_AF_TIM3);
            }
            else if(Channel == 4){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_1;
                GPIO_Init(GPIOB, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOB, GPIO_PinSource1, GPIO_AF_TIM3);
            }
            else return;
        }
        else if( GPIO_AF == 1 ){
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
            if(Channel == 1){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_6;
                GPIO_Init(GPIOC, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM3);
            }
            else if(Channel == 2){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_7;
                GPIO_Init(GPIOC, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM3);
            }
            else if(Channel == 3){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_8;
                GPIO_Init(GPIOC, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_TIM3);
            }
            else if(Channel == 4){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_9;
                GPIO_Init(GPIOC, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_TIM3);
            }
            else return;
        }
        else if( GPIO_AF == 2 ){
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
            if(Channel == 1){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_4;
                GPIO_Init(GPIOB, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_TIM3);
            }
            else if(Channel == 2){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_5;
                GPIO_Init(GPIOB, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_TIM3);
            }
            else return;
        }
    }
    else if(TIMx == TIM4)
    {
        if( GPIO_AF == 0 ){
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
            if(Channel == 1){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_12;
                GPIO_Init(GPIOD, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
            }
            else if(Channel == 2){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_13;
                GPIO_Init(GPIOD, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
            }
            else if(Channel == 3){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_14;
                GPIO_Init(GPIOD, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
            }
            else if(Channel == 4){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_15;
                GPIO_Init(GPIOD, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);
            }
            else return;
        }
        else if( GPIO_AF == 1 ){
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
            if(Channel == 3){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_8;
                GPIO_Init(GPIOB, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_TIM4);
            }
            else if(Channel == 4){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_9;
                GPIO_Init(GPIOB, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_TIM4);
            }
            else return;
        }
    }
    else if(TIMx == TIM5)
    {
        if( GPIO_AF == 0 ){
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
            if(Channel == 1){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_0;
                GPIO_Init(GPIOA, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM5);
            }
            else if(Channel == 2){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_1;
                GPIO_Init(GPIOA, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM5);
            }
            else if(Channel == 3){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_2;
                GPIO_Init(GPIOA, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_TIM5);
            }
            else if(Channel == 4){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_3;
                GPIO_Init(GPIOA, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_TIM5);
            }
            else return;
        }
    }
    else if(TIMx == TIM8)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8 , ENABLE);

        if( GPIO_AF == 0 )
        {
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC , ENABLE);

            if(Channel == 1){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_6;
                GPIO_Init(GPIOC, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM8);
            }
            else if(Channel == 2){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_7;
                GPIO_Init(GPIOC, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM8);
            }
            else if(Channel == 3){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_8;
                GPIO_Init(GPIOC, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_TIM8);
            }
            else if(Channel == 4){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_9;
                GPIO_Init(GPIOC, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_TIM8);
            }
            else return;
        }

    }
    else if(TIMx == TIM9)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9 , ENABLE);

        if( GPIO_AF == 0 )
        {
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

            if(Channel == 1){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_5;
                GPIO_Init(GPIOE, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOE, GPIO_PinSource5, GPIO_AF_TIM9);
            }
            else if(Channel == 2){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_6;
                GPIO_Init(GPIOE, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOE, GPIO_PinSource6, GPIO_AF_TIM9);
            }
            else return;
        }
else if( GPIO_AF == 1 )
        {
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

            if(Channel == 1){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_2;
                GPIO_Init(GPIOA, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_TIM9);
            }
            else if(Channel == 2){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_3;
                GPIO_Init(GPIOA, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_TIM9);
            }
            else return;
        }
    }
    else if(TIMx == TIM10)
    {
        if( GPIO_AF == 0 )
        {
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
            if(Channel == 1){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_8;
                GPIO_Init(GPIOB, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_TIM10);
            }
            else return;
        }
    }
    else if(TIMx == TIM11)
    {
        if( GPIO_AF == 0 )
        {
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
            if(Channel == 1){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_9;
                GPIO_Init(GPIOB, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_TIM11);
            }
            else return;
        }
    }
    else if(TIMx == TIM12)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12,ENABLE);

        if( GPIO_AF == 0 )
        {
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

            if(Channel == 1){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_14;
                GPIO_Init(GPIOB, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_TIM12);
            }
            else if(Channel == 2){
                GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_15;
                GPIO_Init(GPIOB, &GPIO_InitStructure);
                GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_TIM12);
            }
            else return;
        }

    }

    TIM_TimeBaseStructure.TIM_Prescaler = Prescaler;    //Prescaler
    TIM_TimeBaseStructure.TIM_Period = Period;            //count period
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
    TIM_OCInitStructure.TIM_Pulse = 0;

    if(Channel == 1){
        TIM_OC1Init(TIMx, &TIM_OCInitStructure);
    }
    else if(Channel == 2){
        TIM_OC2Init(TIMx, &TIM_OCInitStructure);
    }
    else if(Channel == 3){
        TIM_OC3Init(TIMx, &TIM_OCInitStructure);
    }
    else if(Channel == 4){
        TIM_OC4Init(TIMx, &TIM_OCInitStructure);
    }
    else return;

    TIM_Cmd(TIMx, ENABLE);
    TIM_ARRPreloadConfig(TIMx, ENABLE);
    TIM_CtrlPWMOutputs(TIMx, ENABLE);
}

/***********************************************************************************************************************
* Function:     void HF_Set_PWM(TIM_TypeDef* TIMx , uint8_t Channel , uint16_t Pwm_Value)
*
* Scope:          public
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
void HF_Set_PWM(TIM_TypeDef* TIMx , uint8_t Channel , uint16_t Pwm_Value)
{
    uint16_t TIM_PWM_Period;
    TIM_PWM_Period = TIMx->ARR;
    if(Pwm_Value <= 0) Pwm_Value = 0 ;
    if(Pwm_Value >= TIM_PWM_Period) Pwm_Value = TIM_PWM_Period;
    if(Channel == 1){
        TIM_SetCompare1(TIMx , Pwm_Value);
    }
    else if(Channel == 2){
        TIM_SetCompare2(TIMx , Pwm_Value);
    }
    else if(Channel == 3){
        TIM_SetCompare3(TIMx , Pwm_Value);
    }
    else if(Channel ==4 ){
        TIM_SetCompare4(TIMx , Pwm_Value);
    }
    else return;
}

#ifdef __cplusplus
}
#endif 
