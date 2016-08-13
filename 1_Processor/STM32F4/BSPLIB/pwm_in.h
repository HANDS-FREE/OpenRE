#ifndef PWM_IN_H
#define PWM_IN_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "stm32f4xx.h"

void HF_PWMIN_Init(uint16_t hf_pwmin_channel , uint8_t pwmin_num);
float HF_Get_PWM_Value(uint8_t channel_x);

#ifdef __cplusplus
}
#endif 

#endif // #ifndef PWM_IN_H
