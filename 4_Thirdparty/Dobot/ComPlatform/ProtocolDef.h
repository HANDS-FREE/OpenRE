/****************************************Copyright(c)*****************************************************
**                            Shenzhen Yuejiang Technology Co., LTD.
**
**                                 http://www.dobot.cc
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           ProtocolDef.h
** Latest modified Date:2016-06-01
** Latest Version:      V1.0.0
** Descriptions:        Protocol definition
**
**--------------------------------------------------------------------------------------------------------
** Created by:          Liu Zhufu
** Created date:        2016-06-01
** Version:             V1.0.0
** Descriptions:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#ifndef PROTOCOLDEF_H
#define PROTOCOLDEF_H

#include "RingBuffer.h"

#define SYNC_BYTE   0xAA

#define MAX_PAYLOAD_SIZE (SYNC_BYTE - 1)                                // Minus 1 for not larger than SYNC_BYTE

#pragma pack(push)
#pragma pack(1)

// Just for easy use of this protocol
typedef struct tagMessage {
    uint8_t id;
    uint8_t rw;
    uint8_t isQueued;
    uint8_t paramsLen;
    uint8_t params[MAX_PAYLOAD_SIZE - 2];
}Message;

// Packet header
typedef struct tagPacketHeader {
    uint8_t syncBytes[2];
    uint8_t payloadLen;
}PacketHeader;

typedef struct tagPacketPayload {
    uint8_t id;
    uint8_t ctrl;
    uint8_t params[MAX_PAYLOAD_SIZE - 2];
}PacketPayload;  //负载帧

typedef struct tagPacket {
    PacketHeader header;
    PacketPayload payload;
    uint8_t checksum;
}Packet;  //协议包

typedef void (*SendFunc)(void);

typedef struct tagProtocolHandler {
    // For hardware
    RingBuffer txRawByteQueue;
    RingBuffer rxRawByteQueue;

    Packet txAppPacket;
    Packet rxAppPacket;
    Packet rxDLPacket;

    // For application
    RingBuffer txPacketQueue;
    RingBuffer rxPacketQueue;
}ProtocolHandler;

#pragma pack(pop)

#endif
