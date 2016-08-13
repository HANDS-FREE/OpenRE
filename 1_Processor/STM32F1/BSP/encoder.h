#ifndef __encoder_H__
#define __encoder_H__

#ifdef __cplusplus
extern "C" {
#endif 

#include "stm32f10x.h"
#include "main_config.h"

/*TIM2 CHI1 CHI2---PA0 PA1  TIM3 CHI1 CHI2---PA6 PA7||
 * TIM3 CHI1 CHI2---PB4 PB5 TIM4 CHI1 CHI2---PB6 PB7 */
//Initialize encoder mode, input parameter TIM1 TIM2 TIM3
void HF_Encoder_Init(TIM_TypeDef* TIMx, unsigned char GPIO_AF);

typedef struct ENCODER_Data{
    float TIM2_Count;        //current pulse number, Negative or positive mean different direction
    float TIM3_Count;        //current pulse number, Negative or positive mean different direction
    float TIM4_Count;        //current pulse number, Negative or positive mean different direction
}ENCODER_Data;

extern ENCODER_Data encoder_data_r;

#ifdef __cplusplus
}
#endif 

#endif //encoder.h


