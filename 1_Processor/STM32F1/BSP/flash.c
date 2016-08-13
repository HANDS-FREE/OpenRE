/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: flash.c
* Contact:  QQ Exchange Group -- 521037187
* Version:  V2.0
*
* LICENSING TERMS:  
* The Hands Free is licensed generally under a permissive 3-clause BSD license. 
* Contributions are requiredto be made under the same license.
*
* History: 
* <author>    <time>      <version >       <desc>
* LiuDong    2016.1.8     V1.57            update the name of function
*
* Description:
*        STM32F1--------------
*        no using Pin source
***********************************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif 

#include "flash.h"


#if BSP_CFG_FLASH_EN > 0u

/***********************************************************************************************************************
* Function:     static u16 STMFLASH_ReadHalfWord(u32 faddr)
*
* Scope:
*
* Description:  read half word data(16 bits) from assign address
*               faddr:address to read data (the value must be multiple of 2 )
*
* Arguments:
*
* Return:       the data
*
* Cpu_Time:
*
* History:
* by   mawenke    2015.12.1     creat
***********************************************************************************************************************/
u16 STMFLASH_ReadHalfWord(u32 faddr)
{
    return *(vu16*)faddr; 
}

u32 STMFLASH_ReadWord(u32 faddr)
{
    u32 data;
  	data = ( *(vu16*)faddr )<<16 | ( *(vu16*)(faddr+2));
    return data;	
}
/***********************************************************************************************************************
* Function:     void STMFLASH_Read_Buf(u32 ReadAddr,u16 *pBuffer,u16 NumToRead)
*
* Scope:
*
* Description:  read the wanted length data from assign address
*               ReadAddr:start address
*               pBuffer:data pointer
*               NumToWrite:half word(16Bits)
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
* by   mawenke    2015.12.1     creat
***********************************************************************************************************************/
void STMFLASH_Read_Buf(u32 ReadAddr,u16 *pBuffer,u16 NumToRead)   	
{
    u16 i;
    for(i=0;i<NumToRead;i++)
    {
        pBuffer[i]=STMFLASH_ReadHalfWord(ReadAddr);//read 2 bytes
        ReadAddr+=2; //Offset 2 bytes
    }
}

/***********************************************************************************************************************
* Function:     static void STMFLASH_Write_NoCheck(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)
*
* Scope:
*
* Description:  write data without check
*               WriteAddr:start address
*               pBuffer:data pointer
*               NumToWrite:half word(16Bits)
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
* by   mawenke    2015.12.1     creat
***********************************************************************************************************************/
static void STMFLASH_Write_NoCheck(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)   
{ 			 		 
    u16 i;
    for(i=0;i<NumToWrite;i++)
    {
        FLASH_ProgramHalfWord(WriteAddr,pBuffer[i]);
        WriteAddr+=2;//address add 2
    } 
} 


#if STM32_FLASH_SIZE<256
#define STM_SECTOR_SIZE 1024 //bytes
#else 
#define STM_SECTOR_SIZE	2048
#endif	

/***********************************************************************************************************************
* Function:     void STMFLASH_Write(u32 WriteAddr,u32 *pBuffer,u32 NumToWrite)
*
* Scope:
*
* Description:  write the wanted length data from assign address
*               WriteAddr:start address (the value must be multiple of 2 )
*               pBuffer:data pointer
*               NumToWrite:half word (16bits) (the number of 16bits)
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
* by   mawenke    2015.12.1     creat
***********************************************************************************************************************/
u16 STMFLASH_BUF[STM_SECTOR_SIZE/2];  //2K bytes most
void STMFLASH_Write(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)	
{
    u32 secpos;	   //Sector address
    u16 secoff;	   //Sector offset address (16bits)
    u16 secremain; //surplus address of sector 	 
    u16 i;    
    u32 offaddr;   //address after minus 0X08000000
    if(WriteAddr<STM32_FLASH_BASE||(WriteAddr>=(STM32_FLASH_BASE+1024*STM32_FLASH_SIZE)))return;//Illegal address
    FLASH_Unlock();						//unlock
    offaddr=WriteAddr-STM32_FLASH_BASE;		//actual offset address
    secpos=offaddr/STM_SECTOR_SIZE;			  //sector address 0~127 for STM32F103RBT6
    secoff=(offaddr%STM_SECTOR_SIZE)/2;		//offset in sector (must be multiple of 2)
    secremain=STM_SECTOR_SIZE/2-secoff;		//surplus space of sector
    if(NumToWrite<=secremain)secremain=NumToWrite;//below the value of sector
    while(1) 
    {	
        STMFLASH_Read_Buf(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE,STMFLASH_BUF,STM_SECTOR_SIZE/2);//read all data from sector
        for(i=0;i<secremain;i++)//check data
        {
            if(STMFLASH_BUF[secoff+i]!=0XFFFF)break;//need Erase  
        }
        if(i<secremain)//need Erase
        {
            FLASH_ErasePage(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE);//Erase this sector
            for(i=0;i<secremain;i++)//copy
            {
                STMFLASH_BUF[i+secoff]=pBuffer[i];	  
            }
            STMFLASH_Write_NoCheck(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE,STMFLASH_BUF,STM_SECTOR_SIZE/2);//write to all sector
        }else STMFLASH_Write_NoCheck(WriteAddr,pBuffer,secremain);//write to surplus sector				   
        if(NumToWrite==secremain)break;//end of writing
        else//not end writing
        {
            secpos++;				//sector address add 1
            secoff=0;				//the offset address is 0
            pBuffer+=secremain;  	//offset of pointer
            WriteAddr+=secremain;	//offset of write address
            NumToWrite-=secremain;	//number of bytes is Decreasing
            if(NumToWrite>(STM_SECTOR_SIZE/2))secremain=STM_SECTOR_SIZE/2;//next sector is not enough
            else secremain=NumToWrite;//next sector is enough
        }	 
    };	
    FLASH_Lock();//lock
}

#endif //#if BSP_CFG_FLASH_EN > 0u

#ifdef __cplusplus
}
#endif 
