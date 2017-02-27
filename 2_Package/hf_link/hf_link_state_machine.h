#ifndef HF_LINK_STATE_MACHINE_H
#define HF_LINK_STATE_MACHINE_H

#include "stdio.h"
#include "hf_link_platform.h"

//limite one message's size
static const unsigned short int MESSAGE_BUFER_SIZE = 120;
typedef struct HFMessage{
    unsigned char sender_id;
    unsigned char receiver_id;
    unsigned short int length;
    unsigned char data[MESSAGE_BUFER_SIZE];
}HFMessage;

//communication status
enum Recstate{
    WAITING_FF1,
    WAITING_FF2,
    SENDER_ID,
    RECEIVER_ID,
    RECEIVE_LEN_H,
    RECEIVE_LEN_L,
    RECEIVE_PACKAGE,
    RECEIVE_CHECK
};

class StateMachine
{
public:
    StateMachine(unsigned char my_id_ , unsigned char friend_id_ , unsigned char port_num_)
    {
        my_id = my_id_;   //0x11 means slave ,  read Hands Free Link Manua.doc for detail
        friend_id = friend_id_;   // 0x01 means master
        port_num = port_num_;
#if HF_LINK_NODE_MODEL==0
        board.usartDeviceInit((DeviceType) port_num , 921600);
#endif
    }
    inline unsigned char* getSerializedData(void)
    {
        return tx_buffer;
    }
    inline int getSerializedLength(void)
    {
        return tx_buffer_length;
    }
    unsigned char receiveStates(unsigned char rx_data);
    void sendMessage(const HFMessage* tx_message_);
    HFMessage rx_message ,  tx_message;
    unsigned char my_id , friend_id;
    unsigned char port_num;

private:
    Recstate   receive_state_;
    float receive_message_count  , send_message_count;
    unsigned char tx_buffer[MESSAGE_BUFER_SIZE];
    unsigned int receive_check_sum_;
    short int receive_message_length_;
    short int byte_count_;
    unsigned tx_buffer_length;
};

#endif // HF_LINK_STATE_MACHINE_H
