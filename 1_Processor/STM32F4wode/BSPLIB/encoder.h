#ifndef ENCODER_H
#define ENCODER_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "stm32f4xx.h"
	
// TIM2 CHI1 CHI2---PA0 PA1 || PA15 PB3     TIM3 CHI1 CHI2---PA6 PA7 || PB4 PB5
// TIM4 CHI1 CHI2---PB6 PB7 || PD12 PD13    TIM5 CHI1 CHI2---PA0 PA1
//Initialize encoder mode, input parameter TIM2 TIM3 TIM4 TIM5
void HF_Encoder_Init(TIM_TypeDef* TIMx, uint8_t GPIO_AF);
float HF_Get_Encode_TIM2(void);
float HF_Get_Encode_TIM3(void);
float HF_Get_Encode_TIM4(void);
float HF_Get_Encode_TIM5(void);

#ifdef __cplusplus
}
#endif 

#endif // #ifndef ENCODER_H


