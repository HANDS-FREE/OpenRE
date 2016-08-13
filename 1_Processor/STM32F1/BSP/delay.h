#ifndef __my_delay_H__
#define __my_delay_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f10x.h"
#include "main_config.h"

//if using Time measurement system to measure time difference or system working time. ?
#define Time_Measurement 1	

/**********************************************************************************************************************/
void delay_init(void);
void delay_ms(unsigned short int t);    //using timer to delay time, max delay time is 1864ms
void delay_us(unsigned short int t);    //using timer to delay time, max delay time is 1864ms
/**********************************************************************************************************************/

void Init_Measurement_Timer(void);  //Initialize the Time measurement system
float GET_System_time(void);        //Return the current time(us), max:281474976s--->3257.8 days
float GET_microstime(void);         // Return the time difference(us). max:655s

/**********************************************************************************************************************/
void Get_CPU_Information(void);             //Only calls once to get ID of CPU the capacity of Flash
typedef struct CPU_Hardware_Data{
    unsigned int ChipUniqueID[3];
    unsigned short int  flash_Size;         //  Unit: KB
}CPU_Hardware_Data;
extern CPU_Hardware_Data cpu_hardware_data_r;

/************************************************************************************************************************
***                                                                                                                   ***
***                                                                                                                   ***
***                                                                                                                   ***
*************************************************************************************************************************/

/***********************************************************************************************************************
位带操作,实现51类似的GPIO控制功能,具体实现思想,
ALIENTEK Mini STM32开发板 Copyright(C) 正点原子 2009-2019
***********************************************************************************************************************/
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2))
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr))
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum))
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08

//be sure n<=16!#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出

#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //output
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //input

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n) 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n) 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n) 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n) 

//以下为汇编函数
void WFI_SET(void);		//执行WFI指令
void INTX_DISABLE(void);//关闭所有中断
void INTX_ENABLE(void);	//开启所有中断
void MSR_MSP(u32 addr);	//设置堆栈地址

#ifdef __cplusplus
}
#endif


#endif //__my_delay_H__
