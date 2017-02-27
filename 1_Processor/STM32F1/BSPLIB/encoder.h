#ifndef ENCODER_H
#define ENCODER_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "stm32f10x.h"

/*TIM2 CHI1 CHI2---PA0 PA1  TIM3 CHI1 CHI2---PA6 PA7||
 * TIM3 CHI1 CHI2---PB4 PB5 TIM4 CHI1 CHI2---PB6 PB7 */
//Initialize encoder mode, input parameter TIM1 TIM2 TIM3, Grating_count is the number of grating.
void HF_Encoder_Init(TIM_TypeDef* TIMx , unsigned char GPIO_AF);
float HF_Get_Encode_TIM5(void);//What you get here is the total angle.
float HF_Get_Encode_TIM4(void);
float HF_Get_Encode_TIM3(void);
float HF_Get_Encode_TIM2(void);

#ifdef __cplusplus
}
#endif 

#endif // #ifndef ENCODER_H


