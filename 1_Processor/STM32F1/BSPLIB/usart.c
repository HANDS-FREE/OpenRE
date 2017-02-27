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
void HF_USART_Init(uint8_t USART_Channel ,unsigned int BaudRate,unsigned char GPIO_AF)
{
    //GPIO config
    USART_TypeDef* USARTx;
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    if(USART_Channel == 1){
        USARTx = USART1;
    }
    else if(USART_Channel == 2){
        USARTx = USART2;
    }
    else if(USART_Channel == 3){
        USARTx = USART3;
    }
    else if(USART_Channel == 4){
        USARTx = UART4;
    }
    else if(USART_Channel == 5){
        USARTx = UART5;
    }
    else{
        return;
    }

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
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;		       //USART4_TX   PC.10
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
            
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;		      //USART4_RX	  PC.11
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        }
        UART4_NVIC_Configuration();
    }
    else if(USARTx==UART5){
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD|RCC_APB2Periph_AFIO, ENABLE);
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
        if(GPIO_AF == 0)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;		       //USART4_TX   PC.12
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOC, &GPIO_InitStructure);

            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;		      //USART4_RX	  PD.2
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            GPIO_Init(GPIOD, &GPIO_InitStructure);
        }
        UART5_NVIC_Configuration();
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
void HF_USART_Put_Char(uint8_t USART_Channel  , unsigned char Tx_Byte)
{
    USART_TypeDef* USARTx;

    if(USART_Channel == 1){
        USARTx = USART1;
    }
    else if(USART_Channel == 2){
        USARTx = USART2;
    }
    else if(USART_Channel == 3){
        USARTx = USART3;
    }
    else if(USART_Channel == 4){
        USARTx = UART4;
    }
    else if(USART_Channel == 5){
        USARTx = UART5;
    }
    else{
        return;
    }

    USART_SendData(USARTx , Tx_Byte);
    while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
}

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
void HF_USART_printf(USART_TypeDef* USARTx, uint8_t *Data,...)
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

#ifdef __cplusplus
}
#endif 

