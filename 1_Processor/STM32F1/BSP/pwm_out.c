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

PWM_Out_Data pwm_out_data_r;

#if BSP_CFG_PWMOUT_EN > 0u

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
void HF_PwmOut_Init(TIM_TypeDef* TIMx , unsigned short int Prescaler , unsigned short int Period , unsigned char GPIO_AF) 
{
    
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;

    GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    if(TIMx == TIM1)
    {      
        if( GPIO_AF == 0 ){
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
					/******************************TIM1 Multiplexing Push-pull output*********************************************/
					GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_8 |GPIO_Pin_9|GPIO_Pin_10 |GPIO_Pin_11;
					GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
        else if( GPIO_AF == 1 ){

        }
    }
    else if(TIMx == TIM8)
    {
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);
        if( GPIO_AF == 0 ) {
					/******************************TIM8 Multiplexing Push-pull output*********************************************/
					GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_6 |GPIO_Pin_7|GPIO_Pin_8 |GPIO_Pin_9;
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

		TIM_OC1Init(TIMx, &TIM_OCInitStructure);
		TIM_OCInitStructure.TIM_Pulse = 0;
		TIM_OC2Init(TIMx, &TIM_OCInitStructure);
		TIM_OCInitStructure.TIM_Pulse = 0;
		TIM_OC3Init(TIMx, &TIM_OCInitStructure);
		TIM_OCInitStructure.TIM_Pulse = 0;
		TIM_OC4Init(TIMx, &TIM_OCInitStructure);
		TIM_Cmd(TIMx, ENABLE);
		TIM_CtrlPWMOutputs(TIMx, ENABLE);
}


//set Pulse Width of TIM1
void Pwm_Set_TIM1_CCR1(unsigned short int Pwm_Value)
{
    if( Pwm_Value <= 0 ) Pwm_Value = 0 ;
    if( Pwm_Value >= pwm_out_data_r.TIM1_PWM_Period  ) Pwm_Value = pwm_out_data_r.TIM1_PWM_Period;
    TIM_SetCompare1(TIM1,Pwm_Value);
    pwm_out_data_r.TIM1_PWM1 = Pwm_Value ;
}
void Pwm_Set_TIM1_CCR2(unsigned short int Pwm_Value)
{
    if( Pwm_Value <= 0 ) Pwm_Value = 0 ;
    if( Pwm_Value >= pwm_out_data_r.TIM1_PWM_Period  ) Pwm_Value = pwm_out_data_r.TIM1_PWM_Period;
    TIM_SetCompare2(TIM1,Pwm_Value);
    pwm_out_data_r.TIM1_PWM2 = Pwm_Value ;
}
void Pwm_Set_TIM1_CCR3(unsigned short int Pwm_Value)
{
    if( Pwm_Value <= 0 ) Pwm_Value = 0 ;
    if( Pwm_Value >= pwm_out_data_r.TIM1_PWM_Period  ) Pwm_Value = pwm_out_data_r.TIM1_PWM_Period;
    TIM_SetCompare3(TIM1,Pwm_Value);
    pwm_out_data_r.TIM1_PWM3 = Pwm_Value ;
}
void Pwm_Set_TIM1_CCR4(unsigned short int Pwm_Value)
{
    if( Pwm_Value <= 0 ) Pwm_Value = 0 ;
    if( Pwm_Value >= pwm_out_data_r.TIM1_PWM_Period  ) Pwm_Value = pwm_out_data_r.TIM1_PWM_Period;
    TIM_SetCompare4(TIM1,Pwm_Value);
    pwm_out_data_r.TIM1_PWM4 = Pwm_Value ;
}

//set Pulse Width of TIM1
void Pwm_Set_TIM8_CCR1(unsigned short int Pwm_Value)
{
    if( Pwm_Value <= 0 ) Pwm_Value = 0 ;
    if( Pwm_Value >= pwm_out_data_r.TIM8_PWM_Period  ) Pwm_Value = pwm_out_data_r.TIM8_PWM_Period;
    TIM_SetCompare1(TIM8,Pwm_Value);
    pwm_out_data_r.TIM8_PWM1 = Pwm_Value ;
}
void Pwm_Set_TIM8_CCR2(unsigned short int Pwm_Value)
{
    if( Pwm_Value <= 0 ) Pwm_Value = 0 ;
    if( Pwm_Value >= pwm_out_data_r.TIM8_PWM_Period  ) Pwm_Value = pwm_out_data_r.TIM8_PWM_Period;
    TIM_SetCompare2(TIM8,Pwm_Value);
    pwm_out_data_r.TIM8_PWM2 = Pwm_Value ;
}
void Pwm_Set_TIM8_CCR3(unsigned short int Pwm_Value)
{
    if( Pwm_Value <= 0 ) Pwm_Value = 0 ;
    if( Pwm_Value >= pwm_out_data_r.TIM8_PWM_Period  ) Pwm_Value = pwm_out_data_r.TIM8_PWM_Period;
    TIM_SetCompare3(TIM8,Pwm_Value);
    pwm_out_data_r.TIM8_PWM3 = Pwm_Value ;
}
void Pwm_Set_TIM8_CCR4(unsigned short int Pwm_Value)
{
    if( Pwm_Value <= 0 ) Pwm_Value = 0 ;
    if( Pwm_Value >= pwm_out_data_r.TIM8_PWM_Period  ) Pwm_Value = pwm_out_data_r.TIM8_PWM_Period;
    TIM_SetCompare4(TIM8,Pwm_Value);
    pwm_out_data_r.TIM8_PWM4 = Pwm_Value ;
}

#endif 

#ifdef __cplusplus
}
#endif 
