#ifndef USART_H
#define USART_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "stm32f4xx.h"
#include "stdarg.h"
#include "stdio.h"
#include "string.h"

//Initilaize the serial, First Parameter:USART1,USART2,USART3; 2nd Para:bits rate; 3rd: IO reuse
void HF_USART_Init(USART_TypeDef* USARTx, uint32_t BaudRate, uint8_t GPIO_AF);
void HF_USART_Put_Char(USART_TypeDef* USARTx, uint8_t Tx_Byte);   //USARTx to print 1 byte
void HF_USART_printf(const char * Data, ...);  //format output as printf in C standard library

#ifdef __cplusplus
}
#endif 

#endif // #ifndef USART_H


