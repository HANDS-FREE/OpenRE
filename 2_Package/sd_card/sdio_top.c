/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: sdio_top.c
* Contact:  QQ Exchange Group -- 521037187
* Version:  V2.0
*
* LICENSING TERMS:
* The Hands Free is licensed generally under a permissive 3-clause BSD license.
* Contributions are requiredto be made under the same license.
*
* History:
* <author>      <time>      <version>      <desc>
* mawenke      2015.10.1    V1.0          creat this file
*
* Description:
*
***********************************************************************************************************************/

#include "sdio_top.h"

#if SYSTEM_SUPPORT_SD_CARD >0u   //是否使能SD卡的代码   占用9k flash

SD_Error Status = SD_OK;

unsigned char SD_Card_Init(void)
{

    Status = SD_Init();

    if(Status == SD_OK)    //检测初始化是否成功
    {
        return 1 ;
    }
    else
    {
        return 0 ;
    }

}


/***********************************************************************************************************************
* Function:
*
* Scope:        pubic
*
* Description:  the follow code is a read\write test to sd card
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
* by   mawenke   2015.12.1   creat
***********************************************************************************************************************/
#if SYSTEM_SUPPORT_SD_CARD_TEST > 0u      //使能SD卡测试

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
/* Private define ------------------------------------------------------------*/
#define BLOCK_SIZE            512 /* Block Size in Bytes */
#define NUMBER_OF_BLOCKS      32  /* For Multi Blocks operation (Read/Write) */
#define MULTI_BUFFER_SIZE    (BLOCK_SIZE * NUMBER_OF_BLOCKS)   //buffer size

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
unsigned char Buffer_Block_Tx[BLOCK_SIZE], Buffer_Block_Rx[BLOCK_SIZE];
unsigned char readbuff[BLOCK_SIZE];
unsigned char Buffer_MultiBlock_Tx[MULTI_BUFFER_SIZE], Buffer_MultiBlock_Rx[MULTI_BUFFER_SIZE];
volatile TestStatus EraseStatus = FAILED, TransferStatus1 = FAILED, TransferStatus2 = FAILED;

//static void SD_EraseTest(void);
//static void SD_SingleBlockTest(void);
//static void SD_MultiBlockTest(void);
////fill data to buffer
//static void Fill_Buffer(unsigned char *pBuffer, uint32_t BufferLength, uint32_t Offset);
////比较两个缓冲区中的数据是否相等
//static TestStatus Buffercmp(unsigned char* pBuffer1, unsigned char* pBuffer2, uint32_t BufferLength);
////检查缓冲区的数据是否为0
//static TestStatus eBuffercmp(unsigned char* pBuffer, uint32_t BufferLength);

void SD_Card_Test(void)
{

    Status = SD_Init();

    printf( "\r\n this is a MicroSD card test(no file system).........\r\n " );

    if(Status == SD_OK)
    {
        printf( " \r\n SD_Init success \r\n " );
    }
    else
    {
        printf("\r\n SD_Init failed \r\n" );
        printf("\r\n return Status value is  %d \r\n",Status );
    }
    switch(SDCardInfo.CardType)
    {
    case SDIO_STD_CAPACITY_SD_CARD_V1_1:printf("Card Type:SDSC V1.1\r\n");break;
    case SDIO_STD_CAPACITY_SD_CARD_V2_0:printf("Card Type:SDSC V2.0\r\n");break;
    case SDIO_HIGH_CAPACITY_SD_CARD:printf("Card Type:SDHC V2.0\r\n");break;
    case SDIO_MULTIMEDIA_CARD:printf("Card Type:MMC Card\r\n");break;
    }
    printf( " \r\n CardType is : %d ", SDCardInfo.CardType );
    printf( " \r\n CardCapacity is : %d MB", (u32)(SDCardInfo.CardCapacity>>20) );
    printf( " \r\n CardBlockSize is : %d ", SDCardInfo.CardBlockSize );
    printf( " \r\n RCA is : %d ", SDCardInfo.RCA);
    printf( " \r\n ManufacturerID is : %d \r\n", SDCardInfo.SD_cid.ManufacturerID );

    //    SD_EraseTest();
    //    SD_SingleBlockTest();  //single block writeread test
    //    SD_MultiBlockTest();   //multi block writeread test
}

//static void SD_EraseTest(void)
//{
//    /*------------------- Block Erase ------------------------------------------*/
//    if (Status == SD_OK)
//    {
//        /* Erase NumberOfBlocks Blocks of WRITE_BL_LEN(512 Bytes) */
//        //the first parameter is Erase start address the second is end address
//        Status = SD_Erase(0x00, (BLOCK_SIZE * NUMBER_OF_BLOCKS));
//    }

//    if (Status == SD_OK)
//    {
//        //read erase area
//        Status = SD_ReadMultiBlocks(Buffer_MultiBlock_Rx, 0x00, BLOCK_SIZE, NUMBER_OF_BLOCKS);

//        /* Check if the Transfer is finished */
//        Status = SD_WaitReadOperation();  //check dma is end

//        /* Wait until end of DMA transfer */
//        while(SD_GetStatus() != SD_TRANSFER_OK);
//    }

//    /* Check the correctness of erased blocks */
//    if (Status == SD_OK)
//    {	//compare
//        EraseStatus = eBuffercmp(Buffer_MultiBlock_Rx, MULTI_BUFFER_SIZE);
//    }

//    if(EraseStatus == PASSED)
//        printf("\r\n erase test success ! \r\n" );

//    else
//        printf("\r\n erase test failed ! \r\n");

//}

//static void SD_SingleBlockTest(void)
//{
//    /*------------------- Block Read/Write --------------------------*/
//    /* Fill the buffer to send */
//    Fill_Buffer(Buffer_Block_Tx, BLOCK_SIZE, 0x320F);

//    if (Status == SD_OK)
//    {
//        /* Write block of 512 bytes on address 0 */
//        Status = SD_WriteBlock(Buffer_Block_Tx, 0x00, BLOCK_SIZE);
//        /* Check if the Transfer is finished */
//        Status = SD_WaitWriteOperation();	   //等待dma传输结束
//        while(SD_GetStatus() != SD_TRANSFER_OK); //等待sdio到sd卡传输结束
//    }

//    if (Status == SD_OK)
//    {
//        /* Read block of 512 bytes from address 0 */
//        Status = SD_ReadBlock(Buffer_Block_Rx, 0x00, BLOCK_SIZE);//读取数据
//        /* Check if the Transfer is finished */
//        Status = SD_WaitReadOperation();
//        while(SD_GetStatus() != SD_TRANSFER_OK);
//    }

//    /* Check the correctness of written data */
//    if (Status == SD_OK)
//    {
//        TransferStatus1 = Buffercmp(Buffer_Block_Tx, Buffer_Block_Rx, BLOCK_SIZE);	//比较
//    }

//    if(TransferStatus1 == PASSED)
//        printf("\r\n single block read\write test success ! \r\n");

//    else
//        printf("\r\n single block read\write test failed ! \r\n");
//}


//static void SD_MultiBlockTest(void)
//{
//    /*--------------- Multiple Block Read/Write ---------------------*/
//    /* Fill the buffer to send */
//    Fill_Buffer(Buffer_MultiBlock_Tx, MULTI_BUFFER_SIZE, 0x0);

//    if (Status == SD_OK)
//    {
//        /* Write multiple block of many bytes on address 0 */
//        Status = SD_WriteMultiBlocks(Buffer_MultiBlock_Tx, 0x00, BLOCK_SIZE, NUMBER_OF_BLOCKS);
//        /* Check if the Transfer is finished */
//        Status = SD_WaitWriteOperation();
//        while(SD_GetStatus() != SD_TRANSFER_OK);
//    }

//    if (Status == SD_OK)
//    {
//        /* Read block of many bytes from address 0 */
//        Status = SD_ReadMultiBlocks(Buffer_MultiBlock_Rx, 0x00, BLOCK_SIZE, NUMBER_OF_BLOCKS);
//        /* Check if the Transfer is finished */
//        Status = SD_WaitReadOperation();
//        while(SD_GetStatus() != SD_TRANSFER_OK);
//    }

//    /* Check the correctness of written data */
//    if (Status == SD_OK)
//    {
//        TransferStatus2 = Buffercmp(Buffer_MultiBlock_Tx, Buffer_MultiBlock_Rx, MULTI_BUFFER_SIZE);
//    }

//    if(TransferStatus2 == PASSED)
//        printf("\r\n multi block read\write test success ! \r\n");

//    else
//        printf("\r\n multi block read\write test failed ! \r\n");
//}

///*
// * 函数名：Fill_Buffer
// * 描述  ：在缓冲区中填写数据
// * 输入  ：-pBuffer 要填充的缓冲区
// *         -BufferLength 要填充的大小
// *         -Offset 填在缓冲区的第一个值
// * 输出  ：无
// */
//static void Fill_Buffer(unsigned char *pBuffer, uint32_t BufferLength, uint32_t Offset)
//{
//    uint16_t index = 0;

//    /* Put in global buffer same values */
//    for (index = 0; index < BufferLength; index++ )
//    {
//        pBuffer[index] = index + Offset;
//    }
//}

///*
// * 函数名：Buffercmp
// * 描述  ：比较两个缓冲区中的数据是否相等
// * 输入  ：-pBuffer1, -pBuffer2 : 要比较的缓冲区的指针
// *         -BufferLength 缓冲区长度
// * 输出  ：-PASSED 相等
// *         -FAILED 不等
// */
//static TestStatus Buffercmp(unsigned char* pBuffer1, unsigned char* pBuffer2, uint32_t BufferLength)
//{
//    while (BufferLength--)
//    {
//        if (*pBuffer1 != *pBuffer2)
//        {
//            return FAILED;
//        }

//        pBuffer1++;
//        pBuffer2++;
//    }

//    return PASSED;
//}


///*
// * 函数名：eBuffercmp
// * 描述  ：检查缓冲区的数据是否为0
// * 输入  ：-pBuffer 要比较的缓冲区
// *         -BufferLength 缓冲区长度
// * 输出  ：PASSED 缓冲区的数据全为0
// *         FAILED 缓冲区的数据至少有一个不为0
// */
//static TestStatus eBuffercmp(unsigned char* pBuffer, uint32_t BufferLength)
//{
//    while (BufferLength--)
//    {
//        /* In some SD Cards the erased state is 0xFF, in others it's 0x00 */
//        if ((*pBuffer != 0xFF) && (*pBuffer != 0x00))//擦除后是0xff或0x00
//        {
//            return FAILED;
//        }

//        pBuffer++;
//    }

//    return PASSED;
//}


#endif    //#if SYSTEM_SUPPORT_SD_CARD_TEST > 0u                //使能SD卡测试

#endif    // #if  SYSTEM_SUPPORT_SD_CARD >0u   




