#ifndef CAN_H
#define CAN_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "stm32f10x.h"

void HF_CAN_Init(uint8_t CAN_Channel , uint8_t GPIO_AF , uint8_t Mode ,
                 uint8_t T_SJW , uint8_t T_BS1 , uint8_t T_BS2 , uint16_t BRP);
uint8_t HF_CANTX_Message(uint8_t CAN_Channel , uint8_t StdId  , uint8_t ExtId  ,  uint8_t *TxBuf , uint8_t Length);

#ifdef __cplusplus
}
#endif 

#endif // #ifndef CAN_H

