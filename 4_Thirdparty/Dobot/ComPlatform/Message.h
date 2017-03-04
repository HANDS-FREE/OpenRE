/****************************************Copyright(c)*****************************************************
**                            Shenzhen Yuejiang Technology Co., LTD.
**
**                                 http://www.dobot.cc
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           Message.h
** Latest modified Date:2016-06-01
** Latest Version:      V2.0.0
** Descriptions:        Message API
**
**--------------------------------------------------------------------------------------------------------
** Created by:
** Created date:        2016-06-01
** Version:             V1.0.0
** Descriptions:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#ifndef MESSAGE_H
#define MESSAGE_H

#include "ProtocolDef.h"

typedef enum tagProtocolResult {
    ProtocolNoError,
    ProtocolReadMessageQueueEmpty,
    ProtocolWritePacketQueueFull
}ProtocolResult;

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************************************************
** Function name:       MessageRead
** Descriptions:        Read a message from rx message queue
** Input parameters:    protocolHandler and message
** Output parameters:   None
** Returned value:      ProtocolResult
*********************************************************************************************************/
extern ProtocolResult MessageRead(ProtocolHandler *protocolHandler, Message *message);

/*********************************************************************************************************
** Function name:       MessageWrite
** Descriptions:        Write a message to tx message queue
** Input parameters:    protocolHandler and message
** Output parameters:   None
** Returned value:      ProtocolResult
*********************************************************************************************************/
extern ProtocolResult MessageWrite(ProtocolHandler *protocolHandler, const Message *message);

/*********************************************************************************************************
** Function name:       MessageProcess
** Descriptions:
** Input parameters:    protocolHandler and message
** Output parameters:   None
** Returned value:      None
*********************************************************************************************************/
extern void MessageProcess(ProtocolHandler *protocolHandler);

#ifdef __cplusplus
}
#endif

#endif
