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
*
* Description: To manage all interruption conveniently, putting all interuption initialization in this file and
* called by other files Not cover the interruotion of Watch Dog and delay function
* Interruption use: NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
***********************************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif 

#include "nvic.h"

/***********************************************************************************************************************
***                                                                                                                  ***
***                                           CAN Interruption Conffiguration                ***
***                                                                                                                  ***
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function:     void CAN1_RX0_NVIC_Configuration(void)
*
* Scope:        
*
* Description:  CAN1_RX0 Interruption Conffiguration
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:

***********************************************************************************************************************/
void CAN1_RX0_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //PreemptionPriority  0--4 Lower value, Higher Priority.
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;         //SubPriority 0--4 Lower value, Higher Priority.
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	           //ENABLE Interrupt
    NVIC_Init(&NVIC_InitStructure);
}	

/***********************************************************************************************************************
* Function:     void CAN1_RX1_NVIC_Configuration(void)
*
* Scope:        
*
* Description:  CAN1_RX1 Interruption Conffiguration
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:

***********************************************************************************************************************/
void CAN1_RX1_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
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
void CAN2_RX0_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
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
void CAN2_RX1_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/************************************************************************************************************************
***                                                                                                                   ***
***                               USART Interruption Conffiguration                         ***
***                                                                                                                   ***
*************************************************************************************************************************/

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
* Cpu_Time:  
*
* History:

***********************************************************************************************************************/
void USART1_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //PreemptionPriority  0--4 Lower value, Higher Priority.
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;         //SubPriority 0--4 Lower value, Higher Priority.
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //ENABLE Interrupt
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
* Cpu_Time:  
*
* History:

***********************************************************************************************************************/
void USART2_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
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
* Cpu_Time:  
*
* History:

***********************************************************************************************************************/
void USART3_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
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
* Cpu_Time:  
*
* History:

***********************************************************************************************************************/
void UART4_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
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
* Cpu_Time:  
*
* History:

***********************************************************************************************************************/
void UART5_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}	

/***********************************************************************************************************************
* Function:     void USART6_NVIC_Configuration(void)
*
* Scope:        
*
* Description:  USART6 Interruption Conffiguration
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:

***********************************************************************************************************************/
void USART6_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}	


/************************************************************************************************************************
***                                                                                                                   ***
***                                          TIM Interruption Conffiguration                   ***
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
* Cpu_Time:  
*
* History:

***********************************************************************************************************************/
void TIM1_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //PreemptionPriority  0--4 Lower value, Higher Priority.
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;         //SubPriority 0--4 Lower value, Higher Priority.
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	           //ENABLE Interrupt
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
* Cpu_Time: 
*
* History:

***********************************************************************************************************************/
void TIM2_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
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
* Cpu_Time:  
*
* History:

***********************************************************************************************************************/
void TIM3_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
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
* Cpu_Time:  
*
* History:

***********************************************************************************************************************/
void TIM4_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
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
* Cpu_Time:  
*
* History:

***********************************************************************************************************************/
void TIM5_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
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
* Cpu_Time:  
*
* History:

***********************************************************************************************************************/
void TIM6_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = TIM6_DAC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
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
* Cpu_Time:  
*
* History:

***********************************************************************************************************************/
void TIM7_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
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
* Cpu_Time:  
*
* History:

***********************************************************************************************************************/
void TIM8_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = TIM8_CC_IRQn ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}	

/***********************************************************************************************************************
* Function:     void TIM9_NVIC_Configuration(void)
*
* Scope:        
*
* Description:  TIM9 Interruption Conffiguration
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:

***********************************************************************************************************************/
void TIM9_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = TIM1_BRK_TIM9_IRQn ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}	

/***********************************************************************************************************************
* Function:     void TIM10_NVIC_Configuration(void)
*
* Scope:        
*
* Description:  TIM10 Interruption Conffiguration
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:

***********************************************************************************************************************/
void TIM10_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}	

/***********************************************************************************************************************
* Function:     void TIM11_NVIC_Configuration(void)
*
* Scope:        
*
* Description:  TIM11 Interruption Conffiguration
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:

***********************************************************************************************************************/
void TIM11_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = TIM1_TRG_COM_TIM11_IRQn ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}	

/***********************************************************************************************************************
* Function:     void TIM12_NVIC_Configuration(void)
*
* Scope:        
*
* Description:  TIM12 Interruption Conffiguration
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:

***********************************************************************************************************************/
void TIM12_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = TIM8_BRK_TIM12_IRQn ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}	

/***********************************************************************************************************************
* Function:     void TIM13_NVIC_Configuration(void)
*
* Scope:        
*
* Description:  TIM13 Interruption Conffiguration
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:

***********************************************************************************************************************/
void TIM13_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel =TIM8_UP_TIM13_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}	

/***********************************************************************************************************************
* Function:     void TIM14_NVIC_Configuration(void)
*
* Scope:        
*
* Description:  TIM14 Interruption Conffiguration
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:

***********************************************************************************************************************/
void TIM14_NVIC_Configuration(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = TIM8_TRG_COM_TIM14_IRQn ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}	

/************************************************************************************************************************
***                                                                                                                   ***
***                                          EXTI Interruption Conffiguration                  ***
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
* Cpu_Time:  
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
* Cpu_Time:  
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
* Cpu_Time:  
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
* Cpu_Time:  
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
* Cpu_Time:  
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
* Cpu_Time:  
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
* Cpu_Time:  
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
