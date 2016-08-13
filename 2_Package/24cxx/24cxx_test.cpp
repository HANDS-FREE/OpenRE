/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: 24cxx_test.cpp
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
* Description: 
***********************************************************************************************************************/

#include "24cxx_test.h"

#if AT24CXX_Test_Enalbe == 1

#define  EEP_First_add      0x00    //测试首地址
#define  EEP_Last_add       0xFF    //测试终地址

uint8_t I2c_Buf_Write[EEP_Last_add];
uint8_t I2c_Buf_Read[EEP_Last_add];

/***********************************************************************************************************************
* Function:     void AT24CXX_Test(void)
*
* Scope:        public
*
* Description:  test the at24cxx
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
* by   mawenke   2015.10.1   creat
***********************************************************************************************************************/
void AT24CXX_Test(void)
{

    uint16_t i;
	
    printf( "\r\n this is a test of at24cxx \r\n");

    if(AT24CXX_Init()){
        printf("\r\n at24cxx init ok \r\n");
    }
    else{
        printf("\r\n at24cxx init error\r\n");
    }

    printf("\r\n write data..... \r\n");

    for ( i=0; i<EEP_Last_add; i++ ) //Fill write buffer
    {
        I2c_Buf_Write[i] = i;
        printf("0x%02X ", I2c_Buf_Write[i]);
        if(i%16 == 15)
            printf("\r\n");
    }	
    AT24CXX_Write_Buf(EEP_First_add , I2c_Buf_Write, EEP_Last_add);
		
    printf("\r\n read data..... \r\n");	
		
    AT24CXX_Read_Buf(EEP_First_add , I2c_Buf_Read,  EEP_Last_add);  //11927us
    //printf read data
    for (i=0; i<EEP_Last_add; i++)
    {
        printf("0x%02X ", I2c_Buf_Read[i]);
        if(i%16 == 15)
            printf("\r\n");
    }

    for (i=0; i<EEP_Last_add; i++) //compare
    {

        if(I2c_Buf_Read[i] != I2c_Buf_Write[i])
        {
            printf("0x%02X ", I2c_Buf_Read[i]);
            printf("\r\n error :I2C EEPROM write read failed \r\n");
            return;
        }

    }

    printf("\r\n I2C EEPROM write read success \r\n");

}

#endif  //#if AT24CXX_Test_Enalbe == 1
