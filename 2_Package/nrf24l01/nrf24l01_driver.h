#ifndef __nrf24l01_driver_H__
#define __nrf24l01_driver_H__

#include "bsplib.h"
#include "nrf24l01_config.h"

#define NRF_MODEL_RX				1			//普通接收
#define NRF_MODEL_TX				2			//普通发送
#define NRF_MODEL_RX2				3			//接收模式2,用于双向传输
#define NRF_MODEL_TX2				4			//发送模式2,用于双向传输

#define RX_PLOAD_WIDTH  32  	
#define TX_PLOAD_WIDTH  32 	  
#define TX_ADR_WIDTH    5
#define RX_ADR_WIDTH    5   

class NRF24L01
{
public:
    NRF24L01();
    //nrf24l01初始化  初始化成功返回 1  model=1/2/3/4,ch为实用的通道号  frequency=2400 + ch [MHz]
    unsigned char NRF_Driver_Init(unsigned char model, unsigned char ch);
    //检查是否有通信事件   NRF 接收数据监测   建议1000hz 以上循环调用
    void NRF_Driver_Call(void);
    //nrf24l01发送一个包  *tx_buf 包的首指针  len 包的长度
    void NRF_Tx_Packet(unsigned char * tx_buf, unsigned char len);

    unsigned char NRF_model,NRF_ch;
    unsigned char NRF24L01_2_RXDATA[RX_PLOAD_WIDTH], NRF24L01_2_TXDATA[RX_PLOAD_WIDTH];  //nrf24l01接收和发送数据缓冲区
    unsigned char NRF_RxPacket_Update , NRF_Tx_Packet_Update , NRF_Rx_Len , NRF_Tx_Len;  //NRF 发送包和接收包的更新标志
    float NRF_RxPacket_Num ,NRF_RxPacket_Error_Num ,NRF_RxPacket_Right_Num  ; //NRF历史接收的正确包数量和错误包数量
private:
    void NRF_delay_ms(unsigned char t);
    unsigned char NRF_RW(unsigned char Data);
    void NRF_PWR_Enable(void);
    void NRF_PWR_Disable(void);
    void NRF_PWR_Restart(void);

    void NRF_GPIO_Init(void);

    unsigned char Read_Reg(unsigned char reg);
    unsigned char Write_Reg(unsigned char reg, unsigned char value);
    unsigned char Write_Buf(unsigned char reg, unsigned char *pBuf, unsigned char uchars);
    unsigned char Read_Buf(unsigned char reg, unsigned char *pBuf, unsigned char uchars);

    void NRF_Register_Init(void);
    unsigned char NRF_Connect_Check(void);                 //检查NRF模块是否正常工作
};

extern NRF24L01 nrf24L01;

#endif      //#ifndef __nrf24l01_driver_H__


