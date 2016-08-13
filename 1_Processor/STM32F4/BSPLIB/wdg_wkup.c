/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: wdg_wkup.c
* Contact:  QQ Exchange Group -- 521037187
* Version:  V2.0
*
* LICENSING TERMS:  
* The Hands Free is licensed generally under a permissive 3-clause BSD license. 
* Contributions are requiredto be made under the same license.
*  
* History: 
* <author>      <time>      <version>      <desc>
* mawenke       2015.10.1   V1.0           creat this file
*
* Description:
*        STM32F4--------------
*        no using Pin source
***********************************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif 

#include "wdg_wkup.h"
#include "delay.h"

/***********************************************************************************************************************
***                                                                                                                  ***
***                                        Initialize Indepedent WDG                                                 ***
***                                                                                                                  ***
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function:     void HF_IWDG_Init(void)
*
* Scope:       
*
* Description:  Initialize WDG
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
void HF_IWDG_Init(void) 
{	
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); 	//Enable access to write register
    IWDG_SetPrescaler(IWDG_Prescaler_64);
    IWDG_SetReload(500);							//Frequency: 40K / 64 =  0.625K, and one cycle is 1ms
    IWDG_ReloadCounter();			//the program to feed dog, if not write 0xAAAA every while, WDG will reset
    IWDG_Enable(); 					//enable
}

/***********************************************************************************************************************
* Function:     void HF_IWDG_Feed(void)
*
* Scope:       
*
* Description:  the program to feed dog, if not write 0xAAAA every while, WDG will reset
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
void HF_IWDG_Feed(void)
{   
    IWDG_ReloadCounter();
}

/***********************************************************************************************************************
***                                                                                                                  ***
***                                         Initialize Window WDG                                                    ***
***                                                                                                                  ***
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function:     static void WWDG_NVIC_Init()
*
* Scope:       
*
* Description:  Interruptation Response program
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
static void WWDG_NVIC_Init()
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;             //WWDG interrupt
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;   //PreemptionPriority
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	        //SubPriority
    NVIC_Init(&NVIC_InitStructure);//NVIC initialize
}

u8 WWDG_CNT=0x7f;
/***********************************************************************************************************************
* Function:     void HF_WWDG_Init(u8 tr,u8 wr,u32 fprer)
*
* Scope:       
*
* Description:  save the configure value of WWDG counter, default value is max
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
void HF_WWDG_Init(u8 tr,u8 wr,u32 fprer)
{ 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);   //enable WWDG clock
    WWDG_SetPrescaler(fprer);   //set IWDG Prescaler
    WWDG_SetWindowValue(wr);    //set window value
    WWDG_Enable(tr);	        //enable WWDG, and set counter
    WWDG_ClearFlag();
    WWDG_NVIC_Init();           //initialize WWDG NVIC
    WWDG_EnableIT();            //enable interrupt of WWDG
} 

/***********************************************************************************************************************
* Function:     void HF_WWDG_Set_Counter(u8 cnt)
*
* Scope:       
*
* Description:  reset the value of WWDG counter
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
void HF_WWDG_Set_Counter(u8 cnt)
{
    WWDG_Enable(cnt);
}

/***********************************************************************************************************************
* Function:     void HF_WWDG_IRQHandler(void)
*
* Scope:       
*
* Description:  interruption function of wdg
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
void HF_WWDG_IRQHandler(void)
{
    WWDG_SetCounter(0x7F);	  //if annotate this words, WWDG will reset
    WWDG_ClearFlag();	        //clear flag of advance wake up
}


/***********************************************************************************************************************
***                                                                                                                  ***
***                                          Initialize  Low power consumption                                       ***
***                                                                                                                  ***
***********************************************************************************************************************/

#define WKUP_KD GPIO_ReadInputDataBit(GPIOA  , GPIO_Pin_0)		//PA0 check signal of WKUP Pin

/***********************************************************************************************************************
* Function:     void HF_Sys_Enter_Standby(void)
*
* Scope:       
*
* Description:  system enter standby mode
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
static void Sys_Enter_Standby(void)
{		
    //  while(WKUP_KD);			//waiting for free WKUP KEY
    RCC_AHB1PeriphResetCmd(0X04FF,ENABLE);//RESET all IO
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);//enable PWR clock
    PWR_BackupAccessCmd(ENABLE);//enable access to backup register
    
    RTC_ITConfig(RTC_IT_TS|RTC_IT_WUT|RTC_IT_ALRB|RTC_IT_ALRA,DISABLE);//disable RTC interrupt
    RTC_ClearITPendingBit(RTC_IT_TS|RTC_IT_WUT|RTC_IT_ALRB|RTC_IT_ALRA);//clear RTC interrupt flag
    
    PWR_ClearFlag(PWR_FLAG_WU);//clear Wake-up flag
    PWR_WakeUpPinCmd(ENABLE);  //set WKUP key to wake-up system
    PWR_EnterSTANDBYMode();	   //enter standby mode
}

/***********************************************************************************************************************
* Function:     uint8_t Check_WKUP(void)
*
* Scope:       
*
* Description:  check signal of WKUP Pin
*
* Arguments:
*
* Return:       1-->keep having been pressed over 3s
*               0-->error press
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
uint8_t Check_WKUP(void) 
{
    u8 t=0;
    u8 tx=0;//recording number of free key
    while(1)
    {
        if(WKUP_KD)//have pressed
        {
            t++;
            tx=0;
        }
        else
        {
            tx++;
            if(tx>3)    //no WKUP signal over 90ms
            {
                return 0; //error press, number of press not enough
            }
        }
        delay_ms(30);
        if(t>=100)//having been pressed over 3s
        {
            return 1; //having been pressed over 3s
        }
    }
} 

/***********************************************************************************************************************
* Function:     void EXTI0_IRQHandler(void)
*
* Scope:       
*
* Description:  Interrupt: check posedge from PA0	 
*               Check Interrupt Line 0
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
//void EXTI0_IRQHandler(void)
//{ 		    		    				     		    
//    EXTI_ClearITPendingBit(EXTI_Line0); // clear interrupt flag of Interrupt Line10 
//    if( Check_WKUP() )//power-off
//    {
//        HF_Sys_Enter_Standby(); //enter standby mode
//    }
//} 

/***********************************************************************************************************************
* Function:     void HF_WKUP_Init(void)
*
* Scope:       
*
* Description:  PA0 WKUP initialize
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
void HF_WKUP_Init(void)
{	  
    GPIO_InitTypeDef  GPIO_InitStructure;
    NVIC_InitTypeDef   NVIC_InitStructure;
    EXTI_InitTypeDef   EXTI_InitStructure;
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //PA0
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//input mode
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//pull down mode
    GPIO_Init(GPIOA, &GPIO_InitStructure);//initialize
    
    //check if power on normally
    if(Check_WKUP()==0)
    {
        Sys_Enter_Standby();	//not power-on, enter standby
    }
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);//PA0 connect to interrupt line0
    EXTI_InitStructure.EXTI_Line = EXTI_Line0; //LINE0
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; //interrupt event
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //touch off rising
    EXTI_InitStructure.EXTI_LineCmd = ENABLE; //enable interrupt LINE0
    EXTI_Init(&EXTI_InitStructure); //config
    
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn; //external interrupt 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02; //enable external interrupt channel
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure); //config NVIC
}

#ifdef __cplusplus
}
#endif 


