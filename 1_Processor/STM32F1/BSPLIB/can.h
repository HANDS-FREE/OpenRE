#ifndef CAN_H
#define CAN_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "stm32f10x.h"

void HF_CAN_Init(uint8_t CAN_Channel , unsigned char GPIO_AF);     //  CAN1_TX_RX--PA12_PA11  CAN2_TX_RX--PB13_PA12
void HF_CANTX_Message(uint8_t CAN_Channel , uint8_t Sender_ID  , uint8_t Receiver_ID , uint8_t *TxBuf , uint8_t Length);

#ifdef __cplusplus
}
#endif 

#endif // #ifndef CAN_H

