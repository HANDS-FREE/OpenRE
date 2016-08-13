#ifdef __cplusplus
extern "C" {
#endif 
	
#ifndef __hf_bootloader_H__
#define __hf_bootloader_H__

#include "main_config.h"
#include "bsplib.h"

//Initilaize the debug USART, First Parameter:USARTx
#define BootLoader_Usart_Init  	HF_Usart_Init(USART1 , 921600 ,0) 
	
#if Hardware_Platform==1
#define USART_REC_LEN  	    50*1024     //define Maximum bytes 50K
#define FLASH_APP1_ADDR		0x08010000
//the first app address,  keep 0X08000000~0X0800FFFF to Bootloader (all 64KB)
#endif

#if Hardware_Platform ==4
#define USART_REC_LEN  	    100*1024    //define Maximum bytes 100K
#define FLASH_APP1_ADDR		0x08010000
//the first app address, keep 0X08000000~0X0800FFFF to Bootloader (all 64KB)
#endif

extern unsigned int USART_RX_CNT; //the number of receive byte
extern unsigned char USART_RX_BUF[USART_REC_LEN] ;

void HF_BootLoader_Init(void);
void Boot_Loader_Call(void);
unsigned char Load_Flash_APP(unsigned int  Flash_APP_Adress);
#endif

#ifdef __cplusplus
}
#endif 
