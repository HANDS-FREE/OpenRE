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
* mawenke     2015.10.1   V1.0             creat
* LiuDong     2016.1.8    V1.57            update the name of function
*
* Description: This file defines delay system and system clock
*              system clock is using one timer to record the total time after power-on
*              SysTick(24Bits) used by operation system to have system beat, nor using to make accurate delay  if no operation system 
*              TIM1---TIM8(Bits) every can be used by time measurement system 
*              STM32F1--------------
*              no using Pin source
*              timer7  SysTick 24   TIM7 used by time measurement system initializing defaultly.
************************************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif 

#include "delay.h"

#if SYSTEM_SUPPORT_OS== 1  
#include "includes.h"					//used by ucos 
#endif	

#if  Time_Measurement == 1    //ENABLE Time measurement system and occupy a timer (TIM1---TIM8)
#define Measurement_Timer  TIM7
#define Measurement_Timer_IRQn  TIM7_IRQn
#define Measurement_Timer_RCC_ENABLE  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
#define Measurement_Timer_RCC_DISABLE 	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, DISABLE);
#define Measurement_Timer_IRQn_Function 	void TIM7_IRQHandler(void)
#define Measurement_Timer_Period     0xffff	
#define Measurement_Timer_Prescaler  72-1
#endif
/***********************************************************************************************************************
***                                                                                                                  ***
***                               Delay function or system beat initialize function                                  ***
***                                                                                                                  ***
************************************************************************************************************************/

#if SYSTEM_SUPPORT_OS > 0u    // 1-->enable operation system and use software -delay,  0-->timer delay
//support UCOSII
#ifdef 	OS_CRITICAL_METHOD						        //OS_CRITICAL_METHOD definition, means using UCOSII				
#define delay_ostickspersec	OS_TICKS_PER_SEC	//OS clock beat, means calling frequency
#endif

//SUPPORT UCOSIII
#ifdef 	CPU_CFG_CRITICAL_METHOD					       //CPU_CFG_CRITICAL_METHOD definition, means using UCOSII		
#define delay_ostickspersec	OSCfg_TickRate_Hz	 //OS clock beat, means calling frequency
#endif
	
//systick interrupt response function, used by ucos 
void SysTick_Handler(void)
{	
    if(OSRunning ==1 )			    //OS is working, and executing normal control processing
    {
        OSIntEnter();							//enter interruption
        OSTimeTick();       		  //call ucos clock service program
        OSIntExit();       	 			//trigger interruption of task switch
    }
}

void delay_init(void)   //initialize OS beat
{
    u32 reload;
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//Chose external clock, HCLK/8
    reload=SystemCoreClock/8000000;				       //frequency, unit: K
    reload*=1000000/delay_ostickspersec;		     //set overflow time according to delay_ostickspersec
    //reload is 24BIT register, max value is 16777216, about 1.86s at 72M/8
    SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;     //enable SYSTICK interrupt
    SysTick->LOAD=reload; 						           //enter interrupt every 1/delay_ostickspersec second
    SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;   	 //enable SYSTICK
}

void delay_us(unsigned short int t)
{
    int i;
    for( i=0;i<t;i++)
    {
        int a=9;
        while(a--);
    }   
}

void delay_ms(unsigned short int t)
{
    int i;
    for( i=0;i<t;i++)
    {
        int a=10300;
        while(a--);
    }
}

#else               //0--> accurate delay, not using OS

static u8  fac_us=0;//us delay multiplicand
static u16 fac_ms=0;//ms delay multiplicand

//Frequency of SYSTICK is 1/8 of HCLK
void delay_init(void)
{
    SysTick->CTRL&=0xfffffffb;//clear bit2, and using external clock     HCK/8
    fac_us=SystemCoreClock/8000000;
    fac_ms=(u16)fac_us*1000;
}			    

void delay_us(unsigned short int t)
{		
    u32 temp;
    SysTick->LOAD=t*fac_us;   //load time
    SysTick->VAL=0x00;        //clear counter
    SysTick->CTRL=0x01 ;      //start count backwards
    do
    {
        temp=SysTick->CTRL;
    }
    while(temp&0x01&&!(temp&(1<<16)));//wait arrival of target time
    SysTick->CTRL=0x00;               //DISENABLE timer
    SysTick->VAL =0X00;               //clear counter
}


void delay_ms(unsigned short int t)
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
    SysTick->CTRL=0x00;       //DISENABLE timer
    SysTick->VAL =0X00;       //clear counter
} 


#endif   //#if SYSTEM_SUPPORT_OS== 1   


/************************************************************************************************************************
***                                                                                                                   ***
***                                   System Clock Initialization Function                                            ***
***                                                                                                                   ***
*************************************************************************************************************************/

#if Time_Measurement == 1   //if enable Time measurement system and occupy a timer (TIM1---TIM8)

unsigned int M_time=0;

void Init_Measurement_Timer(void)			   //Initialize time measurement system
{	
    
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    
    Measurement_Timer_RCC_ENABLE;  //Initialize clock
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //************
    NVIC_InitStructure.NVIC_IRQChannel = Measurement_Timer_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	  //*********
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    TIM_DeInit(Measurement_Timer);
    
    TIM_TimeBaseStructure.TIM_Period=Measurement_Timer_Period;		 								/* Value of auto reload register*/
    TIM_TimeBaseStructure.TIM_Prescaler=Measurement_Timer_Prescaler;				    /* TIM_Prescaler 72M/72 */
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 		/* ClockDivision*/
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; /* count upwards*/
    TIM_TimeBaseInit(Measurement_Timer, &TIM_TimeBaseStructure);
    TIM_ClearFlag(Measurement_Timer, TIM_FLAG_Update);							    		/* clear flag of update interruption*/
    TIM_ITConfig(Measurement_Timer,TIM_IT_Update,ENABLE);
    TIM_Cmd(Measurement_Timer, ENABLE);																		/* enable timer */
    
}


Measurement_Timer_IRQn_Function     //Interruption Response Function
{
    
    if ( TIM_GetITStatus(Measurement_Timer , TIM_IT_Update) != RESET )
    {
        M_time++;
        if(M_time >= 0xffffffff)
        {
            M_time=0;
        }
        TIM_ClearITPendingBit(Measurement_Timer , TIM_FLAG_Update);
    }
    
}

/***********************************************************************************************************************
* Function:     float GET_System_time(void)
*
* Scope:        public
*
* Description:  Return the current time(us), max:281474976s--->3257.8 days
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
* by  mawenke 2015.12.1
***********************************************************************************************************************/
float GET_System_time(void)   
{
    
    float temp;
    temp=(float)(Measurement_Timer->CNT+(float)Measurement_Timer_Period*(float)M_time);	       //get count value of current system clock(TIM5->CNT+65536*time/1000000) s
    return temp;
    
}

/***********************************************************************************************************************
* Function:     float GET_microstime(void)
*
* Scope:        public
*
* Description:  Return the time difference(us)
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
* by  mawenke 2015.12.1
***********************************************************************************************************************/
float GET_microstime(void)   
{
    static float lasttime ;
    float temp1,temp2;
    temp1 =(float)(Measurement_Timer->CNT+(float)65536*(float)M_time);
    temp2 =temp1 - lasttime;
    if(temp2<0)
    {
        temp2=((65536 * 0xffffffff- lasttime)+temp1);   //if int type variable overflow, data will be cleared and max time difference is 655s
    }
    lasttime = temp1;
    return temp2;
}


#else        //#if Time_Measurement == 1   //if enable Time measurement system and occupy a timer (TIM1---TIM8)

void Init_Measurement_Timer(void)			   //Initialize time measurement system.
{	
    
}


float GET_Nowtime(void)//return current time(us)
{
    return 0;
}

float GET_microstime(void)   // Return the time difference(us). max:655s
{
    return 0;
}


#endif   //#if Time_Measurement == 1   //if enable Time measurement system and occupy a timer (TIM1---TIM8)



/************************************************************************************************************************
***                                                                                                                   ***
***                                                                                                                   ***
***                                                                                                                   ***
*************************************************************************************************************************/

CPU_Hardware_Data cpu_hardware_data_r;
/***********************************************************************************************************************
* Function:     void Get_CPU_Information(void)
*
* Scope:        public
*
* Description:  Only calls once to get ID of CPU the capacity of Flash
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
* by  mawenke 2015.12.1
***********************************************************************************************************************/
void Get_CPU_Information(void)
{
    static unsigned char i = 0;
    if(i ==0 )
    {
        i = 1;
        cpu_hardware_data_r.ChipUniqueID[0] = *(__IO u32 *)(0X1FFFF7F0); // MSB
        cpu_hardware_data_r.ChipUniqueID[1] = *(__IO u32 *)(0X1FFFF7EC); //
        cpu_hardware_data_r.ChipUniqueID[2] = *(__IO u32 *)(0X1FFFF7E8); // LSB
        cpu_hardware_data_r.flash_Size =  *(__IO u16 *)(0X1FFFF7E0);     //Unit:KB
    }
    //	printf("\r\nID of CPU: %X-%X-%X\r\n",ChipUniqueID[0],ChipUniqueID[1],ChipUniqueID[2]);
    //	printf("\r\nCapacity of Flash: %dKB \r\n", *(__IO u16 *)(0X1FFFF7E0));
}


/************************************************************************************************************************
***                                                                                                                   ***
***                                                                                                                   ***
***                                                                                                                   ***
*************************************************************************************************************************/

/***********************************************************************************************************************
* Function:     void WFI_SET(void)
*
* Scope:        public
*
* Description:  THUMB指令不支持汇编内联 ，采用如下方法实现执行汇编指令WFI
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
* ALIENTEK Mini STM32开发板 Copyright(C) 正点原子 2009-2019
***********************************************************************************************************************/
void WFI_SET(void)
{
    __ASM volatile("wfi");
}
//close all interruption
void INTX_DISABLE(void)
{		  
    __ASM volatile("cpsid i");
}
//enable all interruption
void INTX_ENABLE(void)
{
    __ASM volatile("cpsie i");
}
//set stack address
//addr:address of stack top
__asm void MSR_MSP(u32 addr) 
{
    MSR MSP, r0 			//set Main Stack value
    BX r14
}

#ifdef __cplusplus
}
#endif 

