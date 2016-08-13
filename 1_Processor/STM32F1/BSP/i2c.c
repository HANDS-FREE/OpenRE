/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: i2c.c
* Contact:  QQ Exchange Group -- 521037187
* Version:  V2.0
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
*        IIC Driver Code
***********************************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif 

#include "i2c.h"
#include "nvic.h"

#if BSP_CFG_I2C_EN > 0u	 

/***********************************************************************************************************************
* Function:     void HF_Hardware_I2C_Init(I2C_TypeDef *I2Cx , uint8_t GPIO_AF) 
*
* Scope:  
*
* Description:  I2Cx Initialize
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
void HF_Hardware_I2C_Init(I2C_TypeDef *I2Cx , uint8_t GPIO_AF)
{
    
}	

/***********************************************************************************************************************
* Function:     void Hardware_I2C_Write_Byte(I2C_TypeDef *I2Cx , uint8_t Equipment_Address,uint8_t REG_Address,uint8_t REG_data) 
*
* Scope:       
*
* Description:  single byte write
*               Equipment_Address IIC :equipment address   REG_Address :register write address  REG_data :write address

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
void Hardware_I2C_Write_Byte(I2C_TypeDef *I2Cx , uint8_t Equipment_Address,uint8_t REG_Address,uint8_t REG_data)
{
    
}

/***********************************************************************************************************************
* Function:     uint8_t Hardware_I2C_Read_Byte(I2C_TypeDef *I2Cx , uint8_t Equipment_Address,
*               uint8_t REG_Address)
*
* Scope:
*
* Description:  single byte read
*               Equipment_Address IIC :equipment address   REG_Address :register read address 


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

uint8_t Hardware_I2C_Read_Byte(I2C_TypeDef *I2Cx , uint8_t Equipment_Address,uint8_t REG_Address)
{
    return 0;
}


/***********************************************************************************************************************
* Function:     int Hardware_I2C_Write_Buf(I2C_TypeDef *I2Cx , uint8_t Equipment_Address,uint8_t REG_Address,uint8_t *ptChar,uint8_t size) 
*
* Scope: 
*
* Description:  several byte write   24c02 not support contious write


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
int Hardware_I2C_Write_Buf(I2C_TypeDef *I2Cx , uint8_t Equipment_Address,uint8_t REG_Address,uint8_t *ptChar,uint8_t size)
{
    return 0;
}

/***********************************************************************************************************************
* Function:     int Hardware_I2C_Read_Buf(I2C_TypeDef *I2Cx , uint8_t Equipment_Address,uint8_t REG_Address,uint8_t * ptChar,uint8_t size)
*
* Scope: 
*
* Description:  several byte read   24c02 not support contious read


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
int Hardware_I2C_Read_Buf(I2C_TypeDef *I2Cx , uint8_t Equipment_Address,uint8_t REG_Address,uint8_t * ptChar,uint8_t size)
{
    return 0;
}

/***********************************************************************************************************************
***                                                                                                                  ***
***                                          HF_Simulation_IIC_INIT                                                  ***
***                                                                                                                  ***
************************************************************************************************************************/

static void I2C_delay(uint8_t I2C_FastMode)
{	
//   uint8_t i = 5;
//	 while(i--){};
}

static void SDA_H(uint8_t HF_I2Cx)
{
    if(HF_I2Cx == 1){
        SDA1_H;
    }
    else if(HF_I2Cx == 2){
        SDA2_H;
    }
    else if(HF_I2Cx == 3){
        SDA3_H;
    }
}

static void SDA_L(uint8_t HF_I2Cx)
{
    if(HF_I2Cx == 1){
        SDA1_L;
    }
    else if(HF_I2Cx == 2){
        SDA2_L;
    }
    else if(HF_I2Cx == 3){
        SDA3_L;
    }
}

static void SCL_H(uint8_t HF_I2Cx)
{
    if(HF_I2Cx == 1){
        SCL1_H;
    }
    else if(HF_I2Cx == 2){
        SCL2_H;
    }
    else if(HF_I2Cx == 3){
        SCL3_H;
    }
}

static void SCL_L(uint8_t HF_I2Cx)
{
    if(HF_I2Cx == 1){
        SCL1_L;
    }
    else if(HF_I2Cx == 2){
        SCL2_L;
    }
    else if(HF_I2Cx == 3){
        SCL3_L;
    }
}

static uint8_t SCL_Read(uint8_t HF_I2Cx)
{
    if(HF_I2Cx == 1){
        return (uint8_t)SCL1_Read;
    }
    else if(HF_I2Cx == 2){
        return (uint8_t)SCL2_Read;
    }
    else if(HF_I2Cx == 3){
        return (uint8_t)SCL3_Read;
    }
    return 0;
}

static uint8_t SDA_Read(uint8_t HF_I2Cx)
{
    if(HF_I2Cx == 1){
        return (uint8_t)SDA1_Read;
    }
    else if(HF_I2Cx == 2){
        return (uint8_t)SDA2_Read;
    }
    else if(HF_I2Cx == 3){
        return (uint8_t)SDA3_Read;
    }
    return 0;
}

/***********************************************************************************************************************
***                                                                                                                  ***
***                                                                                                                  ***
***                                                                                                                  ***
************************************************************************************************************************/
static int I2C_Start(uint8_t HF_I2Cx , uint8_t I2C_FastMode)
{
    SDA_H(HF_I2Cx);
    SCL_H(HF_I2Cx);
    I2C_delay(I2C_FastMode);
    if(!SDA_Read(HF_I2Cx))return 0;
    SDA_L(HF_I2Cx);
    I2C_delay(I2C_FastMode);
    if(SDA_Read(HF_I2Cx)) return 0;
    SDA_L(HF_I2Cx);
    I2C_delay(I2C_FastMode);
    return 1;
}

static void I2C_Stop(uint8_t HF_I2Cx , uint8_t I2C_FastMode)
{
    SCL_L(HF_I2Cx);
    I2C_delay(I2C_FastMode);
    SDA_L(HF_I2Cx);
    I2C_delay(I2C_FastMode);
    SCL_H(HF_I2Cx);
    I2C_delay(I2C_FastMode);
    SDA_H(HF_I2Cx);
    I2C_delay(I2C_FastMode);
} 

static void I2C_Ack(uint8_t HF_I2Cx , uint8_t I2C_FastMode)
{	
    SCL_L(HF_I2Cx);
    I2C_delay(I2C_FastMode);
    SDA_L(HF_I2Cx);
    I2C_delay(I2C_FastMode);
    SCL_H(HF_I2Cx);
    I2C_delay(I2C_FastMode);
    SCL_L(HF_I2Cx);
    I2C_delay(I2C_FastMode);
}   

static void I2C_NoAck(uint8_t HF_I2Cx , uint8_t I2C_FastMode)
{	
    SCL_L(HF_I2Cx);
    I2C_delay(I2C_FastMode);
    SDA_H(HF_I2Cx);
    I2C_delay(I2C_FastMode);
    SCL_H(HF_I2Cx);
    I2C_delay(I2C_FastMode);
    SCL_L(HF_I2Cx);
    I2C_delay(I2C_FastMode);
} 

static int I2C_WaitAck(uint8_t HF_I2Cx , uint8_t I2C_FastMode) 	
{
    SCL_L(HF_I2Cx);
    I2C_delay(I2C_FastMode);
    SDA_H(HF_I2Cx);
    I2C_delay(I2C_FastMode);
    SCL_H(HF_I2Cx);
    I2C_delay(I2C_FastMode);
    if(SDA_Read(HF_I2Cx))
    {
        SCL_L(HF_I2Cx);
        I2C_delay(I2C_FastMode);
        return 0;
    }
    SCL_L(HF_I2Cx);
    I2C_delay(I2C_FastMode);
    return 1;
}

static void I2C_SendByte(uint8_t HF_I2Cx , uint8_t SendByte, uint8_t I2C_FastMode) 
{
    uint8_t i=8;
    while(i--)
    {
        SCL_L(HF_I2Cx);
        I2C_delay(I2C_FastMode);
        if(SendByte&0x80)
            SDA_H(HF_I2Cx);
        else
            SDA_L(HF_I2Cx);
        SendByte<<=1;
        I2C_delay(I2C_FastMode);
        SCL_H(HF_I2Cx);
        I2C_delay(I2C_FastMode);
    }
    SCL_L(HF_I2Cx);
}  


static uint8_t I2C_ReadByte(uint8_t HF_I2Cx , uint8_t I2C_FastMode)  
{ 
    uint8_t i=8;
    uint8_t ReceiveByte=0;
    SDA_H(HF_I2Cx);
    while(i--)
    {
        ReceiveByte<<=1;
        SCL_L(HF_I2Cx);
        I2C_delay(I2C_FastMode);
        SCL_H(HF_I2Cx);
        I2C_delay(I2C_FastMode);
        if(SDA_Read(HF_I2Cx))
        {
            ReceiveByte|=0x01;
        }
    }
    SCL_L(HF_I2Cx);
    return ReceiveByte;
} 

void Simulat_I2C_Write_Byte(uint8_t HF_I2Cx , uint8_t Equipment_Address , 
                            uint8_t REG_Address , uint8_t REG_data , uint8_t I2C_FastMode)
{
    if(!I2C_Start(HF_I2Cx , I2C_FastMode))return ;
    I2C_SendByte(HF_I2Cx , Equipment_Address,I2C_FastMode);
    if(!I2C_WaitAck(HF_I2Cx , I2C_FastMode)){I2C_Stop(HF_I2Cx , I2C_FastMode); return ;}
    I2C_SendByte(HF_I2Cx , REG_Address,I2C_FastMode);
    I2C_WaitAck(HF_I2Cx , I2C_FastMode);
    I2C_SendByte(HF_I2Cx , REG_data , I2C_FastMode);
    I2C_WaitAck(HF_I2Cx , I2C_FastMode);
    I2C_Stop(HF_I2Cx , I2C_FastMode);
}

uint8_t Simulat_I2C_Read_Byte(uint8_t HF_I2Cx , uint8_t Equipment_Address , uint8_t REG_Address , uint8_t I2C_FastMode)  
{   	
    uint8_t REG_data;
    if(!I2C_Start(HF_I2Cx , I2C_FastMode))return 0;
    I2C_SendByte(HF_I2Cx , Equipment_Address , I2C_FastMode);
    if(!I2C_WaitAck(HF_I2Cx , I2C_FastMode))
    {
        I2C_Stop(HF_I2Cx , I2C_FastMode);
        return 0;
    }
    I2C_SendByte(HF_I2Cx , (uint8_t)REG_Address , I2C_FastMode);
    I2C_WaitAck(HF_I2Cx , I2C_FastMode);
    I2C_Start(HF_I2Cx , I2C_FastMode);
    I2C_SendByte(HF_I2Cx , Equipment_Address+1 , I2C_FastMode);
    I2C_WaitAck(HF_I2Cx , I2C_FastMode);
    REG_data = I2C_ReadByte(HF_I2Cx , I2C_FastMode);
    I2C_NoAck(HF_I2Cx , I2C_FastMode);
    I2C_Stop(HF_I2Cx , I2C_FastMode);
    return REG_data;
}	

int Simulat_I2C_Write_Buf(uint8_t HF_I2Cx , uint8_t Equipment_Address,uint8_t REG_Address,
                          uint8_t *ptChar , uint8_t size , uint8_t I2C_FastMode)
{
    uint8_t i;
    if(size < 1)
        return 0;
    if(!I2C_Start(HF_I2Cx , I2C_FastMode))
        return 0;
    I2C_SendByte(HF_I2Cx , Equipment_Address,I2C_FastMode);
    if(!I2C_WaitAck(HF_I2Cx , I2C_FastMode))
    {
        I2C_Stop(HF_I2Cx , I2C_FastMode);
        return 0;
    }
    I2C_SendByte(HF_I2Cx , REG_Address,I2C_FastMode);
    I2C_WaitAck(HF_I2Cx , I2C_FastMode);

    for(i=1;i<size; i++)
    {
        I2C_SendByte(HF_I2Cx , *ptChar++,I2C_FastMode);
        I2C_Ack(HF_I2Cx , I2C_FastMode);
    }
    I2C_SendByte(HF_I2Cx , *ptChar++,I2C_FastMode);
    I2C_NoAck(HF_I2Cx , I2C_FastMode);
    I2C_Stop(HF_I2Cx , I2C_FastMode);
    return 1;
}	

int Simulat_I2C_Read_Buf(uint8_t HF_I2Cx , uint8_t Equipment_Address,uint8_t REG_Address,
                         uint8_t * ptChar , uint8_t size , uint8_t I2C_FastMode)
{
    uint8_t i;
    if(size < 1)
        return 0;
    if(!I2C_Start(HF_I2Cx , I2C_FastMode))
        return 0;
    I2C_SendByte(HF_I2Cx , Equipment_Address,I2C_FastMode);
    if(!I2C_WaitAck(HF_I2Cx , I2C_FastMode))
    {
        I2C_Stop(HF_I2Cx , I2C_FastMode);
        return 0;
    }
    I2C_SendByte(HF_I2Cx , REG_Address,I2C_FastMode);
    I2C_WaitAck(HF_I2Cx , I2C_FastMode);
    
    I2C_Start(HF_I2Cx , I2C_FastMode);
    I2C_SendByte(HF_I2Cx , Equipment_Address+1,I2C_FastMode);
    I2C_WaitAck(HF_I2Cx , I2C_FastMode);
    for(i=1;i<size; i++)
    {
        *ptChar++ = I2C_ReadByte(HF_I2Cx , I2C_FastMode);
        I2C_Ack(HF_I2Cx , I2C_FastMode);
    }
    *ptChar++ = I2C_ReadByte(HF_I2Cx , I2C_FastMode);
    I2C_NoAck(HF_I2Cx , I2C_FastMode);
    I2C_Stop(HF_I2Cx , I2C_FastMode);
    return 1;
}	

void HF_Simulat_I2C_Init(uint8_t HF_I2Cx)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; 
    if(HF_I2Cx ==1 ){
        RCC_APB2PeriphClockCmd(RCC_I2C1_SCL|RCC_I2C1_SDA , ENABLE );
        GPIO_InitStructure.GPIO_Pin =  I2C1_Pin_SCL;
        GPIO_Init(GPIO_I2C1_SCL	, &GPIO_InitStructure);
        GPIO_InitStructure.GPIO_Pin =  I2C1_Pin_SDA;
        GPIO_Init(GPIO_I2C1_SDA	, &GPIO_InitStructure);
    }
    else if(HF_I2Cx ==2){
        RCC_APB2PeriphClockCmd(RCC_I2C2_SCL|RCC_I2C2_SDA , ENABLE );
        GPIO_InitStructure.GPIO_Pin =  I2C2_Pin_SCL;
        GPIO_Init(GPIO_I2C2_SCL	, &GPIO_InitStructure);
        GPIO_InitStructure.GPIO_Pin =  I2C2_Pin_SDA;
        GPIO_Init(GPIO_I2C2_SDA	, &GPIO_InitStructure);

    }
    else if(HF_I2Cx ==3){
        RCC_APB2PeriphClockCmd(RCC_I2C3_SCL|RCC_I2C3_SDA , ENABLE );
        GPIO_InitStructure.GPIO_Pin =  I2C3_Pin_SCL;
        GPIO_Init(GPIO_I2C3_SCL	, &GPIO_InitStructure);
        GPIO_InitStructure.GPIO_Pin =  I2C3_Pin_SDA;
        GPIO_Init(GPIO_I2C3_SDA	, &GPIO_InitStructure);
    }

}

#endif    //#if BSP_CFG_I2C_EN > 0u	 

#ifdef __cplusplus
}
#endif 

