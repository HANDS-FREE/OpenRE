/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* Contact:  QQ Exchange Group -- 521037187
*
* LICENSING TERMS:
* The Hands Free is licensed generally under a permissive 3-clause BSD license.
* Contributions are requiredto be made under the same license.
*
* History:
* <author>    <time>      <version >       <desc>
* mawenke       2015.10.1   V1.0           creat this file
* LiuDong     2016.1.8    V1.57            update the name of function
*
*Description: This file defines system clock
***********************************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

#include "delay.h"

float count_time = 0;
float count_us = 0;
float count_ms = 0;
float reload = 0;

#if SYSTEM_SUPPORT_OS > 0u  //using OS

#include "includes.h"  //used by ucos

//support UCOSII
#ifdef 	OS_CRITICAL_METHOD						//OS_CRITICAL_METHOD definition, means using UCOSII
#define delay_ostickspersec	OS_TICKS_PER_SEC	//OS clock beat, means calling frequency
#endif

//support UCOSIII
#ifdef 	CPU_CFG_CRITICAL_METHOD					 //CPU_CFG_CRITICAL_METHOD definition, means using UCOSII
#define delay_ostickspersec	OSCfg_TickRate_Hz	 //OS clock beat, means calling frequency
#endif

void HF_System_Timer_Init(void)   //initialize OS beat
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);//clear bit2, and using external clock     HCK/8
    count_us=SystemCoreClock / 8000000;
    count_ms=(uint16_t)count_us * 1000;

    reload = SystemCoreClock / 8000000;
    //reload is 24BIT register, max value is 16777216, about 0.7989s at 168M/8
    reload *= 1000000/delay_ostickspersec;		  //set overflow time according to delay_ostickspersec

    SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;     //enable SYSTICK interrupt
    SysTick->LOAD=reload; 						 //enter interrupt every 1/delay_ostickspersec second
    //SysTick->VAL = reload;
    SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;   	 //enable SYSTICK
}

#else  //not using OS

void HF_System_Timer_Init(void)
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);//clear bit2, and using external clock     HCK/8
    count_us=SystemCoreClock / 8000000;
    count_ms=(uint16_t)count_us * 1000;
    reload = 16777215;

    SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;     //enable SYSTICK interrupt
    SysTick->LOAD=reload; 						 //enter interrupt every 1/delay_ostickspersec second
    SysTick->VAL = reload;
    SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;   	 //enable SYSTICK
}

#endif //#if SYSTEM_SUPPORT_OS > 0u  //using OS

//systick interrupt response function, used by ucos
void SysTick_Handler(void)
{
    count_time++;
    if(count_time >= 0xffffffff)
    {
        count_time=0;
    }
#if SYSTEM_SUPPORT_OS > 0u  //using OS
    if(OSRunning ==1 )			    //OS is working, and executing normal control processing
    {
        OSIntEnter();				//enter interruption
        OSTimeTick();       		//call ucos clock service program
        OSIntExit();       	 		//trigger interruption of task switch
    }
#endif
}

float HF_Get_System_Time(void)
{
    float count , time;
    count = (float)( (reload + 1 - SysTick->VAL) + (float)(reload + 1) * count_time );
    time = count/count_us;
    return time;
}

float HF_Get_Dtime(void)
{
    static float lasttime ;
    float temp1,temp2;
    temp1 = HF_Get_System_Time();
    temp2 = temp1 - lasttime;
    if(temp2 < 0)
    {
        temp2 = ( ( (float)(reload + 1) * (float)0xffffffff) / count_us) - lasttime  + temp1;
    }
    lasttime = temp1;
    return temp2;
}

void delay_us(uint16_t t)
{
    uint32_t temp1,d;
    temp1 = SysTick->VAL;
    while(1)
    {
        d = temp1 - SysTick->VAL;
        if(d >= (t*count_us)) return;
        else if (d < 0) return;
    }

//    int i;
//    for( i=0 ; i<t ; i++)
//    {
//        int a = 29;
//        while(a--) asm("nop");
//    }
}

void delay_ms(uint16_t t)
{
    float temp1,d;
    temp1 = HF_Get_System_Time();
    while(1)
    {
        d = HF_Get_System_Time() - temp1;
        if(d >= t*1000) return;
        else if(d < 0) return;
    }

//    int i;
//    for( i=0 ; i<t ; i++)
//    {
//        int a = 33568;
//        while(a--) asm("nop");
//    }
}

#ifdef __cplusplus
}
#endif

