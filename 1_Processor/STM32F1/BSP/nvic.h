#ifndef __nvic_H__
#define __nvic_H__

#ifdef __cplusplus
extern "C" {
#endif 

#include "stm32f10x.h"

void CAN1_NVIC_Configuration(void);
void CAN2_NVIC_Configuration(void);
void USART1_NVIC_Configuration(void);
void USART2_NVIC_Configuration(void);
void USART3_NVIC_Configuration(void);
void UART4_NVIC_Configuration(void);
void UART5_NVIC_Configuration(void);
void TIM2_NVIC_Configuration(void);
void TIM3_NVIC_Configuration(void);
void TIM4_NVIC_Configuration(void);
void TIM5_NVIC_Configuration(void);
void TIM6_NVIC_Configuration(void);
void TIM7_NVIC_Configuration(void);
void TIM8_NVIC_Configuration(void);
void EXTI0_NVIC_Configuration(void);
void EXTI1_NVIC_Configuration(void);
void EXTI2_NVIC_Configuration(void);
void EXTI3_NVIC_Configuration(void);
void EXTI4_NVIC_Configuration(void);
void EXTI9_5_NVIC_Configuration(void);
void EXTI15_10_NVIC_Configuration(void);



#ifdef __cplusplus
}
#endif 

#endif //__nvic_H__
