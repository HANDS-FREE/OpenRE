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
    //SCB->VTOR = FLASH_BASE | 0x10000;  //Bootloader
    //INTX_DISABLE();  //close all interruption
    board.boardBasicInit();
    //INTX_ENABLE();	 //enable all interruption
    printf("app start \r\n");
}

////pb9 10 11 14 15
////
//void ledallinit(void)
//{
//    GPIO_InitTypeDef  GPIO_InitStruct;
//    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
//    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
//    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
//    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;

//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);// pa9 pa10
//    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
//    GPIO_Init(GPIOA , &GPIO_InitStruct);

//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE); // pb2 pb6 pb7
//    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
//    GPIO_Init(GPIOB , &GPIO_InitStruct);

//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
//    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_All;
//    GPIO_Init(GPIOC , &GPIO_InitStruct);

//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
//    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_All;
//    GPIO_Init(GPIOD , &GPIO_InitStruct);

//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
//    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_All;
//    GPIO_Init(GPIOE , &GPIO_InitStruct);
//}

//void ledon(int count)
//{
//    if(count <= 15){ GPIO_ResetBits(GPIOA , 1<< count); return; }
//    else  if(count <= 31){GPIO_ResetBits(GPIOB , 1<< (count-16)); return;}
//    else if(count <= 47){GPIO_ResetBits(GPIOC , 1<< (count-32)); return;}
//    else  if(count <= 63){GPIO_ResetBits(GPIOD , 1<< (count-48)); return;}
//    else  if(count <= 79){GPIO_ResetBits(GPIOE , 1<< (count-64)); return;}
//}

//void ledoff(int count)
//{
//    if(count <= 15){ GPIO_SetBits(GPIOA , 1<< count); return; }
//    else  if(count <= 31){GPIO_SetBits(GPIOB , 1<< (count-16)); return;}
//    else if(count <= 47){GPIO_SetBits(GPIOC , 1<< (count-32)); return;}
//    else  if(count <= 63){GPIO_SetBits(GPIOD , 1<< (count-48)); return;}
//    else  if(count <= 79){GPIO_SetBits(GPIOE , 1<< (count-64)); return;}
//}

//void ledallon(void)
//{
//    int i ;

//    for(i=0;i<80;i++)
//    {
//        ledon(i);
//    }
//}

//void ledalloff(void)
//{
//    int i;

//    for(i=0;i<80;i++)
//    {
//        ledoff(i);
//    }
//}

//void delay_ms_(uint16_t t)
//{
//    int i;
//    for( i=0;i<t;i++)
//    {
//        int a=10000;
//        while(a--) asm("nop");
//    }
//}

//int main(void)
//{
//    int count;
//    constructorInit();
//    systemInit();
//    ledallinit();
//    ledalloff();

//    while(1)
//    {
//        ledon(count);
//        delay_ms_(1000);
//        ledoff(count);
//        delay_ms_(1000);
//        count++;
//        if(count == 80)
//        {
//            count=0;
//            ledallon();
//            delay_ms_(1000);
//            delay_ms_(1000);
//            delay_ms_(1000);
//            ledalloff();
//            delay_ms_(1000);
//            delay_ms_(1000);
//            ledallon();
//            delay_ms_(1000);
//            delay_ms_(1000);
//            delay_ms_(1000);
//            ledalloff();
//            delay_ms_(1000);
//            delay_ms_(1000);
//        }
//    }
//}

int main(void)
{
    int count;
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
