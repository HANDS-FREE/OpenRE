/****************************************Copyright(c)*****************************************************
**                            Shenzhen Yuejiang Technology Co., LTD.
**
**                                 http://www.dobot.cc
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           Message.cpp
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
#include "Message.h"
#include "Packet.h"
#include <string.h>

/*********************************************************************************************************
** Function name:       MessageRead
** Descriptions:        Read a message from rx packet queue
** Input parameters:    protocolHandler and message
** Output parameters:   None
** Returned value:      ProtocolResult
*********************************************************************************************************/
ProtocolResult MessageRead(ProtocolHandler *protocolHandler, Message *message)
{
    RingBuffer *rxPacketQueue = &protocolHandler->rxPacketQueue;
    Packet *packet = &protocolHandler->rxAppPacket;

    if (RingBufferIsEmpty(rxPacketQueue)) {
        return ProtocolReadMessageQueueEmpty;
    }
    // Read a packet
    RingBufferDequeue(rxPacketQueue, packet);
    // Transform to message
    message->id = packet->payload.id;
    message->rw = packet->payload.ctrl & 0x01;
    message->isQueued = (packet->payload.ctrl >> 1) & 0x01;
    message->paramsLen = packet->header.payloadLen - 2;
    if (message->paramsLen) {
        memcpy(&message->params[0], &packet->payload.params[0], message->paramsLen);
    }
    return ProtocolNoError;
}

/*********************************************************************************************************
** Function name:       MessageWrite
** Descriptions:        Write a message to tx packet queue
** Input parameters:    protocolHandler and message
** Output parameters:   None
** Returned value:      ProtocolResult
*********************************************************************************************************/
ProtocolResult MessageWrite(ProtocolHandler *protocolHandler, const Message *message)
{
    RingBuffer *txPacketQueue = &protocolHandler->txPacketQueue;
    Packet *packet = &protocolHandler->txAppPacket;

    if (RingBufferIsFull(txPacketQueue)) {
        return ProtocolWritePacketQueueFull;
    }
    // Header
    packet->header.payloadLen = message->paramsLen + 2;

    // Payload
    packet->payload.id = message->id;
    packet->payload.ctrl = 0;  //ÏÈ³õÊ¼»¯ctrl
    packet->payload.ctrl |= message->rw & 0x01;
    packet->payload.ctrl |= (message->isQueued << 1) & 0x02;
    if (message->paramsLen) {
        memcpy(&packet->payload.params[0], &message->params[0], message->paramsLen);
    }
    RingBufferEnqueue(txPacketQueue, packet);

    return ProtocolNoError;
}

/*********************************************************************************************************
** Function name:       MessageProcess
** Descriptions:
** Input parameters:    protocolHandler and message
** Output parameters:   None
** Returned value:      None
*********************************************************************************************************/
void MessageProcess(ProtocolHandler *protocolHandler)
{
    PacketProcess(protocolHandler);
}
