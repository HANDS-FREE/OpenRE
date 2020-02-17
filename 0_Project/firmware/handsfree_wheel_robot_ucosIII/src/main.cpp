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

#include "board.h"
#include "os_include.h"
#include "robot_control.h"
#include "robot_model.h"


#define START_TASK_PRIO		3
#define START_TASK_STK_SIZE 		512
OS_TCB  START_TASK_TCB;
CPU_STK START_TASK_STK[START_TASK_STK_SIZE];
void start_task(void *p_arg);

#define BSP_TASK_PRIO		4
#define BSP_TASK_STK_SIZE 		256
OS_TCB  BSP_TASK_TCB;
CPU_STK BSP_TASK_STK[BSP_TASK_STK_SIZE];
void bsp_task(void *p_arg);

#define MOTOR_TASK_PRIO		5
#define MOTOR_TASK_STK_SIZE 		256
OS_TCB  MOTOR_TASK_TCB;
CPU_STK MOTOR_TASK_STK[MOTOR_TASK_STK_SIZE];
void motor_task(void *p_arg);

#define ROBOT_WHEEL_TASK_PRIO		6
#define ROBOT_WHEEL_TASK_STK_SIZE 		512
OS_TCB  ROBOT_WHEEL_TASK_TCB;
__attribute((aligned (8))) CPU_STK ROBOT_WHEEL_TASK_STK[ROBOT_WHEEL_TASK_STK_SIZE];
void robot_wheel_task(void *p_arg);

#define IMU_TASK_PRIO		7
#define IMU_TASK_STK_SIZE 		256
OS_TCB  IMU_TASK_TCB;
CPU_STK IMU_TASK_STK[IMU_TASK_STK_SIZE];
void imu_task(void *p_arg);

#define HF_LINK_TASK_PRIO		8
#define HF_LINK_TASK_STK_SIZE 		256
OS_TCB  HF_LINK_TASK_TCB;
CPU_STK HF_LINK_TASK_STK[HF_LINK_TASK_STK_SIZE];
void hf_link_task(void *p_arg);


int main(void)
{
    OS_ERR err;
    CPU_SR_ALLOC();

    Board *board = Board::getInstance();
    board->boardBasicInit();

    RobotModel robot_model;
    RobotAbstract robot;
    robot.para = robot_model;
    RobotControl *robot_control_p = RobotControl::getInstance();
    robot_control_p->init(&robot);

    SBUS sbus_node(USART_SBUS);
    robot_control_p->setSBUSRemoteNodePointer(&sbus_node);

    RoboLink robolink_pc_node(&robot , 0x11 , 0x01 , (unsigned char)USART_PC);
    robot_control_p->setRobolinkNodePointer(&robolink_pc_node);

    RoboLink robolink_radio_node(&robot , 0x11 , 0x01 , (unsigned char)USART_RADIO,115200);
    robot_control_p->setRobolinkRadioNodePointer(&robolink_radio_node);

    printf("app start \r\n");

    OSInit(&err);
    OS_CRITICAL_ENTER();//进入临界区
    //Create start task
    OSTaskCreate((OS_TCB 	* )&START_TASK_TCB,		  //任务控制块
                 (CPU_CHAR	* )"start task", 		      //任务名字
                 (OS_TASK_PTR )start_task, 		//任务函数
                 (void		* )0,					      //传递给任务函数的参数
                 (OS_PRIO	  )START_TASK_PRIO,       //任务优先级
                 (CPU_STK   * )&START_TASK_STK[0],	//任务堆栈基地址
            (CPU_STK_SIZE)START_TASK_STK_SIZE/10,	  //任务堆栈深度限位
            (CPU_STK_SIZE)START_TASK_STK_SIZE,		  //任务堆栈大小
            (OS_MSG_QTY  )0,					   //任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
            (OS_TICK	  )0,					     //当使能时间片轮转时的时间片长度，为0时为默认长度，
            (void   	* )0,				       //用户补充的存储区
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
    //使能时间片轮转调度功能,时间片长度为1个系统时钟节拍
    OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);
#endif

    OS_CRITICAL_ENTER();

    OSTaskCreate((OS_TCB 	* )&BSP_TASK_TCB,
                 (CPU_CHAR	* )"bsp task",
                 (OS_TASK_PTR )bsp_task,
                 (void		* )0,
                 (OS_PRIO	  )BSP_TASK_PRIO,
                 (CPU_STK   * )&BSP_TASK_STK[0],
            (CPU_STK_SIZE)BSP_TASK_STK_SIZE/10,
            (CPU_STK_SIZE)BSP_TASK_STK_SIZE,
            (OS_MSG_QTY  )0,
            (OS_TICK	  )0,
            (void   	* )0,
            (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
            (OS_ERR 	* )&err);


    OSTaskCreate((OS_TCB 	* )&MOTOR_TASK_TCB,
                 (CPU_CHAR	* )"motor task",
                 (OS_TASK_PTR )motor_task,
                 (void		* )0,
                 (OS_PRIO	  )MOTOR_TASK_PRIO,
                 (CPU_STK   * )&MOTOR_TASK_STK[0],
            (CPU_STK_SIZE)MOTOR_TASK_STK_SIZE/10,
            (CPU_STK_SIZE)MOTOR_TASK_STK_SIZE,
            (OS_MSG_QTY  )0,
            (OS_TICK	  )0,
            (void   	* )0,
            (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
            (OS_ERR 	* )&err);


    OSTaskCreate((OS_TCB 	* )&ROBOT_WHEEL_TASK_TCB,
                 (CPU_CHAR	* )"robot_wheel task",
                 (OS_TASK_PTR )robot_wheel_task,
                 (void		* )0,
                 (OS_PRIO	  )ROBOT_WHEEL_TASK_PRIO,
                 (CPU_STK   * )&ROBOT_WHEEL_TASK_STK[0],
            (CPU_STK_SIZE)ROBOT_WHEEL_TASK_STK_SIZE/10,
            (CPU_STK_SIZE)ROBOT_WHEEL_TASK_STK_SIZE,
            (OS_MSG_QTY  )0,
            (OS_TICK	  )0,
            (void   	* )0,
            (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
            (OS_ERR 	* )&err);

    OSTaskCreate((OS_TCB 	* )&IMU_TASK_TCB,
                 (CPU_CHAR	* )"imu task",
                 (OS_TASK_PTR )imu_task,
                 (void		* )0,
                 (OS_PRIO	  )IMU_TASK_PRIO,
                 (CPU_STK   * )&IMU_TASK_STK[0],
            (CPU_STK_SIZE)IMU_TASK_STK_SIZE/10,
            (CPU_STK_SIZE)IMU_TASK_STK_SIZE,
            (OS_MSG_QTY  )0,
            (OS_TICK	  )0,
            (void   	* )0,
            (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
            (OS_ERR 	* )&err);

    OSTaskCreate((OS_TCB 	* )&HF_LINK_TASK_TCB,
                 (CPU_CHAR	* )"hf_link task",
                 (OS_TASK_PTR )hf_link_task,
                 (void		* )0,
                 (OS_PRIO	  )HF_LINK_TASK_PRIO,
                 (CPU_STK   * )&HF_LINK_TASK_STK[0],
            (CPU_STK_SIZE)HF_LINK_TASK_STK_SIZE/10,
            (CPU_STK_SIZE)HF_LINK_TASK_STK_SIZE,
            (OS_MSG_QTY  )0,
            (OS_TICK	  )0,
            (void   	* )0,
            (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
            (OS_ERR 	* )&err);

    OS_TaskSuspend((OS_TCB*)&START_TASK_TCB,&err);		//挂起开始任务

    OS_CRITICAL_EXIT();
}

void bsp_task(void *p_arg)
{
    OS_ERR err;
    p_arg = p_arg;
    float bsp_task_i=0;
    Board *board = Board::getInstance();

    while(1)
    {
        bsp_task_i++;
        board->boardBasicCall();            // need time stm32f1  35us
        if(bsp_task_i >= 5)
        {
            bsp_task_i=0;
            board->setLedState(1,2);
        }
        OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err); //delay 10ms   100hz
    }
}

void motor_task(void *p_arg)
{
    OS_ERR err;
    p_arg = p_arg;
    RobotControl *robot_control_p = RobotControl::getInstance();

    while(1)
    {
        robot_control_p->motor_top.loopCall(); //motor speed control
        OSTimeDlyHMSM(0,0,0,5,OS_OPT_TIME_HMSM_STRICT,&err); //delay 5ms 200hz
    }
}

void robot_wheel_task(void *p_arg)
{

    OS_ERR err;
    //CPU_SR_ALLOC();
    p_arg = p_arg;
    RobotControl *robot_control_p = RobotControl::getInstance();

    while(1)
    {
        robot_control_p->loopCall();

        //       OS_CRITICAL_ENTER();
        //        printf("battery_voltage = %.4f  cpu_usage = %.4f cpu_temperature = %.4f\r\n",
        //               board.battery_voltage , board.cpu_usage , board.cpu_temperature
        //               );
        //        OS_CRITICAL_EXIT();

        OSTimeDlyHMSM(0,0,0,50,OS_OPT_TIME_HMSM_STRICT,&err); //delay 50ms  20hz
    }
}

void imu_task(void *p_arg)
{
    OS_ERR err;
    //CPU_SR_ALLOC();
    p_arg = p_arg;

    while(1)
    {
        //imu.topCall();
        OSTimeDly(1,OS_OPT_TIME_PERIODIC,&err);
        //OSTimeDlyHMSM(0,0,0,1,OS_OPT_TIME_HMSM_STRICT,&err); //delay 1ms  1000hz
    }
}

void hf_link_task(void *p_arg)
{
    OS_ERR err;
    p_arg = p_arg;
    RobotControl *robot_control_p = RobotControl::getInstance();
    Board *board = Board::getInstance();

    while(1)
    {
        if(board->usartDeviceReadData(robot_control_p->robolink_node_device)->emptyCheck() == 0){
            robot_control_p->robolink_node->byteAnalysisCall(
                        board->usartDeviceReadData(
                            robot_control_p->robolink_node_device)->getData() );
        }
        else {
            OSTimeDlyHMSM(0,0,0,5,OS_OPT_TIME_HMSM_STRICT,&err); //delay 5ms 200hz
        }
    }
}
