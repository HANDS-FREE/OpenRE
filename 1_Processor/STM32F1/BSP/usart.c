/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: usart.c
* Contact:  QQ Exchange Group -- 521037187
* Version:  V2.0
*
* LICENSING TERMS:  
* The Hands Free is licensed generally under a permissive 3-clause BSD license. 
* Contributions are requiredto be made under the same license.
*
* History: 
* History: 
* <author>    <time>      <version >       <desc>
* mawenke     2015.10.1   V1.0             creat
* LiuDong     2016.1.8    V1.57            update the name of function
*
* Description:  STM32F1 Initialization of USART
*        STM32F1--------------
*        USART1_TX -- PA9
*        USART1_RX -- PA10
*        USART2_TX -- PA2
*        USART2_RX -- PA3
*        USART3_TX -- PB10
*        USART3_RX -- PB11
*        UART4_TX -- 
*        UART4_RX -- 
*        UART5_TX -- 
*        UART5_RX -- 
***********************************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif 

#include "usart.h"
#include "nvic.h"


#if BSP_CFG_USART_EN > 0u	 

/************************************************************************************************************************
***                                                                                                                   ***
***                                          USART Interruption Configuration                                         ***
***                                                                                                                   ***
*************************************************************************************************************************/

//void USART1_NVIC_Configuration(void) 
//{
//	NVIC_InitTypeDef NVIC_InitStructure;
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  
//	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;    
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //PreemptionPriority  0--4 Lower value, Higher Priority.
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	       //SubPriority 0--4 Lower value, Higher Priority.
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		        //ENABLE Interrupt
//	NVIC_Init(&NVIC_InitStructure); 
//}	

//void USART2_NVIC_Configuration(void) 
//{
//	NVIC_InitTypeDef NVIC_InitStructure;
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  
//	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;     
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //PreemptionPriority  0--4 Lower value, Higher Priority.
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	       //SubPriority 0--4 Lower value, Higher Priority.
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		    //ENABLE Interrupt
//	NVIC_Init(&NVIC_InitStructure); 
//}	


//void USART3_NVIC_Configuration(void) 
//{
//	NVIC_InitTypeDef NVIC_InitStructure;
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  
//	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;    
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //PreemptionPriority  0--4 Lower value, Higher Priority.
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	       //SubPriority 0--4 Lower value, Higher Priority.
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		    //ENABLE Interrupt
//	NVIC_Init(&NVIC_InitStructure); 
//}	

//void UART4_NVIC_Configuration(void) 
//{
//	NVIC_InitTypeDef NVIC_InitStructure;
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  
//	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;     
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //PreemptionPriority  0--4 Lower value, Higher Priority.
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;	       //SubPriority 0--4 Lower value, Higher Priority.
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		    //ENABLE Interrupt
//	NVIC_Init(&NVIC_InitStructure); 
//}	


//void UART5_NVIC_Configuration(void) 
//{
//	NVIC_InitTypeDef NVIC_InitStructure;
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  
//	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;     
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //PreemptionPriority  0--4 Lower value, Higher Priority.
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;	       //SubPriority 0--4 Lower value, Higher Priority.
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		    //ENABLE Interrupt
//	NVIC_Init(&NVIC_InitStructure); 
//}	


/***********************************************************************************************************************
* Function:     Usart_Init(USART_TypeDef* USARTx,u32 bound)
*
* Scope:        public
*
* Description:  Initialize USART
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
* by   mawenke    2015.12.1                           creat
* by   LiuDong    2016.1.8       V1.57       update the name of function
***********************************************************************************************************************/
void HF_Usart_Init(USART_TypeDef* USARTx,unsigned int BaudRate,unsigned char GPIO_AF)
{
    //GPIO config
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    if(USARTx==USART1){
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOB, ENABLE);
        if(GPIO_AF == 0)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;		            //USART1_TX  PA.9
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
            
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;		          //USART1_RX	 PA.10
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
        else if(GPIO_AF == 1)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;		            //USART1_TX  PB6
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
            
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;		          //USART1_RX	 PB7
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
            GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);   //use Remapping
        }
        USART1_NVIC_Configuration();
    }
    else if(USARTx==USART2){
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOD, ENABLE);
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
        
        if(GPIO_AF == 0)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;		            //USART2_TX   PA.2
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
            
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //USART2_RX	  PA.3
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
        else if(GPIO_AF == 1)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;		            //USART2_TX   PD5
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOD, &GPIO_InitStructure);
            
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //USART2_RX	  PD6
            GPIO_Init(GPIOD, &GPIO_InitStructure);
            GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);   //use Remapping
        }
        
        USART2_NVIC_Configuration();
    }
    
    else if(USARTx==USART3){
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
        if(GPIO_AF == 0)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;		       //USART3_TX   PB.10
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
            
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;		      //USART3_RX	  PB.11
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
        }
        else if(GPIO_AF == 1){
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;		       //USART3_TX   PC.10
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
            
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;		      //USART3_RX	  PC.11
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
            GPIO_PinRemapConfig(GPIO_FullRemap_USART3, ENABLE);   //use Remapping
        }
        else if(GPIO_AF == 2){
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;		       //USART3_TX   PD8
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOD, &GPIO_InitStructure);
            
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;		      //USART3_RX	  PD9
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            GPIO_Init(GPIOD, &GPIO_InitStructure);
            GPIO_PinRemapConfig(GPIO_FullRemap_USART3, ENABLE);   //use Remapping
        }
        USART3_NVIC_Configuration();
    }
    else if(USARTx==UART4){
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
        if(GPIO_AF == 0)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;		       //USART3_TX   PC.10
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
            
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;		      //USART3_RX	  PC.11
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        }
    }
    else if(USARTx==UART5){
        
    }
    
    USART_InitStructure.USART_BaudRate = BaudRate ; //usually set 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    
    USART_Init(USARTx, &USART_InitStructure);
    USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE); //enable interrupt
    USART_ClearITPendingBit(USARTx, USART_IT_RXNE);
    USART_Cmd(USARTx, ENABLE);                     //enable usart
    
}

/***********************************************************************************************************************
* Function:     void Usart_Put_Char(USART_TypeDef* USARTx  , unsigned char Tx_Byte)
*
* Scope:        public
*
* Description:  USARTx prints 1 byte
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
void Usart_Put_Char(USART_TypeDef* USARTx  , unsigned char Tx_Byte)
{
    USART_SendData(USARTx , Tx_Byte);
    while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
}


/***********************************************************************************************************************
* Function:     int fputc(int ch, FILE *f)
*
* Scope:        public
*
* Description:  support printf function without tick use MicroLIB	
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
#ifdef __cplusplus                      //if use C++ compiler   

#pragma import(__use_no_semihosting)    //add this line and you do not need to tick use micro lib   

//support function that standard library  need             
struct std::__FILE 
{ 
    int handle;
}; 

std::FILE __stdout;   

//define sys_exit() to avoid half-master mode
void _sys_exit(int x) 
{ 
    x = x;
} 

int std::fputc(int ch, std::FILE *f) 
{ 
    while((USART1->SR&0X40)==0);         //cycle send until succeed
    USART1->DR = (u8) ch;
    return ch;
}

#else                                   //if use C compiler

#pragma import(__use_no_semihosting)    //add this line and you do not need to tick use micro lib       
//support function that standard library  need             
struct __FILE 
{ 
    int handle;
}; 

FILE __stdout;   

//define sys_exit() to avoid half-master mode
void _sys_exit(int x) 
{ 
    x = x;
} 

//Redirect fput
int fputc(int ch, FILE *f)
{ 	
    while((USART1->SR&0X40)==0);//cycle send until succeed
    USART1->DR = (u8) ch;
    return ch;
}

#endif

/***********************************************************************************************************************
* Function:     static char *itoa(int value, char *string, int radix)
*
* Scope:        private
*
* Description:  transform int type data to char type data
*               call by SART_printf()
*               -radix =10  means Decimal
*               -value int data to transform
*               -buf   char data have transformed
*               -radix = 10
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
static char *itoa(int value, char *string, int radix)
{
    int     i, d;
    int     flag = 0;
    char    *ptr = string;
    
    /* This implementation only works for decimal numbers. */
    if (radix != 10)
    {
        *ptr = 0;
        return string;
    }
    
    if (!value)
    {
        *ptr++ = 0x30;
        *ptr = 0;
        return string;
    }
    
    /* if this is a negative value insert the minus sign. */
    if (value < 0)
    {
        *ptr++ = '-';
        
        /* Make the value positive. */
        value *= -1;
    }
    
    for (i = 10000; i > 0; i /= 10)
    {
        d = value / i;
        
        if (d || flag)
        {
            *ptr++ = (char)(d + 0x30);
            value -= (d * i);
            flag = 1;
        }
    }
    
    /* Null terminate the string. */
    *ptr = 0;
    
    return string;
    
} /* NCL_Itoa */

/***********************************************************************************************************************
* Function:     void USART_printf(USART_TypeDef* USARTx, uint8_t *Data,...)
*
* Scope:        public
*
* Description:  格式化输出，类似于C库中的printf，但这里没有用到C库
*               典型应用    USART_printf( USART1, "\r\n this is a demo \r\n" );
*               USART_printf( USART1, "\r\n %d \r\n", i );
*            	USART_printf( USART1, "\r\n %s \r\n", j );
*               -USARTx 串口通道，这里只用到了串口1，即USART1
*		        -Data   要发送到串口的内容的指针
*			    -...    其他参数
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
void USART_printf(USART_TypeDef* USARTx, uint8_t *Data,...)
{
    const char *s;
    int d;
    char buf[16];
    
    va_list ap;
    va_start(ap, Data);
    
    while ( *Data != 0)     // 判断是否到达字符串结束符
    {
        if ( *Data == 0x5c )  //'\'
        {
            switch ( *++Data )
            {
            case 'r':							          //回车符
                USART_SendData(USARTx, 0x0d);
                Data ++;
                break;
                
            case 'n':							          //换行符
                USART_SendData(USARTx, 0x0a);
                Data ++;
                break;
                
            default:
                Data ++;
                break;
            }
        }
        else if ( *Data == '%')
        {
            switch ( *++Data )
            {
            case 's':										  //字符串
                s = va_arg(ap, const char *);
                for ( ; *s; s++)
                {
                    USART_SendData(USARTx,*s);
                    while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
                }
                Data++;
                break;
                
            case 'd':										//十进制
                d = va_arg(ap, int);
                itoa(d, buf, 10);
                for (s = buf; *s; s++)
                {
                    USART_SendData(USARTx,*s);
                    while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
                }
                Data++;
                break;
            default:
                Data++;
                break;
            }
        } /* end of else if */
        else USART_SendData(USARTx, *Data++);
        while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
    }
}

/***********************************************************************************************************************
* Function:     void Packet_Reply(USART_TypeDef* USARTx,unsigned char * data, unsigned short int length)
*
* Scope:        public
*
* Description:  USARTx, send serials of data
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
void Packet_Reply(USART_TypeDef* USARTx,unsigned char* data, unsigned short int length)
{
    //send effective data
    unsigned char j=0,check_sum=0;
    while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
    USART_SendData(USARTx, 0xff);
    while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
    USART_SendData(USARTx, 0xff);
    while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
    USART_SendData(USARTx, 0x04);
    check_sum=check_sum+0x04;
    while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
    USART_SendData(USARTx, 0x69);
    check_sum=check_sum+0x69;
    while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
    USART_SendData(USARTx, (unsigned char)(length>>8));
    check_sum=check_sum+(unsigned char)(length>>8);
    while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
    USART_SendData(USARTx, (unsigned char)(length&0xff));
    check_sum=check_sum+(unsigned char)(length&0xff);
    for (j = 0; j < length; j++)
    {
        while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
        USART_SendData(USARTx, *(data + j));
        check_sum=check_sum+*(data + j);
    }
    while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
    USART_SendData(USARTx, check_sum);
}




/************************************************************************************************************************
***                                                                                                                   ***
***                                          Initerrupt Function                                                      ***
***                                                                                                                   ***
*************************************************************************************************************************/

//void USART1_IRQHandler(void) 
//{

//	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
//	{ 
//	//data = USART_ReceiveData(USART1);				  
//		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
//	} 			 

//}


//void USART2_IRQHandler(void) 
//{

//	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
//	{ 
//	//data = USART_ReceiveData(USART2);				  
//		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
//	} 			 

//}


//void USART3_IRQHandler(void) 
//{

//	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
//	{
//    GPS_Usart_IRQ( USART_ReceiveData(USART3) ) ;		
//		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
//	} 	

//}


#endif  //#if BSP_CFG_USART_EN > 0u	 

#ifdef __cplusplus
}
#endif 

