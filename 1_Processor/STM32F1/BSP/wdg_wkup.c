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
* <author>    <time>      <version >       <desc>
* mawenke     2015.10.1   V1.0             creat
* LiuDong     2016.1.8    V1.57            update the name of function
*
* Description:
*        STM32F1--------------
*        no using Pin source
***********************************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif 

#include "wdg_wkup.h"
#include "delay.h"

#if BSP_CFG_WDG_WKUP_EN  > 0u
/************************************************************************************************************************
***                                                                                                                   ***
***                                          Initialize Indepedent WDG                                                ***
***                                                                                                                   ***
*************************************************************************************************************************/
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
* by   mawenke   2015.12.1   creat
***********************************************************************************************************************/
void HF_IWDG_Init(void) 
{	
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); 	//Enable access to write register
    IWDG_SetPrescaler(IWDG_Prescaler_64);           //Frequency: 40K / 64 =  0.625K, and one cycle is 1.6ms
    IWDG_SetReload(800);							              //800*1.6ms = 1.28S
    IWDG_ReloadCounter();								//the program to feed dog, if not write 0xAAAA every while, WDG will reset
    IWDG_Enable(); 									    //enable
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
* by   mawenke   2015.12.1   creat
***********************************************************************************************************************/
void 	HF_IWDG_Feed(void)
{   
    IWDG_ReloadCounter();	  						   
}

/************************************************************************************************************************
***                                                                                                                   ***
***                                          Initialize Window WDG                                                    ***
***                                                                                                                   ***
*************************************************************************************************************************/

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
* by   mawenke   2015.12.1   creat
***********************************************************************************************************************/
static void WWDG_NVIC_Init()
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;    //WWDG  interrupt
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;   //PreemptionPriority
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	 //SubPriority 
    NVIC_Init(&NVIC_InitStructure);//NVIC initialization
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
* by   mawenke   2015.12.1   creat
***********************************************************************************************************************/
void HF_WWDG_Init(u8 tr,u8 wr,u32 fprer)
{ 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);  // enable  WWDG clock
    WWDG_SetPrescaler(fprer);  //set IWDG Prescaler
    WWDG_SetWindowValue(wr);   //set window value
    WWDG_Enable(tr);	         //enable WWDG, and set counter
    WWDG_ClearFlag();
    WWDG_NVIC_Init();          //initialize WWDG NVIC
    WWDG_EnableIT();           //enable interrupt of WWDG
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
* by   mawenke   2015.12.1   creat
***********************************************************************************************************************/
void HF_WWDG_Set_Counter(u8 cnt)
{
    WWDG_Enable(cnt);	 
}

void HF_WWDG_IRQHandler(void)
{
    
    WWDG_SetCounter(0x7F);	  //if annotate this words, WWDG will reset
    WWDG_ClearFlag();	        //clear flag of advance wake up
}


/************************************************************************************************************************
***                                                                                                                   ***
***                                      Initialize  Low power consumption                                            ***
***                                                                                                                   ***
*************************************************************************************************************************/
/***********************************************************************************************************************
* Function:     static void Sys_Standby(void)
*
* Scope:       
*
* Description:  
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
* by   mawenke   2015.12.1   creat
***********************************************************************************************************************/
static void Sys_Standby(void)
{  
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);	//ENABLE PWR clock 
    PWR_WakeUpPinCmd(ENABLE);  //enable the wake-up Pin
    PWR_EnterSTANDBYMode();	  //enter standby mode
}


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
* by   mawenke   2015.12.1   creat
***********************************************************************************************************************/
static void Sys_Enter_Standby(void)
{			 
    RCC_APB2PeriphResetCmd(0X01FC,DISABLE);	//RESET all IO
    Sys_Standby();
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
* by   mawenke   2015.12.1   creat
***********************************************************************************************************************/
static  u8 Check_WKUP(void) 
{
    u8 t=0;	//recording the time when pressing
    //	LED0=0; 
    while(1)
    {
        if(WKUP_KD)
        {
            t++;			//have pressed
            delay_ms(30);
            if(t>=100)		//having been pressed over 3s
            {
                //				LED0=0;	 	//light DS0 
                return 1; 	//having been pressed over 3s
            }
        }else 
        { 
            //			LED0=1;
            return 0; //having been pressed short 3s
        }
    }
} 

//Interrupt: check posedge from PA0	  
//Check Interrupt Line 0
//void EXTI0_IRQHandler(void)
//{ 		    		    				     		    
//	EXTI_ClearITPendingBit(EXTI_Line0); // clear interrupt flag of Interrupt Line10 
//	if(Check_WKUP())//power-off
//	{		  
//		HF_Sys_Enter_Standby();  
//	}
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
* by   mawenke   2015.12.1   creat
***********************************************************************************************************************/
void HF_WKUP_Init(void)
{	
    
    GPIO_InitTypeDef  GPIO_InitStructure;  		  
    NVIC_InitTypeDef NVIC_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0;	 //PA.0
    GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPD;//pull up input
    GPIO_Init(GPIOA, &GPIO_InitStructure);	//Initialize IO
    //use external interrupt 
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);	//connect Interrupt Line 0 with GPIOA
    
    EXTI_InitStructure.EXTI_Line = EXTI_Line0;	//set all line of key
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;			//use external interrupt mode
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  //response at posedge
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);	// initialize external interruption
    
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn; //enable external interrupt line of key
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; 
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //enable external interrupt channel
    NVIC_Init(&NVIC_InitStructure); 
    
    if(Check_WKUP()==0) Sys_Standby();    //enter standby mode
    
}

#endif  //#if BSP_CFG_WDG_WKUP_EN  > 0u

#ifdef __cplusplus
}
#endif 




