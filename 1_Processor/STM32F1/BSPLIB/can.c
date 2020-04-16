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
***********************************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif 

#include "can.h"
#include "nvic.h"

/***********************************************************************************************************************
* Function:
*
* Scope:        public
*
* Description:  CAN initialization
*
* Arguments:
* Mode = CAN_Mode_Normal or CAN_Mode_LoopBack
* CAN BaudRate(stm32f102) = 36/(5+3+1)/4=1Mbps or 36M/((T_Bs1 + 1 + T_Bbs2 + 1 + 1)*Brp)
*
* HF_CAN_Init(uint8_t CAN_Channel , uint8_t GPIO_AF , CAN_Mode_Normal , CAN_SJW_2tq , CAN_BS1_5tq , CAN_BS2_3tq , 4)
*
* Return:
*
* Cpu_Time:
*
* History:
***********************************************************************************************************************/
void HF_CAN_Init(uint8_t CAN_Channel , uint8_t GPIO_AF , uint8_t Mode ,
                 uint8_t T_SJW , uint8_t T_BS1 , uint8_t T_BS2 , uint16_t BRP)
{
    CAN_TypeDef *CANx;
    CAN_InitTypeDef  CAN_InitStructure;
    CAN_FilterInitTypeDef  CAN_FilterInitStructure;
    GPIO_InitTypeDef  GPIO_InitStructure;
    
    if(CAN_Channel == 1){
        CANx=CAN1;
    }
    else{
        return;
    }

    if (CANx == CAN1){
        
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
        if(GPIO_AF == 0){ // remap gpio
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);
            
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;              //PA11:CAN-RX
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       //pull-up input
            GPIO_Init(GPIOA, &GPIO_InitStructure);
            
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;              //PA12:CAN-TX
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	        //Multiplexing mode
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
        else if (GPIO_AF == 1)
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE);
            GPIO_PinRemapConfig(GPIO_Remap1_CAN1 , ENABLE);		      //Pin Multiplexing to CAN1
            
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	              //PB8:CAN-RX
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
            
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;                 //PB9:CAN-TX
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
        }
        else if (GPIO_AF == 2)
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOD, ENABLE);
            GPIO_PinRemapConfig(GPIO_Remap2_CAN1 , ENABLE);
            
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;               //PD0:CAN-RX
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(GPIOD, &GPIO_InitStructure);
            
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;               //PD1:CAN-TX
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(GPIOD, &GPIO_InitStructure);
        }
        CAN1_RX0_NVIC_Configuration() ;
    }

    CAN_DeInit(CANx);
    CAN_StructInit(&CAN_InitStructure);
    CAN_InitStructure.CAN_TTCM = DISABLE;
    CAN_InitStructure.CAN_ABOM = DISABLE;
    CAN_InitStructure.CAN_AWUM = DISABLE;
    CAN_InitStructure.CAN_NART = ENABLE;
    CAN_InitStructure.CAN_RFLM = DISABLE;
    CAN_InitStructure.CAN_TXFP = DISABLE;
    CAN_InitStructure.CAN_Mode = Mode;
    CAN_InitStructure.CAN_SJW = T_SJW;
    CAN_InitStructure.CAN_BS1 = T_BS1;
    CAN_InitStructure.CAN_BS2 = T_BS2;
    CAN_InitStructure.CAN_Prescaler = BRP;
    CAN_Init(CANx, &CAN_InitStructure);

    CAN_FilterInitStructure.CAN_FilterNumber=0;
    CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;
    CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;
    CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;
    CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FilterFIFO0;
    CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;
    CAN_FilterInit(&CAN_FilterInitStructure);

    CAN_ITConfig(CANx, CAN_IT_FMP0, ENABLE);  //interrupt enable
    //CAN_ITConfig(CANx, CAN_IT_TME, ENABLE);
}

/***********************************************************************************************************************
* Function:
*
* Scope:        public
*
* Description:  CAN Send one Message
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
***********************************************************************************************************************/
uint8_t HF_CANTX_Message(uint8_t CAN_Channel , uint8_t StdId  , uint8_t ExtId  ,  uint8_t *TxBuf , uint8_t Length)
{
    CAN_TypeDef *CANx;
    CanTxMsg TxMessage;
    uint16_t i;
    uint8_t mbox;

    if(CAN_Channel == 1){
        CANx=CAN1;
    }
    else{
        return 0;
    }

    if(Length > 8) return 0;

    TxMessage.StdId=StdId;
    TxMessage.ExtId=ExtId;
    TxMessage.RTR=CAN_RTR_DATA;
    TxMessage.IDE=CAN_ID_EXT;
    TxMessage.DLC=Length;

    for(i=0;i<Length;i++)
    {
        TxMessage.Data[i]=*(TxBuf+i);
    }

    mbox = CAN_Transmit(CANx, &TxMessage);

    i = 0;
    while((CAN_TransmitStatus(CANx, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF)) i++;
    if(i >= 0XFFF) return 0; //Failed
    return 1; //Succeed
}

#ifdef __cplusplus
}
#endif
