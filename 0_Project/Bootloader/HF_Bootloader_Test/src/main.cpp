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

void constructorInit(void)
{
    board = Board();
}

void systemInit(void)
{
#ifdef BOOTLOADER_ENABLE
    SCB->VTOR = FLASH_BASE | 0x4000;  //16k Bootloader
#endif
    //INTX_DISABLE();  //close all interruption
    board.boardBasicInit();
    //INTX_ENABLE();	 //enable all interruption
    printf("app start \r\n");
}

int main(void)
{
    int count=0;
    constructorInit();
    systemInit();

    while(1)
    {

        if ( board.cnt_1ms >= 1 )    // 1000hz
        {
            board.cnt_1ms=0;
        }
        if ( board.cnt_2ms >= 2 )    // 500hz
        {
            board.cnt_2ms=0;
        }
        if ( board.cnt_5ms >= 5 )    // 200hz
        {
            board.cnt_5ms=0;
        }
        if ( board.cnt_10ms >= 10 )  // 100hz
        {
            board.cnt_10ms=0;
            board.boardBasicCall();  // need time stm32f1  35us
        }
        if ( board.cnt_20ms >= 20 )  // 50hz
        {
            board.cnt_20ms = 0 ;
        }
        if ( board.cnt_50ms >= 50 )  // 20hz
        {
            board.cnt_50ms = 0 ;
            board.setLedState(0,2);
            printf("welcome to handsfree %d \r\n" , count++);
        }

    }

}
