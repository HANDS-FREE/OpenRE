#ifndef ENCODER_H
#define ENCODER_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "stm32f10x.h"

//Initialize encoder mode, input parameter TIM2 TIM3 TIM4 TIM5
void HF_Encoder_Init(TIM_TypeDef* TIMx, uint8_t GPIO_AF);
float HF_Get_Encode_TIM2(void); //What you get here is the total angle.
float HF_Get_Encode_TIM3(void);
float HF_Get_Encode_TIM4(void);
float HF_Get_Encode_TIM5(void);

#ifdef __cplusplus
}
#endif 

#endif // #ifndef ENCODER_H


