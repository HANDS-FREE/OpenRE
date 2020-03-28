/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* Contact:  QQ Exchange Group -- 521037187
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

#include "main_config.h"
#include "board.h"
#include "stdlib.h"

void mallcotest(void)
{
    char *p=NULL;

    p = (char *)malloc(sizeof(char)*1024*20); //20KB

    if(p== NULL)
    {
        printf("malloc test error\r\n");
    }
    else
    {
        printf("malloc test succsess p = %x \r\n\r\n" , (unsigned int)p);
    }

    free(p);
}

void fputest(void)
{
    float a=1.1,b=1.2,c=1.3,d=1.4;
    int i = 0;
    HF_Get_Dtime();
    while( i<= 1000000)
    {
        i++;
        c+=b/d;
    }
    float d_time = HF_Get_Dtime();
    printf("fpu test d_time = %f , c= %f\r\n" , d_time,c);
#ifdef __FPU_PRESENT
    printf("__FPU_PRESENT = %d __FPU_USED = %d\r\n" , __FPU_PRESENT,__FPU_USED);
#endif
}

int main(void)
{
    Board *board = Board::getInstance();
    board->boardBasicInit();

    printf("welcome to handsfree \r\n");

    mallcotest();
    fputest();

    while(1)
    {
        if ( board->cnt_1ms >= 1 )      // 1000hz
        {
            board->cnt_1ms=0;
        }
        if ( board->cnt_2ms >= 2 )      // 500hz
        {
            board->cnt_2ms=0;
        }
        if ( board->cnt_5ms >= 5 )      // 200hz
        {
            board->cnt_5ms=0;
        }
        if ( board->cnt_10ms >= 10 )    // 100hz
        {
            board->cnt_10ms=0;
            board->boardBasicCall();    // need time stm32f1 35us
        }
        if ( board->cnt_20ms >= 20 )    // 50hz
        {
            board->cnt_20ms = 0 ;
        }
        if ( board->cnt_50ms >= 50 )    // 20hz
        {
            board->cnt_50ms = 0 ;
            board->setLedState(0,2);
        }
        if ( board->cnt_100ms >= 100 )    // 10hz
        {
            board->cnt_100ms = 0 ;
        }
        if ( board->cnt_500ms >= 500 )    // 2hz
        {
            board->cnt_500ms = 0;
        }
        if ( board->cnt_1000ms >= 1000 )  // 1hz
        {
            board->cnt_1000ms = 0;
        }
        if ( board->cnt_2000ms >= 2000 )  // 0.5hz
        {
            board->cnt_2000ms = 0;
        }
    }

    return 0;
}
