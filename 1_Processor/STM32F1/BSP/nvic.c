/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: nvic.c
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
* Description: To manage all interruption conveniently, putting all interuption initialization in this file and called by other files
*              Not cover the interruotion of Watch Dog and delay function
*              Interruption use: NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
*              STM32F1--------------
***********************************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif 

#include "nvic.h"
#include "BSP_TOP.h"

/***********************************************************************************************************************
***                                                                                                                  ***
***                                    CAN Interruption Conffiguration                                               ***
***                                                                                                                  ***
************************************************************************************************************************/
/***********************************************************************************************************************
* Function:     void CAN1_NVIC_Configuration(void)
*
* Scope:        
*
* Description:  CAN1 Interruption Conffiguration
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:

***********************************************************************************************************************/
void CAN1_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //PreemptionPriority  0--4 Lower value, Higher Priority.
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	       //SubPriority 0--4 Lower value, Higher Priority.
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		         //ENABLE Interrupt
    NVIC_Init(&NVIC_InitStructure);
}	

/***********************************************************************************************************************
* Function:     void CAN2_NVIC_Configuration(void)
*
* Scope:
*
* Description:  CAN2 Interruption Conffiguration
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:

***********************************************************************************************************************/
void CAN2_NVIC_Configuration(void) 
{
    //	NVIC_InitTypeDef NVIC_InitStructure;
    //	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    //	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
    //	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //PreemptionPriority  0--4 Lower value, Higher Priority.
    //	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	       //SubPriority 0--4 Lower value, Higher Priority.
    //	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		         //ENABLE Interrupt
    //	NVIC_Init(&NVIC_InitStructure);
}	

/***********************************************************************************************************************
***                                                                                                                  ***
***                         USART Interruption Conffiguration                                                        ***
***                                                                                                                  ***
************************************************************************************************************************/

/***********************************************************************************************************************
* Function:     void USART1_NVIC_Configuration(void)
*
* Scope:        
*
* Description:  USART1 Interruption Conffiguration
*
* Arguments:
*
* Return:
*
* Cpu_Time:     stm32f1(35 us)  stm32f4+nofpu(unknow us) stm32f4+fpu(unknow us)
*
* History:

***********************************************************************************************************************/
void USART1_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //PreemptionPriority  0--4 Lower value, Higher Priority.
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	       //SubPriority 0--4 Lower value, Higher Priority.
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		         //ENABLE Interrupt
    NVIC_Init(&NVIC_InitStructure);
}	

/***********************************************************************************************************************
* Function:     void USART2_NVIC_Configuration(void)
*
* Scope:        
*
* Description:  USART2 Interruption Conffiguration
*
* Arguments:
*
* Return:
*
* Cpu_Time:     stm32f1(35 us)  stm32f4+nofpu(unknow us) stm32f4+fpu(unknow us)
*
* History:

***********************************************************************************************************************/
void USART2_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //PreemptionPriority  0--4 Lower value, Higher Priority.
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	       //SubPriority 0--4 Lower value, Higher Priority.
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		         //ENABLE Interrupt
    NVIC_Init(&NVIC_InitStructure);
}	

/***********************************************************************************************************************
* Function:     void USART3_NVIC_Configuration(void)
*
* Scope:        
*
* Description:  USART3 Interruption Conffiguration
*
* Arguments:
*
* Return:
*
* Cpu_Time:     stm32f1(35 us)  stm32f4+nofpu(unknow us) stm32f4+fpu(unknow us)
*
* History:

***********************************************************************************************************************/
void USART3_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //PreemptionPriority  0--4 Lower value, Higher Priority.
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	       //SubPriority 0--4 Lower value, Higher Priority.
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		         //ENABLE Interrupt
    NVIC_Init(&NVIC_InitStructure);
}	

/***********************************************************************************************************************
* Function:     void USART4_NVIC_Configuration(void)
*
* Scope:        
*
* Description:  USART4 Interruption Conffiguration
*
* Arguments:
*
* Return:
*
* Cpu_Time:     stm32f1(35 us)  stm32f4+nofpu(unknow us) stm32f4+fpu(unknow us)
*
* History:

***********************************************************************************************************************/
void UART4_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //PreemptionPriority  0--4 Lower value, Higher Priority.
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;	       //SubPriority 0--4 Lower value, Higher Priority.
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		         //ENABLE Interrupt
    NVIC_Init(&NVIC_InitStructure);
}	

/***********************************************************************************************************************
* Function:     void USART5_NVIC_Configuration(void)
*
* Scope:        
*
* Description:  USART5 Interruption Conffiguration
*
* Arguments:
*
* Return:
*
* Cpu_Time:     stm32f1(35 us)  stm32f4+nofpu(unknow us) stm32f4+fpu(unknow us)
*
* History:

***********************************************************************************************************************/
void UART5_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //PreemptionPriority  0--4 Lower value, Higher Priority.
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;	       //SubPriority 0--4 Lower value, Higher Priority.
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		         //ENABLE Interrupt
    NVIC_Init(&NVIC_InitStructure);
}	



/************************************************************************************************************************
***                                                                                                                   ***
***                                           TIM Interruption Conffiguration                                         ***
***                                                                                                                   ***
*************************************************************************************************************************/

/***********************************************************************************************************************
* Function:     void TIM1_NVIC_Configuration(void)
*
* Scope:        
*
* Description:  TIM1 Interruption Conffiguration
*
* Arguments:
*
* Return:
*
* Cpu_Time:     stm32f1(35 us)  stm32f4+nofpu(unknow us) stm32f4+fpu(unknow us)
*
* History:

***********************************************************************************************************************/
void TIM1_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //PreemptionPriority  0--4 Lower value, Higher Priority.
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	       //SubPriority 0--4 Lower value, Higher Priority.
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		         //ENABLE Interrupt
    NVIC_Init(&NVIC_InitStructure);
}	

/***********************************************************************************************************************
* Function:     void TIM2_NVIC_Configuration(void)
*
* Scope:        
*
* Description:  TIM2 Interruption Conffiguration
*
* Arguments:
*
* Return:
*
* Cpu_Time:     stm32f1(35 us)  stm32f4+nofpu(unknow us) stm32f4+fpu(unknow us)
*
* History:

***********************************************************************************************************************/
void TIM2_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //PreemptionPriority  0--4 Lower value, Higher Priority.
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	       //SubPriority 0--4 Lower value, Higher Priority.
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		         //ENABLE Interrupt
    NVIC_Init(&NVIC_InitStructure);
}	

/***********************************************************************************************************************
* Function:     void TIM3_NVIC_Configuration(void)
*
* Scope:        
*
* Description:  TIM3 Interruption Conffiguration
*
* Arguments:
*
* Return:
*
* Cpu_Time:     stm32f1(35 us)  stm32f4+nofpu(unknow us) stm32f4+fpu(unknow us)
*
* History:

***********************************************************************************************************************/
void TIM3_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //PreemptionPriority  0--4 Lower value, Higher Priority.
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	       //SubPriority 0--4 Lower value, Higher Priority.
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		         //ENABLE Interrupt
    NVIC_Init(&NVIC_InitStructure);
}	

/***********************************************************************************************************************
* Function:     void TIM4_NVIC_Configuration(void)
*
* Scope:        
*
* Description:  TIM4 Interruption Conffiguration
*
* Arguments:
*
* Return:
*
* Cpu_Time:     stm32f1(35 us)  stm32f4+nofpu(unknow us) stm32f4+fpu(unknow us)
*
* History:

***********************************************************************************************************************/
void TIM4_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //PreemptionPriority  0--4 Lower value, Higher Priority.
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	       //SubPriority 0--4 Lower value, Higher Priority.
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		         //ENABLE Interrupt
    NVIC_Init(&NVIC_InitStructure);
}	

/***********************************************************************************************************************
* Function:     void TIM5_NVIC_Configuration(void)
*
* Scope:        
*
* Description:  TIM5 Interruption Conffiguration
*
* Arguments:
*
* Return:
*
* Cpu_Time:     stm32f1(35 us)  stm32f4+nofpu(unknow us) stm32f4+fpu(unknow us)
*
* History:
***********************************************************************************************************************/
void TIM5_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //PreemptionPriority  0--4 Lower value, Higher Priority.
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	       //SubPriority 0--4 Lower value, Higher Priority.
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		         //ENABLE Interrupt
    NVIC_Init(&NVIC_InitStructure);
}	

/***********************************************************************************************************************
* Function:     void TIM6_NVIC_Configuration(void)
*
* Scope:        
*
* Description:  TIM6 Interruption Conffiguration
*
* Arguments:
*
* Return:
*
* Cpu_Time:     stm32f1(35 us)  stm32f4+nofpu(unknow us) stm32f4+fpu(unknow us)
*
* History:
***********************************************************************************************************************/
void TIM6_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //PreemptionPriority  0--4 Lower value, Higher Priority.
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	       //SubPriority 0--4 Lower value, Higher Priority.
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		         //ENABLE Interrupt
    NVIC_Init(&NVIC_InitStructure);
}	

/***********************************************************************************************************************
* Function:     void TIM7_NVIC_Configuration(void)
*
* Scope:        
*
* Description:  TIM7 Interruption Conffiguration
*
* Arguments:
*
* Return:
*
* Cpu_Time:     stm32f1(35 us)  stm32f4+nofpu(unknow us) stm32f4+fpu(unknow us)
*
* History:
***********************************************************************************************************************/
void TIM7_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //PreemptionPriority  0--4 Lower value, Higher Priority.
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	       //SubPriority 0--4 Lower value, Higher Priority.
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		         //ENABLE Interrupt
    NVIC_Init(&NVIC_InitStructure);
}	

/***********************************************************************************************************************
* Function:     void TIM8_NVIC_Configuration(void)
*
* Scope:        
*
* Description:  TIM8 Interruption Conffiguration
*
* Arguments:
*
* Return:
*
* Cpu_Time:     stm32f1(35 us)  stm32f4+nofpu(unknow us) stm32f4+fpu(unknow us)
*
* History:
***********************************************************************************************************************/
void TIM8_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //PreemptionPriority  0--4 Lower value, Higher Priority.
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	       //SubPriority 0--4 Lower value, Higher Priority.
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		         //ENABLE Interrupt
    NVIC_Init(&NVIC_InitStructure);
}	


/************************************************************************************************************************
***                                                                                                                   ***
***                                              EXTI Interruption Conffiguration                                     ***
***                                                                                                                   ***
*************************************************************************************************************************/

/***********************************************************************************************************************
* Function:     void EXTI0_NVIC_Configuration(void)
*
* Scope:        
*
* Description:  EXTI0 Interruption Conffiguration
*
* Arguments:
*
* Return:
*
* Cpu_Time:     stm32f1(35 us)  stm32f4+nofpu(unknow us) stm32f4+fpu(unknow us)
*
* History:
***********************************************************************************************************************/
void EXTI0_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}	

/***********************************************************************************************************************
* Function:     void EXTI1_NVIC_Configuration(void)
*
* Scope:        
*
* Description:  EXTI1 Interruption Conffiguration
*
* Arguments:
*
* Return:
*
* Cpu_Time:     stm32f1(35 us)  stm32f4+nofpu(unknow us) stm32f4+fpu(unknow us)
*
* History:
***********************************************************************************************************************/
void EXTI1_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}	

/***********************************************************************************************************************
* Function:     void EXTI2_NVIC_Configuration(void)
*
* Scope:        
*
* Description:  EXTI2 Interruption Conffiguration
*
* Arguments:
*
* Return:
*
* Cpu_Time:     stm32f1(35 us)  stm32f4+nofpu(unknow us) stm32f4+fpu(unknow us)
*
* History:

***********************************************************************************************************************/
void EXTI2_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}	

/***********************************************************************************************************************
* Function:     void EXTI3_NVIC_Configuration(void)
*
* Scope:        
*
* Description:  EXTI3 Interruption Conffiguration
*
* Arguments:
*
* Return:
*
* Cpu_Time:     stm32f1(35 us)  stm32f4+nofpu(unknow us) stm32f4+fpu(unknow us)
*
* History:

***********************************************************************************************************************/
void EXTI3_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/***********************************************************************************************************************
* Function:     void EXTI4_NVIC_Configuration(void)
*
* Scope:        
*
* Description:  EXTI4 Interruption Conffiguration
*
* Arguments:
*
* Return:
*
* Cpu_Time:     stm32f1(35 us)  stm32f4+nofpu(unknow us) stm32f4+fpu(unknow us)
*
* History:

***********************************************************************************************************************/
void EXTI4_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/***********************************************************************************************************************
* Function:     void EXTI9_5_NVIC_Configuration(void)
*
* Scope:        
*
* Description:  EXTI9_5 Interruption Conffiguration
*
* Arguments:
*
* Return:
*
* Cpu_Time:     stm32f1(35 us)  stm32f4+nofpu(unknow us) stm32f4+fpu(unknow us)
*
* History:

***********************************************************************************************************************/
void EXTI9_5_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}	

/***********************************************************************************************************************
* Function:     void EXTI15_10_NVIC_Configuration(void)
*
* Scope:        
*
* Description:  EXTI15_10 Interruption Conffiguration
*
* Arguments:
*
* Return:
*
* Cpu_Time:     stm32f1(35 us)  stm32f4+nofpu(unknow us) stm32f4+fpu(unknow us)
*
* History:

***********************************************************************************************************************/
void EXTI15_10_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}	


#ifdef __cplusplus
}
#endif 
