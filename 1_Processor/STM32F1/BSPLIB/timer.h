#ifndef TIMER_H
#define TIMER_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "stm32f10x.h"

void HF_Timer_Init(TIM_TypeDef* TIMx, uint32_t Time_us);//Input parameter :TIMx and delay time(us), *timer2--7     1ms

#ifdef __cplusplus
}
#endif 

#endif //#ifndef TIMER_H


