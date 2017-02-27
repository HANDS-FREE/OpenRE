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

#include "board.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_it.h"

void USART1_IRQHandler(void)
{
    unsigned char data =0;
#if SYSTEM_SUPPORT_OS == 1
    OSIntEnter();
#endif
    if(USART1->SR&(1<<5))
    {
        data=USART1->DR;
        if( board.getUsartQueue(1)->fullCheck() ==0 ){
            board.getUsartQueue(1)->putData(data);
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
        if( board.getUsartQueue(2)->fullCheck() ==0 ){
            board.getUsartQueue(2)->putData(data);
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
        if( board.getUsartQueue(3)->fullCheck() ==0 ){
            board.getUsartQueue(3)->putData(data);
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
        if( board.getUsartQueue(4)->fullCheck() ==0 ){
            board.getUsartQueue(4)->putData(data);
        }
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
        if( board.getUsartQueue(5)->fullCheck() ==0 ){
            board.getUsartQueue(5)->putData(data);
        }
        USART_ClearITPendingBit(UART5 , USART_IT_RXNE);   //clear interrupt flag
    }
#if SYSTEM_SUPPORT_OS == 1
    OSIntExit();
#endif
}

void USART6_IRQHandler(void)
{
    unsigned char data = 0;
#if SYSTEM_SUPPORT_OS == 1
    OSIntEnter();
#endif
    if(USART_GetITStatus(USART6, USART_IT_RXNE) != RESET)
    {
        data = USART_ReceiveData(USART6);
        if( board.getUsartQueue(6)->fullCheck() ==0 ){
            board.getUsartQueue(6)->putData(data);
        }
        USART_ClearITPendingBit(USART6 , USART_IT_RXNE);   //clear interrupt flag
    }
#if SYSTEM_SUPPORT_OS == 1
    OSIntExit();
#endif
}

void TIM6_DAC_IRQHandler(void)
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

#if SYSTEM_SUPPORT_OS == 1
    OSIntEnter();
#endif

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
