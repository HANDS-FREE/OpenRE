#ifndef FLASH_H
#define FLASH_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "stm32f4xx.h"

//start address of FLASH
#define STM32_FLASH_BASE 0x08000000  //start address of STM32 FLASH

//FLASH start address of sector
#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000)  //start address of sector 0,  16 Kbytes
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000)  //start address of sector 1,  16 Kbytes
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000)  //start address of sector 2,  16 Kbytes
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000)  //start address of sector 3,  16 Kbytes
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000)  //start address of sector 4,  64 Kbytes
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000)  //start address of sector 5,  128 Kbytes
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000)  //start address of sector 6,  128 Kbytes
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000)  //start address of sector 7,  128 Kbytes
#define ADDR_FLASH_SECTOR_8     ((uint32_t)0x08080000)  //start address of sector 8,  128 Kbytes
#define ADDR_FLASH_SECTOR_9     ((uint32_t)0x080A0000)  //start address of sector 9,  128 Kbytes
#define ADDR_FLASH_SECTOR_10    ((uint32_t)0x080C0000)  //start address of sector 10, 128 Kbytes
#define ADDR_FLASH_SECTOR_11    ((uint32_t)0x080E0000)  //start address of sector 11, 128 Kbytes

uint32_t HF_Flash_ReadWord(uint32_t faddr);  //read word (16bits)
void HF_Flash_Write(uint32_t WriteAddr, uint32_t *pBuffer, uint32_t NumToWrite);  //write the wanted length data from assign address
void HF_Flash_Read(uint32_t ReadAddr, uint32_t *pBuffer, uint32_t NumToRead);  //read half word data(16 bits) from assign address

#ifdef __cplusplus
}
#endif 

#endif // #ifndef FLASH_H

