#ifndef RTC_H
#define RTC_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "stm32f4xx.h"

uint8_t HF_RTC_Init(void); //RTC initialization
void HF_Get_RTC_Time(uint8_t* year , uint8_t* month , uint8_t* date , uint8_t* week,
                     uint8_t* hour , uint8_t* min , uint8_t* sec , uint8_t* ampm);

ErrorStatus RTC_Set_Time(uint8_t hour, uint8_t min, uint8_t sec, uint8_t ampm);//RTC time config
ErrorStatus RTC_Set_Date(uint8_t year, uint8_t month, uint8_t date, uint8_t week);//RTC date config
void RTC_Set_AlarmA(uint8_t week, uint8_t hour, uint8_t min, uint8_t sec);//set alarm clock time
void RTC_Set_WakeUp(uint32_t wksel, uint16_t cnt);//config cycle wake-up timer

#ifdef __cplusplus
}
#endif 

#endif // RTC_H


