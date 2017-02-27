#ifndef PWM_IN_H
#define PWM_IN_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "stm32f4xx.h"

//pwm in channel 0
#define  RCC_PWM_IN_CHANNEL0        RCC_AHB1Periph_GPIOB
#define  GPIO_PWM_IN_CHANNEL0      GPIOB
#define  EXTI_PWM_IN_CHANNEL0        EXTI_PortSourceGPIOB

//pwm in channel 1
#define  RCC_PWM_IN_CHANNEL1        RCC_AHB1Periph_GPIOC
#define  GPIO_PWM_IN_CHANNEL1      GPIOC
#define  EXTI_PWM_IN_CHANNEL1        EXTI_PortSourceGPIOC

//pwm in channel 2
#define  RCC_PWM_IN_CHANNEL2        RCC_AHB1Periph_GPIOC
#define  GPIO_PWM_IN_CHANNEL2      GPIOC
#define  EXTI_PWM_IN_CHANNEL2        EXTI_PortSourceGPIOC

//pwm in channel 3
#define  RCC_PWM_IN_CHANNEL3        RCC_AHB1Periph_GPIOC
#define  GPIO_PWM_IN_CHANNEL3      GPIOC
#define  EXTI_PWM_IN_CHANNEL3        EXTI_PortSourceGPIOC

//pwm in channel 4
#define  RCC_PWM_IN_CHANNEL4        RCC_AHB1Periph_GPIOC
#define  GPIO_PWM_IN_CHANNEL4      GPIOC
#define  EXTI_PWM_IN_CHANNEL4        EXTI_PortSourceGPIOC

//pwmin_channel = 0,1,2,3,4
//PC0 PC1 PC2 PC3 PC4  external interrupt
void HF_PWMIN_Init(uint8_t pwmin_channel);
float HF_Get_PWM_Value(uint8_t channel_x); //current input value of PWM (Unit:us)

#ifdef __cplusplus
}
#endif 

#endif // #ifndef PWM_IN_H
