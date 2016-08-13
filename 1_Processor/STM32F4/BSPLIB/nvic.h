#ifndef NVIC_H
#define NVIC_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "stm32f4xx.h"

void CAN1_RX0_NVIC_Configuration(void);
void CAN1_RX1_NVIC_Configuration(void);
void CAN2_RX0_NVIC_Configuration(void);
void CAN2_RX1_NVIC_Configuration(void);

void USART1_NVIC_Configuration(void);
void USART2_NVIC_Configuration(void);
void USART3_NVIC_Configuration(void);
void UART4_NVIC_Configuration(void);
void UART5_NVIC_Configuration(void);
void USART6_NVIC_Configuration(void);
void TIM1_NVIC_Configuration(void);
void TIM2_NVIC_Configuration(void);
void TIM3_NVIC_Configuration(void);
void TIM4_NVIC_Configuration(void);
void TIM5_NVIC_Configuration(void);
void TIM6_NVIC_Configuration(void);
void TIM7_NVIC_Configuration(void);
void TIM8_NVIC_Configuration(void);
void TIM9_NVIC_Configuration(void);
void TIM10_NVIC_Configuration(void);
void TIM11_NVIC_Configuration(void);
void TIM12_NVIC_Configuration(void);
void TIM13_NVIC_Configuration(void);
void TIM14_NVIC_Configuration(void);

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

#endif // #ifndef NVIC_H
