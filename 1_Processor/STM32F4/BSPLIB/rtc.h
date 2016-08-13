#ifndef RTC_H
#define RTC_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "stm32f4xx.h"

//calendar strcuture
typedef struct
{
    volatile unsigned char hour;
    volatile unsigned char min;
    volatile unsigned char sec;
    volatile unsigned char ampm;
    //Gregorian calendar
    volatile unsigned char  w_year;
    volatile unsigned char  w_month;
    volatile unsigned char  w_date;
    volatile unsigned char  week;
}CALENDAR;
extern CALENDAR calendar_r;

unsigned char HF_RTC_Init(void); //RTC initialization
void HF_RTC_Time_Renew(void);    //renew time structure

ErrorStatus RTC_Set_Time(unsigned char hour, unsigned char min, unsigned char sec, unsigned char ampm);//RTC time config
ErrorStatus RTC_Set_Date(unsigned char year, unsigned char month, unsigned char date, unsigned char week);//RTC date config
void RTC_Set_AlarmA(unsigned char week, unsigned char hour, unsigned char min, unsigned char sec);//set alarm clock time
void RTC_Set_WakeUp(u32 wksel, u16 cnt);//config cycle wake-up timer

#ifdef __cplusplus
}
#endif 

#endif // RTC_H


