#ifndef __flash_H__
#define __flash_H__

#ifdef __cplusplus
extern "C" {
#endif 

#include "stm32f10x.h"
#include "main_config.h"

//according to users' need to set these parameters
#define STM32_FLASH_SIZE 512 	 		//capacity of STM32 Flash (KB)
#define STM32_FLASH_WREN 1        // 1-->enable write  0-->disable write

//start address of FLASH
#define STM32_FLASH_BASE 0x08000000 	//start address of STM32 FLASH

u32 STMFLASH_ReadWord(u32 faddr);
void STMFLASH_Read_Buf(u32 ReadAddr, u16 *pBuffer, u16 NumToRead);
void STMFLASH_Write(u32 WriteAddr, u16 *pBuffer, u16 NumToWrite);

#ifdef __cplusplus
}
#endif 

#endif //__flash_H__


