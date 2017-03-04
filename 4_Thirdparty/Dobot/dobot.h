
#include "ComPlatform/Protocol.h"
#include "command.h"
#include "stdio.h"
#include "board.h"

class Dobot
{
public:
    Dobot(unsigned char port_num_ = 2) {
        port_num = port_num_;
        board = Board::getInstance();
        HF_USART_Init(port_num, 115200 , 0);

        gJOGJointParams.velocity[0] = 100;
        gJOGJointParams.velocity[1] = 100;
        gJOGJointParams.velocity[2] = 100;
        gJOGJointParams.velocity[3] = 100;
        gJOGJointParams.acceleration[0] = 80;
        gJOGJointParams.acceleration[1] = 80;
        gJOGJointParams.acceleration[2] = 80;
        gJOGJointParams.acceleration[3] = 80;

        gJOGCommonParams.velocityRatio = 50;   //速度比例，关节点动和坐标轴点动共用参数
        gJOGCommonParams.accelerationRatio = 50;

        gJOGCmd.cmd = 0;   //点动命令，取值范围0--8, 0:无效状态
        gJOGCmd.isJoint = true;  //false:0--坐标点动   true:1--关节点动

        gPTPCoordinateParams.xyzVelocity = 100;   //PTP模式下xyz 3轴坐标轴速度
        gPTPCoordinateParams.rVelocity = 100;     //PTP模式下末端速度
        gPTPCoordinateParams.xyzAcceleration = 80;
        gPTPCoordinateParams.rAcceleration = 80;

        gPTPCommonParams.velocityRatio = 50;  //PTP模式速度比例
        gPTPCommonParams.accelerationRatio = 50;

        gPTPCmd.ptpMode = MOVL_XYZ;  //MOVL_XYZ：直线运动,参数为目标点坐标
        gPTPCmd.x = 137.8772;
        gPTPCmd.y = 37.5856;
        gPTPCmd.z = -0.6136;
        gPTPCmd.r = 1.8265;

        gQueuedCmdIndex = 0;
        //
        //
        //
    }

public:
    void init(void)
    {
        ProtocolInit();  //初始化协议所需要的各种数据结构体
        SetPTPCoordinateParams(&gPTPCoordinateParams, true, &gQueuedCmdIndex);
        SetPTPCommonParams(&gPTPCommonParams, true, &gQueuedCmdIndex);
        SetPTPCmd(&gPTPCmd, true, &gQueuedCmdIndex);
    }

    void call(void)
    {
        Message message;
        MessageProcess(&gUART4ProtocolHandler);

        if (RingBufferGetCount(&gUART4ProtocolHandler.txRawByteQueue))
        {   //在此处开启发送中断，只要发送队列不为空则一直发送数据
            if (RingBufferIsEmpty(&gUART4ProtocolHandler.txRawByteQueue) == false)
            { //一直发送
                uint8_t data;
                RingBufferDequeue(&gUART4ProtocolHandler.txRawByteQueue, &data);
                HF_USART_Put_Char(port_num , data);
            }
        }
        if(board->getUsartQueue(port_num)->emptyCheck() == 0)
        {
            uint8_t data = board->getUsartQueue(port_num)->getData();
            if (RingBufferIsFull(&gUART4ProtocolHandler.rxRawByteQueue) == false) {
                RingBufferEnqueue(&gUART4ProtocolHandler.rxRawByteQueue, &data);
            }
        }

        if(MessageRead(&gUART4ProtocolHandler, &message)==ProtocolNoError)
        {
#if 1
            //打印接收到的返回数据
            printf("Rx message: ");
            printf("message id:%d, rw:%d, isQueued:%d, paramsLen:%d\r\n",
                   message.id, message.rw, message.isQueued, message.paramsLen);
            printf("params: ");
            for(int i=0; i<message.paramsLen; i++)
            {
                printf("%02x ", message.params[i]);
            }
            printf("\r\n");
#endif
        }
    }

    void setEffectorPos(float x ,float y ,float z ,float r)
    {
        gPTPCmd.ptpMode = MOVL_XYZ;
        gPTPCmd.x = x;
        gPTPCmd.y = y;
        gPTPCmd.z = z;
        gPTPCmd.r = r;
        SetPTPCmd(&gPTPCmd, true, &gQueuedCmdIndex);
    }

private:
    JOGJointParams gJOGJointParams;  //关节点动参数
    JOGCommonParams gJOGCommonParams;  //点动公共参数
    JOGCmd gJOGCmd;  //点动功能指令
    //PTP:再现功能
    PTPCoordinateParams gPTPCoordinateParams;  //坐标轴点位参数
    PTPCommonParams gPTPCommonParams;  //点位公共参数
    PTPCmd gPTPCmd;  //点位功能指令
    uint64_t gQueuedCmdIndex;
    Board* board;

private:
    unsigned char port_num;
};

