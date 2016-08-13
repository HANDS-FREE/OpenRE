#ifndef __spi_H__
#define __spi_H__

#ifdef __cplusplus
extern "C" {
#endif 

#include "stm32f10x.h"
#include "main_config.h"

//Initialize serial external interface of SPI, config SPI working on master mode
void HF_SPI_Init(SPI_TypeDef *SPIx, unsigned char GPIO_AF);    //SPI interface initialization, input parameter SPI1 SPI2
unsigned char HF_SPI_ReadWriteByte(SPI_TypeDef *SPIx, unsigned char TxData);      //SPI w/r data function

#ifdef __cplusplus
}
#endif 

#endif //__spi_H__


