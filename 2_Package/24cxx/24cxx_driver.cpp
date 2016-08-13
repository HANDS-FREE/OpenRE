/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
*
* FileName: 24cxx_driver.cpp
*
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
* Description:  对于不同的IIC芯片，操作延时不一样，并且有的不支持连续读取和写入，mpu6050可以连续操作
24cxx不支持连续写入和读取，所以BUF操作本质是字节操作的循环 ,每次读取或写入后至少隔离200us才能再次操作
字节写入时间间隔至少  1200us  ,字节读取正常,不需要时间间隔
每写入一个字节平均时间：  >1.5ms   主要是间隔延时,每读取一个字节的平均时间   50us   没有间隔延时
***********************************************************************************************************************/

#include "24cxx_test.h"

#if Hardware_Platform == 1    //STM32 F1xx

#include "stm32f10x.h"
#define RCC_I2C_SCL       RCC_APB2Periph_GPIOB
#define GPIO_I2C_SCL      GPIOB
#define I2C_Pin_SCL       GPIO_Pin_6
#define RCC_I2C_SDA       RCC_APB2Periph_GPIOB
#define GPIO_I2C_SDA      GPIOB
#define I2C_Pin_SDA       GPIO_Pin_7
#define SCL_H             GPIO_I2C_SCL->BSRR = I2C_Pin_SCL
#define SCL_L             GPIO_I2C_SCL->BRR  = I2C_Pin_SCL
#define SDA_H             GPIO_I2C_SDA->BSRR = I2C_Pin_SDA
#define SDA_L             GPIO_I2C_SDA->BRR  = I2C_Pin_SDA
#define SCL_read          GPIO_I2C_SCL->IDR  & I2C_Pin_SCL
#define SDA_read          GPIO_I2C_SDA->IDR  & I2C_Pin_SDA

#endif

#if Hardware_Platform == 4    //STM32 F4xx

#include "stm32f4xx.h"
#define RCC_I2C_SCL       RCC_AHB1Periph_GPIOB
#define GPIO_I2C_SCL      GPIOB
#define I2C_Pin_SCL       GPIO_Pin_6
#define RCC_I2C_SDA       RCC_AHB1Periph_GPIOB
#define GPIO_I2C_SDA      GPIOB
#define I2C_Pin_SDA       GPIO_Pin_7
#define SCL_H             GPIO_I2C_SCL->BSRRL = I2C_Pin_SCL
#define SCL_L             GPIO_I2C_SCL->BSRRH  = I2C_Pin_SCL
#define SDA_H             GPIO_I2C_SDA->BSRRL = I2C_Pin_SDA
#define SDA_L             GPIO_I2C_SDA->BSRRH  = I2C_Pin_SDA
#define SCL_read          GPIO_I2C_SCL->IDR  & I2C_Pin_SCL
#define SDA_read          GPIO_I2C_SDA->IDR  & I2C_Pin_SDA

#endif

#define AT24CXX_WriteByte_delay   delay_us(1500)    //每次写入一个字节,要delay后再写入下一个

static void I2C_delay(void)
{
#if Hardware_Platform == 1
    //   uint8_t i = 5;
    //   while(i--){};
#endif
#if Hardware_Platform == 4
      uint8_t i = 70;
      while(i--){};
#endif
}

static int I2C_Start(void)
{
    SDA_H;
    SCL_H;
    I2C_delay();
    if(!SDA_read)return 0;	//SDA线为低电平则总线忙,退出
    SDA_L;
    I2C_delay();
    if(SDA_read) return 0;	//SDA线为高电平则总线出错,退出
    SDA_L;
    I2C_delay();
    return 1;
}

static void I2C_Stop(void)
{
    SCL_L;
    I2C_delay();
    SDA_L;
    I2C_delay();
    SCL_H;
    I2C_delay();
    SDA_H;
    I2C_delay();
} 

static void I2C_Ack(void)
{	
    SCL_L;
    I2C_delay();
    SDA_L;
    I2C_delay();
    SCL_H;
    I2C_delay();
    SCL_L;
    I2C_delay();
}   

static void I2C_NoAck(void)
{	
    SCL_L;
    I2C_delay();
    SDA_H;
    I2C_delay();
    SCL_H;
    I2C_delay();
    SCL_L;
    I2C_delay();
} 

static int I2C_WaitAck(void) 	  //返回为:=1有ACK,=0无ACK
{
    SCL_L;
    I2C_delay();
    SDA_H;
    I2C_delay();
    SCL_H;
    I2C_delay();
    if(SDA_read)
    {
        SCL_L;
        I2C_delay();
        return 0;
    }
    SCL_L;
    I2C_delay();
    return 1;
}

static void I2C_SendByte(unsigned char SendByte)   //数据从高位到低位
{
    unsigned char i=8;
    while(i--)
    {
        SCL_L;
        I2C_delay();
        if(SendByte&0x80)
            SDA_H;
        else
            SDA_L;
        SendByte<<=1;
        I2C_delay();
        SCL_H;
        I2C_delay();
    }
    SCL_L;
}  

static unsigned char I2C_ReadByte(void)    //数据从高位到低位
{ 
    unsigned char i=8;
    unsigned char ReceiveByte=0;

    SDA_H;
    while(i--)
    {
        ReceiveByte<<=1;
        SCL_L;
        I2C_delay();
        SCL_H;
        I2C_delay();
        if(SDA_read)
        {
            ReceiveByte|=0x01;
        }
    }
    SCL_L;
    return ReceiveByte;
} 

/***********************************************************************************************************************
* Function:    void AT24CXX_WriteOneByte(unsigned short int REG_Address , unsigned char REG_data)
*
* Scope:        public
*
* Description:  write one byte to at24cxx
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
* by   mawenke   2015.10.1   creat
***********************************************************************************************************************/
void AT24CXX_WriteOneByte(unsigned short int REG_Address , unsigned char REG_data)
{				   	  	    																 
    I2C_Start();
    if(EE_TYPE>AT24C16)                //address
    {
        I2C_SendByte(0XA0);	             //send write command
        I2C_WaitAck();
        I2C_SendByte(REG_Address >>8);   //send high address
    }else
    {
        I2C_SendByte(0XA0+((REG_Address /256)<<1));   //send equipment address 0XA0 + write high address
    }
    I2C_WaitAck();
    I2C_SendByte(REG_Address %256);   //send low address
    I2C_WaitAck();
    I2C_SendByte(REG_data);           //send data
    I2C_WaitAck();
    I2C_Stop();
}

/***********************************************************************************************************************
* Function:     unsigned char AT24CXX_ReadOneByte(unsigned short int REG_Address)
*
* Scope:        public
*
* Description:  read one byte of at24cxx , return the data
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
* by   mawenke   2015.10.1   creat
***********************************************************************************************************************/
unsigned char AT24CXX_ReadOneByte(unsigned short int REG_Address)
{				  
    unsigned char REG_data;
    I2C_Start();
    if(EE_TYPE>AT24C16)
    {
        I2C_SendByte(0XA0);
        I2C_WaitAck();
        I2C_SendByte(REG_Address>>8);
        I2C_WaitAck();
    }else I2C_SendByte(0XA0+((REG_Address/256)<<1));

    I2C_WaitAck();
    I2C_SendByte(REG_Address%256);
    I2C_WaitAck();
    I2C_Start();
    I2C_SendByte(0XA1);
    I2C_WaitAck();
    REG_data=I2C_ReadByte();
    I2C_NoAck	();
    I2C_Stop();
    return REG_data;
}

/***********************************************************************************************************************
* Function:     void AT24CXX_Write_Buf(unsigned short int WriteAddr,unsigned char *pBuffer,unsigned short int NumToWrite)
*
* Scope:        public
*
* Description:  write one buf of at24cxx ,  24c02不支持连续操作
*
* Arguments:
* ReadAddr :the first read address
* pBuffer  :
* NumToRead:num to read
* Return:
*
* Cpu_Time:  
*
* History:
* by   mawenke   2015.10.1   creat
***********************************************************************************************************************/
void AT24CXX_Write_Buf(unsigned short int WriteAddr,unsigned char *pBuffer,unsigned short int NumToWrite)
{
    while(NumToWrite--)
    {     
        AT24CXX_WriteOneByte(WriteAddr,*pBuffer);			 
        WriteAddr++;
        pBuffer++;
		  	AT24CXX_WriteByte_delay;
    }
}

/***********************************************************************************************************************
* Function:     void AT24CXX_Read_Buf(unsigned short int ReadAddr,unsigned char *pBuffer,unsigned short int NumToRead)
*
* Scope:        public
*
* Description:  read one buf of at24cxx    24c02不支持连续操作
*
* Arguments:
* ReadAddr :the first read address
* pBuffer  :
* NumToRead:num to read
* Return:
*
* Cpu_Time:  
*
* History:
* by   mawenke   2015.10.1   creat
***********************************************************************************************************************/
void AT24CXX_Read_Buf(unsigned short int ReadAddr,unsigned char *pBuffer,unsigned short int NumToRead)
{
    /*  I2C_delay_us(200); */     //每次操作隔离200us，留给主机去做
	 unsigned short int read_i;
	 read_i=ReadAddr;
    while(NumToRead)
    {
       *pBuffer++=AT24CXX_ReadOneByte(read_i++);
       NumToRead--;
    }
}


/***********************************************************************************************************************
* Function:     void AT24CXX_Write_16data(unsigned short int WriteAddr,unsigned short int data)
*
* Scope:        public
*
* Description:  write a unsigned short int data of at24cxx
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
* by   mawenke   2015.10.1   creat
***********************************************************************************************************************/
void AT24CXX_Write_16data(unsigned short int WriteAddr,unsigned short int data)
{
    unsigned char temp1,temp2;
    temp1=(unsigned char)(data>>8);
    temp2=(unsigned char)(data&0x00ff);
    AT24CXX_WriteOneByte(WriteAddr,temp1);
    AT24CXX_WriteByte_delay;
    AT24CXX_WriteOneByte(WriteAddr+1,temp2);
}


/***********************************************************************************************************************
* Function:     unsigned short int AT24CXX_Read_16data(unsigned short int WriteAddr )
*
* Scope:        public
*
* Description:  read a unsigned short int data of at24cxx , return the data
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
* by   mawenke   2015.10.1   creat
***********************************************************************************************************************/
unsigned short int AT24CXX_Read_16data(unsigned short int WriteAddr )
{
    unsigned short int data;
    data= ( AT24CXX_ReadOneByte(WriteAddr) << 8 ) | AT24CXX_ReadOneByte(WriteAddr+1);
    return data;
}


/***********************************************************************************************************************
* Function:     static unsigned char AT24CXX_Check(void)
*
* Scope:        private
*
* Description:  check the at24cxx , return 0: error  return 1: right 
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
* by   mawenke   2015.10.1   creat
***********************************************************************************************************************/
static unsigned char AT24CXX_Check(void)
{
    unsigned char temp;
    AT24CXX_WriteOneByte(EE_TYPE,0x55);
    delay_ms(5);
    temp=AT24CXX_ReadOneByte(EE_TYPE);
    if(temp==0X55)return 1;
    else	return 0;
}

/***********************************************************************************************************************
* Function:     static unsigned char AT24CXX_Check(void)
*
* Scope:        private
*
* Description:  init the at24cxx , return 0: error  return 1: right 
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
* by   mawenke   2015.10.1   creat
***********************************************************************************************************************/
unsigned char AT24CXX_Init(void)
{

    GPIO_InitTypeDef  GPIO_InitStructure;

#if Hardware_Platform == 1

    RCC_APB2PeriphClockCmd( RCC_I2C_SCL|RCC_I2C_SDA , ENABLE );
    GPIO_InitStructure.GPIO_Pin =  I2C_Pin_SCL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  //开漏输出
    GPIO_Init(GPIO_I2C_SCL, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin =  I2C_Pin_SDA;
    GPIO_Init(GPIO_I2C_SDA, &GPIO_InitStructure);

#endif

#if Hardware_Platform == 4

    RCC_AHB1PeriphClockCmd( RCC_I2C_SCL|RCC_I2C_SDA , ENABLE );
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;  //开漏输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

    GPIO_InitStructure.GPIO_Pin =  I2C_Pin_SCL;
    GPIO_Init(GPIO_I2C_SCL, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin =  I2C_Pin_SDA;
    GPIO_Init(GPIO_I2C_SDA, &GPIO_InitStructure);

#endif

    return(AT24CXX_Check());
}


