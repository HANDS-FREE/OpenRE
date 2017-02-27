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
* <author>      <time>      <version>      <desc>
* mawenke       2015.10.1   V1.0           creat this file
*
* Description:    STM32F4 Initialization of USART
***********************************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "usart.h"
#include "nvic.h"

/***********************************************************************************************************************
* Function:     void HF_Usart_Init(USART_TypeDef* USARTx , unsigned int BaudRate , uint8_t GPIO_AF)
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
***********************************************************************************************************************/
void HF_USART_Init(uint8_t USART_Channel , uint32_t BaudRate , uint8_t GPIO_AF)
{
    USART_TypeDef* USARTx;
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    GPIO_StructInit(&GPIO_InitStructure);
    
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
    else if(USART_Channel == 6){
        USARTx = USART6;
    }
    else{
        return;
    }

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//Multiplexing
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//frequency 50MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //Multiplexing push-pull output
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;   //pull up

    if(USARTx==USART1){
        
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
        
        if(GPIO_AF == 0){
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
            GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
            GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
            GPIO_Init(GPIOA,&GPIO_InitStructure);
        }
        else if(GPIO_AF == 1){
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
            GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_USART1);
            GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_USART1);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
            GPIO_Init(GPIOB,&GPIO_InitStructure);
        }
        USART1_NVIC_Configuration();
    }
    else if(USARTx==USART2){
        
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
        
        if(GPIO_AF == 0) {
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
            GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2);
            GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
        else if(GPIO_AF == 1){
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
            GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_USART2);
            GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,GPIO_AF_USART2);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6;
            GPIO_Init(GPIOD, &GPIO_InitStructure);
        }
        USART2_NVIC_Configuration();
    }
    
    else if(USARTx==USART3){
        
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
        
        if(GPIO_AF == 0){
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
            GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3);
            GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
        }
        else if(GPIO_AF == 1){
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
            GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_USART3);
            GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_USART3);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        }
        else if(GPIO_AF == 2){
            
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
            GPIO_PinAFConfig(GPIOD,GPIO_PinSource8,GPIO_AF_USART3);
            GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_USART3);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
            GPIO_Init(GPIOD, &GPIO_InitStructure);
        }
        USART3_NVIC_Configuration();
    }
    else if(USARTx==UART4){
        
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
        
        if(GPIO_AF == 0)
        {
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
            GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_UART4);
            GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_UART4);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
        else if(GPIO_AF == 1){
            
        }
        UART4_NVIC_Configuration();
    }
    else if(USARTx==UART5){
        
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
        
        if(GPIO_AF == 0)
        {
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOD, ENABLE);
            GPIO_PinAFConfig(GPIOC,GPIO_PinSource12,GPIO_AF_UART5);
            GPIO_PinAFConfig(GPIOD,GPIO_PinSource2,GPIO_AF_UART5);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
            GPIO_Init(GPIOD, &GPIO_InitStructure);
        }
        else if(GPIO_AF == 1){
            
        }
        UART5_NVIC_Configuration();
    }
    else if(USARTx==USART6){
        
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6,ENABLE);
        
        if(GPIO_AF == 0)
        {
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
            GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_USART6);
            GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_USART6);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
            GPIO_Init(GPIOC,&GPIO_InitStructure);
        }
        else if(GPIO_AF == 1)
        {
            
        }
        USART6_NVIC_Configuration();
    }
    
    USART_InitStructure.USART_BaudRate = BaudRate ;  //set naud rate 9600 115200 256000 921600
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
* Function:     void Usart_Put_Char(USART_TypeDef* USARTx  , uint8_t Tx_Byte)
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
***********************************************************************************************************************/
void HF_USART_Put_Char(uint8_t USART_Channel , uint8_t Tx_Byte)
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
    else if(USART_Channel == 6){
        USARTx = USART6;
    }
    else{
        return;
    }

    while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
    USART_SendData(USARTx , Tx_Byte);
}

/***********************************************************************************************************************
* Function:     static char *itoa(int value, char *string, int radix)
*
* Scope:        private
*
* Description:  transform int type data to char type data
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
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
* Description:
* example:          USART_printf( USART1, "\r\n this is a demo \r\n" );
*            		USART_printf( USART1, "\r\n %d \r\n", i );
*            		USART_printf( USART1, "\r\n %s \r\n", j );
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
***********************************************************************************************************************/
void HF_USART_printf(USART_TypeDef* USARTx , const char * Data , ...)
{
    const char *s;
    int d;
    char buf[16];
    va_list ap;
    va_start(ap, Data);

    while ( *Data != 0)        //if Terminator
    {
        if ( *Data == 0x5c )   //'\'
        {
            switch ( *++Data )
            {
            case 'r':                                     //Carriage return character
                USART_SendData(USARTx, 0x0d);
                Data ++;
                break;

            case 'n':                                     //Line break
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
            case 's':                                    //string
                s = va_arg(ap, const char *);
                for ( ; *s; s++)
                {
                    USART_SendData(USARTx,*s);
                    while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
                }
                Data++;
                break;

            case 'd':                                   //decimal
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
