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

#include "main_config.h"
#include "board.h"
#include "stdlib.h"

void mallcotest(void)
{
    char *p=NULL;
    char *p2=NULL;

    p = (char *)malloc(sizeof(char)*1024*80); //80KB

    if(p== NULL)
    {
        printf("malloc error\r\n");
    }
    else
    {
        printf("malloc succsess p = %x \r\n" , (unsigned int)p);
    }

    free(p);

    p2 = (char *)malloc(sizeof(char)*1024*80);
    if(p2== NULL)
    {
        printf("free error\r\n");
    }
    else
    {
        printf("free succsess p = %x \r\n" , (unsigned int)p2);
    }

    free(p2);
}

//void newdeletetest(void)
//{
//  int *p = new int(1024);
//  if(p== NULL)
//  {
//      printf("new error \r\n");
//  }
//  else
//  {
//      printf("new succsess p=%x \r\n" , p);
//  }

//  delete p;

//  if(p== NULL)
//  {
//      printf("delete succsess \r\n");
//  }
//  else
//  {
//      printf("delete error p=%x \r\n" , p);
//  }
//}


int main(void)
{

    board = Board();
    board.boardBasicInit();

    printf("welcome to handsfree \r\n");

    mallcotest();
    //  newdeletetest();

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
            board.boardBasicCall();   // need time stm32f1  35us
        }
        if ( board.cnt_20ms >= 20 )  // 50hz
        {
            board.cnt_20ms = 0 ;

        }
        if ( board.cnt_50ms >= 50 )  // 20hz
        {
            board.cnt_50ms = 0 ;
            board.setLedState(0,2);
        }
    }

}
