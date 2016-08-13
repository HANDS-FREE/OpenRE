/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
*
* FileName: nrf24l01_driver.cpp
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
* Description:  本文件封装了24l01 2.4G射频通信模块   可用于双节点模拟全双工通信
***********************************************************************************************************************/

#include "nrf24l01_driver.h"

#if SYSTEM_SUPPORT_NRF > 0u  

#if Hardware_Platform == 1    //STM32 F1xx

/**************定义NRF使用的SPI接口******************/
#define NRF_SPI      SPI1     

/***************NRF_PWR GPIO******************/
#define RCC_NRF_PWR           RCC_APB2Periph_GPIOE
#define GPIO_NRF_PWR          GPIOE
#define GPIO_NRF_PWR_Pin      GPIO_Pin_4

#define RCC_NRF_CSN        RCC_APB2Periph_GPIOE
#define GPIO_NRF_CSN       GPIOE 
#define GPIO_NRF_CSN_Pin   GPIO_Pin_6

#define RCC_NRF_CE         RCC_APB2Periph_GPIOE
#define GPIO_NRF_CE        GPIOE
#define GPIO_NRF_CE_Pin    GPIO_Pin_5

//#define RCC_NRF24L01_IRQ   RCC_APB2Periph_GPIOC
//#define GPIO_NRF_IRQ       GPIOC
//#define GPIO_NRF_IRQ_Pin   GPIO_Pin_5

//#define CSN_H        GPIO_NRF_CSN->BSRR = RCC_NRF_CSN
//#define CSN_L        GPIO_NRF_CSN->BRR  = RCC_NRF_CSN
//#define CE_H         RCC_NRF_CE->BSRR   = GPIO_NRF_CE
//#define CE_L         RCC_NRF_CE->BRR    = GPIO_NRF_CE

#define CSN_H       GPIO_SetBits(GPIO_NRF_CSN , GPIO_NRF_CSN_Pin) 
#define CSN_L       GPIO_ResetBits(GPIO_NRF_CSN , GPIO_NRF_CSN_Pin)
#define CE_H        GPIO_SetBits(GPIO_NRF_CE , GPIO_NRF_CE_Pin) 
#define CE_L        GPIO_ResetBits(GPIO_NRF_CE , GPIO_NRF_CE_Pin)

#endif

#if Hardware_Platform == 4    //STM32 F4xx

/**************定义NRF使用的SPI接口******************/
#define NRF_SPI      SPI1    

/***************NRF_PWR GPIO******************/
#define RCC_NRF_PWR           RCC_AHB1Periph_GPIOE
#define GPIO_NRF_PWR          GPIOE
#define GPIO_NRF_PWR_Pin      GPIO_Pin_8

#define RCC_NRF_CSN        RCC_AHB1Periph_GPIOC
#define GPIO_NRF_CSN       GPIOC 
#define GPIO_NRF_CSN_Pin   GPIO_Pin_4

#define RCC_NRF_CE         RCC_AHB1Periph_GPIOC
#define GPIO_NRF_CE        GPIOC
#define GPIO_NRF_CE_Pin    GPIO_Pin_5

//#define RCC_NRF24L01_IRQ   RCC_AHB1Periph_GPIOC
//#define GPIO_NRF_IRQ       GPIOC
//#define GPIO_NRF_IRQ_Pin   GPIO_Pin_5

//#define CSN_H        GPIO_NRF_CSN->BSRRL = GPIO_NRF_CSN_Pin
//#define CSN_L        GPIO_NRF_CSN->BSRRH = GPIO_NRF_CSN_Pin
//#define CE_H         GPIO_NRF_CE->BSRRL  = GPIO_NRF_CE_Pin
//#define CE_L         GPIO_NRF_CE->BSRRH  = GPIO_NRF_CE_Pin

#define CSN_H       GPIO_SetBits(GPIO_NRF_CSN , GPIO_NRF_CSN_Pin) 
#define CSN_L       GPIO_ResetBits(GPIO_NRF_CSN , GPIO_NRF_CSN_Pin)
#define CE_H        GPIO_SetBits(GPIO_NRF_CE , GPIO_NRF_CE_Pin) 
#define CE_L        GPIO_ResetBits(GPIO_NRF_CE , GPIO_NRF_CE_Pin)

#endif

unsigned char	TX_ADDRESS[TX_ADR_WIDTH] = {0xAA,0xBB,0xCC,0x00,0x01};	//本地地址
unsigned char	RX_ADDRESS[RX_ADR_WIDTH] = {0xAA,0xBB,0xCC,0x00,0x01};	//接收地址	

//***************************************NRF24L01寄存器指令*******************************************************
#define NRF_READ_REG    0x00  	// 读寄存器指令
#define NRF_WRITE_REG   0x20   	// 写寄存器指令
#define R_RX_PL_WID   	0x60
#define RD_RX_PLOAD     0x61  	// 读取接收数据指令
#define WR_TX_PLOAD     0xA0  	// 写待发数据指令
#define FLUSH_TX        0xE1 	// 冲洗发送 FIFO指令
#define FLUSH_RX        0xE2  	// 冲洗接收 FIFO指令
#define REUSE_TX_PL     0xE3  	// 定义重复装载数据指令
#define NOP             0xFF  	// 保留
//*************************************SPI(nRF24L01)寄存器地址****************************************************
#define CONFIG          0x00  // 配置收发状态，CRC校验模式以及收发状态响应方式
#define EN_AA           0x01  // 自动应答功能设置
#define EN_RXADDR       0x02  // 可用信道设置
#define SETUP_AW        0x03  // 收发地址宽度设置
#define SETUP_RETR      0x04  // 自动重发功能设置
#define RF_CH           0x05  // 工作频率设置
#define RF_SETUP        0x06  // 发射速率、功耗功能设置
#define NRFRegSTATUS    0x07  // 状态寄存器
#define OBSERVE_TX      0x08  // 发送监测功能
#define CD              0x09  // 地址检测           
#define RX_ADDR_P0      0x0A  // 频道0接收数据地址
#define RX_ADDR_P1      0x0B  // 频道1接收数据地址
#define RX_ADDR_P2      0x0C  // 频道2接收数据地址
#define RX_ADDR_P3      0x0D  // 频道3接收数据地址
#define RX_ADDR_P4      0x0E  // 频道4接收数据地址
#define RX_ADDR_P5      0x0F  // 频道5接收数据地址
#define TX_ADDR         0x10  // 发送地址寄存器
#define RX_PW_P0        0x11  // 接收频道0接收数据长度
#define RX_PW_P1        0x12  // 接收频道1接收数据长度
#define RX_PW_P2        0x13  // 接收频道2接收数据长度
#define RX_PW_P3        0x14  // 接收频道3接收数据长度
#define RX_PW_P4        0x15  // 接收频道4接收数据长度
#define RX_PW_P5        0x16  // 接收频道5接收数据长度
#define FIFO_STATUS     0x17  // FIFO栈入栈出状态寄存器设置

#define RX_DR           6    //中断标志
#define TX_DS           5
#define MAX_RT          4


NRF24L01 nrf24L01;

/***********************************************************************************************************************
***                                                                                                                  ***
***                                           bottom port Function below                                             ***
***                                                                                                                  ***
***********************************************************************************************************************/
NRF24L01::NRF24L01(void)
{

}

void NRF24L01::NRF_delay_ms(unsigned char t)
{
    delay_ms(t);
}

unsigned char NRF24L01::NRF_RW(unsigned char Data)
{
    return( HF_SPI_ReadWriteByte(NRF_SPI , Data) );
}

/***********************************************************************************************************************
* Function:     void NRF24L01::NRF_PWR_Enable(void)
*
* Scope:        private
*
* Description:  nrf power on
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
void NRF24L01::NRF_PWR_Enable(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  //普通输出模式
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;   //上拉
    RCC_AHB1PeriphClockCmd(RCC_NRF_PWR , ENABLE );
    GPIO_InitStructure.GPIO_Pin = GPIO_NRF_PWR_Pin ;
    GPIO_Init(GPIO_NRF_PWR , &GPIO_InitStructure);

    GPIO_SetBits(GPIO_NRF_PWR , GPIO_NRF_PWR_Pin );
    NRF_delay_ms(50);
}

/***********************************************************************************************************************
* Function:     void NRF24L01::NRF_PWR_Enable(void)
*
* Scope:        private
*
* Description:  nrf power off
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
void NRF24L01::NRF_PWR_Disable(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  //普通输出模式
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;   //上拉
    RCC_AHB1PeriphClockCmd(RCC_NRF_PWR , ENABLE );
    GPIO_InitStructure.GPIO_Pin = GPIO_NRF_PWR_Pin ;
    GPIO_Init(GPIO_NRF_PWR , &GPIO_InitStructure);

    GPIO_ResetBits(GPIO_NRF_PWR , GPIO_NRF_PWR_Pin );
    NRF_delay_ms(50);
}

/***********************************************************************************************************************
* Function:     void NRF24L01::NRF_PWR_Enable(void)
*
* Scope:        private
*
* Description:  nrf power restar
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
void NRF24L01::NRF_PWR_Restart(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  //普通输出模式
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;   //上拉
    RCC_AHB1PeriphClockCmd(RCC_NRF_PWR , ENABLE );
    GPIO_InitStructure.GPIO_Pin = GPIO_NRF_PWR_Pin ;
    GPIO_Init(GPIO_NRF_PWR , &GPIO_InitStructure);

    GPIO_ResetBits(GPIO_NRF_PWR , GPIO_NRF_PWR_Pin );
    delay_ms(50);
    GPIO_SetBits(GPIO_NRF_PWR , GPIO_NRF_PWR_Pin );
    delay_ms(50);
}


void NRF24L01::NRF_GPIO_Init(void)
{

    GPIO_InitTypeDef GPIO_InitStructure;
    //	EXTI_InitTypeDef EXTI_InitStructure;    //不使用中断模式
    //  NVIC_InitTypeDef NVIC_InitStructure;

    NRF_PWR_Disable();
    NRF_PWR_Enable() ;                 //给NRF上电

#if Hardware_Platform == 1

    HF_SPI_Init(NRF_SPI , 0);          //初始化SPI口

    RCC_APB2PeriphClockCmd(RCC_NRF_CE, ENABLE);           //使能GPIO的时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_NRF_CE_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIO_NRF_CE, &GPIO_InitStructure);

    RCC_APB2PeriphClockCmd(RCC_NRF_CSN, ENABLE);          //使能GPIO的时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_NRF_CSN_Pin;
    GPIO_Init(GPIO_NRF_CSN, &GPIO_InitStructure);

    CE_H;                                    //初始化时先拉高
    CSN_H;                                   //初始化时先拉高

    //	//配置NRF2401的中断模式IRQ
    //	RCC_APB2PeriphClockCmd(RCC_NRF24L01_IRQ, ENABLE);  //使能GPIO的时钟
    //	GPIO_InitStructure.GPIO_Pin = NRF24L01_IRQ;
    //	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU  ;     //上拉输入
    //	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    //	GPIO_Init(GPIO_NRF24L01_IRQ, &GPIO_InitStructure);
    //	GPIO_SetBits(GPIO_NRF24L01_IRQ,NRF24L01_IRQ);
    //
    //	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource8);
    //	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    //  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
    //  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//抢占优先级
    //  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    //  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    //
    //  NVIC_Init(&NVIC_InitStructure);
    //  EXTI_InitStructure.EXTI_Line = EXTI_Line8;
    //  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    //  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    //  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    //  EXTI_Init(&EXTI_InitStructure);

#endif

#if Hardware_Platform == 4

    HF_SPI_Init(NRF_SPI , 0);          //初始化SPI口

    RCC_AHB1PeriphClockCmd(RCC_NRF_CE, ENABLE);           //使能GPIO的时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_NRF_CE_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;         //输出模式
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;        //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO_NRF_CE, &GPIO_InitStructure);

    RCC_AHB1PeriphClockCmd(RCC_NRF_CSN, ENABLE);          //使能GPIO的时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_NRF_CSN_Pin;
    GPIO_Init(GPIO_NRF_CSN, &GPIO_InitStructure);

    CE_H;                                    //初始化时先拉高
    CSN_H;                                   //初始化时先拉高

    //	//配置NRF2401的中断模式IRQ
    //	RCC_APB2PeriphClockCmd(RCC_NRF24L01_IRQ, ENABLE);  //使能GPIO的时钟
    //	GPIO_InitStructure.GPIO_Pin = NRF24L01_IRQ;
    //	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU  ;     //上拉输入
    //	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    //	GPIO_Init(GPIO_NRF24L01_IRQ, &GPIO_InitStructure);
    //	GPIO_SetBits(GPIO_NRF24L01_IRQ,NRF24L01_IRQ);
    //
    //	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource8);
    //	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    //  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
    //  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//抢占优先级
    //  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    //  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    //
    //  NVIC_Init(&NVIC_InitStructure);
    //  EXTI_InitStructure.EXTI_Line = EXTI_Line8;
    //  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    //  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    //  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    //  EXTI_Init(&EXTI_InitStructure);

#endif

    CE_L;                                    //enable 24L01
    CSN_H;
}


/***********************************************************************************************************************
***                                                                                                                  ***
***                                           driver function below                                                  ***
***                                                                                                                  ***
***********************************************************************************************************************/

unsigned char NRF24L01::Write_Reg(unsigned char reg , unsigned char value)
{
    unsigned char status;
    CSN_L;					 /* 选通器件 */
    status = NRF_RW(reg);    /* 写寄存器地址 */
    NRF_RW(value);		     /* 写数据 */
    CSN_H;					 /* 禁止该器件 */
    return 	status;
}

unsigned char NRF24L01::Read_Reg(unsigned char reg)
{
    unsigned char reg_val;
    CSN_L;					  /* 选通器件 */
    NRF_RW(reg);			  /* 写寄存器地址 */
    reg_val = NRF_RW(0);	  /* 读取该寄存器返回数据 */
    CSN_H;					  /* 禁止该器件 */
    return 	reg_val;
}

unsigned char NRF24L01::Write_Buf(unsigned char reg, unsigned char *pBuf, unsigned char uchars)
{
    unsigned char i;
    unsigned char status;
    CSN_L;				        /* 选通器件 */
    status = NRF_RW(reg);	    /* 写寄存器地址 */
    for(i=0; i<uchars; i++)
    {
        NRF_RW(pBuf[i]);		/* 写数据 */
    }
    CSN_H;						/* 禁止该器件 */
    return 	status;
}

unsigned char NRF24L01::Read_Buf(unsigned char reg, unsigned char *pBuf, unsigned char uchars)
{
    unsigned char i;
    unsigned char status;
    CSN_L;						/* 选通器件 */
    status = NRF_RW(reg);	    /* 写寄存器地址 */
    for(i=0; i<uchars; i++)
    {
        pBuf[i] = NRF_RW(0);    /* 读取返回数据 */
    }
    CSN_H;						/* 禁止该器件 */
    return 	status;
}

//connect success between MCU and NRF
unsigned char NRF24L01::NRF_Connect_Check(void)
{ 
    unsigned char buf1[5];
    unsigned char i;
    /*write 5 byte*/
    Write_Buf(NRF_WRITE_REG+TX_ADDR,TX_ADDRESS,5);
    /*read 5 byte*/
    Read_Buf(NRF_READ_REG+TX_ADDR,buf1,5);
    /*compare*/
    for(i=0;i<5;i++)
    {
        if(buf1[i]!=TX_ADDRESS[i])
            break;
    }
    if(i==5)
        return 1;  //connect success between MCU and NRF
    else
        return 0;  //connect failed between MCU and NRF
}

/***********************************************************************************************************************
* Function:     void NRF24L01::NRF_Register_Init(void)
*
* Scope:        private
*
* Description:  init NRF register
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
void NRF24L01::NRF_Register_Init(void)   
{

    CE_L;

    Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,RX_ADDRESS,RX_ADR_WIDTH);	//写RX节点地址
    Write_Buf(NRF_WRITE_REG+TX_ADDR,TX_ADDRESS,TX_ADR_WIDTH); 		//写TX节点地址
    Write_Reg(NRF_WRITE_REG+EN_AA,0x01); 							//使能通道0的自动应答
    Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01);						//使能通道0的接收地址

    Write_Reg(NRF_WRITE_REG+SETUP_RETR,0x1a);						//设置自动重发间隔时间:500us;最大自动重发次数:10次 2M波特率下
    Write_Reg(NRF_WRITE_REG+RF_CH,NRF_ch);							//设置RF通道为CHANAL
    Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f); 						//设置TX发射参数,0db增益,2Mbps,低噪声增益开启
    //Write_Reg(NRF_WRITE_REG+RF_SETUP,0x07); 						//设置TX发射参数,0db增益,1Mbps,低噪声增益开启
    //Write_Reg(NRF_WRITE_REG+RF_SETUP,0x27); 						//设置TX发射参数,0db增益,250Kbps,低噪声增益开启

    if(NRF_model==1)				//RX
    {
        Write_Reg(NRF_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);		//选择通道0的有效数据宽度
        Write_Reg(NRF_WRITE_REG + CONFIG, 0x0f);   		        //IRQ收发完成中断开启,16位CRC,主接收
    }
    else if(NRF_model==2)		//TX
    {
        Write_Reg(NRF_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);		 //选择通道0的有效数据宽度
        Write_Reg(NRF_WRITE_REG + CONFIG, 0x0e);   		         //IRQ收发完成中断开启,16位CRC,主发送
    }
    else if(NRF_model==3)		//RX2
    {
        Write_Reg(FLUSH_TX,0xff);
        Write_Reg(FLUSH_RX,0xff);
        Write_Reg(NRF_WRITE_REG + CONFIG, 0x0f);   		         //IRQ收发完成中断开启,16位CRC,主接收

        NRF_RW(0x50);
        NRF_RW(0x73);
        Write_Reg(NRF_WRITE_REG+0x1c,0x01);
        Write_Reg(NRF_WRITE_REG+0x1d,0x06);
    }
    else if(NRF_model==4)		//TX2
    {
        Write_Reg(NRF_WRITE_REG + CONFIG, 0x0e);   		        //IRQ收发完成中断开启,16位CRC,主发送
        Write_Reg(FLUSH_TX,0xff);
        Write_Reg(FLUSH_RX,0xff);

        NRF_RW(0x50);
        NRF_RW(0x73);
        Write_Reg(NRF_WRITE_REG+0x1c,0x01);
        Write_Reg(NRF_WRITE_REG+0x1d,0x06);
    }

    CE_H;
}


/************************************************************************************************************************
***                                                                                                                   ***
***                                           outside port function                                                   ***
***                                                                                                                   ***
*************************************************************************************************************************/

/***********************************************************************************************************************
* Function:    unsigned char NRF24L01::NRF_Init(unsigned char model, unsigned char ch)
*
* Scope:        public
*
* Description:  nrf24l01 init   retur 1 : success  frequency=2400 + ch [MHz]  nrf.Init(NRF_MODEL_TX2,80)
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
unsigned char NRF24L01::NRF_Driver_Init(unsigned char model, unsigned char ch)
{
    NRF_model=model;
    NRF_ch=ch;

    NRF_GPIO_Init();
    //	NRF_delay_ms(2);
    NRF_Register_Init();
    //	NRF_delay_ms(2);
    if( NRF_Connect_Check() )
    {
#if SYSTEM_SUPPORT_NRF_Debug >0u
        printf ( "\r\n NRF init success \r\n" ) ;
#endif
        return 1;
    }
    else
    {
#if SYSTEM_SUPPORT_NRF_Debug >0u
        printf ( "\r\n NRF init failed \r\n" ) ;
#endif
        return 0;
    }
}	


/***********************************************************************************************************************
* Function:     void NRF24L01::NRF_Check_Event(void)
*
* Scope:        public
*
* Description:  NRF receive check   1000hz suggest
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
void NRF24L01::NRF_Driver_Call(void)
{
    unsigned char sta = Read_Reg(NRF_READ_REG + NRFRegSTATUS);

    if(sta & (1<<RX_DR))
    {
        unsigned char rx_len = Read_Reg(R_RX_PL_WID);
        if(rx_len<33 && ( NRF_RxPacket_Update != 1 ) )      // receive right and last data hans been deal
        {
            Read_Buf(RD_RX_PLOAD,NRF24L01_2_RXDATA,rx_len); // read receive payload from RX_FIFO buffer
            NRF_RxPacket_Update = 1;
            NRF_Rx_Len=rx_len;
            //dt.Data_Receive_Anl(NRF24L01_2_RXDATA,rx_len);
        }
        else
        {
            Write_Reg(FLUSH_RX,0xff); //clear receive buffer
        }
    }
    if(sta & (1<<TX_DS))
    {

    }
    if(sta & (1<<MAX_RT))
    {
        if(sta & 0x01)	//TX FIFO FULL
        {
            Write_Reg(FLUSH_TX,0xff);
        }
    }
    Write_Reg(NRF_WRITE_REG + NRFRegSTATUS, sta);
}


/***********************************************************************************************************************
* Function:     void NRF24L01::NRF_Tx_Packet(unsigned char * tx_buf, unsigned char len)
*
* Scope:        public
*
* Description:  nrf24l01 send data
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
void NRF24L01::NRF_Tx_Packet(unsigned char * tx_buf, unsigned char len)
{	
    CE_L;		 //StandBy I model
    if(NRF_model == NRF_MODEL_TX || NRF_model == NRF_MODEL_TX2)
    {
        Write_Buf(NRF_WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH);  //loader receiver address
        Write_Buf(WR_TX_PLOAD, tx_buf, len); 			                  //load data
    }
    else if(NRF_model == NRF_MODEL_RX2)
    {
        Write_Buf(0xa8, tx_buf, len);  //load data
    }
    CE_H;		 //high CE , send data
}


#endif    //#if SYSTEM_SUPPORT_NRF > 0u  
