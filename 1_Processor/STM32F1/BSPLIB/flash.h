#ifndef FLASH_H
#define FLASH_H
#ifdef __cplusplus
extern "C" {
#endif 

#include "stm32f10x.h"

//according to users' need to set these parameters
#define STM32_FLASH_SIZE 512 	 		//capacity of STM32 Flash (KB)
#define STM32_FLASH_WREN 1        // 1-->enable write  0-->disable write

//start address of FLASH
#define STM32_FLASH_BASE 0x08000000 	//start address of STM32 FLASH, and this is where the codes are saved.
#define FLASH_SAVE_ADDR 0X08070000 // make sure the data will be saved without covering the codes.
u32 STMFLASH_ReadWord(u32 faddr);
void HF_Flash_Read(u32 ReadAddr, u16 *pBuffer, u16 NumToRead);
void HF_Flash_Write(u32 WriteAddr, u16 *pBuffer, u16 NumToWrite);

#ifdef __cplusplus
}
#endif 

#endif // #ifndef FLASH_H


