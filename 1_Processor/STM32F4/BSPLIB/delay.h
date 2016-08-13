#ifndef DELAY_H
#define DELAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx.h"
#include "main_config.h"

/**********************************************************************************************************************/
void delay_init(void);
void delay_ms(uint16_t t);    //using timer to delay time, max delay time is 1864ms
void delay_us(uint16_t t);    //using timer to delay time, max delay time is 1864ms
/**********************************************************************************************************************/
void HF_System_Timer_Init(void);  //Initialize the Time measurement system
float HF_Get_System_Time(void);   //Return the current time(us), max:281474976s--->3257.8 days
float HF_Get_Dtime(void);         // Return the time difference(us). max:655s

#ifdef __cplusplus
}
#endif

#endif  // #ifndef DELAY_H
