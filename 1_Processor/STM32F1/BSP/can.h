#ifndef __can_H__
#define __can_H__

#ifdef __cplusplus
extern "C" {
#endif 


#include "stm32f10x.h"
#include "main_config.h"


#define CAN_BAUDRATE	1000     //1M Baud Rate
#define MYCAN_ID  0x01
//can.c
void HF_Can_Init(CAN_TypeDef *CANx, unsigned char GPIO_AF);     //  CAN1_TX_RX--PA12_PA11  CAN2_TX_RX--PB13_PA12
void Can_Tx_Message(CAN_TypeDef* CANx, uint8_t MY_ID, uint8_t Receiver_ID, uint8_t *TxBuf, uint8_t Length);

#ifdef __cplusplus
}
#endif 

#endif //__can_H__


