#ifndef PWM_OUT_H
#define PWM_OUT_H

#ifdef __cplusplus
extern "C" {
#endif 
	
#include "stm32f4xx.h"
	
//PWM initialization, parameter TIM1,PA8,9,10,11 TIM8 PC6,7,8,9    default Prescaler :72-1  frequency:1MHZ   default cycle:2000-->20ms
void HF_PWMOut_Init(TIM_TypeDef* TIMx, uint16_t Prescaler, uint16_t Period, uint8_t GPIO_AF);

void HF_PWM_Set_TIM1_CCR1(uint16_t Pwm_Value);
void HF_PWM_Set_TIM1_CCR2(uint16_t Pwm_Value);
void HF_PWM_Set_TIM1_CCR3(uint16_t Pwm_Value);
void HF_PWM_Set_TIM1_CCR4(uint16_t Pwm_Value);
void HF_PWM_Set_TIM8_CCR1(uint16_t Pwm_Value);
void HF_PWM_Set_TIM8_CCR2(uint16_t Pwm_Value);
void HF_PWM_Set_TIM8_CCR3(uint16_t Pwm_Value);
void HF_PWM_Set_TIM8_CCR4(uint16_t Pwm_Value);
void HF_PWM_Set_TIM9_CCR1(uint16_t Pwm_Value);
void HF_PWM_Set_TIM9_CCR2(uint16_t Pwm_Value);
void HF_PWM_Set_TIM12_CCR1(uint16_t Pwm_Value);
void HF_PWM_Set_TIM12_CCR2(uint16_t Pwm_Value);

#ifdef __cplusplus
}
#endif 

#endif // #ifndef PWM_OUT_H


