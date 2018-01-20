/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* Contact:  QQ Exchange Group -- 521037187
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

/************************************************************************************************************************
***                                                                                                                   ***
***                                           Code of external interface                                              ***
***                                                                                                                   ***
*************************************************************************************************************************/

	
/***********************************************************************************************************************
* Function:      void HF_PwmOut_Init(TIM_TypeDef* TIMx , uint16_t Prescaler , uint16_t Period)
*
* Scope:         public
*
* Description:   PWM timer initialization, input parameter : TIM1 TIM8     default period 20ms
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
void HF_PWMChannel_Init(TIM_TypeDef* TIMx , uint8_t Channel , uint16_t Prescaler,uint16_t Period, uint8_t GPIO_AF)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;

    GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); //使能GPIO外设和AFIO复用功能模块时钟

    if(TIMx == TIM1)
    {      
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
        if( GPIO_AF == 0 ){
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
					/******************************TIM1 Multiplexing Push-pull output*********************************************/
                    if(Channel == 1)
                        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ;
                    else if(Channel == 2)
                        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
                    else if(Channel == 3)
                        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
                    else if(Channel == 4)
                        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
                    else return;
					GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
        else if( GPIO_AF == 1 ){
                   /******************************TIM1 Multiplexing Push-pull output*********************************************/
                   if(Channel == 1)
                   {
                       RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
                       GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ;
                       GPIO_Init(GPIOA, &GPIO_InitStructure);
                   }
                   else if(Channel == 2)
                   {
                       RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
                       GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
                       GPIO_Init(GPIOA, &GPIO_InitStructure);
                   }
                   else if(Channel == 3)
                   {
                       RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
                       GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
                       GPIO_Init(GPIOB, &GPIO_InitStructure);
                   }
                   else if(Channel == 4)
                   {
                       RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
                       GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
                       GPIO_Init(GPIOB, &GPIO_InitStructure);
                   }
                   else return;
        }
    }
    else if(TIMx == TIM2)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
        if( GPIO_AF == 0 ){
                    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
                    /******************************TIM1 Multiplexing Push-pull output*********************************************/
                    if(Channel == 1)
                        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
                    else if(Channel == 2)
                        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
                    else if(Channel == 3)
                        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
                    else if(Channel == 4)
                        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
                    else return;
                    GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
        else if( GPIO_AF == 1 ){
                    GPIO_PinRemapConfig(GPIO_FullRemap_TIM2,ENABLE);
                   /******************************TIM1 Multiplexing Push-pull output*********************************************/
                   if(Channel == 1)
                   {
                       RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
                       GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 ;
                       GPIO_Init(GPIOA, &GPIO_InitStructure);
                   }
                   else if(Channel == 2)
                   {
                       RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
                       GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
                       GPIO_Init(GPIOB, &GPIO_InitStructure);
                   }
                   else if(Channel == 3)
                   {
                       RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
                       GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
                       GPIO_Init(GPIOB, &GPIO_InitStructure);
                   }
                   else if(Channel == 4)
                   {
                       RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
                       GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
                       GPIO_Init(GPIOB, &GPIO_InitStructure);
                   }
                   else return;
        }
    }
    else if(TIMx == TIM3)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
        if( GPIO_AF == 0 ){
                    /******************************TIM1 Multiplexing Push-pull output*********************************************/
                    if(Channel == 1)
                    {
                        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
                        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ;
                        GPIO_Init(GPIOA, &GPIO_InitStructure);
                    }
                    else if(Channel == 2)
                    {
                        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
                        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 ;
                        GPIO_Init(GPIOA, &GPIO_InitStructure);
                    }
                    else if(Channel == 3)
                    {
                        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
                        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ;
                        GPIO_Init(GPIOB, &GPIO_InitStructure);
                    }
                    else if(Channel == 4)
                    {
                        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
                        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 ;
                        GPIO_Init(GPIOB, &GPIO_InitStructure);
                    }
                    else return;

        }
        else if( GPIO_AF == 1 ){
             GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,ENABLE);
             RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
                   /******************************TIM1 Multiplexing Push-pull output*********************************************/
                   if(Channel == 1)
                       GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ;
                   else if(Channel == 2)
                       GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 ;
                   else if(Channel == 3)
                       GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ;
                   else if(Channel == 4)
                       GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
                   else return;
                   GPIO_Init(GPIOC, &GPIO_InitStructure);
        }
    }
    else if(TIMx == TIM4)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
        if( GPIO_AF == 0 ){
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
                    /******************************TIM1 Multiplexing Push-pull output*********************************************/
                    if(Channel == 1)
                        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ;
                    else if(Channel == 2)
                        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 ;
                    else if(Channel == 3)
                        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ;
                    else if(Channel == 4)
                        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 ;
                    else return;
                    GPIO_Init(GPIOB, &GPIO_InitStructure);
        }
        else if( GPIO_AF == 1 ){
             GPIO_PinRemapConfig(GPIO_Remap_TIM4,ENABLE);
             RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
                   /******************************TIM1 Multiplexing Push-pull output*********************************************/
                   if(Channel == 1)
                       GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 ;
                   else if(Channel == 2)
                       GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 ;
                   else if(Channel == 3)
                       GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 ;
                   else if(Channel == 4)
                       GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 ;
                   else return;
                   GPIO_Init(GPIOD, &GPIO_InitStructure);
        }
    }
    else if(TIMx == TIM5)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
        if( GPIO_AF == 0 ){
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
                    /******************************TIM1 Multiplexing Push-pull output*********************************************/
                    if(Channel == 1)
                        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
                    else if(Channel == 2)
                        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ;
                    else if(Channel == 3)
                        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ;
                    else if(Channel == 4)
                        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ;
                    else return;
                    GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
        else if( GPIO_AF == 1 ){

        }
    }
    else if(TIMx == TIM8)
    {
         RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);
         if( GPIO_AF == 0 ) {
                    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
					/******************************TIM8 Multiplexing Push-pull output*********************************************/
                    if(Channel == 1)
                        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ;
                    else if(Channel == 2)
                        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
                    else if(Channel == 3)
                        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
                    else if(Channel == 4)
                        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
                    else return;
					GPIO_Init(GPIOC, &GPIO_InitStructure);
        }
        else if( GPIO_AF == 1 ){

        }
    }


		TIM_TimeBaseStructure.TIM_Prescaler = Prescaler;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseStructure.TIM_Period = Period;
		TIM_TimeBaseStructure.TIM_ClockDivision = 0;
		TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

		TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);

		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
		TIM_OCInitStructure.TIM_Pulse =0;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
		TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
		TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
		TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
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
		TIM_CtrlPWMOutputs(TIMx, ENABLE);
}


//Set Pulse Width
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
