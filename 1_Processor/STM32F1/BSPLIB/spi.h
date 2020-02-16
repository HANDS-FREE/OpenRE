#ifndef SPI_H
#define SPI_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "stm32f10x.h"

//Initialize serial external interface of SPI, config SPI working on master mode
void HF_SPI_Init(uint8_t SPI_Channel , uint8_t GPIO_AF);    //SPI interface initialization, input parameter SPI1 SPI2
uint8_t HF_SPI_ReadWriteByte(uint8_t SPI_Channel , uint8_t TxData);      //SPI w/r data function

#ifdef __cplusplus
}
#endif 

#endif // #ifndef SPI_H


