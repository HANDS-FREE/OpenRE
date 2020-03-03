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
* mawenke       2015.10.1   V1.0           creat this file
*
* Description: 
*        STM32F4--------------
*        SPI1 --- PA5,6,7   SPI2 --- PB13,14,15
***********************************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif 

#include "spi.h"
#include "nvic.h"	 

/***********************************************************************************************************************
* Function:
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
***********************************************************************************************************************/
void HF_SPI_Init(uint8_t SPI_Channel ,  uint8_t GPIO_AF)
{	 
    SPI_TypeDef *SPIx;
    SPI_InitTypeDef  SPI_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; //Multiplexing
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;

    if(SPI_Channel == 1){
        SPIx=SPI1;
    }
    else if(SPI_Channel == 2){
        SPIx=SPI2;
    }
    else if(SPI_Channel == 3){
        SPIx=SPI3;
    }
    else{
        return;
    }

    if(SPIx == SPI1)
    {
        RCC_APB2PeriphClockCmd(	RCC_APB2Periph_SPI1, ENABLE );
        
        if(GPIO_AF == 0)
        {
            RCC_AHB1PeriphClockCmd(	RCC_AHB1Periph_GPIOA , ENABLE );
            GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
            GPIO_SetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
            GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
            GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
            GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);
        }
        else if(GPIO_AF == 1)
        {
            
        }
        //	RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1,ENABLE);//reset SPI1
        //	RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1,DISABLE);//stop reset SPI1
    }
    else if(SPIx == SPI2)
    {
        RCC_APB1PeriphClockCmd(	RCC_APB1Periph_SPI2, ENABLE );
        
        if(GPIO_AF == 0)
        {
            RCC_AHB1PeriphClockCmd(	RCC_AHB1Periph_GPIOB , ENABLE );
            GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
            GPIO_SetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
            GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_SPI2);
            GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_SPI2);
            GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_SPI2);
        }
        else if(GPIO_AF == 1)
        {
            
        }
        //	 RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI2,ENABLE);  //reset SPI2
        //	 RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI2,DISABLE); //stop reset SPI2
    }
    
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		    /******/
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPIx, &SPI_InitStructure);
    SPI_Cmd(SPIx, ENABLE);
    
    HF_SPI_ReadWriteByte(SPI_Channel , 0xff);   //start the transfer
} 	 

/***********************************************************************************************************************
* Function:
*
* Scope:        public
*
* Description:  SPI read write
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
uint8_t HF_SPI_ReadWriteByte(uint8_t SPI_Channel , uint8_t TxData)
{
    SPI_TypeDef *SPIx;

    if(SPI_Channel == 1){
        SPIx=SPI1;
    }
    else if(SPI_Channel == 2){
        SPIx=SPI2;
    }
    else if(SPI_Channel == 3){
        SPIx=SPI3;
    }
    else{
        return 0;
    }

    while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET);     //send buffer is empty
    SPI_I2S_SendData(SPIx, TxData);                                     //send a data
    while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET);
    return SPI_I2S_ReceiveData(SPIx);
}	

#ifdef __cplusplus
}
#endif 

