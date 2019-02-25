/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* Contact:  QQ Exchange Group -- 521037187
*
* LICENSING TERMS:  
* The Hands Free is licensed generally under a permissive 3-clause BSD license. 
* Contributions are requiredto be made under the same license.
*
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
#include "delay.h"

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
***********************************************************************************************************************/
void HF_Hardware_I2C_Init(I2C_TypeDef *I2Cx , uint8_t GPIO_AF)
{
    
}	

/***********************************************************************************************************************
* Function:     void Hardware_I2C_Write_Byte(I2C_TypeDef *I2Cx ,
*               uint8_t Equipment_Address,uint8_t REG_Address,uint8_t REG_data)
*
* Scope:       
*
* Description:  single byte write
*               Equipment_Address IIC :equipment address   REG_Address :register write address
*               REG_data :write address
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
void HF_Hardware_I2C_Write_Byte(I2C_TypeDef *I2Cx , uint8_t Equipment_Address,uint8_t REG_Address,uint8_t REG_data)
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
***********************************************************************************************************************/

uint8_t HF_Hardware_I2C_Read_Byte(I2C_TypeDef *I2Cx , uint8_t Equipment_Address,uint8_t REG_Address)
{
    return 0;
}


/***********************************************************************************************************************
* Function:     int Hardware_I2C_Write_Buf(I2C_TypeDef *I2Cx , uint8_t Equipment_Address
*                                          ,uint8_t REG_Address,uint8_t *ptChar,uint8_t size)
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
***********************************************************************************************************************/
int HF_Hardware_I2C_Write_Buf(I2C_TypeDef *I2Cx , uint8_t Equipment_Address
                              ,uint8_t REG_Address,uint8_t *ptChar,uint8_t size)
{
    return 0;
}

/***********************************************************************************************************************
* Function:     int Hardware_I2C_Read_Buf(I2C_TypeDef *I2Cx , uint8_t Equipment_Address
*                                         ,uint8_t REG_Address,uint8_t * ptChar,uint8_t size)
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
***********************************************************************************************************************/
int HF_Hardware_I2C_Read_Buf(I2C_TypeDef *I2Cx , uint8_t Equipment_Address
                             ,uint8_t REG_Address,uint8_t * ptChar,uint8_t size)
{
    return 0;
}


/***********************************************************************************************************************
***                                                                                                                  ***
***                                                  Simulation IIC                                        ***
***                                                                                                                  ***
***********************************************************************************************************************/

I2C_Sensor_Type iic_sensor_type[3];

static void iic_delay_us(uint8_t HF_I2Cx , uint8_t t)
{
    if(iic_sensor_type[HF_I2Cx-1] == I2C_Sensor_Type_Typical_Fast) delay_us(t);
    else if (iic_sensor_type[HF_I2Cx-1] == I2C_Sensor_Type_Typical_Slow) delay_us(2*t);
    else if(iic_sensor_type[HF_I2Cx-1] == I2C_Sensor_Type_KS103) delay_us(t);
    else delay_us(t);
}

static void SDA_H(uint8_t HF_I2Cx)
{
    if(HF_I2Cx == 1){
        IIC1_SDA=1;
    }
    else if(HF_I2Cx == 2){
        IIC2_SDA=1;
    }
    else if(HF_I2Cx == 3){
        IIC3_SDA=1;
    }
}

static void SDA_L(uint8_t HF_I2Cx)
{
    if(HF_I2Cx == 1){
        IIC1_SDA=0;
    }
    else if(HF_I2Cx == 2){
        IIC2_SDA=0;
    }
    else if(HF_I2Cx == 3){
        IIC3_SDA=0;
    }
}

static void SCL_H(uint8_t HF_I2Cx)
{
    if(HF_I2Cx == 1){
        IIC1_SCL=1;
    }
    else if(HF_I2Cx == 2){
        IIC2_SCL=1;
    }
    else if(HF_I2Cx == 3){
        IIC3_SCL=1;
    }
}

static void SCL_L(uint8_t HF_I2Cx)
{
    if(HF_I2Cx == 1){
        IIC1_SCL=0;
    }
    else if(HF_I2Cx == 2){
        IIC2_SCL=0;
    }
    else if(HF_I2Cx == 3){
        IIC3_SCL=0;
    }
}

static uint8_t SDA_Read(uint8_t HF_I2Cx)
{
    if(HF_I2Cx == 1){
        return (uint8_t)IIC1_READ_SDA;
    }
    else if(HF_I2Cx == 2){
        return (uint8_t)IIC2_READ_SDA;
    }
    else if(HF_I2Cx == 3){
        return (uint8_t)IIC3_READ_SDA;
    }
    return 0;
}

static void SDA_IN(uint8_t HF_I2Cx)
{
    if(HF_I2Cx == 1){
        IIC1_SDA_IN();
    }
    else if(HF_I2Cx == 2){
        IIC2_SDA_IN();
    }
    else if(HF_I2Cx == 3){
        IIC3_SDA_IN();
    }
}

static void SDA_OUT(uint8_t HF_I2Cx)
{
    if(HF_I2Cx == 1){
        IIC1_SDA_OUT();
    }
    else if(HF_I2Cx == 2){
        IIC2_SDA_OUT();
    }
    else if(HF_I2Cx == 3){
        IIC3_SDA_OUT();
    }
}

/***********************************************************************************************************************
***                                                                                                                  ***
***                                                                                                                  ***
***                                                                                                                  ***
***********************************************************************************************************************/
static void I2C_Start(uint8_t HF_I2Cx)
{
    SDA_OUT(HF_I2Cx);
    SDA_H(HF_I2Cx);
    SCL_H(HF_I2Cx);
    iic_delay_us(HF_I2Cx , 4);
    SDA_L(HF_I2Cx);
    iic_delay_us(HF_I2Cx , 4);
    SDA_L(HF_I2Cx);
}

static void I2C_Stop(uint8_t HF_I2Cx)
{
    SDA_OUT(HF_I2Cx);
    SCL_L(HF_I2Cx);
    SDA_L(HF_I2Cx);
    iic_delay_us(HF_I2Cx , 4);
    SCL_H(HF_I2Cx);
    SDA_H(HF_I2Cx);
    iic_delay_us(HF_I2Cx , 4);
} 

static int I2C_WaitAck(uint8_t HF_I2Cx)
{

    uint8_t ucErrTime=0;
    SDA_IN(HF_I2Cx);
    SCL_H(HF_I2Cx);iic_delay_us(HF_I2Cx , 1);
    SDA_H(HF_I2Cx);iic_delay_us(HF_I2Cx , 1);

    while(SDA_Read(HF_I2Cx))
    {
        ucErrTime++;
        if(ucErrTime>250)
        {
            I2C_Stop(HF_I2Cx);
            return 0;
        }
    }

    SCL_L(HF_I2Cx);
    return 1;
}

static void I2C_Ack(uint8_t HF_I2Cx)
{	
    SCL_L(HF_I2Cx);
    SDA_OUT(HF_I2Cx);
    SDA_L(HF_I2Cx);
    iic_delay_us(HF_I2Cx , 2);
    SCL_H(HF_I2Cx);
    iic_delay_us(HF_I2Cx , 2);
    SCL_L(HF_I2Cx);
}   

static void I2C_NoAck(uint8_t HF_I2Cx)
{	
    SCL_L(HF_I2Cx);
    SDA_OUT(HF_I2Cx);
    SDA_H(HF_I2Cx);
    iic_delay_us(HF_I2Cx , 2);
    SCL_H(HF_I2Cx);
    iic_delay_us(HF_I2Cx , 2);
    SCL_L(HF_I2Cx);
} 

static void I2C_SendByte(uint8_t HF_I2Cx , uint8_t SendByte)
{
    uint8_t i=8;
    SDA_OUT(HF_I2Cx);
    SCL_L(HF_I2Cx);
    while(i--)
    {
        if(SendByte&0x80)
            SDA_H(HF_I2Cx);
        else
            SDA_L(HF_I2Cx);
        SendByte<<=1;

        iic_delay_us(HF_I2Cx , 2);
        SCL_H(HF_I2Cx);
        iic_delay_us(HF_I2Cx , 2);
        SCL_L(HF_I2Cx);
        iic_delay_us(HF_I2Cx , 2);
    }
}  

static uint8_t I2C_ReadByte(uint8_t HF_I2Cx , uint8_t ack)
{ 
    uint8_t i=8;
    uint8_t ReceiveByte=0;

    SDA_IN(HF_I2Cx);

    for(i=0;i<8;i++ )
    {
        SCL_L(HF_I2Cx);
        iic_delay_us(HF_I2Cx , 2);
        SCL_H(HF_I2Cx);

        ReceiveByte<<=1;
        if(SDA_Read(HF_I2Cx))ReceiveByte++;
        iic_delay_us(HF_I2Cx , 1);
    }
    if (!ack)
        I2C_NoAck(HF_I2Cx);
    else
        I2C_Ack(HF_I2Cx);

    return ReceiveByte;
} 

void HF_Simulat_I2C_Write_Byte(uint8_t HF_I2Cx , uint8_t Equipment_Address ,
                               uint8_t REG_Address , uint8_t REG_data)
{
    I2C_Start(HF_I2Cx);
    I2C_SendByte(HF_I2Cx , Equipment_Address);
    if(!I2C_WaitAck(HF_I2Cx)){I2C_Stop(HF_I2Cx); return ;}
    I2C_SendByte(HF_I2Cx , REG_Address);
    I2C_WaitAck(HF_I2Cx);
    I2C_SendByte(HF_I2Cx , REG_data);
    I2C_WaitAck(HF_I2Cx);
    I2C_Stop(HF_I2Cx);
}

uint8_t HF_Simulat_I2C_Read_Byte(uint8_t HF_I2Cx , uint8_t Equipment_Address
                                 , uint8_t REG_Address)
{   	
    uint8_t REG_data;
    I2C_Start(HF_I2Cx);
    I2C_SendByte(HF_I2Cx , Equipment_Address);
    if(!I2C_WaitAck(HF_I2Cx))
    {
        I2C_Stop(HF_I2Cx);
        return 0;
    }
    I2C_SendByte(HF_I2Cx , (uint8_t)REG_Address);
    I2C_WaitAck(HF_I2Cx);
    I2C_Start(HF_I2Cx);
    I2C_SendByte(HF_I2Cx , Equipment_Address+1);
    I2C_WaitAck(HF_I2Cx);
    if(iic_sensor_type[HF_I2Cx-1] == I2C_Sensor_Type_KS103) delay_us(70);
    REG_data = I2C_ReadByte(HF_I2Cx,0);
    I2C_Stop(HF_I2Cx);
    return REG_data;
}	

uint8_t HF_Simulat_I2C_Write_Buf(uint8_t HF_I2Cx , uint8_t Equipment_Address,uint8_t REG_Address,
                                 uint8_t *ptChar , uint8_t size)
{
    uint8_t i;
    if(size < 1)
        return 0;
    I2C_Start(HF_I2Cx);
    I2C_SendByte(HF_I2Cx , Equipment_Address);
    if(!I2C_WaitAck(HF_I2Cx))
    {
        I2C_Stop(HF_I2Cx);
        return 0;
    }
    I2C_SendByte(HF_I2Cx , REG_Address);
    I2C_WaitAck(HF_I2Cx);

    for(i=1;i<size; i++)
    {
        I2C_SendByte(HF_I2Cx , *ptChar++);
        I2C_Ack(HF_I2Cx);
    }
    I2C_SendByte(HF_I2Cx , *ptChar++);
    I2C_NoAck(HF_I2Cx);
    I2C_Stop(HF_I2Cx);
    return 1;
}	

uint8_t HF_Simulat_I2C_Read_Buf(uint8_t HF_I2Cx , uint8_t Equipment_Address,uint8_t REG_Address,
                                uint8_t * ptChar , uint8_t size)
{
    uint8_t i;
    if(size < 1)
        return 0;
    I2C_Start(HF_I2Cx);
    I2C_SendByte(HF_I2Cx , Equipment_Address);
    if(!I2C_WaitAck(HF_I2Cx))
    {
        I2C_Stop(HF_I2Cx);
        return 0;
    }
    I2C_SendByte(HF_I2Cx , REG_Address);
    I2C_WaitAck(HF_I2Cx);
    
    I2C_Start(HF_I2Cx);
    I2C_SendByte(HF_I2Cx , Equipment_Address+1);
    I2C_WaitAck(HF_I2Cx);
    for(i=1;i<size; i++)
    {
        *ptChar++ = I2C_ReadByte(HF_I2Cx,1);
    }
    *ptChar++ = I2C_ReadByte(HF_I2Cx,0);
    I2C_Stop(HF_I2Cx);
    return 1;
}	

void HF_Simulat_I2C_Init(uint8_t HF_I2Cx , I2C_Sensor_Type sensor_type)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    if(HF_I2Cx ==1 ){
        iic_sensor_type[0] = sensor_type;
        RCC_APB2PeriphClockCmd(RCC_I2C1_SCL|RCC_I2C1_SDA , ENABLE );
        GPIO_InitStructure.GPIO_Pin =  I2C1_PIN_SCL;
        GPIO_Init(GPIO_I2C1_SCL	, &GPIO_InitStructure);
        GPIO_InitStructure.GPIO_Pin =  I2C1_PIN_SDA;
        GPIO_Init(GPIO_I2C1_SDA	, &GPIO_InitStructure);
    }
    else if(HF_I2Cx ==2){
        iic_sensor_type[1] = sensor_type;
        RCC_APB2PeriphClockCmd(RCC_I2C2_SCL|RCC_I2C2_SDA , ENABLE );
        GPIO_InitStructure.GPIO_Pin =  I2C2_PIN_SCL;
        GPIO_Init(GPIO_I2C2_SCL	, &GPIO_InitStructure);
        GPIO_InitStructure.GPIO_Pin =  I2C2_PIN_SDA;
        GPIO_Init(GPIO_I2C2_SDA	, &GPIO_InitStructure);

    }
    else if(HF_I2Cx ==3){
        iic_sensor_type[2] = sensor_type;
        RCC_APB2PeriphClockCmd(RCC_I2C3_SCL|RCC_I2C3_SDA , ENABLE );
        GPIO_InitStructure.GPIO_Pin =  I2C3_PIN_SCL;
        GPIO_Init(GPIO_I2C3_SCL	, &GPIO_InitStructure);
        GPIO_InitStructure.GPIO_Pin =  I2C3_PIN_SDA;
        GPIO_Init(GPIO_I2C3_SDA	, &GPIO_InitStructure);
    }
    SCL_H(HF_I2Cx);
    SDA_H(HF_I2Cx);
}

#ifdef __cplusplus
}
#endif 

