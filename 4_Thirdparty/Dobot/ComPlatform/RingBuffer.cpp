/****************************************Copyright(c)*****************************************************
**                            Shenzhen Yuejiang Technology Co., LTD.
**
**                                 http://www.dobot.cc
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           RingBuffer.cpp
** Latest modified Date:
** Latest Version:      V1.0.0
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Created by:          Liu Zhufu
** Created date:        2016-06-01
** Version:             V1.0.0
** Descriptions:        Ring buffer self implementation
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "RingBuffer.h"
#include <string.h>
#include "board.h"

/*********************************************************************************************************
** Function name:       RingBufferInit
** Descriptions:        RingBuffer init
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
*********************************************************************************************************/
void RingBufferInit(RingBuffer *ringBuffer, void *addr, uint32_t capacity, int32_t elemSize)
{
    // Static property
    ringBuffer->addr = addr;
    ringBuffer->capacity = capacity;
    ringBuffer->elemSize = elemSize;
    // Dynamic property
    ringBuffer->isEmpty = true;
    ringBuffer->isFull = false;
    ringBuffer->count = 0;
    ringBuffer->readAddress = 0;
    ringBuffer->writeAddress = 0;

    ringBuffer->readIndex = 1;
    ringBuffer->writeIndex = 1;
}

/*********************************************************************************************************
** Function name:       RingBufferClear
** Descriptions:
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
*********************************************************************************************************/
void RingBufferClear(RingBuffer *ringBuffer)
{
    // Dynamic property
    ringBuffer->isEmpty = true;
    ringBuffer->isFull = false;
    ringBuffer->count = 0;
    ringBuffer->readAddress = 0;
    ringBuffer->writeAddress = 0;

    ringBuffer->readIndex = ringBuffer->writeIndex;
}

/*********************************************************************************************************
** Function name:       RingBufferEnqueue
** Descriptions:        RingBuffer enqueue
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
*********************************************************************************************************/
void RingBufferEnqueue(RingBuffer *ringBuffer, void *addr)   //Èë¶Ó
{
    if (addr) {
        memcpy((uint8_t *)ringBuffer->addr + ringBuffer->writeAddress * ringBuffer->elemSize, addr, ringBuffer->elemSize);
    }
    ringBuffer->writeAddress = (ringBuffer->writeAddress + 1) % ringBuffer->capacity;
    ringBuffer->writeIndex++;
#ifdef __arm__
    __disable_irq();
#endif
    ringBuffer->count++;
    ringBuffer->isEmpty = false;
    if (ringBuffer->count == ringBuffer->capacity) {
        ringBuffer->isFull = true;
    }
#ifdef __arm__
    __enable_irq();
#endif
}

/*********************************************************************************************************
** Function name:       RingBufferDequeue
** Descriptions:        RingBuffer dequeue
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
*********************************************************************************************************/
void RingBufferDequeue(RingBuffer *ringBuffer, void *addr)
{
    if (addr) {
        memcpy(addr, (uint8_t *)ringBuffer->addr + ringBuffer->readAddress * ringBuffer->elemSize, ringBuffer->elemSize);
    }
    ringBuffer->readAddress = (ringBuffer->readAddress + 1) % ringBuffer->capacity;
    ringBuffer->readIndex++;
#ifdef __arm__
    __disable_irq();
#endif
    ringBuffer->count--;
    if (ringBuffer->count == 0) {
        ringBuffer->isEmpty = true;
    }
    ringBuffer->isFull = false;
#ifdef __arm__
    __enable_irq();
#endif
}
