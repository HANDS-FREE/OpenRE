#ifndef USART_H
#define USART_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "stm32f4xx.h"
#include "stdarg.h"
#include "stdio.h"

//Initilaize the serial, First Parameter:USART1,USART2,USART3; 2nd Para:bits rate; 3rd: IO reuse
void HF_USART_Init(uint8_t USART_Channel , uint32_t BaudRate , uint8_t GPIO_AF);
void HF_USART_Put_Char(uint8_t USART_Channel , uint8_t Tx_Byte);   //USARTx to print 1 byte
void HF_USART_printf(USART_TypeDef* USARTx , const char * Data, ...);  //format output as printf in C standard library

#ifdef __cplusplus
}
#endif 

#endif // #ifndef USART_H


