#ifndef __wdg_H__
#define __wdg_H__

#ifdef __cplusplus
extern "C" {
#endif 

#include "stm32f10x.h"
#include "main_config.h"

void HF_IWDG_Init(void);
void HF_IWDG_Feed(void);

void HF_WWDG_Init(u8 tr, u8 wr, u32 fprer);//Initialize WDG
void HF_WWDG_Set_Counter(u8 cnt);       //Set the counter of WDG

#define WKUP_KD  GPIOA->IDR & GPIO_Pin_0		//PA0 check if have WK_UP KEY pressed
void HF_WKUP_Init(void); 			//PA0 WKUP Initialization

#ifdef __cplusplus
}
#endif 	

#endif
