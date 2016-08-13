#ifndef __24cxx_iic_bsp_H__
#define __24cxx_iic_bsp_H__

#include "BSP_TOP.h"              

#define AT24C01		127
#define AT24C02		255
#define AT24C04		511
#define AT24C08		1023
#define AT24C16		2047
#define AT24C32		4095
#define AT24C64	  8191
#define AT24C128	16383
#define AT24C256	32767  

//the type of your at24c
#define EE_TYPE AT24C02
	
//init the at24cxx , return 0: error  return 1: right 	
unsigned char AT24CXX_Init(void); 

void AT24CXX_WriteOneByte(unsigned short int WriteAddr,unsigned char DataToWrite);
unsigned char AT24CXX_ReadOneByte(unsigned short int ReadAddr);				
void AT24CXX_Write_Buf(unsigned short int WriteAddr,unsigned char *pBuffer,unsigned short int NumToWrite);	//从指定地址开始写入指定长度的数据
void AT24CXX_Read_Buf(unsigned short int ReadAddr,unsigned char *pBuffer,unsigned short int NumToRead);   	//从指定地址开始读出指定长度的数据
void AT24CXX_Write_16data(unsigned short int WriteAddr,unsigned short int data);
unsigned short int AT24CXX_Read_16data(unsigned short int WriteAddr );
#endif //24cxx_iic_bsp.h



