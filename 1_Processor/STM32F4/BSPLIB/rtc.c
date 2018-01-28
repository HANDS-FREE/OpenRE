/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* Contact:  QQ Exchange Group -- 521037187
*
* LICENSING TERMS:  
* The Hands Free is licensed generally under a permissive 3-clause BSD license. 
* Contributions are requiredto be made under the same license.
*
* History: 
* <author>      <time>      <version>      <desc>
* mawenke       2015.10.1   V1.0           creat this file 
* Lidexin       2015.10.1   V1.0           creat this file       
*   
* Description:
*        RTC Driver Code
*        STM32F4--------------
*        no using Pin source
************************************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif 

#include "rtc.h"	 
#include "delay.h"
#include "usart.h"

//RTOS
#if SYSTEM_SUPPORT_OS==1
#include "includes.h"
#endif

/***********************************************************************************************************************
* Function:    ErrorStatus RTC_Set_Time(uint8_t hour,uint8_t min,uint8_t sec,uint8_t ampm)
* 
* Scope:      
* 
* Description:  RTC time config
*               hour,min,sec:hour, minute, second
*								ampm:@RTC_AM_PM_Definitions  :RTC_H12_AM/RTC_H12_PM
* Arguments: 
* 
* Return: 1,succeed
* 				0,failed to initialize
* Cpu_Time:  stm32f4
* 
* History:
***********************************************************************************************************************/
ErrorStatus RTC_Set_Time(uint8_t hour,uint8_t min,uint8_t sec,uint8_t ampm)
{
    RTC_TimeTypeDef RTC_TimeTypeInitStructure;
    
    RTC_TimeTypeInitStructure.RTC_Hours=hour;
    RTC_TimeTypeInitStructure.RTC_Minutes=min;
    RTC_TimeTypeInitStructure.RTC_Seconds=sec;
    RTC_TimeTypeInitStructure.RTC_H12=ampm;
    
    return RTC_SetTime(RTC_Format_BIN,&RTC_TimeTypeInitStructure);
}

/***********************************************************************************************************************
* Function:    ErrorStatus RTC_Set_Date(uint8_t year,uint8_t month,uint8_t date,uint8_t week)
* 
* Scope:      
* 
* Description:  RTC date config 
*               year,month,date:year(0~99),month(1~12),day(0~31)
*								week:week(1~7,0,ilegal!)
* Arguments: 
* 
* Return: 1,succeed
* 				0,failed to initialize
* Cpu_Time:  stm32f4
* 
* History:
***********************************************************************************************************************/
ErrorStatus RTC_Set_Date(uint8_t year,uint8_t month,uint8_t date,uint8_t week)
{
    
    RTC_DateTypeDef RTC_DateTypeInitStructure;
    
    RTC_DateTypeInitStructure.RTC_Date=date;
    RTC_DateTypeInitStructure.RTC_Month=month;
    RTC_DateTypeInitStructure.RTC_WeekDay=week;
    RTC_DateTypeInitStructure.RTC_Year=year;
    
    return RTC_SetDate(RTC_Format_BIN,&RTC_DateTypeInitStructure);
}

/***********************************************************************************************************************
* Function:    void RTC_Get_Time(uint8_t *hour,uint8_t *min,uint8_t *sec,uint8_t *ampm)
* 
* Scope:      
* 
* Description:  get RTC time 
*               *hour,*min,*sec: hour,min,sec
*								*ampm:@RTC_AM_PM_Definitions  :RTC_H12_AM/RTC_H12_PM.
* Arguments: 
* 
* Return:
* 				
* Cpu_Time:  stm32f4
* 
* History: 
***********************************************************************************************************************/
void RTC_Get_Time(uint8_t* hour,uint8_t* min,uint8_t* sec,uint8_t* ampm)
{
    RTC_TimeTypeDef RTC_TimeStruct;
    RTC_GetTime(RTC_Format_BIN,&RTC_TimeStruct);
    
    *hour=RTC_TimeStruct.RTC_Hours;
    *min=RTC_TimeStruct.RTC_Minutes;
    *sec=RTC_TimeStruct.RTC_Seconds;
    *ampm=RTC_TimeStruct.RTC_H12;
}

/***********************************************************************************************************************
* Function:    void RTC_Get_Date(uint8_t *year,uint8_t *month,uint8_t *date,uint8_t *week)
* 
* Scope:      
* 
* Description:  get RTC date
*               *year,*mon,*date: year,mon,date
*								*week:week
* Arguments: 
* 
* Return:
* 				
* Cpu_Time:  stm32f4
* 
* History:
***********************************************************************************************************************/
void RTC_Get_Date(uint8_t* year,uint8_t* month,uint8_t* date,uint8_t* week)
{
    RTC_DateTypeDef  RTC_DateStruct;
    RTC_GetDate(RTC_Format_BIN, &RTC_DateStruct);
    
    *year=RTC_DateStruct.RTC_Year;
    *month=RTC_DateStruct.RTC_Month;
    *date=RTC_DateStruct.RTC_Date;
    *week=RTC_DateStruct.RTC_WeekDay;
}

/***********************************************************************************************************************
* Function:    uint8_t HF_RTC_Init(void)
* 
* Scope:      
* 
* Description: 
*       
* Arguments: 
* 
* Return: 1,succeed
* 				0,failed to initialize LSE
* 				
* Cpu_Time:  stm32f4
* 
* History: 
***********************************************************************************************************************/
uint8_t HF_RTC_Init(void)
{
    RTC_InitTypeDef RTC_InitStructure;
    uint16_t retry=0X1FFF;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);//ENABLE clock of PWR
    PWR_BackupAccessCmd(ENABLE);//enable access of backup register
    
    if(RTC_ReadBackupRegister(RTC_BKP_DR0)!=0x5050)//check if is first configuration of RTC
    {
        RCC_LSEConfig(RCC_LSE_ON);//ENABLE LSE
        while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)//check if set flag of RCC, and wait LSE is ready
        {
            retry++;
            delay_ms(10);
        }
        if(retry==0)return 1;//Initialize clock failed, the Crystal has error
        
        RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);//set LSE to be the clock of RTC
        RCC_RTCCLKCmd(ENABLE);//enable RTC
        
        RTC_InitStructure.RTC_AsynchPrediv = 0x7F;//RTC Prescaler(1~0X7F)
        RTC_InitStructure.RTC_SynchPrediv  = 0xFF;//RTC Prescaler(0~7FFF)
        RTC_InitStructure.RTC_HourFormat   = RTC_HourFormat_24;//SET RTC 24 hours mode
        RTC_Init(&RTC_InitStructure);
        
        RTC_Set_Time(00,00,00,RTC_H12_AM);//set time
        RTC_Set_Date(16,1,1,5);//set date
        
        RTC_WriteBackupRegister(RTC_BKP_DR0,0x5050);//have initialized
    }
    return 0;
}

/***********************************************************************************************************************
* Function:    void RTC_Set_AlarmA(uint8_t week,uint8_t hour,uint8_t min,uint8_t sec)
* 
* Scope:      
* 
* Description:  Initialize clock
*    transform the time data to seconds 
*    time base is 1,1,1970
*    legal input is 1970~2099
*    return 0-->succeeded,others-->failed 
*
* Arguments: 
* 
* Return:
* 				
* Cpu_Time:  stm32f4
* 
* History: 
***********************************************************************************************************************/
void RTC_Set_AlarmA(uint8_t week,uint8_t hour,uint8_t min,uint8_t sec)
{ 
    EXTI_InitTypeDef EXTI_InitStructure;
    RTC_AlarmTypeDef RTC_AlarmTypeInitStructure;
    RTC_TimeTypeDef RTC_TimeTypeInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    RTC_AlarmCmd(RTC_Alarm_A,DISABLE);//disable alarm clock A
    
    RTC_TimeTypeInitStructure.RTC_Hours=hour;//hour
    RTC_TimeTypeInitStructure.RTC_Minutes=min;//minute
    RTC_TimeTypeInitStructure.RTC_Seconds=sec;//second
    RTC_TimeTypeInitStructure.RTC_H12=RTC_H12_AM;
    
    RTC_AlarmTypeInitStructure.RTC_AlarmDateWeekDay=week;//week
    RTC_AlarmTypeInitStructure.RTC_AlarmDateWeekDaySel=RTC_AlarmDateWeekDaySel_WeekDay;//according to week to ring
    RTC_AlarmTypeInitStructure.RTC_AlarmMask=RTC_AlarmMask_None;//accurate to match week
    RTC_AlarmTypeInitStructure.RTC_AlarmTime=RTC_TimeTypeInitStructure;
    RTC_SetAlarm(RTC_Format_BIN,RTC_Alarm_A,&RTC_AlarmTypeInitStructure);
    
    
    RTC_ClearITPendingBit(RTC_IT_ALRA);//clear flag of alarm clock A
    EXTI_ClearITPendingBit(EXTI_Line17);//clear flag of Interrupt LINE17
    
    RTC_ITConfig(RTC_IT_ALRA,ENABLE);//enable alarm clock A interrupt
    RTC_AlarmCmd(RTC_Alarm_A,ENABLE);//enable alarm clock A
    
    EXTI_InitStructure.EXTI_Line = EXTI_Line17;//LINE17
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//interrupt event
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //touch off at rising
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;//enable LINE17
    EXTI_Init(&EXTI_InitStructure);//configuration
    
    NVIC_InitStructure.NVIC_IRQChannel = RTC_Alarm_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//PreemptionPriority
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//SubPriority
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//enable external interrupt
    NVIC_Init(&NVIC_InitStructure);//configuration
    
    
}

/***********************************************************************************************************************
* Function:    void RTC_Set_WakeUp(uint32_t wksel,uint16_t cnt)
* 
* Scope:      
* 
* Description: configure cycle wake-up timer
*							 wksel:
*							 #define RTC_WakeUpClock_RTCCLK_Div16        ((uint32_t)0x00000000)
*							 #define RTC_WakeUpClock_RTCCLK_Div8         ((uint32_t)0x00000001)
*							 #define RTC_WakeUpClock_RTCCLK_Div4         ((uint32_t)0x00000002)
*							 #define RTC_WakeUpClock_RTCCLK_Div2         ((uint32_t)0x00000003)
*							 #define RTC_WakeUpClock_CK_SPRE_16bits      ((uint32_t)0x00000004)
*							 #define RTC_WakeUpClock_CK_SPRE_17bits      ((uint32_t)0x00000006)
*							 cnt:value to auto reload, when decreasing to 0 will touch off interrupt
*
* Arguments: 
* 
* Return:
* 				
* Cpu_Time:  stm32f4
* 
* History: 
***********************************************************************************************************************/
void RTC_Set_WakeUp(uint32_t wksel,uint16_t cnt)
{ 
    EXTI_InitTypeDef   EXTI_InitStructure;
    NVIC_InitTypeDef   NVIC_InitStructure;
    
    RTC_WakeUpCmd(DISABLE);//disable WAKE UP
    RTC_WakeUpClockConfig(wksel);//choose wake-up timer
    RTC_SetWakeUpCounter(cnt);//config  auto reload register of WAKE-UP
    
    RTC_ClearITPendingBit(RTC_IT_WUT); //clear flag of RTC WAKE UP
    EXTI_ClearITPendingBit(EXTI_Line22);//clear interrupt flag of LINE22
    
    RTC_ITConfig(RTC_IT_WUT,ENABLE);//enable WAKE UP timer interrupt
    RTC_WakeUpCmd( ENABLE);//enable WAKE UP timer
    
    EXTI_InitStructure.EXTI_Line = EXTI_Line22;//LINE22
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//interrupt event
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //touch off at rising
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;//enable interrupt LINE22
    EXTI_Init(&EXTI_InitStructure);//configuration
    
    NVIC_InitStructure.NVIC_IRQChannel = RTC_WKUP_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//PreemptionPriority
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//SubPriority
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//enable external interrupt channel
    NVIC_Init(&NVIC_InitStructure);//configuration
}

/***********************************************************************************************************************
* Function:    void RTC_Alarm_IRQHandler(void)
* 
* Scope:      
* 
* Description: RTC alarm clock interrupt program
*       
* Arguments: 
* 
* Return:	
* 				
* Cpu_Time:  stm32f4
* 
* History:   
***********************************************************************************************************************/
void RTC_Alarm_IRQHandler(void)
{ 
#if SYSTEM_SUPPORT_OS == 1
    OSIntEnter();
#endif
    
    if(RTC_GetFlagStatus(RTC_FLAG_ALRAF)==SET)//ALARM A interrupt
    {
        RTC_ClearFlag(RTC_FLAG_ALRAF);//clear interrupt flag
    }
    EXTI_ClearITPendingBit(EXTI_Line17);	//clear interrupt line17 flag
    
#if SYSTEM_SUPPORT_OS == 1
    OSIntExit();
#endif
}

/***********************************************************************************************************************
* Function:    void RTC_WKUP_IRQHandler(void)
* 
* Scope:      
* 
* Description: RTC wake-up interrupt program
*       
* Arguments: 
* 
* Return:	
* 				
* Cpu_Time:  stm32f4
* 
* History:
***********************************************************************************************************************/
void RTC_WKUP_IRQHandler(void)
{  
#if SYSTEM_SUPPORT_OS == 1
    OSIntEnter();
#endif
    
    if(RTC_GetFlagStatus(RTC_FLAG_WUTF)==SET)//WK_UP interrupt
    {
        RTC_ClearFlag(RTC_FLAG_WUTF);	//clear interrupt flag
    }
    EXTI_ClearITPendingBit(EXTI_Line22);//clear interrupt line22 flag
    
#if SYSTEM_SUPPORT_OS == 1
    OSIntExit();
#endif
}

uint8_t const table_week[12]={0,3,3,6,1,4,6,2,5,0,3,5}; //month correct data
/***********************************************************************************************************************
* Function:    uint8_t RTC_Get_Week(uint16_t year,uint8_t month,uint8_t day)
* 
* Scope:      
* 
* Description: Input date data to get week data
*							 legal input is 1901-2099
*							 year,month,day：Gregorian calendar date
*
* Arguments: 
* 
* Return:	week data	
* 				
* Cpu_Time:  stm32f4
* 
* History:
***********************************************************************************************************************/
uint8_t RTC_Get_Week(uint16_t year,uint8_t month,uint8_t day)
{	
    uint16_t temp2;
    uint8_t yearH,yearL;
    
    yearH=year/100;	yearL=year%100;
    //if 21th century, year need add 100
    if (yearH>19)yearL+=100;
    //leap year only calculate after 1900
    temp2=yearL+yearL/4;
    temp2=temp2%7;
    temp2=temp2+day+table_week[month-1];
    if (yearL%4==0&&month<3)temp2--;
    temp2%=7;
    if(temp2==0)temp2=7;
    return temp2;
}	

/***********************************************************************************************************************
* Function:    void HF_RTC_Time_Renew(void)
* 
* Scope:      
* 
* Description: RTC time update function
*       
* Arguments: 
* 
* Return:	
* 				
* Cpu_Time:  stm32f4
* 
* History: 
***********************************************************************************************************************/
void HF_Get_RTC_Time(uint8_t* year , uint8_t* month , uint8_t* date , uint8_t* week
                     ,uint8_t* hour , uint8_t* min , uint8_t* sec , uint8_t* ampm)
{
    RTC_Get_Date(year , month , date , week);  //get RTC date
    RTC_Get_Time(hour , min , sec , ampm);     //get RTC time
}

#ifdef __cplusplus
}
#endif 


