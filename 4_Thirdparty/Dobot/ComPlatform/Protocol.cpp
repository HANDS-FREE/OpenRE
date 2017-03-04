/****************************************Copyright(c)*****************************************************
**                            Shenzhen Yuejiang Technology Co., LTD.
**
**                                 http://www.dobot.cc
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           Protocol.cpp
** Latest modified Date:2016-06-01
** Latest Version:      V1.0.0
** Descriptions:        Protocol interface
**
**--------------------------------------------------------------------------------------------------------
** Created by:          Liu Zhufu
** Created date:        2016-03-14
** Version:             V1.0.0
** Descriptions:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
//#include "stm32f10x.h"
#include "Protocol.h"
#include <stdio.h>
#include <string.h>
//#include "../driver/usart.h"

/*********************************************************************************************************
** Protocol buffer definition
*********************************************************************************************************/
#define RAW_TX_BYTE_BUFFER_SIZE    1024
#define RAW_RX_BYTE_BUFFER_SIZE    4096
#define RAW_BYTE_BUFFER_SIZE    4096
#define PACKET_BUFFER_SIZE  8

// UART4
uint8_t gUART4TXRawByteBuffer[RAW_BYTE_BUFFER_SIZE];
uint8_t gUART4RXRawByteBuffer[RAW_BYTE_BUFFER_SIZE];
Packet gUART4TXPacketBuffer[PACKET_BUFFER_SIZE];
Packet gUART4RXPacketBuffer[PACKET_BUFFER_SIZE];

ProtocolHandler gUART4ProtocolHandler;


/*********************************************************************************************************
** Function name:       ProtocolInit
** Descriptions:        Init the protocol buffer etc.
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
*********************************************************************************************************/
void ProtocolInit(void)
{
    // Init UART4 protocol
    RingBufferInit(&gUART4ProtocolHandler.txRawByteQueue, gUART4TXRawByteBuffer, RAW_BYTE_BUFFER_SIZE, sizeof(uint8_t));
    RingBufferInit(&gUART4ProtocolHandler.rxRawByteQueue, gUART4RXRawByteBuffer, RAW_BYTE_BUFFER_SIZE, sizeof(uint8_t));
    RingBufferInit(&gUART4ProtocolHandler.txPacketQueue, gUART4TXPacketBuffer, PACKET_BUFFER_SIZE, sizeof(Packet));
    RingBufferInit(&gUART4ProtocolHandler.rxPacketQueue, gUART4RXPacketBuffer, PACKET_BUFFER_SIZE, sizeof(Packet));

}

/*********************************************************************************************************
** Function name:       ProtocolProcess
** Descriptions:        Process the protocol
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
*********************************************************************************************************/
void ProtocolProcess(void)
{
//    Message message;
//    MessageProcess(&gUART4ProtocolHandler);
//    if (RingBufferGetCount(&gUART4ProtocolHandler.txRawByteQueue)) {
//        USART_ITConfig(UART4, USART_IT_TXE, ENABLE);  //在此处开启发送中断，只要发送队列不为空则一直发送数据
//    }

//    if(MessageRead(&gUART4ProtocolHandler, &message)==ProtocolNoError)
//    {
//        #if 1
//        //打印接收到的返回数据
//        printf("Rx message: ");
//        printf("message id:%d, rw:%d, isQueued:%d, paramsLen:%d\r\n",
//                message.id, message.rw, message.isQueued, message.paramsLen);
//        printf("params: ");
//        for(int i=0; i<message.paramsLen; i++)
//        {
//            printf("%02x ", message.params[i]);
//        }
//        printf("\r\n");
//        #endif
//    }
}
