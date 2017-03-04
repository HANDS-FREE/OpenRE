#ifndef COMMAND_H
#define COMMAND_H

/****************************************Copyright(c)*****************************************************
**                            Shenzhen Yuejiang Technology Co., LTD.
**
**                                 http://www.dobot.cc
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           command.h
** Latest modified Date:
** Latest Version:      V1.0.0
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Created by:          LiYi
** Created date:        2016-06-01
** Version:             V1.0.0
** Descriptions:        Data definition
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/

#include <stdint.h>

/*********************************************************************************************************
** Data structure
*********************************************************************************************************/
#pragma pack(push)
#pragma pack(1)

enum
{
    JUMP_XYZ,
    MOVJ_XYZ,
    MOVL_XYZ,
    JUMP_ANGLE,
    MOVJ_ANGLE,
    MOVL_ANGLE,
    MOVJ_INC,
    MOVL_INC,
};

typedef struct tagEndEffectorParams {
    float xBias;
    float yBias;
    float zBias;
}EndEffectorParams;

typedef struct tagJOGJointParams {
    float velocity[4];    //4轴坐标轴(x,y,z,r) 速度
    float acceleration[4];  //4轴坐标轴(x,y,z,r) 加速度
}JOGJointParams;

typedef struct tagJOGCoordinateParams {
    float velocity[4];
    float acceleration[4];
}JOGCoordinateParams;

typedef struct tagJOGCommonParams {
    float velocityRatio;
    float accelerationRatio;
}JOGCommonParams;

typedef struct tagJOGCmd {
    uint8_t isJoint;
    uint8_t cmd;
}JOGCmd;

typedef struct tagPTPJointParams {
    float velocity[4];
    float acceleration[4];
}PTPJointParams;

typedef struct tagPTPCoordinateParams {
    float xyzVelocity;   //PTP 模式下xyz 3轴坐标轴速度
    float rVelocity;   //PTP 模式下末端速度
    float xyzAcceleration;  //
    float rAcceleration;
}PTPCoordinateParams;

typedef struct tagPTPJumpParams {
    float jumpHeight;
    float maxJumpHeight;
}PTPJumpParams;

typedef struct tagPTPCommonParams {
    float velocityRatio;
    float accelerationRatio;
}PTPCommonParams;

typedef struct tagPTPCmd {
uint8_t ptpMode;
    float x;
    float y;
    float z;
    float r;
}PTPCmd;

#pragma pack(pop)




/*********************************************************************************************************
** End effector function
*********************************************************************************************************/
extern int SetEndEffectorParams(EndEffectorParams *endEffectorParams);
extern int SetEndEffectorLaser(bool on, bool isQueued, uint64_t *queuedCmdIndex);
extern int SetEndEffectorSuctionCup(bool suck, bool isQueued, uint64_t *queuedCmdIndex);
extern int SetEndEffectorGripper(bool grip, bool isQueued, uint64_t *queuedCmdIndex);

/*********************************************************************************************************
** JOG function
*********************************************************************************************************/
extern int SetJOGJointParams(JOGJointParams *jogJointParams, bool isQueued, uint64_t *queuedCmdIndex);
extern int SetJOGCoordinateParams(JOGCoordinateParams *jogCoordinateParams, bool isQueued, uint64_t *queuedCmdIndex);
extern int SetJOGCommonParams(JOGCommonParams *jogCommonParams, bool isQueued, uint64_t *queuedCmdIndex);
extern int SetJOGCmd(JOGCmd *jogCmd, bool isQueued, uint64_t *queuedCmdIndex);

/*********************************************************************************************************
** PTP function
*********************************************************************************************************/
extern int SetPTPJointParams(PTPJointParams *ptpJointParams, bool isQueued, uint64_t *queuedCmdIndex);
extern int SetPTPCoordinateParams(PTPCoordinateParams *ptpCoordinateParams, bool isQueued, uint64_t *queuedCmdIndex);
extern int SetPTPJumpParams(PTPJumpParams *ptpJumpParams, bool isQueued, uint64_t *queuedCmdIndex);
extern int SetPTPCommonParams(PTPCommonParams *ptpCommonParams, bool isQueued, uint64_t *queuedCmdIndex);
extern int SetPTPCmd(PTPCmd *ptpCmd, bool isQueued, uint64_t *queuedCmdIndex);

#endif
