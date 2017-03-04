/****************************************Copyright(c)*****************************************************
**                            Shenzhen Yuejiang Technology Co., LTD.
**
**                                 http://www.dobot.cc
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           Packet.h
** Latest modified Date:2016-06-01
** Latest Version:      V2.0.0
** Descriptions:        Packet API
**
**--------------------------------------------------------------------------------------------------------
** Created by:
** Created date:        2016-06-01
** Version:             V1.0.0
** Descriptions:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#ifndef PACKET_H
#define PACKET_H

#include "ProtocolDef.h"

/*********************************************************************************************************
** Function name:       PacketProcess
** Descriptions:        Packet write process
** Input parameters:    packetHandler
** Output parameters:   None
** Returned value:      None
*********************************************************************************************************/
extern void PacketProcess(ProtocolHandler *protocolHandler);

#endif
