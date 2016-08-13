#ifndef __uasrt_H__
#define __uasrt_H__

#ifdef __cplusplus
extern "C" {
#endif 

#include "stm32f10x.h"
#include "stdarg.h"	 	 
#include "stdio.h"	 	 
#include "string.h"	 
#include "main_config.h"

//Initilaize the serial, First Parameter:USART1,USART2,USART3; 2nd Para:bits rate; 3rd: IO reuse
void HF_Usart_Init(USART_TypeDef* USARTx, unsigned int BaudRate, unsigned char GPIO_AF);
void Usart_Put_Char(USART_TypeDef* USARTx, unsigned char Tx_Byte);   //USARTx to print 1 byte
void USART_printf(USART_TypeDef* USARTx, uint8_t *Data, ...);  //format output as printf in C standard library

//int fputc(int ch, FILE *f);

#ifdef __cplusplus
}
#endif 

#endif //__usart_H__


