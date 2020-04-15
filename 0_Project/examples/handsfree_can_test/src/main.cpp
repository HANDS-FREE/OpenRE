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
* mawenke      2015.10.1    V1.0          creat this file
*
* Description:
***********************************************************************************************************************/

#include "main_config.h"
#include "board.h"
#include "stdlib.h"

extern "C" {

#ifdef __STM32F10x_CONF_H
void USB_LP_CAN1_RX0_IRQHandler(void)
#endif
#ifdef __STM32F4xx_CONF_H
void CAN1_RX0_IRQHandler(void)
#endif
{
#if SYSTEM_SUPPORT_OS == 1
    OSIntEnter();
#endif
    if (CAN_GetITStatus(CAN1,CAN_IT_FMP0)!= RESET)
    {
        CanRxMsg RxMessage;

        CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
        printf("CAN1 IRQHandler Receive Data: %s \r\n",RxMessage.Data);

        Board::getInstance()->setLedState(2,2);
        CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
    }
#if SYSTEM_SUPPORT_OS == 1
    OSIntExit();
#endif
}

#ifdef __STM32F4xx_CONF_H
void CAN2_RX0_IRQHandler(void)
{
#if SYSTEM_SUPPORT_OS == 1
    OSIntEnter();
#endif
    if (CAN_GetITStatus(CAN2,CAN_IT_FMP0)!= RESET)
    {
        CanRxMsg RxMessage;

        CAN_Receive(CAN2, CAN_FIFO0, &RxMessage);
        printf("CAN2 IRQHandler Receive Data: %s \r\n",RxMessage.Data);

        Board::getInstance()->setLedState(3,2);
        CAN_ClearITPendingBit(CAN2, CAN_IT_FMP0);
    }
#if SYSTEM_SUPPORT_OS == 1
    OSIntExit();
#endif
}
#endif
}

uint8_t can1_send_data(void)
{
    uint8_t Data[8]={'c','a','n','t','e','s','t','!'};
    return HF_CANTX_Message(1,0x02,0x01,Data,8);
}

uint8_t can2_send_data(void)
{
#ifdef __STM32F4xx_CONF_H
    uint8_t Data[8]={'c','a','n','t','e','s','t','!'};
    return HF_CANTX_Message(2,0x02,0x01,Data,8);
#endif
}

void can1_inquire_data(void)
{
    CanRxMsg RxMessage;
    if( CAN_MessagePending(CAN1,CAN_FIFO0) == 0 ) return;
    CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
    printf("CAN1 Inquire Receive Data: %s \r\n",RxMessage.Data);
}

void can2_inquire_data(void)
{
#ifdef __STM32F4xx_CONF_H
    CanRxMsg RxMessage;
    if( CAN_MessagePending(CAN2,CAN_FIFO0) ==0 ) return;
    CAN_Receive(CAN2, CAN_FIFO0, &RxMessage);
    printf("CAN2 Inquire Receive Data: %s \r\n",RxMessage.Data);
#endif
}

int main(void)
{
    Board *board = Board::getInstance();
    board->boardBasicInit();

#ifdef __STM32F10x_CONF_H
    HF_CAN_Init(1 , 1 , CAN_Mode_Normal , CAN_SJW_2tq , CAN_BS1_5tq , CAN_BS2_3tq , 4);
#endif

#ifdef __STM32F4xx_CONF_H
    HF_CAN_Init(1 , 0 , CAN_Mode_LoopBack , CAN_SJW_1tq , CAN_BS1_9tq , CAN_BS2_4tq , 3);
    HF_CAN_Init(2 , 1 , CAN_Mode_Normal , CAN_SJW_1tq , CAN_BS1_9tq , CAN_BS2_4tq , 3);
#endif

    printf("CAN test .... \r\n");

    while(1)
    {
        if ( board->cnt_1ms >= 1 )      // 1000hz
        {
            board->cnt_1ms=0;
        }
        if ( board->cnt_2ms >= 2 )      // 500hz
        {
            board->cnt_2ms=0;
        }
        if ( board->cnt_5ms >= 5 )      // 200hz
        {
            board->cnt_5ms=0;
        }
        if ( board->cnt_10ms >= 10 )    // 100hz
        {
            board->cnt_10ms=0;
            board->boardBasicCall();    // need time stm32f1 35us
        }
        if ( board->cnt_20ms >= 20 )    // 50hz
        {
            board->cnt_20ms = 0 ;
        }
        if ( board->cnt_50ms >= 50 )    // 20hz
        {
            board->cnt_50ms = 0 ;
            board->setLedState(1,2);
        }
        if ( board->cnt_100ms >= 100 )    // 10hz
        {
            board->cnt_100ms = 0 ;
        }
        if ( board->cnt_500ms >= 500 )    // 2hz
        {
            board->cnt_500ms = 0;
            can1_send_data();
            can2_send_data();
        }
        if ( board->cnt_1000ms >= 1000 )  // 1hz
        {
            board->cnt_1000ms = 0;
        }
        if ( board->cnt_2000ms >= 2000 )  // 0.5hz
        {
            board->cnt_2000ms = 0;
        }
    }

    return 0;
}


