#ifndef WDG_WKUP_H
#define WDG_WKUP_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "stm32f10x.h"

void HF_IWDG_Init(void);
void HF_IWDG_Feed(void);

void HF_WWDG_Init(uint8_t tr, uint8_t wr, uint32_t fprer); //Initialize WDG
void HF_WWDG_Set_Counter(uint8_t cnt); //Set the counter of WDG

#define WKUP_KD  GPIOA->IDR & GPIO_Pin_0   //PA0 check if have WK_UP KEY pressed
void HF_WKUP_Init(void);                   //PA0 WKUP Initialization

#ifdef __cplusplus
}
#endif 

#endif // #ifndef WDG_WKUP_H
