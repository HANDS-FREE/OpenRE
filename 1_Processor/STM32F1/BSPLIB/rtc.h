#ifndef RTC_H
#define RTC_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "stm32f10x.h"

unsigned char HF_RTC_Init(void); //RTC initialization
void HF_Get_RTC_Time(uint8_t* year , uint8_t* month , uint8_t* date , uint8_t* week,
                     uint8_t* hour , uint8_t* min , uint8_t* sec , uint8_t* ampm);

unsigned char RTC_Get_Week(unsigned short int year, unsigned char month, unsigned char day);

void RTC_Alarm_Set(unsigned short int syear, unsigned char smon, unsigned char sday,
                   unsigned char hour, unsigned char min, unsigned char sec);
unsigned char RTC_Set(unsigned short int syear, unsigned char smon, unsigned char sday,
                      unsigned char hour, unsigned char min, unsigned char sec);//set time

#ifdef __cplusplus
}
#endif 

#endif // RTC_H


