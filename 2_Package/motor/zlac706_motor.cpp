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

#include "zlac706_motor.h"
#include "board.h"

#define MOTOR1_USART 2
#define MOTOR2_USART 4
#define MOTOR_MAXSPEED 1080

void ZLAC706Motors::init(RobotAbstract *robot_)
{
    para = &robot_->para.motor_para;
    motors = &robot_->motors;
    sensors = &robot_->sensors;

    HF_USART_Init(MOTOR1_USART,57600,0);
    HF_USART_Init(MOTOR2_USART,57600,0);
    //motor_int_speed_mode();
    motors->m1.mode_state = 1;
    motors->m2.mode_state = 1;

    motor1_queue = Board::getInstance()->getUsartQueue(MOTOR1_USART);
    motor2_queue = Board::getInstance()->getUsartQueue(MOTOR2_USART);
}

void ZLAC706Motors::loopCall(void)
{
    unsigned char check_sum=0;
    short int data_=0;

    //motor error eliminate
    if(motors->m1.online_state == 1 && motors->m2.online_state == 1 && motors->m1.stop_fault_motor == 0 &&
            motors->m2.stop_fault_motor == 0 && motors->m1.mode_state == 1 && ( ((motors->m1.fault_state & 0x01) == 0) ||
                                                                                ((motors->m2.fault_state & 0x01) == 0)) )
    {
        motor_error_detect_cnt1_++;
        if(motor_error_detect_cnt1_ > 1/para->pid_t) //1s
        {
            motor_error_detect_cnt1_ = 0;
            Board::getInstance()->setBeepTweet(200);
            setMode(0,1);
        }
    }
    else{
        motor_error_detect_cnt1_ = 0;
    }

    if(motors->m1.online_state == 1 && motors->m2.online_state == 1 && motors->m1.stop_fault_motor == 0 &&
            motors->m2.stop_fault_motor == 0 && motors->m1.mode_state == 0 && ( ((motors->m1.fault_state & 0x01) == 1) ||
                                                                                ((motors->m2.fault_state & 0x01) == 1)))
    {
        motor_error_detect_cnt2_++;
        if(motor_error_detect_cnt2_ > 1/para->pid_t) //1s
        {
            motor_error_detect_cnt2_ = 0;
            Board::getInstance()->setBeepTweet(200);
            setMode(0,0);
        }
    }
    else {
        motor_error_detect_cnt2_ = 0;
    }

    //motor online detect
    if(motor1_connect_quality < 30)  //off line
    {
        motors->m1.online_state = 0;
        motor1_connect_quality =5;
        motors->m1.motor_voltage = 0;
        motors->m1.motor_current = 0;
        motors->m1.measure_angle_speed = 0;
    }
    if(motor2_connect_quality < 30)  //off line
    {
        motors->m2.online_state = 0;
        motor2_connect_quality =5;
        motors->m2.motor_voltage = 0;
        motors->m2.motor_current = 0;
        motors->m2.measure_angle_speed = 0;
    }

    if(motors->m1.online_state == 0 && motor1_connect_quality >80)//SPEED_MODE
    {
        motors->m1.online_state = 1;
        Board::getInstance()->setBeepTweet(10);
        HF_USART_Put_Char(MOTOR1_USART,0x02);
        HF_USART_Put_Char(MOTOR1_USART,0x00);
        HF_USART_Put_Char(MOTOR1_USART,0xc4);
        HF_USART_Put_Char(MOTOR1_USART,0xc6);
        delay_ms(2);
        HF_USART_Put_Char(MOTOR1_USART,0x06);
        HF_USART_Put_Char(MOTOR1_USART,0x00);
        HF_USART_Put_Char(MOTOR1_USART,0x00);
        HF_USART_Put_Char(MOTOR1_USART,0x06);
        delay_ms(2);
        HF_USART_Put_Char(MOTOR1_USART,0x00);
        HF_USART_Put_Char(MOTOR1_USART,0x00);
        HF_USART_Put_Char(MOTOR1_USART,0x01);
        HF_USART_Put_Char(MOTOR1_USART,0x01);
        delay_ms(2);
    }
    if(motors->m2.online_state == 0 && motor2_connect_quality >80)//SPEED_MODE
    {
        motors->m2.online_state = 1;
        Board::getInstance()->setBeepTweet(10);
        HF_USART_Put_Char(MOTOR2_USART,0x02);
        HF_USART_Put_Char(MOTOR2_USART,0x00);
        HF_USART_Put_Char(MOTOR2_USART,0xc4);
        HF_USART_Put_Char(MOTOR2_USART,0xc6);
        delay_ms(2);
        HF_USART_Put_Char(MOTOR2_USART,0x06);
        HF_USART_Put_Char(MOTOR2_USART,0x00);
        HF_USART_Put_Char(MOTOR2_USART,0x00);
        HF_USART_Put_Char(MOTOR2_USART,0x06);
        delay_ms(2);
        HF_USART_Put_Char(MOTOR2_USART,0x00);
        HF_USART_Put_Char(MOTOR2_USART,0x00);
        HF_USART_Put_Char(MOTOR2_USART,0x01);
        HF_USART_Put_Char(MOTOR2_USART,0x01);
        delay_ms(2);
    }

    if(motor1_connect_quality >= 20)
    {
        motor1_connect_quality = motor1_connect_quality - (200*para->pid_t);
    }
    if(motor2_connect_quality >= 20)
    {
        motor2_connect_quality = motor2_connect_quality - (200*para->pid_t);
    }

    while(!motor1_queue->emptyCheck())
    {
        m1d[0]=m1d[1];
        m1d[1]=m1d[2];
        m1d[2]=m1d[3];
        m1d[3]=motor1_queue->getData();

        switch (m1d[0])
        {
        case 0x80:
            check_sum = (m1d[0] + m1d[1] + m1d[2]) & 0x00ff;
            if(m1d[3] == check_sum)
            {
                unsigned char Status_word =  m1d[2];
                unsigned char Status_ov_i = Status_word & (0x01 << 1);
                unsigned char Status_ov_u = Status_word & (0x01 << 2);
                unsigned char Status_err_enc = Status_word & (0x01 << 3);
                unsigned char Status_ov_q = Status_word & (0x01 << 5);
                unsigned char Status_ov_load = Status_word & (0x01 << 6);
                motors->m1.fault_state = Status_word;
                //if(Status_ov_load)
                if(Status_ov_i || Status_ov_load)
                {
                    motors->m1.stop_fault_motor = 1;
                }
                else motors->m1.stop_fault_motor = 0;
            }
            break;
        case 0xe1:
            check_sum = (m1d[0] + m1d[1] + m1d[2]) & 0x00ff;
            if(m1d[3] == check_sum)
            {
                data_ = m1d[1];
                data_ = data_ << 8 | m1d[2];
                motor1_connect_quality = 100;
                motors->m1.motor_voltage = data_;
            }
            break;
        case 0xe2:
            check_sum = (m1d[0] + m1d[1] + m1d[2]) & 0x00ff;
            if(m1d[3] == check_sum)
            {
                data_ = m1d[1];
                data_ = data_ << 8 | m1d[2];
                motors->m1.motor_current = data_ / 100.0;
            }
            break;
        case 0xe4:
            check_sum = (m1d[0] + m1d[1] + m1d[2]) & 0x00ff;
            if(m1d[3] == check_sum)
            {
                data_ = m1d[1];
                data_ = data_ << 8 | m1d[2];
                float speed_rpm = data_ * 6000.0 / 16384.0;
                motors->m1.measure_angle_speed = 360.0 * (-speed_rpm / 60.0 );
            }
            break;
        case 0xe6: break;
        case 0xe7: break;
        case 0xe8:
            check_sum = (m1d[0] + m1d[1] + m1d[2]) & 0x00ff;
            if(m1d[3] == check_sum)
            {
                c_past_total_pose1 = (c_past_total_pose1 & 0x0000ffff) | ((int)m1d[1]<<24 | (int)m1d[2]<<16 | 0xff << 8 | 0xff);
            }
            break;
        case 0xe9:
            check_sum = (m1d[0] + m1d[1] + m1d[2]) & 0x00ff;
            if(m1d[3] == check_sum)
            {
                c_past_total_pose1 = (c_past_total_pose1 & 0xffff0000) | ((int)0x00<<24 | (int)0x00<<16 | (int)m1d[1]<<8 | (int)m1d[2]);
                c_past_total_angle1 = -(float)c_past_total_pose1 * 360.0 / 4096.0;
                motors->m1.past_total_angle = c_past_total_angle1;
            }
            break;
        }
    }

    if(motors->m1.stop_fault_motor == 1)
    {
        motor1_alarm_time++;
        if(motor1_alarm_time >= 20/para->pid_t) //20S
        {
            clear_the_alarm(MOTOR1_USART);
            delay_ms(2);
            setMode(0,motors->m1.mode_state);
            motors->m1.stop_fault_motor = 0;
            motor1_alarm_time = 0;
        }
    }
    else
    {
        motors->m1.stop_fault_motor = 0;
        motor1_alarm_time = 0;
    }


    while(!motor2_queue->emptyCheck())
    {
        m2d[0]=m2d[1];
        m2d[1]=m2d[2];
        m2d[2]=m2d[3];
        m2d[3]=motor2_queue->getData();

        switch (m2d[0])
        {
        case 0x80:
            check_sum = (m2d[0] + m2d[1] + m2d[2]) & 0x00ff;
            if(m2d[3] == check_sum)
            {
                unsigned char Status_word =  m2d[2];
                unsigned char Status_ov_i = Status_word & (0x01 << 1);
                unsigned char Status_ov_u = Status_word & (0x01 << 2);
                unsigned char Status_err_enc = Status_word & (0x01 << 3);
                unsigned char Status_ov_q = Status_word & (0x01 << 5);
                unsigned char Status_ov_load = Status_word & (0x01 << 6);
                motors->m2.fault_state = Status_word;
                //if(Status_ov_load)
                if(Status_ov_i || Status_ov_load)
                {
                    motors->m2.stop_fault_motor = 1;
                }
                else motors->m2.stop_fault_motor = 0;
            }
            break;
        case 0xe1:
            check_sum = (m2d[0] + m2d[1] + m2d[2]) & 0x00ff;
            if(m2d[3] == check_sum)
            {
                data_ = m2d[1];
                data_ = data_ << 8 | m2d[2];
                motor2_connect_quality = 100;
                motors->m2.motor_voltage = data_;
            }
            break;
        case 0xe2:
            check_sum = (m2d[0] + m2d[1] + m2d[2]) & 0x00ff;
            if(m2d[3] == check_sum)
            {
                data_ = m2d[1];
                data_ = data_ << 8 | m2d[2];
                motors->m2.motor_current = data_ / 100.0;
            }
            break;
        case 0xe4:
            check_sum = (m2d[0] + m2d[1] + m2d[2]) & 0x00ff;
            if(m2d[3] == check_sum)
            {
                data_ = m2d[1];
                data_ = data_ << 8 | m2d[2];
                float speed_rpm = data_ * 6000.0 / 16384.0;
                motors->m2.measure_angle_speed = 360.0 * (-speed_rpm / 60.0 );
            }
            break;
        case 0xe6: break;
        case 0xe7: break;
        case 0xe8:
            check_sum = (m2d[0] + m2d[1] + m2d[2]) & 0x00ff;
            if(m2d[3] == check_sum)
            {
                c_past_total_pose2 = (c_past_total_pose2 & 0x0000ffff) | ((int)m2d[1]<<24 | (int)m2d[2]<<16 | 0xff << 8 | 0xff);
            }
            break;
        case 0xe9:
            check_sum = (m2d[0] + m2d[1] + m2d[2]) & 0x00ff;
            if(m2d[3] == check_sum)
            {
                c_past_total_pose2 = (c_past_total_pose2 & 0xffff0000) | ((int)0x00<<24 | (int)0x00<<16 | (int)m2d[1]<<8 | (int)m2d[2]);
                c_past_total_angle2 = -(float)c_past_total_pose2 * 360.0 / 4096.0;
                motors->m2.past_total_angle = c_past_total_angle2;
            }
            break;
        }

    }

    if(motors->m2.stop_fault_motor == 1)
    {
        motor2_alarm_time++;
        if(motor2_alarm_time >= 20/para->pid_t) //20S
        {
            clear_the_alarm(MOTOR2_USART);
            delay_ms(2);
            setMode(0,motors->m2.mode_state);
            motors->m2.stop_fault_motor = 0;
            motor2_alarm_time = 0;
        }
    }
    else{
        motors->m2.stop_fault_motor = 0;
        motor2_alarm_time = 0;
    }

    if(motors->m1.stop_fault_motor || motors->m2.stop_fault_motor)
        Board::getInstance()->setLedState(3,2);
}

void ZLAC706Motors::setMode(unsigned char motor_id_, unsigned char mode_)
{
    if(motor_id_ == 0)
    {
        if(mode_ == 1)
        {
            setTOSpeedMode();
        }
        else
        {
            setToForceMode();
        }
    }
}

void ZLAC706Motors::controlEnable(unsigned char motor_id_)
{

}

void ZLAC706Motors::controlDisable(unsigned char motor_id_)
{

}

void ZLAC706Motors::setAngleSpeed(unsigned char motor_id_ , float expect_angle_speed_)
{
    if(expect_angle_speed_ > MOTOR_MAXSPEED) expect_angle_speed_ = MOTOR_MAXSPEED;
    if(expect_angle_speed_ < -MOTOR_MAXSPEED) expect_angle_speed_ = -MOTOR_MAXSPEED;

    if(motors->m1.stop_fault_motor || motors->m2.stop_fault_motor)
    {
        expect_angle_speed_ = 0;
    }

    if(motor_id_ == 0)
    {
        motors->m1.expect_angle_speed = expect_angle_speed_;
        motors->m2.expect_angle_speed = expect_angle_speed_;
        usart_set_angle_speed(MOTOR1_USART,motors->m1.mode_state,-expect_angle_speed_);
        usart_set_angle_speed(MOTOR2_USART,motors->m2.mode_state,-expect_angle_speed_);
    }
    if(motor_id_ == 1)
    {
        motors->m1.expect_angle_speed = expect_angle_speed_;
        usart_set_angle_speed(MOTOR1_USART,motors->m1.mode_state,-expect_angle_speed_);
    }
    if(motor_id_ == 2)
    {
        motors->m2.expect_angle_speed = expect_angle_speed_;
        usart_set_angle_speed(MOTOR2_USART,motors->m2.mode_state,-expect_angle_speed_);
    }
}

float ZLAC706Motors::getAngleSpeed(unsigned char motor_id_){
    if(motor_id_ == 1)
    {
        return motors->m1.measure_angle_speed;
    }
    if(motor_id_ == 2)
    {
        return motors->m2.measure_angle_speed;
    }
    return 0;
}

float ZLAC706Motors::getDPastAngel(unsigned char motor_id_){
    float d;
    if(motor_id_ == 1){
        d = c_past_total_angle1 - l_past_total_angle1;
        l_past_total_angle1 = c_past_total_angle1;
        if(d > 500) d =0;
        if(d < -500) d=0;
        return d;
    }
    if(motor_id_ == 2){
        d = c_past_total_angle2 - l_past_total_angle2;
        l_past_total_angle2 = c_past_total_angle2;
        if(d > 500) d =0;
        if(d < -500) d=0;
        return d;
    }
    return 0;
}

void ZLAC706Motors::clear_the_alarm(unsigned char channel)
{
    HF_USART_Put_Char(channel,0x4A);
    HF_USART_Put_Char(channel,0x00);
    HF_USART_Put_Char(channel,0x00);
    HF_USART_Put_Char(channel,0x4A);
}

void ZLAC706Motors::usart_set_angle_speed(unsigned char channel ,unsigned char mode, float expect_angle_speed)
{
    float rpm = (expect_angle_speed * 60) / 360;
    short int value = (short int)((rpm / 6000.0) * 16384.0);
    unsigned char high_byte = (value & 0xff00) >> 8 ;
    unsigned char low_byte = (value & 0x00ff);
    unsigned char check_sum = ( (short int)(0x06 + high_byte + low_byte) ) & 0x00ff ;

    if(mode == 1)
    {
        HF_USART_Put_Char(channel,0x06);
        HF_USART_Put_Char(channel,high_byte);
        HF_USART_Put_Char(channel,low_byte);
        HF_USART_Put_Char(channel,check_sum);
    }

    HF_USART_Put_Char(channel,0x80);
    HF_USART_Put_Char(channel,0x00);
    HF_USART_Put_Char(channel,0x80);
}

void ZLAC706Motors::motor_int_speed_mode(void)
{
    unsigned short protect_i = 8000; //mA
    unsigned char h_8bit,l_8bit;
    l_8bit = protect_i;
    h_8bit = protect_i >> 8;

    HF_USART_Put_Char(MOTOR1_USART,0x53);
    HF_USART_Put_Char(MOTOR1_USART,0x00);
    HF_USART_Put_Char(MOTOR1_USART,0x00);
    HF_USART_Put_Char(MOTOR1_USART,0x53);
    HF_USART_Put_Char(MOTOR2_USART,0x53);
    HF_USART_Put_Char(MOTOR2_USART,0x00);
    HF_USART_Put_Char(MOTOR2_USART,0x00);
    HF_USART_Put_Char(MOTOR2_USART,0x53);
    delay_ms(5);

    HF_USART_Put_Char(MOTOR1_USART,0x02);
    HF_USART_Put_Char(MOTOR1_USART,0x00);
    HF_USART_Put_Char(MOTOR1_USART,0xc4);
    HF_USART_Put_Char(MOTOR1_USART,0xc6);
    delay_ms(2);
    HF_USART_Put_Char(MOTOR1_USART,0x06);
    HF_USART_Put_Char(MOTOR1_USART,0x00);
    HF_USART_Put_Char(MOTOR1_USART,0x00);
    HF_USART_Put_Char(MOTOR1_USART,0x06);
    delay_ms(2);
    HF_USART_Put_Char(MOTOR1_USART,0x00);
    HF_USART_Put_Char(MOTOR1_USART,0x00);
    HF_USART_Put_Char(MOTOR1_USART,0x01);
    HF_USART_Put_Char(MOTOR1_USART,0x01);
    delay_ms(2);
    HF_USART_Put_Char(MOTOR1_USART,0x80);
    HF_USART_Put_Char(MOTOR1_USART,0x00);
    HF_USART_Put_Char(MOTOR1_USART,0x80);
    delay_ms(2);
    HF_USART_Put_Char(MOTOR1_USART,0x2d);
    HF_USART_Put_Char(MOTOR1_USART,h_8bit);
    HF_USART_Put_Char(MOTOR1_USART,l_8bit);
    HF_USART_Put_Char(MOTOR1_USART,0x2d + h_8bit + l_8bit);
    delay_ms(2);

    HF_USART_Put_Char(MOTOR2_USART,0x02);
    HF_USART_Put_Char(MOTOR2_USART,0x00);
    HF_USART_Put_Char(MOTOR2_USART,0xc4);
    HF_USART_Put_Char(MOTOR2_USART,0xc6);
    delay_ms(2);
    HF_USART_Put_Char(MOTOR2_USART,0x06);
    HF_USART_Put_Char(MOTOR2_USART,0x00);
    HF_USART_Put_Char(MOTOR2_USART,0x00);
    HF_USART_Put_Char(MOTOR2_USART,0x06);
    delay_ms(2);
    HF_USART_Put_Char(MOTOR2_USART,0x00);
    HF_USART_Put_Char(MOTOR2_USART,0x00);
    HF_USART_Put_Char(MOTOR2_USART,0x01);
    HF_USART_Put_Char(MOTOR2_USART,0x01);
    delay_ms(2);
    HF_USART_Put_Char(MOTOR2_USART,0x80);
    HF_USART_Put_Char(MOTOR2_USART,0x00);
    HF_USART_Put_Char(MOTOR2_USART,0x80);
    delay_ms(2);
    HF_USART_Put_Char(MOTOR2_USART,0x2d);
    HF_USART_Put_Char(MOTOR2_USART,h_8bit);
    HF_USART_Put_Char(MOTOR2_USART,l_8bit);
    HF_USART_Put_Char(MOTOR2_USART,0x2d + h_8bit + l_8bit);
    delay_ms(5);
}

void ZLAC706Motors:: setToForceMode(void)
{
    if(motors->m1.online_state || motors->m2.online_state)
    {
        ////change mode
        //HF_USART_Put_Char(MOTOR1_USART,0x02);
        //HF_USART_Put_Char(MOTOR1_USART,0x00);
        //HF_USART_Put_Char(MOTOR1_USART,0xc1);
        //HF_USART_Put_Char(MOTOR1_USART,0xc3);

        ////send force
        //HF_USART_Put_Char(MOTOR1_USART,0x08);
        //HF_USART_Put_Char(MOTOR1_USART,0x00);
        //HF_USART_Put_Char(MOTOR1_USART,0x00);
        //HF_USART_Put_Char(MOTOR1_USART,0x08);

        ////start
        //HF_USART_Put_Char(MOTOR1_USART,0x00);
        //HF_USART_Put_Char(MOTOR1_USART,0x00);
        //HF_USART_Put_Char(MOTOR1_USART,0x01);
        //HF_USART_Put_Char(MOTOR1_USART,0x01);

        ////stop
        HF_USART_Put_Char(MOTOR1_USART,0x00);
        HF_USART_Put_Char(MOTOR1_USART,0x00);
        HF_USART_Put_Char(MOTOR1_USART,0x00);
        HF_USART_Put_Char(MOTOR1_USART,0x00);

        // -----------------------------------

        //HF_USART_Put_Char(MOTOR2_USART,0x02);
        //HF_USART_Put_Char(MOTOR2_USART,0x00);
        //HF_USART_Put_Char(MOTOR2_USART,0xc1);
        //HF_USART_Put_Char(MOTOR2_USART,0xc3);

        //HF_USART_Put_Char(MOTOR2_USART,0x08);
        //HF_USART_Put_Char(MOTOR2_USART,0x00);
        //HF_USART_Put_Char(MOTOR2_USART,0x00);
        //HF_USART_Put_Char(MOTOR2_USART,0x08);

        //HF_USART_Put_Char(MOTOR2_USART,0x00);
        //HF_USART_Put_Char(MOTOR2_USART,0x00);
        //HF_USART_Put_Char(MOTOR2_USART,0x01);
        //HF_USART_Put_Char(MOTOR2_USART,0x01);

        HF_USART_Put_Char(MOTOR2_USART,0x00);
        HF_USART_Put_Char(MOTOR2_USART,0x00);
        HF_USART_Put_Char(MOTOR2_USART,0x00);
        HF_USART_Put_Char(MOTOR2_USART,0x00);

        delay_ms(5);

        motors->m1.mode_state = 0;
        motors->m2.mode_state = 0;
    }
}

void ZLAC706Motors::setTOSpeedMode(void)
{
    if(motors->m1.online_state || motors->m2.online_state)
    {
        //change mode
        HF_USART_Put_Char(MOTOR1_USART,0x02);
        HF_USART_Put_Char(MOTOR1_USART,0x00);
        HF_USART_Put_Char(MOTOR1_USART,0xc4);
        HF_USART_Put_Char(MOTOR1_USART,0xc6);

        delay_ms(2);

        //set speed 0
        HF_USART_Put_Char(MOTOR1_USART,0x06);
        HF_USART_Put_Char(MOTOR1_USART,0x00);
        HF_USART_Put_Char(MOTOR1_USART,0x00);
        HF_USART_Put_Char(MOTOR1_USART,0x06);

        delay_ms(2);

        //start
        HF_USART_Put_Char(MOTOR1_USART,0x00);
        HF_USART_Put_Char(MOTOR1_USART,0x00);
        HF_USART_Put_Char(MOTOR1_USART,0x01);
        HF_USART_Put_Char(MOTOR1_USART,0x01);

        delay_ms(2);

        //------------------------------------
        HF_USART_Put_Char(MOTOR2_USART,0x02);
        HF_USART_Put_Char(MOTOR2_USART,0x00);
        HF_USART_Put_Char(MOTOR2_USART,0xc4);
        HF_USART_Put_Char(MOTOR2_USART,0xc6);

        delay_ms(2);

        HF_USART_Put_Char(MOTOR2_USART,0x06);
        HF_USART_Put_Char(MOTOR2_USART,0x00);
        HF_USART_Put_Char(MOTOR2_USART,0x00);
        HF_USART_Put_Char(MOTOR2_USART,0x06);

        delay_ms(2);

        HF_USART_Put_Char(MOTOR2_USART,0x00);
        HF_USART_Put_Char(MOTOR2_USART,0x00);
        HF_USART_Put_Char(MOTOR2_USART,0x01);
        HF_USART_Put_Char(MOTOR2_USART,0x01);

        delay_ms(5);
        motors->m1.mode_state = 1;
        motors->m2.mode_state = 1;
    }
}
