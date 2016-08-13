#ifndef __rtc_H__
#define __rtc_H__

#ifdef __cplusplus
extern "C" {
#endif 

#include "stm32f10x.h"
#include "main_config.h"

//time structure
typedef struct
{
    volatile  unsigned char hour;
    volatile  unsigned char min;
    volatile  unsigned char sec;
    //Gregorian calendar
    volatile  unsigned short int w_year;
    volatile  unsigned char  w_month;
    volatile  unsigned char  w_date;
    volatile  unsigned char  week;
}CALENDAR;


extern CALENDAR calendar_r;	//calendar strcuture

//////
unsigned char HF_RTC_Init(void);						//RTC initialization
void HF_RTC_Time_Renew(void);	  //renew time structure

unsigned char RTC_Get_Week(unsigned short int year, unsigned char month, unsigned char day);

//unsigned char RTC_Init(void);        //Initialize RTC,return 0-->failed,retuen 1-->succeeded.
void RTC_Alarm_Set(unsigned short int syear, unsigned char smon, unsigned char sday, unsigned char hour, unsigned char min, unsigned char sec);
unsigned char RTC_Set(unsigned short int syear, unsigned char smon, unsigned char sday, unsigned char hour, unsigned char min, unsigned char sec);//set time


#ifdef __cplusplus
}
#endif 

#endif //__rtc_H__


