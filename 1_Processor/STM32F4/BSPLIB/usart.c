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
void HF_USART_Init(USART_TypeDef* USARTx , uint32_t BaudRate , uint8_t GPIO_AF)
{

    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    GPIO_StructInit(&GPIO_InitStructure);
    
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
void HF_USART_Put_Char(USART_TypeDef* USARTx  , uint8_t Tx_Byte)
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
***********************************************************************************************************************/

#ifdef __GNUC__

#include <errno.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <sys/unistd.h>

#ifndef STDOUT_USART
#define STDOUT_USART 1
#endif

#ifndef STDERR_USART
#define STDERR_USART 1
#endif

#ifndef STDIN_USART
#define STDIN_USART 1
#endif

#undef errno
extern int errno;

/*
 environ
 A pointer to a list of environment variables and their values.
 For a minimal environment, this empty list is adequate:
 */
char *__env[1] = { 0 };
char **environ = __env;

int _write(int file, char *ptr, int len);

void _exit(int status) {
    _write(1, "exit", 4);
    while (1) {
        ;
    }
}

int _close(int file) {
    return -1;
}
/*
 execve
 Transfer control to a new process. Minimal implementation (for a system without processes):
 */
int _execve(char *name, char **argv, char **env) {
    errno = ENOMEM;
    return -1;
}
/*
 fork
 Create a new process. Minimal implementation (for a system without processes):
 */

int _fork() {
    errno = EAGAIN;
    return -1;
}
/*
 fstat
 Status of an open file. For consistency with other minimal implementations in these examples,
 all files are regarded as character special devices.
 The `sys/stat.h' header file required is distributed in the `include' subdirectory for this C library.
 */
int _fstat(int file, struct stat *st) {
    st->st_mode = S_IFCHR;
    return 0;
}

/*
 getpid
 Process-ID; this is sometimes used to generate strings unlikely to conflict with other processes. Minimal implementation, for a system without processes:
 */

int _getpid() {
    return 1;
}

/*
 isatty
 Query whether output stream is a terminal. For consistency with the other minimal implementations,
 */
int _isatty(int file) {
    switch (file){
    case STDOUT_FILENO:
    case STDERR_FILENO:
    case STDIN_FILENO:
        return 1;
    default:
        //errno = ENOTTY;
        errno = EBADF;
        return 0;
    }
}


/*
 kill
 Send a signal. Minimal implementation:
 */
int _kill(int pid, int sig) {
    errno = EINVAL;
    return (-1);
}

/*
 link
 Establish a new name for an existing file. Minimal implementation:
 */

int _link(char *old, char *new) {
    errno = EMLINK;
    return -1;
}

/*
 lseek
 Set position in a file. Minimal implementation:
 */
int _lseek(int file, int ptr, int dir) {
    return 0;
}

/*
 sbrk
 Increase program data space.
 Malloc and related functions depend on this
 */
caddr_t _sbrk(int incr) {

    extern char _ebss; // Defined by the linker
    static char *heap_end;
    char *prev_heap_end;

    if (heap_end == 0) {
        heap_end = &_ebss;
    }
    prev_heap_end = heap_end;

    char * stack = (char*) __get_MSP();
    if (heap_end + incr >  stack)
    {
        _write (STDERR_FILENO, "Heap and stack collision\n", 25);
        errno = ENOMEM;
        return  (caddr_t) -1;
        //abort ();
    }

    heap_end += incr;
    return (caddr_t) prev_heap_end;

}

/*
 read
 Read a character to a file. `libc' subroutines will use this system routine for input from all files, including stdin
 Returns -1 on error or blocks until the number of characters have been read.
 */


int _read(int file, char *ptr, int len) {
    int n;
    int num = 0;
    switch (file) {
    case STDIN_FILENO:
        for (n = 0; n < len; n++) {
#if   STDIN_USART == 1
            while ((USART1->SR & USART_FLAG_RXNE) == (uint16_t)RESET) {}
            char c = (char)(USART1->DR & (uint16_t)0x01FF);
#elif STDIN_USART == 2
            while ((USART2->SR & USART_FLAG_RXNE) == (uint16_t) RESET) {}
            char c = (char) (USART2->DR & (uint16_t) 0x01FF);
#elif STDIN_USART == 3
            while ((USART3->SR & USART_FLAG_RXNE) == (uint16_t)RESET) {}
            char c = (char)(USART3->DR & (uint16_t)0x01FF);
#endif
            *ptr++ = c;
            num++;
        }
        break;
    default:
        errno = EBADF;
        return -1;
    }
    return num;
}

/*
 stat
 Status of a file (by name). Minimal implementation:
 int    _EXFUN(stat,( const char *__path, struct stat *__sbuf ));
 */

int _stat(const char *filepath, struct stat *st) {
    st->st_mode = S_IFCHR;
    return 0;
}

/*
 times
 Timing information for current process. Minimal implementation:
 */

clock_t _times(struct tms *buf) {
    return -1;
}

/*
 unlink
 Remove a file's directory entry. Minimal implementation:
 */
int _unlink(char *name) {
    errno = ENOENT;
    return -1;
}

/*
 wait
 Wait for a child process. Minimal implementation:
 */
int _wait(int *status) {
    errno = ECHILD;
    return -1;
}

/*
 write
 Write a character to a file. `libc' subroutines will use this system routine for output to all files, including stdout
 Returns -1 on error or number of bytes sent
 */
int _write(int file, char *ptr, int len) {
    int n;
    switch (file) {
    case STDOUT_FILENO: /*stdout*/
        for (n = 0; n < len; n++) {
#if STDOUT_USART == 1
            while ((USART1->SR & USART_FLAG_TC) == (uint16_t)RESET) {}
            USART1->DR = (*ptr++ & (uint16_t)0x01FF);
#elif  STDOUT_USART == 2
            while ((USART2->SR & USART_FLAG_TC) == (uint16_t) RESET) {
            }
            USART2->DR = (*ptr++ & (uint16_t) 0x01FF);
#elif  STDOUT_USART == 3
            while ((USART3->SR & USART_FLAG_TC) == (uint16_t)RESET) {}
            USART3->DR = (*ptr++ & (uint16_t)0x01FF);
#endif
        }
        break;
    case STDERR_FILENO: /* stderr */
        for (n = 0; n < len; n++) {
#if STDERR_USART == 1
            while ((USART1->SR & USART_FLAG_TC) == (uint16_t)RESET) {}
            USART1->DR = (*ptr++ & (uint16_t)0x01FF);
#elif  STDERR_USART == 2
            while ((USART2->SR & USART_FLAG_TC) == (uint16_t) RESET) {
            }
            USART2->DR = (*ptr++ & (uint16_t) 0x01FF);
#elif  STDERR_USART == 3
            while ((USART3->SR & USART_FLAG_TC) == (uint16_t)RESET) {}
            USART3->DR = (*ptr++ & (uint16_t)0x01FF);
#endif
        }
        break;
    default:
        errno = EBADF;
        return -1;
    }
    return len;
}

#else

#ifdef __cplusplus                      //if use C++ compiler

#pragma import(__use_no_semihosting)    //add this line and you do not need to tick use micro lib

//support function that standard library  need
struct std::__FILE
{
    int handle;
};

__FILE __stdout;

//define sys_exit() to avoid half-master mode
void _sys_exit(int x)
{
    x = x;
}

int std::fputc(int ch, std::FILE *f)
{
    while((USART1->SR&0X40)==0);        //cycle send until succeed
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

#endif

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
void HF_USART_printf(const char * Data , ...)
{
    const char *s;
    int d;
    char buf[16];
    USART_TypeDef* USARTx=USART1;
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
