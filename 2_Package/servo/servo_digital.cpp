/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: robot_wheel_config.h
* Contact:  QQ Exchange Group -- 521037187
* Version:  V2.0
*
* LICENSING TERMS:
* The Hands Free is licensed generally under a permissive 3-clause BSD license.
* Contributions are requiredto be made under the same license.
*
* History:
* <author>      <time>      <version>      <desc>
* mawenke       2015.10.1   V1.0           creat this file
* Description:
*
***********************************************************************************************************************/

#include "servo_digital.h"

#define	OK                      0x00     // 返回状态正常或该指令完成
#define	ResServoPosInfo         0x01     // 请求舵机位置信息
#define	CheckError              0x02     // 校验位错误
#define	InvalidPosition         0x03     // 插入或删除位置出现错误
#define	NoSuchServo             0x04     // 没有这个舵机号码
#define	NoSuchType              0x05     // 没有这种数据包类型
#define	NoSuchInstructionType 	0x06     // 没有这种指令类型
#define NoSuchFile              0x07     // 没有fianlfile文件
#define HaveFile                0x08     // 存在finalfile文件,但没有动作序列
#define HaveActionFrame         0x09     // 文件中存在动作序列
#define ServoIDNumber           0x0a     // 舵机的连通的ID号
#define UpLoadActionsNameType   0x0b     // 回复下位机中已经存储的微动作的列表

//--- Control Table Address ---
//EEPROM AREA
#define P_MODEL_NUMBER_L      0									  //型号代码L
#define P_MODOEL_NUMBER_H     1									  //型号代码H
#define P_VERSION             2									  //固件版本
#define P_ID                  3									  //ID特征值
#define P_BAUD_RATE           4									  //波特率
#define P_RETURN_DELAY_TIME   5									  //返回延迟时间
#define P_CW_ANGLE_LIMIT_L    6									  //最小角度L
#define P_CW_ANGLE_LIMIT_H    7									  //最小角度H
#define P_CCW_ANGLE_LIMIT_L   8									  //最大角度（L）（CCW代表逆时针）
#define P_CCW_ANGLE_LIMIT_H   9									  //最大角度（H）
#define P_SYSTEM_DATA2        10								  //（保留）
#define P_LIMIT_TEMPERATURE   11							      //最高的界限温度
#define P_DOWN_LIMIT_VOLTAGE  12								  //最低的界限电压
#define P_UP_LIMIT_VOLTAGE    13								  //最高的界限电压
#define P_MAX_TORQUE_L        14								  //最大转力矩L
#define P_MAX_TORQUE_H        15								  //最大转力矩H
#define P_RETURN_LEVEL        16								  //状态反馈程度
#define P_ALARM_LED           17								  //LED 警报 警报引导
#define P_ALARM_SHUTDOWN      18								  //撤消扭矩警报
#define P_OPERATING_MODE      19
#define P_DOWN_CALIBRATION_L  20
#define P_DOWN_CALIBRATION_H  21
#define P_UP_CALIBRATION_L    22
#define P_UP_CALIBRATION_H    23

#define P_TORQUE_ENABLE          (24)						  //激活扭矩
#define P_LED                    (25)						  //LED
#define P_CW_COMPLIANCE_MARGIN   (26)						  //顺时针柔性边距
#define P_CCW_COMPLIANCE_MARGIN  (27)						  //逆时针柔性边距
#define P_CW_COMPLIANCE_SLOPE    (28)						  //顺时针柔性斜率
#define P_CCW_COMPLIANCE_SLOPE   (29)						  //逆时针伺服斜率
#define P_GOAL_POSITION_L        (30)						  //目标位置（低）
#define P_GOAL_POSITION_H        (31)						  //目标位置（高）
#define P_GOAL_SPEED_L           (32)					 	  //运动速度（低）
#define P_GOAL_SPEED_H           (33)					    //运动速度（高）
#define P_TORQUE_LIMIT_L         (34)					    //扭矩限制（低）
#define P_TORQUE_LIMIT_H         (35)					//扭矩限制（高）
#define P_PRESENT_POSITION_L     (36)					//当前位置（低）
#define P_PRESENT_POSITION_H     (37)				    //当前位置（高）
#define P_PRESENT_SPEED_L        (38)				    //当前速度（低）
#define P_PRESENT_SPEED_H        (39)				    //当前速度（高）
#define P_PRESENT_LOAD_L         (40)				    //当前负载（低）
#define P_PRESENT_LOAD_H         (41)			        //当前负载（高）
#define P_PRESENT_VOLTAGE        (42)			        //当前电压
#define P_PRESENT_TEMPERATURE    (43)			        //当前温度
#define P_REGISTERED_INSTRUCTION (44)
#define P_PAUSE_TIME             (45)
#define P_MOVING                 (46)
#define P_LOCK                   (47)
#define P_PUNCH_L                (48)
#define P_PUNCH_H                (49)

//--- Instruction ---
#define INST_PING           0x01						//连通性检测程序,无操作，用来得到状态数据包	  
#define INST_READ           0x02					    //数据读取,读取控制表中的数值
#define INST_WRITE          0x03						//数据写入,向控制表中写入数值
#define INST_REG_WRITE      0x04						//写入寄存器,和数据写入类似，但在操作指令给出之前处于备用模式.注册表写入指令和数据写入指令类似，但是两者指令包完成的时间是不同的
#define INST_ACTION         0x05						//操作,引发写入的指令 ,即接收该指令后，执行INST_REG_WRITE的内容（避免延迟，舵机不同步），无返回状态包
#define INST_RESET          0x06						//复位,把Dynamixel舵机的控制表数值调整到出厂设置值
#define INST_DIGITAL_RESET  0x07
#define INST_SYSTEM_READ    0x0C
#define INST_SYSTEM_WRITE   0x0D
#define INST_SYNC_WRITE     0x83						// 同时写入,用于同时控制多个Dynamixel舵机
#define INST_SYNC_REG_WRITE 0x84

#define CLEAR_BUFFER gbRxBufferReadPointer = gbRxBufferWritePointer
#define DEFAULT_RETURN_PACKET_SIZE 6
#define BROADCASTING_ID 0xfe
#define ACTION_COMPLETE 0
#define ACTION_ERROR 1

#define PNULL 0
#define DEFAULTSPEED 512
#define RX_TIMEOUT_COUNT2   500L
#define RX_TIMEOUT_COUNT1  (RX_TIMEOUT_COUNT2*10L)

uint8_t ServoDigital::TxPacket(uint8_t bID, uint8_t bInstruction, uint8_t bParameterLength)
{
    //bParameterLength为参数PARAMETER长度，返回数据包长信息(除掉指令等)
    uint8_t bCount, bPacketLength;
    uint8_t bCheckSum;

    gbpTxBuffer[0] = 0xff;
    gbpTxBuffer[1] = 0xff;
    gbpTxBuffer[2] = bID;
    gbpTxBuffer[3] = bParameterLength + 2;		//Length(Paramter,Instruction,Checksum)
    gbpTxBuffer[4] = bInstruction;
    for (bCount = 0; bCount < bParameterLength; bCount++)
    {
        gbpTxBuffer[bCount + 5] = gbpParameter[bCount];
    }
    bCheckSum = 0;
    bPacketLength = bParameterLength + 4 + 2;				//bPacketLength包含了两个0XFF	,和checksum
    for (bCount = 2; bCount < bPacketLength - 1; bCount++) //except 0xff,checksum
    {
        bCheckSum += gbpTxBuffer[bCount];
    }

    gbpTxBuffer[bCount] = (uint8_t) (~bCheckSum); //Writing Checksum  with  Bit Inversion
    //USART_ITConfig(SERVO_CONTROL_USART, USART_IT_RXNE, ENABLE);
    CLEAR_BUFFER;

    board.axServoTxModel();

    for (bCount = 0; bCount < bPacketLength; bCount++)
    {
        axServoSendTxByte(gbpTxBuffer[bCount]);
    }

    board.axServoRxModel();
    //for(i=0;i<0x8fff;i++);
    return (bPacketLength);		   //返回发送的所有数据长度
}


/*uint8_t RxPacket(uint8_t bRxPacketLength)
 * bRxPacketLength 我们准备接收的数据长度
 * return 实际返回的数据长度（包括0XFF）
 * */
uint8_t ServoDigital::RxPacket(uint8_t bRxPacketLength)
{

    unsigned long ulCounter;
    uint8_t bCount, bLength, bChecksum;
    uint8_t bTimeout;
    bTimeout = 0;
    /*接受循环
     * 当接受到指定长度的数据或者超时的时候退出循环*/
    for (bCount = 0; bCount < bRxPacketLength; bCount++)
    {
        ulCounter = 0;
        /*利用中断接受数据
         * 主程序处于等待状态
         * 当中断缓冲区里面没有数据gbRxBufferReadPointer == gbRxBufferWritePointer
         * 时间计数器自增
         * 当超时或者中断缓冲区里面有数据的时候跳出等待*/
        while (gbRxBufferReadPointer == gbRxBufferWritePointer)
        {
            if (ulCounter++ > RX_TIMEOUT_COUNT1)
            {
                bTimeout = 1;
                break;
            }
        }
        if (bTimeout) break;
        gbpRxBuffer[bCount] = gbpRxInterruptBuffer[gbRxBufferReadPointer++];
    }  //这里把数据都从中断队列中放到RxBuffer里面了

    bLength = bCount;
    bChecksum = 0;
    /*默认情况下TxPacket与RxPacket连续使用
     * 当上一个数据包不是BROADCASTING_ID时有返回的数据*/
    if (gbpTxBuffer[2] != BROADCASTING_ID)
    {
        if (bTimeout && (bRxPacketLength != 255))
        {				 //超时，且未接收完
            //TxDString("\r\n [Error:RxD Timeout]");
            CLEAR_BUFFER; //清空接收缓冲区
            return 0;
        }

        if (bLength > 3) //checking is available.				 //接收数据长度至少要大于3位
        {
            if (gbpRxBuffer[0] != 0xff || gbpRxBuffer[1] != 0xff)
            {
                //TxDString("\r\n [Error:Wrong Header]");
                CLEAR_BUFFER;	  //清空接收缓冲区
                return 0;
            }
            if (gbpRxBuffer[2] != gbpTxBuffer[2])
            {
                //TxDString("\r\n [Error:TxID != RxID]");
                CLEAR_BUFFER;
                return 0;
            }
            if (gbpRxBuffer[3] != bLength - 4) 		 //接受到的数据长度-4不等于length
            {					//默认状态包长度不大于255
                //TxDString("\r\n [Error:Wrong Length]");
                CLEAR_BUFFER;
                return 0;
            }
            for (bCount = 2; bCount < bLength; bCount++)
                bChecksum += gbpRxBuffer[bCount];
            if (bChecksum != 0xff)
            {
                //TxDString("\r\n [Error:Wrong CheckSum]");
                CLEAR_BUFFER;
                return 0;
            }
        }
    }
    //	USART_ITConfig(SERVO_CONTROL_USART, USART_IT_RXNE, DISABLE);
    return bLength;
}

//uint8_t axPing(uint8_t bID) {
//unsigned char bTxPacketLength, bRxPacketLength;
//bTxPacketLength = TxPacket(bCount, INST_PING, 0);
//bRxPacketLength = RxPacket(255); //我们准备接收好多个数据
//if (bRxPacketLength == DEFAULT_RETURN_PACKET_SIZE)
//	;
//}

uint8_t ServoDigital::axTorqueOff(uint8_t bID) //释放舵机的力矩
{
    gbpParameter[0] = P_TORQUE_ENABLE; //Address of Torque
    gbpParameter[1] = 0; //Writing Data
    TxPacket(bID, INST_WRITE, 2);
    if (RxPacket(DEFAULT_RETURN_PACKET_SIZE) == DEFAULT_RETURN_PACKET_SIZE)
        return OK;
    else
        return NoSuchServo;
}

uint8_t ServoDigital::axTorqueOn(uint8_t bID) //使能舵机的力矩
{
    gbpParameter[0] = P_TORQUE_ENABLE; //Address of Torque
    gbpParameter[1] = 1; //Writing Data
    TxPacket(bID, INST_WRITE, 2);
    if (RxPacket(DEFAULT_RETURN_PACKET_SIZE) == DEFAULT_RETURN_PACKET_SIZE)
        return OK;
    else
        return NoSuchServo;
}

//给某个舵机位置
//发送给某一个舵机一个要移动到的位置，包括三个参数 1ID 2位置 3速度
uint8_t ServoDigital::axSendPosition(uint8_t bID, uint16_t target_pos, uint16_t target_speed)
{
    gbpParameter[0] = P_GOAL_POSITION_L; //Address of Firmware Version
    gbpParameter[1] = target_pos; //Writing Data P_GOAL_POSITION_L
    gbpParameter[2] = target_pos >> 8; //Writing Data P_GOAL_POSITION_H
    gbpParameter[3] = target_speed; //Writing Data P_GOAL_SPEED_L
    gbpParameter[4] = target_speed >> 8; //Writing Data P_GOAL_SPEED_H
    TxPacket(bID, INST_WRITE, 5);
    if (RxPacket(DEFAULT_RETURN_PACKET_SIZE + 1) == DEFAULT_RETURN_PACKET_SIZE)
    {
        return OK;
    }

    else
    {
        return NoSuchServo;
    }

}

/*uint16_t axReadPosition(uint8_t bID)
 * parameter
 * 		bID 舵机号
 * return value
 * 		舵机位置
 * 		0xffff表示出错了
 * */

uint16_t ServoDigital::axReadPosition(uint8_t bID) 			  //读取某个舵机的位置
{
    unsigned int Position;
    gbpParameter[0] = P_PRESENT_POSITION_L; //位置数据的起始地址 #define P_GOAL_POSITION_L (30) 参见数据手册
    gbpParameter[1] = 2;   //读取长度
    TxPacket(bID, INST_READ, 2);
    if(RxPacket(DEFAULT_RETURN_PACKET_SIZE + gbpParameter[1]) != DEFAULT_RETURN_PACKET_SIZE + gbpParameter[1])
    {
        Position = 0xffff;
    }
    else
    {
        Position = ((unsigned int) gbpRxBuffer[6]) << 8;
        Position += gbpRxBuffer[5];
    }
    return Position;
}


void ServoDigital::axTorqueOffAll(void)					//释放所有舵机力矩
{
    gbpParameter[0] = P_TORQUE_ENABLE;
    gbpParameter[1] = 0x00;
    TxPacket(BROADCASTING_ID, INST_WRITE, 2);

}

void ServoDigital::axTorqueOnAll(void) 				  //使能所有舵机力矩
{
    gbpParameter[0] = P_TORQUE_ENABLE;
    gbpParameter[1] = 0x01;
    TxPacket(BROADCASTING_ID, INST_WRITE, 2);
}


/*void axScan(void)
 * Return Values
 * 		在线舵机总数
 * 所能检测ID的范围0~AX_MAX_NUM-1
 * 检测连线的舵机号码保存在全局数组axOline[30]
 * 检测连线的舵机数保存在全局数组axOlineNum
 * */

void ServoDigital::getServoConnective(void)
{		
    //PING舵机从几号开始
    uint8_t bCount;
    axOlineNum = 0;
    for (bCount = 0; bCount < AX_MAX_NUM - 1; bCount++)  //用一个循环查询每一个舵机的状态为了快速我们只扫描0x00~0x1f
    {
        TxPacket(bCount, INST_PING, 0);
        if (RxPacket(255) == DEFAULT_RETURN_PACKET_SIZE) //如果返回包的长度正确
            axOline[axOlineNum++] = bCount;
    }

    packageReplyToDebug( ServoIDNumber, (uint8_t *) &axOline[0], axOlineNum);

}


void ServoDigital::moveServoPosition(uint8_t *p, uint8_t num)
{
    uint8_t i, err = OK;
    uint16_t pos;
    for (i = 0; i < num / 3; i++) {
        pos = (*(p + (3 * i) + 2)) * 256 + (*(p + (3 * i) + 1));
        err |= axSendPosition(*p + (3 * i), pos, DEFAULTSPEED);
    }

    packageReplyToDebug( err, PNULL, 0);
}


void ServoDigital::moveServoPosWithSpeed(uint8_t *p, uint8_t num)
{
    uint8_t i, err = OK;
    uint16_t pos, speed;
    for (i = 0; i < num / 5; i++)
    {
        pos = *(p + (5 * i) + 2) * 256 + *(p + (5* i) +1);
        speed = *(p + (5* i) + 4) * 256 + *(p + (5 * i)+3 );
        err |= axSendPosition(*(p + (5 * i)), pos, speed);
    }
    packageReplyToDebug( err, PNULL, 0);
}

/*GetServoPosition(uint8_t *p,uint8_t num)
 * parameter:
 * 		*p
 * 			指向有效数据数组的头指针
 * 		num
 * 			有数组有效长度
 * */
void ServoDigital::getServoPosition(uint8_t *p, uint8_t num)
{
    uint8_t i;
    uint8_t retdata[100];
    uint16_t tmp;
    switch (num) {
    case 1:
        if (*p == BROADCASTING_ID) { //读取全部舵机pos
            for (i = 0; i < axOlineNum; i++) {
                retdata[i*3] = axOline[i];
                tmp = axReadPosition(axOline[i]);
                retdata[i*3+1] =tmp & 0xff;
                retdata[i*3+2] =(tmp & 0xff00) >> 8;
            }

        } else {
            retdata[0] = *p;
            tmp = axReadPosition(*p);
            retdata[1] = tmp & 0xff;
            retdata[2] = (tmp&0xff00) >> 8;
        }
        packageReplyToDebug( ResServoPosInfo, (uint8_t *) &retdata[0],
                axOlineNum * 3);
        break;
        //case 2:
    default:
        for (i = 0; i < num; i++) {
            retdata[i*3] = *p;
            tmp = axReadPosition(*p);
            p++;
            retdata[i*3+1] = tmp & 0xff;
            retdata[i*3+2] = (tmp & 0xff00) >> 8;
        }
        packageReplyToDebug( ResServoPosInfo, (uint8_t *) &retdata,
                             num * 3);
        break;
    }
}

void ServoDigital::enableServo(uint8_t *p, uint8_t num)
{
    uint8_t err = OK;
    uint8_t i, *p0;
    p0 = p;
    switch (num)
    {
    case 1:
        if (*p0 == BROADCASTING_ID) { //读取全部舵机pos
            axTorqueOnAll();
            err = OK;
            packageReplyToDebug( err, PNULL, 0);

        } else {
            err = axTorqueOn(*p0);
            packageReplyToDebug( err, PNULL, 0);
        }
        break;
    default:
        for (i = 0; i < num; i++)
            err |= axTorqueOn(*p0++);
        packageReplyToDebug( err, PNULL, 0);
        break;
    }
}

void ServoDigital::disableServo(uint8_t *p, uint8_t num)
{
    uint8_t err = OK;
    uint8_t i, *p0;
    p0 = p;
    switch (num) {
    case 1:
        if (*p0 == BROADCASTING_ID) { //读取全部舵机pos
            axTorqueOffAll();
            err = OK;
            packageReplyToDebug( err, PNULL, 0);
        } else {
            err = axTorqueOff(*p0++);
            packageReplyToDebug( err, PNULL, 0);
        }
        break;
    case 2:
        for (i = 0; i < num; i++)
            err |= axTorqueOff(*p0);
        packageReplyToDebug( err, PNULL, 0);
        break;
    }
}



void ServoDigital::executeInstruction(uint8_t *p, uint8_t num)
{
    uint8_t err;
    uint8_t i;

    board.axServoTxModel();  //Send
    for (i = 0; i < num; i++)
    {
        axServoSendTxByte(*p++);
    }

    board.axServoRxModel(); //Rec
    //for(i=0;i<0x8fff;i++);
    if (RxPacket(DEFAULT_RETURN_PACKET_SIZE) == DEFAULT_RETURN_PACKET_SIZE)
        err = OK;
    else
        err = NoSuchServo;
    packageReplyToDebug( err, PNULL, 0);
}


/***********************
*void playMicroAction(uint8_t *p,uint16_t poolSize)
 * parameter:
 * 		*p
 * 			指令池首地址指针
 * 		poolSize
 * 			指令池大小*
 * void playMicroAction(uint8_t *p, uint16_t poolSize) {
     * FF FF FE LENGTH INST_SYNC_WRITE(0X83)
     * 1E(1st write add) 04(write bytes)
     * ID1 	POSL   POSH   SPEEDL   SPEEDH
     * ID1 	POSL   POSH   SPEEDL   SPEEDH
     * ...
     * ...
     * IDN 	POSL   POSH   SPEEDL   SPEEDH
     * CHECKSUM
     * hence all package length is LENGTH(*(P+3))+4
     *
*	uint16_t packageLength, j, time;
    uint16_t packageNum, i;
//	TimeInterval = (*p) * 10;												 //感觉应该*10																
    packageLength = (uint16_t)(*(p+1)+(uint16_t)*(p+2)*256);		//可能有问题 （必须滴）
    packageNum = (poolSize-3)/ packageLength;
    p = p+3;
   board.axServoTxModel();;
    for (i = 0; i < packageNum; i++) {
        //启动延时函数
        MiniActionBeginFlag = 1;
        while(NewKeyActionFlag != 1)
            ;
        for (j = 0; j <packageLength; j++) {
axServoSendTxByte(*p++);
        }

        NewKeyActionFlag = 0;
    }
   board.axServoRxModel();
}  
*********************/


void ServoDigital::TxPacketBroadSynWrite(uint8_t bInstruction, uint8_t bParameterLength) {
    uint8_t bCount, bPacketLength;
    gbpTxBuffer[0] = 0xff;
    gbpTxBuffer[1] = 0xff;
    gbpTxBuffer[2] = 0xfe;
    gbpTxBuffer[3] = bParameterLength + 2;
    //Length(Paramter,Instruction,Checksum)
    gbpTxBuffer[4] = bInstruction;
    for (bCount = 0; bCount < bParameterLength; bCount++) {
        gbpTxBuffer[bCount + 5] = gbpParameter[bCount];
    }
    bPacketLength = bParameterLength + 5;	//可能有问题

    board.axServoTxModel();
    for (bCount = 0; bCount < bPacketLength; bCount++) {
        axServoSendTxByte(gbpTxBuffer[bCount]);
    }

    board.axServoRxModel();
}

void ServoDigital::changeServoID(uint8_t *p, uint8_t num)
{
    gbpParameter[0] = P_ID; //舵机ID地址
    gbpParameter[1] = *p;
    if(num == 1){			 //一次只能给1个制定的ID
        TxPacket(BROADCASTING_ID,INST_WRITE,2);
        getServoConnective();
    }
    else{
        // packageReplyToDebug( CheckError, (void *)0, 0);
    }
}

uint8_t ServoDigital::axSendSpeed(uint8_t bID, uint16_t target_speed)
//发送给某一个舵机一个要移动到的位置，包括三个参数 1ID 2位置 3速度
{
    gbpParameter[0] = P_GOAL_SPEED_L; //Address of Firmware Version
    gbpParameter[3] = target_speed; //Writing Data P_GOAL_SPEED_L
    gbpParameter[4] = target_speed >> 8; //Writing Data P_GOAL_SPEED_H
    TxPacket(bID, INST_WRITE, 3);
    if (RxPacket(DEFAULT_RETURN_PACKET_SIZE) == DEFAULT_RETURN_PACKET_SIZE)
        return OK;
    else
        return NoSuchServo;
}

//length只包含data的长度
//ff Length_L	  Length_H	 0	 2	   command_type	****	   Check_Sum
//command_type代被回复指令类型，data代表返回数据的指针,length代表要发送的也就是我的下家返回给我的数据长度，要打包送给上位机
void ServoDigital::packageReplyToDebug(unsigned char command_type,unsigned char * data, unsigned int length)
{		

#if SERVO_DEBUG_EN ==1
    unsigned char Length_H, Length_L, Check_Sum = 0;
    unsigned int j = 0;
    Length_H = (length + 6) >> 8;
    Length_L = (length + 6);

    board.debugPutChar(0XFF); //包头
    board.debugPutChar(Length_L); //长度1
    Check_Sum = Check_Sum + Length_L;
    board.debugPutChar(Length_H); //长度2
    Check_Sum = Check_Sum + Length_H;
    board.debugPutChar(0); //ID =0,代表数字舵机
    board.debugPutChar(2); //代表这是回复信息
    Check_Sum = Check_Sum + 2; //代表指令类型
    board.debugPutChar(command_type);
    Check_Sum = Check_Sum + command_type;
    //发送有效数据
    for (j = 0; j < length; j++)
    {
        board.debugPutChar(*(data + j));
        Check_Sum = Check_Sum + *(data + j);
    }
    Check_Sum = ~Check_Sum; //计算校验和

    board.debugPutChar(Check_Sum);
    Check_Sum = 0;

#endif

    return;

}
