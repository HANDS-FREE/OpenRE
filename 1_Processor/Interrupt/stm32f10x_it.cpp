/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: 
* Contact:  QQ Exchange Group -- 521037187
* Version:  V2.0
*
* LICENSING TERMS:
* The Hands Free is licensed generally under a permissive 3-clause BSD license. 
* Contributions are requiredto be made under the same license.
*
* History:
* <author>      <time>      <version>      <desc>
*
* Description:   
***********************************************************************************************************************/

#include "main_config.h"
#include "os_include.h"
#include "board.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f10x_it.h"

void USART1_IRQHandler(void)
{
    unsigned char data;
#if SYSTEM_SUPPORT_OS == 1
    OSIntEnter();
#endif
    if(USART1->SR&(1<<5))
    {
        data=USART1->DR;
        if( board.usart1_queue.fullCheck() ==0 ){
            board.usart1_queue.putData(data);
        }
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);   // clear interrupt flag
    }
#if SYSTEM_SUPPORT_OS == 1
    OSIntExit();
#endif
}

void USART2_IRQHandler(void)
{
    unsigned char data = 0;
#if SYSTEM_SUPPORT_OS == 1
    OSIntEnter();
#endif
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        data = USART_ReceiveData(USART2);
        if( board.usart2_queue.fullCheck() ==0 ){
            board.usart2_queue.putData(data);
        }
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);  // clear interrupt flag
    }
#if SYSTEM_SUPPORT_OS == 1
    OSIntExit();
#endif
}

void USART3_IRQHandler(void)
{
    unsigned char data = 0;
#if SYSTEM_SUPPORT_OS == 1
    OSIntEnter();
#endif
    if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
    {
        data=USART_ReceiveData(USART3);
        if( board.usart3_queue.fullCheck() ==0 ){
            board.usart3_queue.putData(data);
        }
        USART_ClearITPendingBit(USART3,USART_IT_RXNE);  //clear interrupt flag
    }
#if SYSTEM_SUPPORT_OS == 1
    OSIntExit();
#endif
}

void UART4_IRQHandler(void)
{
    unsigned char data = 0;
#if SYSTEM_SUPPORT_OS == 1
    OSIntEnter();
#endif
    if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
    {
        data = USART_ReceiveData(UART4);
        if( board.usart4_queue.fullCheck() ==0 ){
            board.usart4_queue.putData(data);
        }
        //HF_USART_Put_Char(4 , data);
        //board.setLedState(1,1);
        USART_ClearITPendingBit(UART4, USART_IT_RXNE);     //clear interrupt flag
    }
#if SYSTEM_SUPPORT_OS == 1
    OSIntExit();
#endif
}

void UART5_IRQHandler(void)
{
    unsigned char data = 0;
#if SYSTEM_SUPPORT_OS == 1
    OSIntEnter();
#endif
    if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)
    {
        data = USART_ReceiveData(UART5);
        if( board.usart5_queue.fullCheck() ==0 ){
            board.usart5_queue.putData(data);
        }
        //HF_USART_Put_Char(5 , data);
        //board.setLedState(1,1);
        USART_ClearITPendingBit(UART5 , USART_IT_RXNE);   //clear interrupt flag
    }
#if SYSTEM_SUPPORT_OS == 1
    OSIntExit();
#endif
}

void TIM6_IRQHandler(void)
{
#if SYSTEM_SUPPORT_OS == 1
    OSIntEnter();
#endif
    if(TIM_GetITStatus(TIM6 , TIM_IT_Update)== SET  )
    {
        board.cnt_1ms++;
        board.cnt_2ms++;
        board.cnt_5ms++;
        board.cnt_10ms++;
        board.cnt_20ms++;
        board.cnt_50ms++;
        TIM_ClearITPendingBit(TIM6 , TIM_FLAG_Update);     // clear interrupt flag
    }
#if SYSTEM_SUPPORT_OS == 1
    OSIntExit();
#endif
}

void HardFault_Handler(void)
{
    unsigned char i;
#if SYSTEM_SUPPORT_OS == 1
    OSIntEnter();
#endif
    //    for(i=0;i<20;i++)
    //    {
    //        board.setBeepState(2);
    //        delay_ms(100);
    //    }
    board.setBeepModel(3); // 10hz
    //	__disable_fault_irq();  //reset
    //	NVIC_SystemReset();
#if SYSTEM_SUPPORT_OS == 1
    OSIntExit();
#endif
}

#ifdef __cplusplus
}
#endif
