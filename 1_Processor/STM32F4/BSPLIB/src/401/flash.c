/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* Contact:  QQ Exchange Group -- 521037187
*
* LICENSING TERMS:
* The Hands Free is licensed generally under a permissive 3-clause BSD license.
* Contributions are requiredto be made under the same license.
*
* History: 
* <author>      <time>      <version>      <desc>
*
* Description:
*       STM32F4--------------
*       no using Pin source
***********************************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif 

#include "flash.h"

/***********************************************************************************************************************
* Function:     uint32_t HF_Flash_ReadWord(uint32_t faddr)
*
* Scope: 
*
* Description:  read half word data(16 bits) from assign address
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
uint32_t HF_Flash_ReadWord(uint32_t faddr)
{
   return *(vu32*)faddr;
}  

/***********************************************************************************************************************
* Function:     uint16_t HF_Flash_GetFlashSector(uint32_t addr)
*
* Scope:   
*
* Description:  get flash sector of address
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
uint16_t HF_Flash_GetFlashSector(uint32_t addr)
{
    if(addr<ADDR_FLASH_SECTOR_1)return FLASH_Sector_0;
    else if(addr<ADDR_FLASH_SECTOR_2)return FLASH_Sector_1;
    else if(addr<ADDR_FLASH_SECTOR_3)return FLASH_Sector_2;
    else if(addr<ADDR_FLASH_SECTOR_4)return FLASH_Sector_3;
    else if(addr<ADDR_FLASH_SECTOR_5)return FLASH_Sector_4;
    else if(addr<ADDR_FLASH_SECTOR_6)return FLASH_Sector_5;
    else if(addr<ADDR_FLASH_SECTOR_7)return FLASH_Sector_6;
    else if(addr<ADDR_FLASH_SECTOR_8)return FLASH_Sector_7;
    else if(addr<ADDR_FLASH_SECTOR_9)return FLASH_Sector_8;
    else if(addr<ADDR_FLASH_SECTOR_10)return FLASH_Sector_9;
    else if(addr<ADDR_FLASH_SECTOR_11)return FLASH_Sector_10;
    return FLASH_Sector_11;
}

/***********************************************************************************************************************
* Function:     void HF_Flash_Write(uint32_t WriteAddr,uint32_t *pBuffer,uint32_t NumToWrite)
*
* Scope: 
*
* Description:  write the wanted length data from assign address
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
void HF_Flash_Write(uint32_t WriteAddr,uint32_t *pBuffer,uint32_t NumToWrite)
{ 
    FLASH_Status status = FLASH_COMPLETE;
    uint32_t addrx=0;
    uint32_t endaddr=0;
    if(WriteAddr<STM32_FLASH_BASE||WriteAddr%4)return; //Illegal address
    FLASH_Unlock();             //unlock
    FLASH_DataCacheCmd(DISABLE);//must disable data cache while FLASH erasing
    
    addrx=WriteAddr;        //start address to write
    endaddr=WriteAddr+NumToWrite*4;	//end address to write
    if(addrx<0X1FFF0000)    //only master store area need be erased
    {
        while(addrx<endaddr)  //erase all
        {
            if(HF_Flash_ReadWord(addrx)!=0XFFFFFFFF)//if not is 0XFFFFFFFF, need to be erased
            {
                status=FLASH_EraseSector(HF_Flash_GetFlashSector(addrx),VoltageRange_3);//VCC=2.7~3.6V之间!!
                if(status!=FLASH_COMPLETE)break;	//have error
            }else addrx+=4;
        }
    }
    if(status==FLASH_COMPLETE)
    {
        while(WriteAddr<endaddr)//write data
        {
            if(FLASH_ProgramWord(WriteAddr,*pBuffer)!=FLASH_COMPLETE)//writing data
            {
                break;          //error to writing
            }
            WriteAddr+=4;
            pBuffer++;
        }
    }
    FLASH_DataCacheCmd(ENABLE); //finish FLASH eraseing, enable data cache
    FLASH_Lock(); //lock
} 

/***********************************************************************************************************************
* Function:     void HF_Flash_Read(uint32_t ReadAddr,uint32_t *pBuffer,uint32_t NumToRead)
*
* Scope:   
*
* Description:  read the wanted length data from assign address
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
void HF_Flash_Read(uint32_t ReadAddr,uint32_t *pBuffer,uint32_t NumToRead)
{
    uint32_t i;
    for(i=0;i<NumToRead;i++)
    {
        pBuffer[i]=HF_Flash_ReadWord(ReadAddr);//read 4 bytes
        ReadAddr+=4;//offset 4 bytes
    }
}

#ifdef __cplusplus
}
#endif 
