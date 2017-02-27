#ifndef USART_H
#define USART_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "stm32f4xx.h"
#include "stdarg.h"
#include "stdio.h"

//USART_Channel = 1~6 , 2nd Para:bits rate; 3rd: IO reuse
void HF_USART_Init(uint8_t USART_Channel , uint32_t BaudRate , uint8_t GPIO_AF);
void HF_USART_Put_Char(uint8_t USART_Channel , uint8_t Tx_Byte);
//format output as printf in C standard library
void HF_USART_printf(USART_TypeDef* USARTx , const char * Data, ...);

#ifdef __cplusplus
}
#endif 

#endif // #ifndef USART_H


