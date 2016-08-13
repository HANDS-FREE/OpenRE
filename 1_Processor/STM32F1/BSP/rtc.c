/***********************************************************************************************************************
* Copyright (C)  ALIENTEK Mini STM32开发板 Copyright(C) 正点原子
* FileName:   rtc.c
* Contact:    QQ Exchange Group -- 521037187
* Version :   V2.0
*
* LICENSING TERMS:  
* The Hands Free is licensed generally under a permissive 3-clause BSD license. 
* Contributions are requiredto be made under the same license.
*
* History:  
* History: 
* <author>    <time>      <version >       <desc>
* ALIENTEK Mini STM32开发板 Copyright(C) 正点原子 
* LiuDong    2016.1.8       V1.57       update the name of function
* Lidexin    2016.1.11      V1.58       change the function RTC_Get_Week() and the function HF_RTC_Init()
*
* Description: 
*        STM32F1--------------
*        no using Pin source
***********************************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif 

#include "rtc.h"	 
#include "delay.h"
#include "usart.h"
	
CALENDAR calendar_r;//clock structure

#if BSP_CFG_RTC_EN > 0u

//month data table											 
unsigned char const table_week[12]={0,3,3,6,1,4,6,2,5,0,3,5}; //month correct data
//month data table of normal year
const unsigned char mon_table[12]={31,28,31,30,31,30,31,31,30,31,30,31};

/***********************************************************************************************************************
* Function:     static unsigned char Is_Leap_Year(unsigned short int year)
* 
* Scope:      
* 
* Description:  judge whether is leap year
*               month          1  2  3  4  5  6  7  8  9  10 11 12	
*               leap year      31 29 31 30 31 30 31 31 30 31 30 31
*               not leap year  31 28 31 30 31 30 31 31 30 31 30 31
* Input : Year
* Arguments: 
* 
* Return:       1,is leap year
* 				0,not is leap year
* Cpu_Time:
* 
* History:
* ALIENTEK Mini STM32开发板 Copyright(C) 正点原子
* by   mawenke   2015.12.1     
************************************************************************************************************************/
static unsigned char Is_Leap_Year(unsigned short int year)
{			  
    if(year%4==0) //must be divisible by 4
    {
        if(year%100==0)
        {
            if(year%400==0)return 1;//If end is 00, must be divisible by 400
            else return 0;
        }else return 1;
    }else return 0;
}	 		

/************************************************************************************************************************
* Function:    unsigned char RTC_Get_Week(unsigned short int year,unsigned char month,unsigned char day)
* 
* Scope:      
* 
* Description: Input date data to get week data
*              legal input is 1901-2099
*			   year,month,day：Gregorian calendar date
*
* Arguments: 
* 
* Return:	   week data
* 				
* Cpu_Time:
* 
* History:  
* ALIENTEK Mini STM32开发板 Copyright(C) 正点原子
* by   mawenke   2015.12.1  
*************************************************************************************************************************/
unsigned char RTC_Get_Week(unsigned short int year,unsigned char month,unsigned char day)
{	
    
    unsigned short int temp2;
    unsigned char yearH,yearL;
    
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

/*************************************************************************************************************************
* Function:    static unsigned char RTC_Get(void)
* 
* Scope:      
* 
* Description: get current time
*
* Arguments: 
* 
* Return:	   0-->succeeded  others-->failed
* 				
* Cpu_Time:
* 
* History:  
* ALIENTEK Mini STM32开发板 Copyright(C) 正点原子
* by   mawenke   2015.12.1  
**************************************************************************************************************************/
static unsigned char RTC_Get(void)
{
    static unsigned short int daycnt=0;
    unsigned int timecount=0;
    unsigned int temp=0;
    unsigned short int temp1=0;
    timecount=RTC_GetCounter();
    temp=timecount/86400;   //get days(correspond the second)
    if(daycnt!=temp)//over one day
    {
        daycnt=temp;
        temp1=1970;	//start at 1970
        while(temp>=365)
        {
            if(Is_Leap_Year(temp1))//is leap year
            {
                if(temp>=366)temp-=366;//the seconds of leap year
                else {temp1++;break;}
            }
            else temp-=365;	  //normal year
            temp1++;
        }
        calendar_r.w_year=temp1;//get year
        temp1=0;
        while(temp>=28)//over one month
        {
            if(Is_Leap_Year(calendar_r.w_year)&&temp1==1)//judge if is leap month (February)
            {
                if(temp>=29)temp-=29;//the seconds of leap year
                else break;
            }
            else
            {
                if(temp>=mon_table[temp1])temp-=mon_table[temp1];//normal year
                else break;
            }
            temp1++;
        }
        calendar_r.w_month=temp1+1;	//get month
        calendar_r.w_date=temp+1;  	//get date
    }
    temp=timecount%86400;     		//get second
    calendar_r.hour=temp/3600;     	//hour
    calendar_r.min=(temp%3600)/60; 	//minute
    calendar_r.sec=(temp%3600)%60; 	//second
    calendar_r.week=RTC_Get_Week(calendar_r.w_year,calendar_r.w_month,calendar_r.w_date);//get week
    return 0;
}	 

/*************************************************************************************************************************
* Function:    RTC_NVIC_Config(void)
*
* Scope:       private
*
* Description: RTC Configuration of Interruption
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
* ALIENTEK Mini STM32开发板 Copyright(C) 正点原子
* by   mawenke   2015.12.1
**************************************************************************************************************************/
static void RTC_NVIC_Config(void)
{	
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;		//RTC Global Interrupt
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//PreemptionPriority
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	//SubPriority
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		//ENABLE  the interrupt
    NVIC_Init(&NVIC_InitStructure);		//Initialize the NVIC register
}

/*************************************************************************************************************************
* Function:    RTC_IRQHandler(void)
*
* Scope:       private
*
* Description: RTC Interruptation update every second
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
* ALIENTEK Mini STM32开发板 Copyright(C) 正点原子
* by   mawenke   2015.12.1
**************************************************************************************************************************/
void RTC_IRQHandler(void)
{		 
#if SYSTEM_SUPPORT_OS == 1
    OSIntEnter();
#endif
    
    if (RTC_GetITStatus(RTC_IT_SEC) != RESET)//RTC Interruptation
    {
        RTC_Get();//更新时间
    }
    if(RTC_GetITStatus(RTC_IT_ALR)!= RESET)//alarm clock interrupt
    {
        
        RTC_ClearITPendingBit(RTC_IT_ALR);		//clear clock interrupt
        RTC_Get();				//update time
        // 	printf("Alarm Time:%d-%d-%d %d:%d:%d\n",calendar_r.w_year,calendar_r.w_month,calendar_r.w_date,calendar_r.hour,calendar_r.min,calendar_r.sec);//输出闹铃时间
        
    }
    RTC_ClearITPendingBit(RTC_IT_SEC|RTC_IT_OW);		//clear alarm clock interrupt
    RTC_WaitForLastTask();
    
#if SYSTEM_SUPPORT_OS == 1
    OSIntExit();
#endif	
}



/************************************************************************************************************************
***                                                                                                                   ***
***                                          Interface code                                                           ***
***                                                                                                                   ***
*************************************************************************************************************************/

/*************************************************************************************************************************
* Function:    HF_RTC_Init(void)
*
* Scope:       public
*
* Description: Configration of RTC
*              Initialize RTC, and check its' state is normal or not
*              BKP->DR1 used to save if is first configuration
*
* Arguments:
*
* Return:	   0-->normal  others-->error
*
* Cpu_Time:
*
* History:
* ALIENTEK Mini STM32开发板 Copyright(C) 正点原子
* by   mawenke    2015.12.1                          creat
* by   LiuDong    2016.1.8       V1.57       update the name of function
**************************************************************************************************************************/
unsigned char HF_RTC_Init(void)
{
    
    //check if is first configuration of RTC
    unsigned char temp=0;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);	//ENABLE clock of PWR and BKP
    PWR_BackupAccessCmd(ENABLE);	 //enable access of backup register
    if (BKP_ReadBackupRegister(BKP_DR1) != 0x5050)		//read data from backup register
    {
        BKP_DeInit();	//RESET backuo area
        RCC_LSEConfig(RCC_LSE_ON);	//set external LSE, and use LSE
        while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET&&temp<250)	//check if set flag of RCC, and wait LSE is ready
        {
            temp++;
            delay_ms(10);
        }
        if(temp>=250) return 1;//Initialize clock failed, the Crystal has error
        RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);		//set LSE to be the clock of RTC
        RCC_RTCCLKCmd(ENABLE);	//enable RTC
        
        RTC_WaitForLastTask();	//wait finish writing RTC register
        RTC_WaitForSynchro();		//wait RTC sync
        RTC_ITConfig(RTC_IT_SEC, ENABLE);		//ENABLE RTC Interrupt
        RTC_WaitForLastTask();	//wait finish writing RTC register
        RTC_EnterConfigMode();/// allow to configure
        RTC_SetPrescaler(32767); //set Prescaler
        RTC_WaitForLastTask();	//wait finish writing RTC register
        RTC_Set(2015,1,14,17,42,55);  //set time
        RTC_ExitConfigMode(); //quit configuration mode
        BKP_WriteBackupRegister(BKP_DR1, 0X5050);	//write user program data to assign backup register
    }
    else//system continue counting time
    {
        RTC_WaitForSynchro();	//wait finish writing RTC register
        RTC_ITConfig(RTC_IT_SEC, ENABLE);	//enable RTC interrupt
        RTC_WaitForLastTask();	//wait finish writing RTC register
    }
    RTC_NVIC_Config();//RTC interrupt NVIC configure
    RTC_Get();//update time
    return 0; //ok
    
}		 	

/*************************************************************************************************************************
* Function:    unsigned char RTC_Set(unsigned short int syear,unsigned char smon,unsigned char sday,unsigned char hour,unsigned char min,unsigned char sec)
*
* Scope:       public
*
* Description: set clock
*              transform the time data to seconds
*              time base is 1,1,1970
*              legal input is 1970~2099
*
* Arguments:
*
* Return:	   0-->succeeded  others-->failed
*
* Cpu_Time:
*
* History:
* ALIENTEK Mini STM32开发板 Copyright(C) 正点原子
* by   mawenke   2015.12.1
**************************************************************************************************************************/
unsigned char RTC_Set(unsigned short int syear,unsigned char smon,unsigned char sday,unsigned char hour,unsigned char min,unsigned char sec)
{
    unsigned short int t;
    unsigned int seccount=0;
    if(syear<1970||syear>2099)return 1;
    for(t=1970;t<syear;t++)	//add all second data of year
    {
        if(Is_Leap_Year(t))seccount+=31622400;//seconds of leap year
        else seccount+=31536000;			  //seconds of noramal year
    }
    smon-=1;
    for(t=0;t<smon;t++)	   //add all second data of month
    {
        seccount+=(unsigned int)mon_table[t]*86400;//add second of every month
        if(Is_Leap_Year(syear)&&t==1)seccount+=86400;//if is leap year,  add one more day time
    }
    seccount+=(unsigned int)(sday-1)*86400;//add all second before
    seccount+=(unsigned int)hour*3600;//second of hour
    seccount+=(unsigned int)min*60;	 //second of minute
    seccount+=sec;//add second
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);	//enable clock of PWR and BKP
    PWR_BackupAccessCmd(ENABLE);	// enable access to backup register
    RTC_SetCounter(seccount);	//set value of RTC counter
    
    RTC_WaitForLastTask();	//wait finish writing RTC register
    return 0;
}

/*************************************************************************************************************************
* Function:    void RTC_Alarm_Set(unsigned short int syear,unsigned char smon,unsigned char sday,unsigned char hour,unsigned char min,unsigned char sec)
*
* Scope:       public
*
* Description: Initialize clock
*              transform the time data to seconds
*              time base is 1,1,1970
*              legal input is 1970~2099
*
* Arguments:
*
* Return:	   0-->succeeded  others-->failed
*
* Cpu_Time:
*
* History:
* ALIENTEK Mini STM32开发板 Copyright(C) 正点原子
* by   mawenke   2015.12.1
**************************************************************************************************************************/
void RTC_Alarm_Set(unsigned short int syear,unsigned char smon,unsigned char sday,unsigned char hour,unsigned char min,unsigned char sec)
{
    unsigned short int t;
    unsigned int seccount=0;
    if(syear<1970||syear>2099)return ;
    for(t=1970;t<syear;t++)	//add all second data of year
    {
        if(Is_Leap_Year(t))seccount+=31622400;//seconds of leap year
        else seccount+=31536000;			  //seconds of noramal year
    }
    smon-=1;
    for(t=0;t<smon;t++)	   //add all second data of month
    {
        seccount+=(unsigned int)mon_table[t]*86400;//add second of every month
        if(Is_Leap_Year(syear)&&t==1)seccount+=86400;//if is leap year,  add one more day time
    }
    seccount+=(unsigned int)(sday-1)*86400;//add all second before
    seccount+=(unsigned int)hour*3600;//second of hour
    seccount+=(unsigned int)min*60;	 //second of minute
    seccount+=sec;//add second
    //set clock
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);	//enable clock of PWR and BKP
    PWR_BackupAccessCmd(ENABLE);	//enable access to backup register
    //3 upside steps are necessary
    
    RTC_SetAlarm(seccount);
    
    RTC_WaitForLastTask();	//wait finish writing RTC register
    
    return ;
}

/*************************************************************************************************************************
* Function:    void HF_RTC_Time_Renew(void)
*
* Scope:       public
*
* Description: RTC time update function
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
* ALIENTEK Mini STM32开发板 Copyright(C) 正点原子
* by   mawenke   2015.12.1
**************************************************************************************************************************/
void HF_RTC_Time_Renew(void)   //update time structure
{
    RTC_Get();
}


#endif 

#ifdef __cplusplus
}
#endif 

