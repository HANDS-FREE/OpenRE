/****************************************Copyright(c)*****************************************************
**                            Shenzhen Yuejiang Technology Co., LTD.
**
**                                 http://www.dobot.cc
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           RingBuffer.h
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
#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include <stdint.h>
#include <stdbool.h>

#pragma pack(push)
#pragma pack(1)  //使RingBuffer结构体的数据连续存储

typedef struct tagRingBuffer {
    // Static property
    void *addr;
    uint32_t capacity;
    uint32_t elemSize;
    // Dynamic property
    volatile bool isEmpty;
    volatile bool isFull;
    volatile uint32_t count;
    volatile uint32_t readAddress;
    volatile uint32_t writeAddress;
    volatile uint64_t readIndex;
    volatile uint64_t writeIndex;
}RingBuffer;

#pragma pack(pop)

/*********************************************************************************************************
** Function name:       RingBufferInit
** Descriptions:        RingBuffer init
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
*********************************************************************************************************/
extern void RingBufferInit(RingBuffer *ringBuffer, void *addr, uint32_t capacity, int32_t elemSize);

/*********************************************************************************************************
** Function name:       RingBufferClear
** Descriptions:
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
*********************************************************************************************************/
extern void RingBufferClear(RingBuffer *ringBuffer);

/*********************************************************************************************************
** Function name:       RingBufferIsEmpty
** Descriptions:
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
*********************************************************************************************************/
inline bool RingBufferIsEmpty(RingBuffer *ringBuffer)
{
    return ringBuffer->isEmpty;
}

/*********************************************************************************************************
** Function name:       RingBufferIsFull
** Descriptions:
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
*********************************************************************************************************/
inline bool RingBufferIsFull(RingBuffer *ringBuffer)
{
    return ringBuffer->isFull;
}

/*********************************************************************************************************
** Function name:       RingBufferGetCount
** Descriptions:
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
*********************************************************************************************************/
inline uint32_t RingBufferGetCount(RingBuffer *ringBuffer)
{
    return ringBuffer->count;
}

/*********************************************************************************************************
** Function name:       RingBufferGetLeft
** Descriptions:
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
*********************************************************************************************************/
inline uint32_t RingBufferGetLeft(RingBuffer *ringBuffer)
{
    return ringBuffer->capacity - ringBuffer->count;
}

/*********************************************************************************************************
** Function name:       RingBufferDataAt
** Descriptions:
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
*********************************************************************************************************/
inline void *RingBufferDataAt(RingBuffer *ringBuffer, uint32_t index)
{
    uint32_t trueIndex = (ringBuffer->readAddress + index) % ringBuffer->capacity;

    return (uint8_t *)ringBuffer->addr + trueIndex * ringBuffer->elemSize;
}

/*********************************************************************************************************
** Function name:       RingBufferEnqueue
** Descriptions:        RingBuffer enqueue
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
*********************************************************************************************************/
extern void RingBufferEnqueue(RingBuffer *ringBuffer, void *addr);

/*********************************************************************************************************
** Function name:       RingBufferDequeue
** Descriptions:        RingBuffer dequeue
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
*********************************************************************************************************/
extern void RingBufferDequeue(RingBuffer *ringBuffer, void *addr);

#ifdef __cplusplus
}
#endif

#endif
