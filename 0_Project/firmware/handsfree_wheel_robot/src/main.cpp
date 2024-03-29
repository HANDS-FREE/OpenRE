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
    RobotModel robot_model;

    Board *board = Board::getInstance();
    board->boardBasicInit();
    //set battery low voltage alarm
    board->setBatteryPara(robot_model.system_para.battery_series , robot_model.system_para.battery_voltage_alarm_);

    RobotAbstract robot;
    robot.para = robot_model;
    RobotControl *robot_control_p = RobotControl::getInstance();
    robot_control_p->init(&robot);

    //SBUS sbus_node(USART_SBUS);
    //robot_control_p->setSBUSRemoteNodePointer(&sbus_node);

    RoboLink robolink_pc_node(&robot , 0x11 , 0x01 , (unsigned char)USART_PC);
    robot_control_p->setRobolinkNodePointer(&robolink_pc_node);

    //RoboLink robolink_radio_node(&robot , 0x11 , 0x01 , (unsigned char)USART_RADIO,115200);
    //robot_control_p->setRobolinkRadioNodePointer(&robolink_radio_node);

    Sensors *sensors = Sensors::getInstance();
    sensors->init(&robot);

    printf("app start \r\n");

    while(1)
    {
        //if(robot_control_p->sbus_node && (!board->usartDeviceReadData(robot_control_p->sbus_node_device)->emptyCheck()))
        //{
        //    robot_control_p->sbus_node->receiveByteAnlState(
        //                board->usartDeviceReadData(robot_control_p->sbus_node_device)->getData()
        //                );
        //}

        if(robot_control_p->robolink_node && (!board->usartDeviceReadData(robot_control_p->robolink_node_device)->emptyCheck()))
        {
            robot_control_p->robolink_node->byteAnalysisCall(
                        board->usartDeviceReadData(robot_control_p->robolink_node_device)->getData()
                        );
        }

        //if(robot_control_p->robolink_radio_node && (!board->usartDeviceReadData(robot_control_p->robolink_radio_node_device)->emptyCheck()))
        //{
        //    robot_control_p->robolink_radio_node->byteAnalysisCall(
        //                board->usartDeviceReadData(robot_control_p->robolink_radio_node_device)->getData()
        //                );
        //}

        if ( board->cnt_1ms >= 1 )      // 1000hz
        {
            board->cnt_1ms=0;
            sensors->loopCall();        //need time: 400us~1700us(stm32f4 nofpu)
        }
        if ( board->cnt_2ms >= 2 )      // 500hz
        {
            board->cnt_2ms=0;
        }
        if ( board->cnt_5ms >= 5 )      // 200hz
        {
            board->cnt_5ms=0;
            robot_control_p->motor_top.loopCall(); //need time: 70us(stm32f1) 32us(stm32f4 nofpu)
        }
        if ( board->cnt_10ms >= 10 )    // 100hz
        {
            board->cnt_10ms=0;
            board->boardBasicCall();    //need time: 35us(stm32f1) 7us(stm32f4 nofpu)
        }
        if ( board->cnt_20ms >= 20 )    // 50hz
        {
            board->cnt_20ms = 0 ;
        }
        if ( board->cnt_50ms >= 50 )    // 20hz
        {
            board->cnt_50ms = 0 ;
            robot_control_p->loopCall();  //need time:280(stm32f1) 70us(stm32f4 nofpu)
            board->setLedState(1,2);
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
