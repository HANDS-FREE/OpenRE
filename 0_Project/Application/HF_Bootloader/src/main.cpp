/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: main.c
* Contact:  QQ Exchange Group -- 521037187
* Version:  V2.0
*
* LICENSING TERMS:
* The Hands Free is licensed generally under a permissive 3-clause BSD license. 
* Contributions are requiredto be made under the same license.
*
* History:
* <author>      <time>      <version>      <desc>
* mawenke      2015.10.1    V1.0          creat this file
*
* Description:   
***********************************************************************************************************************/

#include "main_includes.h"

unsigned int enter_bootloader_flag;	
#define BootLoader_Wait  1000

void bootloader_delay_ms(unsigned short int t)
{
    int i;
    for( i=0;i<t;i++)
    {
        int a=42000;
        while(a--);
    }
}

void System_Init(void)
{

    enter_bootloader_flag=STMFLASH_ReadWord(FLASH_APP1_ADDR - 4);
    if(enter_bootloader_flag !=256 )    //jump to app code
    {
        enter_bootloader_flag=256;
        STMFLASH_Write(FLASH_APP1_ADDR - 4 , &enter_bootloader_flag , 1);
        bootloader_delay_ms(BootLoader_Wait);
        enter_bootloader_flag=0;
        STMFLASH_Write(FLASH_APP1_ADDR - 4 , &enter_bootloader_flag , 1);
        Load_Flash_APP(FLASH_APP1_ADDR);
    }
    enter_bootloader_flag = 0;
    STMFLASH_Write(FLASH_APP1_ADDR - 4 , &enter_bootloader_flag , 1);

    HF_Led_Key_Init();

    INTX_DISABLE();  //close all interruption
    HF_Set_Beep_State(1);
    bootloader_delay_ms(200);
    HF_Set_Beep_State(0);
    bootloader_delay_ms(200);
    HF_Set_Beep_State(1);
    bootloader_delay_ms(200);
    HF_Set_Beep_State(0);
    bootloader_delay_ms(200);
    HF_Set_Beep_State(1);
    bootloader_delay_ms(500);
    HF_Set_Beep_State(0);
    INTX_ENABLE();	 //enable all interruption

    HF_BootLoader_Init();
    printf("bootloader start \r\n");
}


int main(void)
{

    System_Init();

    while(1)
    {
        Boot_Loader_Call();
        bootloader_delay_ms(500);
        if(USART_RX_CNT) {
            HF_Set_Led_State(0,2);
        }
        else{

            HF_Set_Led_State(0,1);
        }
    }
}

