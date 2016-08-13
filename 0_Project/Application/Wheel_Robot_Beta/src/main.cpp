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
*s
* Description:   
***********************************************************************************************************************/

#include "main_includes.h"

void constructorInit(void)
{
    board = Board();
    my_robot = RobotAbstract();
    motor_top = MotorTop();
    robot_head = HeadAX();
    hands_free_robot = RobotWheel();
    sbus = SBUS();
    imu = IMU();
    usart1_queue = Queue();
    hf_link_pc_node =  HFLink(0x11,0x01,&my_robot);
    hf_link_node_pointer=&hf_link_pc_node;
}

void systemInit(void)
{
    //SCB->VTOR = FLASH_BASE | 0x10000;  //Bootloader
    //INTX_DISABLE();  //close all interruption
    board.boardBasicInit();
    motor_top.motorTopInit(3 , 1560 , 0.02 , 0);
    robot_head.axServoInit();
    hands_free_robot.robotWheelTopInit();
    sbus.sbusInit();
    imu.topInit(1,0,1,1,0,1);
    //INTX_ENABLE();	 //enable all interruption
    printf("app start \r\n");
}

int main(void)
{
    constructorInit();
    systemInit();

    while(1)
    {

        if(usart1_queue.emptyCheck()==0){
            hf_link_pc_node.byteAnalysisCall(usart1_queue.getData());
        }
        if ( board.cnt_1ms >= 1 )      // 1000hz
        {
            board.cnt_1ms=0;
            imu.topCall();             // stm32f4 -- 631us(fpu)
        }
        if ( board.cnt_2ms >= 2 )      // 500hz
        {
            board.cnt_2ms=0;
        }
        if ( board.cnt_5ms >= 5 )      // 200hz
        {
            board.cnt_5ms=0;
        }
        if ( board.cnt_10ms >= 10 )    // 100hz
        {
            board.cnt_10ms=0;
            board.boardBasicCall();    // need time stm32f1  35us
        }
        if ( board.cnt_20ms >= 20 )    // 50hz
        {
            board.cnt_20ms = 0 ;
            board.motorEnable(0);
            board.motorSetPWM(1,2000);
            //motor_top.motorTopCall();  //motor speed control
        }
        if ( board.cnt_50ms >= 50 )    // 20hz
        {
            board.cnt_50ms = 0 ;
            robot_head.headTopCall();
           // hands_free_robot.robotWheelTopCall(); //robot control interface
            board.setLedState(0,2);
        }

    }

    return 0;
}


