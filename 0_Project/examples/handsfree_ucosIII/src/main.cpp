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
#include "os_include.h"

#define START_TASK_PRIO		3	
#define START_STK_SIZE 		512
OS_TCB StartTaskTCB;
CPU_STK START_TASK_STK[START_STK_SIZE];
void start_task(void *p_arg);

#define LED0_TASK_PRIO		4
#define LED0_STK_SIZE 		256
OS_TCB Led0TaskTCB;
CPU_STK LED0_TASK_STK[LED0_STK_SIZE];
void led0_task(void *p_arg);

#define BEPP_TASK_PRIO		5
#define BEPP_STK_SIZE 		256
OS_TCB Led1TaskTCB;
CPU_STK BEPP_TASK_STK[BEPP_STK_SIZE];
void beep_task(void *p_arg);

#define FLOAT_TASK_PRIO		6
#define FLOAT_STK_SIZE		256
OS_TCB	FloatTaskTCB;
__attribute((aligned (8))) CPU_STK	FLOAT_TASK_STK[FLOAT_STK_SIZE];
void float_task(void *p_arg);


int main(void)
{
    OS_ERR err;
    CPU_SR_ALLOC();

    Board *board = Board::getInstance();
    board->boardBasicInit();

    printf("app start \r\n");

    OSInit(&err);
    OS_CRITICAL_ENTER();//进入临界区
    //Create start task
    OSTaskCreate((OS_TCB 	* )&StartTaskTCB,		  //任务控制块
                 (CPU_CHAR	* )"start task", 		  //任务名字
                 (OS_TASK_PTR )start_task, 		      //任务函数
                 (void		* )0,					  //传递给任务函数的参数
                 (OS_PRIO	  )START_TASK_PRIO,       //任务优先级
                 (CPU_STK   * )&START_TASK_STK[0],	  //任务堆栈基地址
            (CPU_STK_SIZE)START_STK_SIZE/10,	  //任务堆栈深度限位
            (CPU_STK_SIZE)START_STK_SIZE,		  //任务堆栈大小
            (OS_MSG_QTY  )0,					  //任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
            (OS_TICK	  )0,					  //当使能时间片轮转时的时间片长度，为0时为默认长度，
            (void   	* )0,				      //用户补充的存储区
            (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,  //任务选项
            (OS_ERR 	* )&err);				   //存放该函数错误时的返回值
    OS_CRITICAL_EXIT();	 //退出临界区
    OSStart(&err);       //开启UCOSIII

    while(1);
}

void start_task(void *p_arg)
{

    OS_ERR err;
    CPU_SR_ALLOC();
    p_arg = p_arg;
    CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u
    OSStatTaskCPUUsageInit(&err);  	//统计任务
#endif

#ifdef CPU_CFG_INT_DIS_MEAS_EN		  //如果使能了测量中断关闭时间
    CPU_IntDisMeasMaxCurReset();
#endif

#if	OS_CFG_SCHED_ROUND_ROBIN_EN   //当使用时间片轮转的时候
    //使能时间片轮转调度功能,时间片长度为1个系统时钟节拍，既1*5=5ms
    OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);
#endif		

    OS_CRITICAL_ENTER();

    OSTaskCreate((OS_TCB 	* )&Led0TaskTCB,
                 (CPU_CHAR	* )"led0 task",
                 (OS_TASK_PTR )led0_task,
                 (void		* )0,
                 (OS_PRIO	  )LED0_TASK_PRIO,
                 (CPU_STK   * )&LED0_TASK_STK[0],
            (CPU_STK_SIZE)LED0_STK_SIZE/10,
            (CPU_STK_SIZE)LED0_STK_SIZE,
            (OS_MSG_QTY  )0,
            (OS_TICK	  )0,
            (void   	* )0,
            (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
            (OS_ERR 	* )&err);


    OSTaskCreate((OS_TCB 	* )&Led1TaskTCB,
                 (CPU_CHAR	* )"beep task",
                 (OS_TASK_PTR )beep_task,
                 (void		* )0,
                 (OS_PRIO	  )BEPP_TASK_PRIO,
                 (CPU_STK   * )&BEPP_TASK_STK[0],
            (CPU_STK_SIZE)BEPP_STK_SIZE/10,
            (CPU_STK_SIZE)BEPP_STK_SIZE,
            (OS_MSG_QTY  )0,
            (OS_TICK	  )0,
            (void   	* )0,
            (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
            (OS_ERR 	* )&err);

    OSTaskCreate((OS_TCB 	* )&FloatTaskTCB,
                 (CPU_CHAR	* )"float test task",
                 (OS_TASK_PTR )float_task,
                 (void		* )0,
                 (OS_PRIO	  )FLOAT_TASK_PRIO,
                 (CPU_STK   * )&FLOAT_TASK_STK[0],
            (CPU_STK_SIZE)FLOAT_STK_SIZE/10,
            (CPU_STK_SIZE)FLOAT_STK_SIZE,
            (OS_MSG_QTY  )0,
            (OS_TICK	  )0,
            (void   	* )0,
            (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
            (OS_ERR 	* )&err);

    OS_TaskSuspend((OS_TCB*)&StartTaskTCB,&err);		//挂起开始任务

    OS_CRITICAL_EXIT();
}


void led0_task(void *p_arg)
{
    OS_ERR err;
    p_arg = p_arg;
    Board *board = Board::getInstance();

    while(1)
    {
        board->setLedState(0,0);
        OSTimeDlyHMSM(0,0,0,200,OS_OPT_TIME_HMSM_STRICT,&err); //delay 200ms
        board->setLedState(0,1);
        OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&err); //delay 500ms
    }
}

void beep_task(void *p_arg)
{
    OS_ERR err;
    p_arg = p_arg;
    Board *board = Board::getInstance();

    while(1)
    {
        board->setBeepState(1);
        OSTimeDlyHMSM(0,0,0,200,OS_OPT_TIME_HMSM_STRICT,&err);
        board->setBeepState(0);
        OSTimeDlyHMSM(0,0,0,800,OS_OPT_TIME_HMSM_STRICT,&err);
        board->setBeepState(1);
        OSTimeDlyHMSM(0,0,0,800,OS_OPT_TIME_HMSM_STRICT,&err);
        board->setBeepState(0);
        OSTimeDlyHMSM(0,0,0,800,OS_OPT_TIME_HMSM_STRICT,&err);
    }
}

void float_task(void *p_arg)
{
    OS_ERR err;
    p_arg = p_arg;
    static float float_num=0.01;
    CPU_SR_ALLOC();

    while(1)
    {
        float_num+=0.01f;
        OS_CRITICAL_ENTER();
        printf("float_num is: %.4f \r\n", float_num);
        OS_CRITICAL_EXIT();
        OSTimeDlyHMSM(0,0,0,100,OS_OPT_TIME_HMSM_STRICT,&err); //delay 500ms
    }
}
