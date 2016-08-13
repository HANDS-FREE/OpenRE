/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: delay.c
* Contact:  QQ Exchange Group -- 521037187
* Version:  V2.0
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
*Description: This file defines delay system and system clock
*             system clock is using one timer to record the total time after power-on
*             SysTick(24Bits) used by operation system to have system beat, nor using to make accurate delay
*             if no operation system
*             STM32F4--------------
*             no using Pin source
*             timer5  SysTick 24   TIM5 used by time measurement system initializing defaultly. 
***********************************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif 

#include "delay.h"

#if SYSTEM_SUPPORT_OS > 0u    // 1-->enable operation system and use software -delay,  0-->timer delay

#include "includes.h"  //used by ucos

//support UCOSII
#ifdef 	OS_CRITICAL_METHOD						//OS_CRITICAL_METHOD definition, means using UCOSII
#define delay_ostickspersec	OS_TICKS_PER_SEC	//OS clock beat, means calling frequency
#endif                                        

//support UCOSIII                             
#ifdef 	CPU_CFG_CRITICAL_METHOD					 //CPU_CFG_CRITICAL_METHOD definition, means using UCOSII
#define delay_ostickspersec	OSCfg_TickRate_Hz	 //OS clock beat, means calling frequency
#endif

//systick interrupt response function, used by ucos
void SysTick_Handler(void)
{
    if(OSRunning ==1 )			    //OS is working, and executing normal control processing
    {
        OSIntEnter();				//enter interruption
        OSTimeTick();       		//call ucos clock service program
        OSIntExit();       	 		//trigger interruption of task switch
    }
}

void delay_init(void)   //initialize OS beat
{
    u32 reload;
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//Chose external clock, HCLK/8
    reload=SystemCoreClock/8000000;				            //frequency, unit: K
    reload*=1000000/delay_ostickspersec;		            //set overflow time according to delay_ostickspersec
    //reload is 24BIT register, max value is 16777216, about 1.86s at 72M/8
    SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;     //enable SYSTICK interrupt
    SysTick->LOAD=reload; 						 //enter interrupt every 1/delay_ostickspersec second
    SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;   	 //enable SYSTICK
}

void delay_us(uint16_t t)
{    
    int i;
    for( i=0;i<t;i++)
    {
        int a=40;
        while(a--) asm("nop");
    }    
}

void delay_ms(uint16_t t)
{
    int i;
    for( i=0;i<t;i++)
    {
        int a=42000;
        while(a--) asm("nop");
    }
}

#else                //0--> accurate delay, not using OS

uint8_t fac_us=0; //us delay multiplicand  
uint16_t fac_ms=0; //ms delay multiplicand

//SYSTICK的时钟固定为HCLK时钟的1/8
void delay_init()
{
    SysTick->CTRL&=0xfffffffb;//clear bit2, and using external clock     HCK/8
    fac_us=SystemCoreClock/8000000;
    fac_ms=(uint16_t)fac_us*1000;
}			    

void delay_us(uint16_t t)
{		
    u32 temp;
    SysTick->LOAD=t*fac_us;  //load time
    SysTick->VAL=0x00;       //clear counter
    SysTick->CTRL=0x01 ;     //start count backwards
    do
    {
        temp=SysTick->CTRL;
    }
    while(temp&0x01&&!(temp&(1<<16)));//wait arrival of target time
    SysTick->CTRL=0x00;               //DISENABLE timer
    SysTick->VAL =0X00;               //clear counter
}

void delay_ms(uint16_t t)
{	 		  	  
    u32 temp;
    SysTick->LOAD=(u32)t*fac_ms;  //load time (SysTick->LOAD为24bit)
    SysTick->VAL =0x00;           //clear counter
    SysTick->CTRL=0x01 ;          //start count backwards
    do
    {
        temp=SysTick->CTRL;
    }
    while(temp&0x01&&!(temp&(1<<16)));//wait arrival of target time
    SysTick->CTRL=0x00;               //DISENABLE timer
    SysTick->VAL =0X00;               //clear counter
} 


#endif       //#if SYSTEM_SUPPORT_OS== 1   



/***********************************************************************************************************************
***                                                                                                                  ***
***                                         System Clock Initialization Function                                     ***
***                                                                                                                  ***
***********************************************************************************************************************/

//if using Time measurement system to measure time difference or system working time. ?
#define Time_Measurement 1	

#if  Time_Measurement == 1    //enable time measurement system, need occupy a timer from TIM1--TIM8
#define Measurement_Timer  TIM5
#define Measurement_Timer_IRQn  TIM5_IRQn
#define Measurement_Timer_RCC_ENABLE  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); 
#define Measurement_Timer_RCC_DISABLE 	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, DISABLE); 
#define Measurement_Timer_IRQn_Function 	void TIM5_IRQHandler(void)
#define Measurement_Timer_Period  0xffffffff		
#define Measurement_Timer_Prescaler 84-1
#endif

#if Time_Measurement == 1               //if enable Time measurement system and occupy a timer (TIM1---TIM8)

float M_time=0;

void HF_System_Timer_Init(void)		//Initialize time measurement system
{	   
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    
    Measurement_Timer_RCC_ENABLE;       //Initialize clock
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = Measurement_Timer_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    TIM_DeInit(Measurement_Timer);
    
    TIM_TimeBaseStructure.TIM_Period=Measurement_Timer_Period;	/* Value of auto reload register*/
    TIM_TimeBaseStructure.TIM_Prescaler=Measurement_Timer_Prescaler;	 /* TIM_Prescaler 72M/72 */
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 		/* ClockDivision*/
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;   /* count upwards*/
    TIM_TimeBaseInit(Measurement_Timer, &TIM_TimeBaseStructure);
    TIM_ClearFlag(Measurement_Timer, TIM_FLAG_Update);			/* clear flag of update interruption*/
    TIM_ITConfig(Measurement_Timer,TIM_IT_Update,ENABLE);
    TIM_Cmd(Measurement_Timer, ENABLE);							/* enable timer */  
}

Measurement_Timer_IRQn_Function      //Interruption Response Function
{  
#if SYSTEM_SUPPORT_OS == 1
    OSIntEnter();
#endif 
    if ( TIM_GetITStatus(Measurement_Timer , TIM_IT_Update) != RESET )
    {
        M_time++;
        if(M_time >= 0xffffffff)
        {
            M_time=0;
        }
        TIM_ClearITPendingBit(Measurement_Timer , TIM_FLAG_Update); //clear interrupt flag
    }
#if SYSTEM_SUPPORT_OS == 1
    OSIntExit();
#endif
}

float HF_Get_System_Time(void)
{	
    //get count value of current system clock(TIM5->CNT+65536*time/1000000) s
    float time;
    time=(float)(Measurement_Timer->CNT+(float)Measurement_Timer_Period*M_time);
    return time;
}

float HF_Get_Dtime(void)
{
    static float lasttime ;
    float temp1,temp2;
    temp1 =(float)(Measurement_Timer->CNT+(float)Measurement_Timer_Period*(float)M_time);
    temp2 =temp1 - lasttime;
    if(temp2<0)
    {   //if int type variable overflow, data will be cleared and max time difference is 655s
        temp2=(( Measurement_Timer_Period * 0xffffffff- lasttime ) + temp1 );
    }
    lasttime = temp1;
    return temp2;
}


#else //#if Time_Measurement == 1
//if enable Time measurement system and occupy a timer (TIM1---TIM8)
void HF_System_Timer_Init(void)	//Initialize time measurement system.
{	
    
}


float HF_Get_System_Time(void) //return current time(us)
{
    return 0;
}

float HF_Get_Dtime(void) //  Return the time difference(us). max:655s
{
    return 0;
}

#endif

#ifdef __cplusplus
}
#endif 

