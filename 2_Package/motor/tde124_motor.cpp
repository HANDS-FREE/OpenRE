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
* Description: The file defined a Class for motor control ， you can use it Conveniently and modify a litter
*              for a different circuit board
***********************************************************************************************************************/

#include "tde124_motor.h"
#include "board.h"

#define MOTOR_MAXSPEED 2160

typedef struct{
    uint16_t position;//电机当前位置 0 ~ 65535
    uint16_t pos_last;//电机上次计数位置值 0 ~ 65535
    float speed;//电调当前速度值，放大100倍，单位rpm
    float current;//电调当前的电流标幺值，放大100倍
    uint8_t tmp;//电机当前温度值，单位摄氏度
    uint8_t throttle;//电调油门百分比
    uint8_t state;//电调状态，0：正常
}ESC_INF;

typedef struct{
    uint16_t stdid;//电调的标准帧ID
    uint8_t txd[8];//发送数据缓存
    uint8_t rxd[8];//接收数据缓存
}CAN_DATA;

ESC_INF motor[4];
CAN_DATA tx,rx;

extern "C" {

unsigned char can_rx_cnt = 0;
int can_rx_cnt_filter = 0;

#ifdef __STM32F4xx_CONF_H
void CAN2_RX0_IRQHandler(void)
{
#if SYSTEM_SUPPORT_OS == 1
    OSIntEnter();
#endif
    if (CAN_GetITStatus(CAN2,CAN_IT_FMP0)!= RESET)
    {
        CanRxMsg RxMessage;
        RxMessage.StdId=0x0000;
        RxMessage.ExtId=0x0000;
        RxMessage.IDE=0;
        RxMessage.DLC=0;
        RxMessage.FMI=0;

        CAN_Receive(CAN2, CAN_FIFO0, &RxMessage);

        if(can_rx_cnt_filter <= 500) //about 1S
        {
            can_rx_cnt_filter++;
            return;
        }

        rx.stdid = RxMessage.StdId;
        unsigned char esc_id = rx.stdid - 0x401;
        for(unsigned char i=0;i<8;i++)
            rx.rxd[i]=RxMessage.Data[i];

        if(rx.rxd[0]==0xFF&&rx.rxd[1]==0xFF&&rx.rxd[2]==0xFF&&rx.rxd[3]==0xFF
                &&rx.rxd[4]==0xFF&&rx.rxd[5]==0xFF&&rx.rxd[6]==0xFF)
            motor[esc_id].state=rx.rxd[7];
        else
        {
            motor[esc_id].position = (int16_t)(rx.rxd[1]<<8 | rx.rxd[0]) ;
            motor[esc_id].speed  = -(int16_t)(rx.rxd[3]<<8 | rx.rxd[2])*0.01f;
            motor[esc_id].current = (rx.rxd[5]<<8 | rx.rxd[4])*0.01f;
            motor[esc_id].tmp = rx.rxd[6];
            motor[esc_id].throttle=rx.rxd[7];
        }

        static int i=0;
        i++;
        if(i>=100)
        {
            i=0;
            Board::getInstance()->setLedState(2,2);
        }

        //Board::getInstance()->setBeepTweet(10);
        //printf("CAN2 IRQHandler Receive Data: %s \r\n",RxMessage.Data);
        //printf("ID = %x \r\n",rx.stdid);

        CAN_ClearITPendingBit(CAN2, CAN_IT_FMP0);
    }
    NVIC_ClearPendingIRQ(CAN2_RX0_IRQn);
#if SYSTEM_SUPPORT_OS == 1
    OSIntExit();
#endif
}
#endif

}

void TDE124Motors::init(RobotAbstract *robot_)
{
    para = &robot_->para.motor_para;
    motors = &robot_->motors;
    sensors = &robot_->sensors;

    HF_CAN_Init(2 , 1 , CAN_Mode_Normal , CAN_SJW_1tq , CAN_BS1_9tq , CAN_BS2_4tq , 3);

    motors->m1.mode_state = 1;
    motors->m2.mode_state = 1;
    motors->m3.mode_state = 1;
    motors->m4.mode_state = 1;

    setMode(0,motors->m1.mode_state);
}

void TDE124Motors::loopCall(void)
{
    //motors->m1.past_total_angle = motor[0].position * ;
    motors->m1.measure_angle_speed = motor[0].speed * 6;
    motors->m1.motor_current = motor[0].current;

    motors->m2.measure_angle_speed = motor[1].speed * 6;
    motors->m2.motor_current = motor[1].current;

    motors->m3.measure_angle_speed = motor[2].speed * 6;
    motors->m3.motor_current = motor[2].current;

    motors->m4.measure_angle_speed = motor[3].speed * 6;
    motors->m4.motor_current = motor[3].current;
}

void TDE124Motors::setMode(unsigned char motor_id_, unsigned char mode_)
{
    uint8_t i;
    switch(mode_)
    {
    case 1:	tx.stdid = 0x3FF;break;  //Speed Loop
    case 2:	tx.stdid = 0x400;break;  //Current Loop
    case 3:	tx.stdid = 0x3FE;break;  //Position Loop
    default:;break;
    }
    for(i=0;i<8;i++)
        tx.txd[i]=0x00;

    can_send_tx_data();
}

void TDE124Motors::controlEnable(unsigned char motor_id_)
{
    tx.stdid=0x600;
    tx.txd[0]=motor_id_;
    tx.txd[1]=0x00;
    tx.txd[2]=0x88;
    tx.txd[3]=0x00;

    can_send_tx_data();
}

void TDE124Motors::controlDisable(unsigned char motor_id_)
{
    tx.stdid=0x600;
    tx.txd[0]=motor_id_;
    tx.txd[1]=0x00;
    tx.txd[2]=0xCC;
    tx.txd[3]=0x00;

    can_send_tx_data();
}

void TDE124Motors::setAngleSpeed(unsigned char motor_id_ , float expect_angle_speed_)
{
    if(expect_angle_speed_ > MOTOR_MAXSPEED) expect_angle_speed_ = MOTOR_MAXSPEED;
    if(expect_angle_speed_ < -MOTOR_MAXSPEED) expect_angle_speed_ = -MOTOR_MAXSPEED;

    if(motors->m1.stop_fault_motor || motors->m2.stop_fault_motor)
    {
        expect_angle_speed_ = 0;
    }

    uint8_t spd_L,spd_H;
    int16_t spd_ref;
    spd_ref= - (int16_t)(expect_angle_speed_ * 5.0f / 6.0); //rpm
    spd_L=(spd_ref&0x00FF);
    spd_H=(spd_ref>>8);
    tx.stdid=0x3FF;

    switch(motor_id_)
    {
    case 0:
        tx.txd[0]=spd_L;
        tx.txd[1]=spd_H;
        tx.txd[2]=spd_L;
        tx.txd[3]=spd_H;
        tx.txd[4]=spd_L;
        tx.txd[5]=spd_H;
        tx.txd[6]=spd_L;
        tx.txd[7]=spd_H;
        break;
    case 1:
        tx.txd[0]=spd_L;
        tx.txd[1]=spd_H;
        break;
    case 2:
        tx.txd[2]=spd_L;
        tx.txd[3]=spd_H;
        break;
    case 3:
        tx.txd[4]=spd_L;
        tx.txd[5]=spd_H;
        break;
    case 4:
        tx.txd[6]=spd_L;
        tx.txd[7]=spd_H;
        break;
    default:;break;
    }

    can_send_tx_data();
}

float TDE124Motors::getAngleSpeed(unsigned char motor_id_){
    if(motor_id_ == 1)
    {
        return motors->m1.measure_angle_speed;
    }
    if(motor_id_ == 2)
    {
        return motors->m2.measure_angle_speed;
    }
    if(motor_id_ == 3)
    {
        return motors->m3.measure_angle_speed;
    }
    if(motor_id_ == 4)
    {
        return motors->m4.measure_angle_speed;
    }
    return 0;
}

float TDE124Motors::getDPastAngel(unsigned char motor_id_){
    motor_id_--;

    float delta=motor[motor_id_].position - motor[motor_id_].pos_last;
    if(delta < -32768.0)  delta = delta + 65536;
    if(delta > 32768.0) delta = delta - 65536;
    motor[motor_id_].pos_last=motor[motor_id_].position;

    delta = delta * 360 / 65536.0;

    if(delta > 200) delta =0;
    if(delta < -200) delta =0;
    return -delta;
}

void TDE124Motors::clear_the_alarm(unsigned char channel)
{

}

void TDE124Motors::can_send_tx_data(void)
{
    HF_CANTX_Message(2,tx.stdid,0,tx.txd,8);
    Board::getInstance()->setLedState(3,2);
}
