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

#include "main_includes.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_it.h"

void USART1_IRQHandler(void)
{
    unsigned char data;
#if SYSTEM_SUPPORT_OS == 1
    OSIntEnter();
#endif
    if(USART1->SR&(1<<5))
    {
        data=USART1->DR;
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);   // clear interrupt flag
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

#ifdef __cplusplus
}
#endif


