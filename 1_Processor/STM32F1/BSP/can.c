/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: can.c
* Contact:  QQ Exchange Group -- 521037187
* Version:  V2.0
*
* LICENSING TERMS:  
* The Hands Free is licensed generally under a permissive 3-clause BSD license. 
* Contributions are requiredto be made under the same license.
*
* History: 
* <author>    <time>      <version >       <desc>
* mawenke     2015.10.1   V1.0             creat
* LiuDong     2016.1.8    V1.57            update the name of function
*
* Description: 
***********************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif 

#include "can.h"
#include "nvic.h"

#if BSP_CFG_CAN_EN > 0u	 

/************************************************************************************************************************
***                                                                                                                   ***
***                                              CAN Interrupt Config                                                 ***
***                                                                                                                   ***
*************************************************************************************************************************/

//static void CAN1_NVIC_Configuration(void) 
//{
//	NVIC_InitTypeDef NVIC_InitStructure;
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		 	/*interrupt config*/
//	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;	   //CAN1 RX0interrupt
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		   //PreemptionPriority0
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			   //SubPriority0
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//	
//}

/***********************************************************************************************************************
* Function:     void Can_Init(void)
*
* Scope:        public
*
* Description:  can initialization
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
* by   mawenke    2015.12.1                             creat
* by   LiuDong    2016.1.8       V1.57       update the name of function
***********************************************************************************************************************/
void HF_Can_Init(CAN_TypeDef *CANx , unsigned char GPIO_AF)     //  CAN1_TX_RX--PA12_PA11  CAN2_TX_RX--PB13_PA12
{
    
    CAN_InitTypeDef        CAN_InitStructure;
    CAN_FilterInitTypeDef  CAN_FilterInitStructure;
    GPIO_InitTypeDef  GPIO_InitStructure;
    
    if (CANx == CAN1){
        
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
        if(GPIO_AF == 0){
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);
            
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	              //PA11:CAN-RX
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			    //pull-up input
            GPIO_Init(GPIOA, &GPIO_InitStructure);
            
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;					       //PA12:CAN-TX
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			       //Multiplexing mode
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
        else if (GPIO_AF == 1)
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE);
            
            GPIO_PinRemapConfig(GPIO_Remap1_CAN1 , ENABLE);		      //Pin Multiplexing to CAN1
            
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	              //PB8:CAN-RX
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			  //pull-up input
            GPIO_Init(GPIOB, &GPIO_InitStructure);
            
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;					      //PB9:CAN-TX
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			    //Multiplexing mode
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
        }
        else if (GPIO_AF == 2)
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOD, ENABLE);
            
            GPIO_PinRemapConfig(GPIO_Remap2_CAN1 , ENABLE);		     //Pin Multiplexing to CAN1
            
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	             //PD0:CAN-RX
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 //pull-up input
            GPIO_Init(GPIOD, &GPIO_InitStructure);
            
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;					     //PD1:CAN-TX
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			   //Multiplexing mode
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(GPIOD, &GPIO_InitStructure);
        }
        CAN1_NVIC_Configuration() ;
    }
    else if (CANx == CAN2){
        
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
        if(GPIO_AF == 0){
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE);
            
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	               //PB5:CAN-RX
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			   //pull-up input
            GPIO_Init(GPIOB, &GPIO_InitStructure);
            
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;					       //PB6:CAN-TX
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			     //Multiplexing mode
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
        }
        else if (GPIO_AF == 1)
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE);
            
            GPIO_PinRemapConfig(GPIO_Remap_CAN2 , ENABLE);		        //Pin Multiplexing to CAN1
            
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	              //PB12:CAN-RX
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			    //pull-up input
            GPIO_Init(GPIOB, &GPIO_InitStructure);
            
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;					      //PB13:CAN-TX
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			      //Multiplexing mode
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
        }
        CAN2_NVIC_Configuration() ;
    }
    CAN_DeInit(CANx);
    CAN_StructInit(&CAN_InitStructure);
    CAN_InitStructure.CAN_TTCM = DISABLE;			   //MCR-TTCM  enable time touch communicate mode
    CAN_InitStructure.CAN_ABOM = DISABLE;			   //MCR-ABOM  auto manage offline
    CAN_InitStructure.CAN_AWUM = DISABLE;			   //MCR-AWUM  auto wake-up
    CAN_InitStructure.CAN_NART = DISABLE;			   //MCR-NART  禁止报文自动重传	  0-自动重传   1-报文只传一次
    CAN_InitStructure.CAN_RFLM = DISABLE;			   //MCR-RFLM  接收FIFO 锁定模式  0-溢出时新报文会覆盖原有报文  1-溢出时，新报文丢弃
    CAN_InitStructure.CAN_TXFP = DISABLE;			   //MCR-TXFP  发送FIFO优先级 0-优先级取决于报文标示符 1-优先级取决于发送请求的顺序
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;	   //BTR-SILM/LBKM   CAN normal communicate mode
    //2 5 3
    CAN_InitStructure.CAN_SJW = CAN_SJW_2tq;		   //BTR-SJW 重新同步跳跃宽度 1个时间单元
    CAN_InitStructure.CAN_BS1 = CAN_BS1_5tq;		   //BTR-TS1 时间段1 占用了2个时间单元
    CAN_InitStructure.CAN_BS2 = CAN_BS2_3tq;		   //BTR-TS1 时间段2 占用了3个时间单元
    
#if(CAN_BAUDRATE == 1000) /* 1MBps */
    CAN_InitStructure.CAN_Prescaler = 4;			   //BTR-BRP 波特率分频器  定义了时间单元的时间长度 36/(2+4+4)/10=1Mbps
#endif
#if(CAN_BAUDRATE == 500) /* 500KBps */
    CAN_InitStructure.CAN_Prescaler = 8;
#endif
#if(CAN_BAUDRATE == 250) /* 250KBps */
    CAN_InitStructure.CAN_Prescaler = 16;
#endif
#if(CAN_BAUDRATE == 125) /* 125KBps */
    CAN_InitStructure.CAN_Prescaler = 32;
#endif
#if(CAN_BAUDRATE == 100) /* 100KBps */
    CAN_InitStructure.CAN_Prescaler = 40;
#endif
#if(CAN_BAUDRATE == 50) /* 50KBps */
    CAN_InitStructure.CAN_Prescaler = 80;
#endif
#if(CAN_BAUDRATE == 20) /* 20KBps */
    CAN_InitStructure.CAN_Prescaler = 200;
#endif
#if(CAN_BAUDRATE == 10) /* 10KBps */
    CAN_InitStructure.CAN_Prescaler = 400;
#endif
    CAN_Init(CANx, &CAN_InitStructure);
    
    
    // 	  /* CAN过滤器初始化 */
    // 	  CAN_FilterInitStructure.CAN_FilterNumber = 0;//command_chgspeed;	//每种命令对应一种过滤器
    
    // 	  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;		//FM1R  过滤器组0的工作模式。
    // 	  																	//0: 过滤器组x的2个32位寄存器工作在标识符屏蔽位模式；
    // 																		//1: 过滤器组x的2个32位寄存器工作在标识符列表模式。
    // 	  CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;	//FS1R 过滤器组0(13～0)的位宽。
    // 	  																	//0：过滤器位宽为2个16位； 1：过滤器位宽为单个32位。
    
    // 	  /* 使能报文标示符过滤器按照标示符的内容进行比对过滤，扩展ID不是如下的就抛弃掉，是的话，会存入FIFO0。 */
    // 	  CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;				//要过滤的ID高位
    // 	  CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;				//要过滤的ID低位
    // 	  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
    // 	  CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
    // 	  CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;				//FFAx : 过滤器位宽设置 报文在通过了某过滤器的过滤后，
    // 	  												 //将被存放到其关联的FIFO中。 0：过滤器被关联到FIFO0； 1：过滤器被关联到FIFO1。
    // 	  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;				//FACTx : 过滤器激活 软件对某位设置1来激活相应的过滤器。只有对FACTx位清0，
    // 	  																	//或对CAN_FMR寄存器的FINIT位设置1后，才能修改相应的过滤器寄存器
    // 																		  //x(CAN_FxR[0:1])。 0：过滤器被禁用； 1：过滤器被激活。
    // 	  CAN_FilterInit(&CAN_FilterInitStructure);
    
    
    /* CAN Filter Initialization*/
    CAN_FilterInitStructure.CAN_FilterNumber = 0;//command_chgspeed;	//every command correspond every filter
    
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;		//FM1R   working mode of filter group 0
    //0: 过滤器组x的2个32位寄存器工作在标识符屏蔽位模式；
    //1: 过滤器组x的2个32位寄存器工作在标识符列表模式。
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;	//FS1R 过滤器组0(13～0)的位宽。
    //0：过滤器位宽为2个16位； 1：过滤器位宽为单个32位。
    
    /* 使能报文标示符过滤器按照标示符的内容进行比对过滤，扩展ID不是如下的就抛弃掉，是的话，会存入FIFO0。 */
    CAN_FilterInitStructure.CAN_FilterIdHigh = (((u32)0x1314<<3)&0xFFFF0000)>>16;				//要过滤的ID高位
    CAN_FilterInitStructure.CAN_FilterIdLow = (((u32)0x1314<<3)|CAN_ID_EXT|CAN_RTR_DATA)&0xFFFF;				//要过滤的ID低位
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0;
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0;
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FilterFIFO0;				//FFAx : 过滤器位宽设置 报文在通过了某过滤器的过滤后，
    //将被存放到其关联的FIFO中。 0：过滤器被关联到FIFO0； 1：过滤器被关联到FIFO1。
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;				//FACTx : 过滤器激活 软件对某位设置1来激活相应的过滤器。只有对FACTx位清0，
    //或对CAN_FMR寄存器的FINIT位设置1后，才能修改相应的过滤器寄存器
    //x(CAN_FxR[0:1])。 0：过滤器被禁用； 1：过滤器被激活。
    CAN_FilterInit(&CAN_FilterInitStructure);
    
    /* CAN FIFO0 ENABLE receive interrput*/
    CAN_ITConfig(CANx, CAN_IT_FMP0, ENABLE);  //enable interrupt
    CAN_ITConfig(CANx, CAN_IT_TME, ENABLE);
    
}	



/************************************************************************************************************************
***                                                                                                                   ***
***                                           Interrupt Function                                                      ***
***                                                                                                                   ***
*************************************************************************************************************************/

void USB_LP_CAN1_RX0_IRQHandler(void)
{
    
    if (CAN_GetITStatus(CAN1,CAN_IT_FMP0)!= RESET) 
    {   
        
        CanRxMsg RxMessage;	
        RxMessage.StdId=0x0000;   //Sender ID
        RxMessage.ExtId=0x0000;   //Receiver ID 
        RxMessage.IDE=0;
        RxMessage.DLC=0;
        RxMessage.FMI=0;		
        CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);  
        
        //			if((RxMessage.ExtId==((UID<<8)|MYID)) && (RxMessage.DLC==0x06) && (RxMessage.Data[0]==0x03))	//receive target rate
        //			{
        //	  				 
        //					 
        //			}
        
        CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
        
    }
    
}

/***********************************************************************************************************************
* Function:     void Can_Tx_Message(void)
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
* by   mawenke    2015.12.1     creat
***********************************************************************************************************************/
void Can_Tx_Message(CAN_TypeDef* CANx , uint8_t Sender_ID  , uint8_t Receiver_ID , uint8_t *TxBuf , uint8_t Length)
{
    
    CanTxMsg TxMessageBuffer;
    uint8_t i;
    TxMessageBuffer.StdId=0x00;	 
    TxMessageBuffer.ExtId=( (Sender_ID << 8) | Receiver_ID ); //Sender ID | Receiver ID
    TxMessageBuffer.RTR=CAN_RTR_DATA;	     // 传输消息的帧类型为数据帧（还有远程帧）
    TxMessageBuffer.IDE=CAN_ID_EXT;		     // 消息标志符实验标准标识符
    
    TxMessageBuffer.DLC=Length;					   // 发送两帧，一帧8位
    
    for(i=0;i<Length;i++)
    {
        TxMessageBuffer.Data[i]=*(TxBuf+i);
    }
    
    CAN_Transmit(CANx, &TxMessageBuffer);  
    
}	

#endif   //#if BSP_CFG_CAN_EN > 0u	

#ifdef __cplusplus
}
#endif

