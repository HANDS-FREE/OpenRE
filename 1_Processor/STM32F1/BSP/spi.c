/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: spi.c
* Contact:  QQ Exchange Group -- 521037187
* Version:  V2.0
*
* LICENSING TERMS:  
* The Hands Free is licensed generally under a permissive 3-clause BSD license. 
* Contributions are requiredto be made under the same license.
*
* History: 
* <author>    <time>      <version >       <desc>
* mawenke     2015.10.1   V1.0             creat
* LiuDong     2016.1.8    V1.57            update the name of function
*
* Description: 
*        STM32F1--------------
***********************************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif 

#include "spi.h"
#include "nvic.h"	 


#if BSP_CFG_SPI_EN > 0u 


#define GPIO_SPI1     GPIOA
#define RCC_SPI1      RCC_APB2Periph_GPIOA
#define SPI1_NSS      GPIO_Pin_4
#define SPI1_SCK      GPIO_Pin_5
#define SPI1_MISO     GPIO_Pin_6
#define SPI1_MOSI     GPIO_Pin_7

#define GPIO_SPI2     GPIOB
#define RCC_SPI2      RCC_APB2Periph_GPIOB
#define SPI2_NSS      GPIO_Pin_12
#define SPI2_SCK      GPIO_Pin_13
#define SPI2_MISO     GPIO_Pin_14
#define SPI2_MOSI     GPIO_Pin_15	 

/***********************************************************************************************************************
* Function:     HF_SPI_Init(SPI_TypeDef *SPIx , unsigned char GPIO_AF) 
*
* Scope:        public
*
* Description:  Initialize serial external interface of SPI, config SPI working on master mode
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
* by   mawenke    2015.12.1                           creat
* by   LiuDong    2016.1.8       V1.57       update the name of function
***********************************************************************************************************************/
void HF_SPI_Init(SPI_TypeDef *SPIx , unsigned char GPIO_AF)    //SPI interface initialization, input parameter SPI1 SPI2
{	 
    SPI_InitTypeDef  SPI_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;   	//initialize SPI structure
    
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //SPI设置为两线全双工
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		                    //config SPI working on master mode
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		                //SPI发送接收为8位数据帧结构
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;		                      //串行时钟在不操作时，时钟为低电平
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	                      //第一个时钟沿开始采集数据
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		                        //NSS有软件(使用SSI为)管理
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;  //SPI波特率预分频值为8
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	                //data start transmiss at MSB
    SPI_InitStructure.SPI_CRCPolynomial = 7;	                          //CRC值计算的多项式
    
    if(SPIx == SPI1)
    {
        RCC_APB2PeriphClockCmd(	RCC_APB2Periph_SPI1, ENABLE );
        if (GPIO_AF == 0 ){
            RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE );
            GPIO_InitStructure.GPIO_Pin = SPI1_MISO| SPI1_MOSI| SPI1_SCK;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //Multiplexing push-pull output
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(GPIO_SPI1, &GPIO_InitStructure);
            GPIO_SetBits(GPIO_SPI1,SPI1_MISO| SPI1_MOSI| SPI1_SCK);
        }
        else if(GPIO_AF == 1){
            RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOB, ENABLE );
            GPIO_PinRemapConfig(GPIO_Remap_SPI1 , ENABLE);		     //Pin Multiplexing to spi1
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //Multiplexing push-pull output
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(GPIO_SPI1, &GPIO_InitStructure);
            GPIO_SetBits(GPIO_SPI1,GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5);
        }
        SPI_Init(SPI1, &SPI_InitStructure);
        SPI_Cmd(SPI1, ENABLE);                          //enable spi
        HF_SPI_ReadWriteByte(SPI1,0xff);                //start transmission
        
    }
    else if(SPIx == SPI2)
    {
        RCC_APB1PeriphClockCmd(	RCC_APB1Periph_SPI2, ENABLE );
        if (GPIO_AF == 0 ){
            RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE );
            GPIO_InitStructure.GPIO_Pin = SPI2_MISO| SPI2_MOSI| SPI2_SCK;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //Multiplexing push-pull output
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(GPIO_SPI2, &GPIO_InitStructure);
            GPIO_SetBits(GPIO_SPI2,SPI2_MISO| SPI2_MOSI| SPI2_SCK);
        }
        else if(GPIO_AF == 1){
        }
        SPI_Init(SPI2, &SPI_InitStructure);
        SPI_Cmd(SPI2, ENABLE);
        HF_SPI_ReadWriteByte(SPI2,0xff);                                           //start transmission
        
    }
    
} 	 

/***********************************************************************************************************************
* Function:     unsigned char HF_SPI_ReadWriteByte(SPI_TypeDef *SPIx , unsigned char TxData)
*
* Scope:        public
*
* Description:  SPI w/r data function
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
unsigned char HF_SPI_ReadWriteByte(SPI_TypeDef *SPIx , unsigned char TxData)                    
{
    while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET);     //flag of send cache is not reset
    SPI_I2S_SendData(SPIx, TxData);                                     //send data
    while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET);    //flag of receivecache is not reset
    return SPI_I2S_ReceiveData(SPIx);                                   //receive data
}	

#endif  //#if BSP_CFG_SPI_EN > 0u 

#ifdef __cplusplus
}
#endif 

