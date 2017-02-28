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
#include "os_include.h"
#include "libs_include.h"

#define START_TASK_PRIO			10  
#define START_STK_SIZE			512
OS_STK START_TASK_STK[START_STK_SIZE];
void start_task(void *pdata);

#define LED0_TASK_PRIO			7
#define LED0_STK_SIZE			  512
OS_STK LED0_TASK_STK[LED0_STK_SIZE];
void led0_task(void *pdata);

#define BEEP_TASK_PRIO			6
#define BEEP_STK_SIZE			  512
OS_STK BEEP_TASK_STK[BEEP_STK_SIZE];
void beep_task(void *pdata);

#define FLOAT_TASK_PRIO			5
#define FLOAT_STK_SIZE			512
//如果任务中使用printf来打印浮点数据的话一点要8字节对齐
__attribute((aligned (8)))  OS_STK FLOAT_TASK_STK[FLOAT_STK_SIZE];
void float_task(void *pdata);

int main(void)
{
    Board *board = Board::getInstance();
    board->boardBasicInit();

    printf("app start \r\n");

    OSInit();
    //Create start task
    OSTaskCreate(start_task,(void *)0,(OS_STK *)&START_TASK_STK[START_STK_SIZE-1],START_TASK_PRIO );
    OSStart();
}

void start_task(void *pdata)
{
    OS_CPU_SR cpu_sr=0;
    pdata = pdata;
    OSStatInit();          //开启统计任务
    OS_ENTER_CRITICAL();   //进入临界区(无法被中断打断)
    OSTaskCreate(led0_task,(void *)0,(OS_STK*)&LED0_TASK_STK[LED0_STK_SIZE-1],LED0_TASK_PRIO);	  //Create led0 task
    OSTaskCreate(beep_task,(void *)0,(OS_STK*)&BEEP_TASK_STK[BEEP_STK_SIZE-1],BEEP_TASK_PRIO);	  //Create beep task
    OSTaskCreate(float_task,(void*)0,(OS_STK*)&FLOAT_TASK_STK[FLOAT_STK_SIZE-1],FLOAT_TASK_PRIO); //Create float test task
    OSTaskSuspend(START_TASK_PRIO);	//挂起起始任务.
    OS_EXIT_CRITICAL();				//退出临界区(可以被中断打断)
}

void led0_task(void *pdata)
{	 	
    Board *board = Board::getInstance();

    while(1)
    {
        board->setLedState(0,0);
        OSTimeDlyHMSM (0 , 0 , 0 , 80);
        board->setLedState(0,1);
        OSTimeDlyHMSM (0 , 0 , 0 , 150);
    };
}

void beep_task(void *pdata)
{	  
    Board *board = Board::getInstance();

    while(1)
    {
        board->setBeepState(0);
        OSTimeDlyHMSM (0 , 0 , 0 , 500);
        board->setBeepState(1);
        OSTimeDlyHMSM (0 , 0 , 0 , 500);
    };
}

void float_task(void *pdata)
{
    OS_CPU_SR cpu_sr=0;
    static float float_num=0.01;
    while(1)
    {
        float_num+=0.01f;
        OS_ENTER_CRITICAL();
        printf("float_num is: %.4f\r\n",float_num);
        OS_EXIT_CRITICAL();
        OSTimeDlyHMSM (0 , 0 , 0 , 500);
    }
}

