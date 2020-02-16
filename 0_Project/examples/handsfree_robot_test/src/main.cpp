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
#include "robot_control.h"
#include "robot_model.h"
#include "sensors.h"

int main(void)
{
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

    Sensors sensors;
    sensors.init(&robot);

    printf("app start \r\n");

    while(1)
    {
        if(robot_control_p->sbus_node && (!board->usartDeviceReadData(robot_control_p->sbus_node_device)->emptyCheck()))
        {
            robot_control_p->sbus_node->receiveByteAnlState(
                        board->usartDeviceReadData(robot_control_p->sbus_node_device)->getData()
                        );
        }
        if(robot_control_p->robolink_node && (!board->usartDeviceReadData(robot_control_p->robolink_node_device)->emptyCheck()))
        {
            robot_control_p->robolink_node->byteAnalysisCall(
                        board->usartDeviceReadData(robot_control_p->robolink_node_device)->getData()
                        );
        }
        if(robot_control_p->robolink_radio_node && (!board->usartDeviceReadData(robot_control_p->robolink_radio_node_device)->emptyCheck()))
        {
            robot_control_p->robolink_radio_node->byteAnalysisCall(
                        board->usartDeviceReadData(robot_control_p->robolink_radio_node_device)->getData()
                        );
        }

        if ( board->cnt_1ms >= 1 )      // 1000hz
        {
            board->cnt_1ms=0;
            //imu.topCall();
        }
        if ( board->cnt_2ms >= 2 )      // 500hz
        {
            board->cnt_2ms=0;
        }
        if ( board->cnt_5ms >= 5 )      // 200hz
        {
            board->cnt_5ms=0;
            robot_control_p->motor_top.loopCall(); //motor speed control
            sensors.loopCall();
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
            robot_control_p->robot_test();
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
