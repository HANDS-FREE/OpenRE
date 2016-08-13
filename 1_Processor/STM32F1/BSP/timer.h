#ifndef __timer_H__
#define __timer_H__

#ifdef __cplusplus
extern "C" {
#endif 

#include "stm32f10x.h"
#include "main_config.h"


void HF_Timer_Init(TIM_TypeDef* TIMx, int Time_us);	//Input parameter :TIMx and delay time(us), *timer2--7     1ms


#ifdef __cplusplus
}
#endif 

#endif //#ifndef __timer_H__


