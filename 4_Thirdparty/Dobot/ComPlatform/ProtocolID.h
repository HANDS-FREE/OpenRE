/****************************************Copyright(c)*****************************************************
**                            Shenzhen Yuejiang Technology Co., LTD.
**
**                                 http://www.dobot.cc
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           ProtocolID.h
** Latest modified Date:2016-08-17
** Latest Version:      V1.2.0
** Descriptions:        Protocol ID definition
**
**--------------------------------------------------------------------------------------------------------
** Created by:          Liu Zhufu
** Created date:        2016-03-15
** Version:             V1.0.0
** Descriptions:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#ifndef PROTOCOLID_H
#define PROTOCOLID_H

typedef enum {
    // Device information
    ProtocolFunctionDeviceInfoBase = 0,
    ProtocolDeviceSN = ProtocolFunctionDeviceInfoBase + 0,
    ProtocolDeviceName = ProtocolFunctionDeviceInfoBase + 1,
    ProtocolDeviceVersion = ProtocolFunctionDeviceInfoBase + 2,

    // Pose
    ProtocolFunctionPoseBase = 10,
    ProtocolGetPose = ProtocolFunctionPoseBase + 0,
    ProtocolResetPose = ProtocolFunctionPoseBase + 1,
    ProtocolGetKinematics = ProtocolFunctionPoseBase + 2,

    // Alarm
    ProtocolFunctionALARMBase = 20,
    ProtocolAlarmsState = ProtocolFunctionALARMBase + 0,

    // HOME
    ProtocolFunctionHOMEBase = 30,
    ProtocolHOMEParams = ProtocolFunctionHOMEBase + 0,
    ProtocolHOMECmd = ProtocolFunctionHOMEBase + 1,

    // HHT
    ProtocolFunctionHHTBase = 40,

    ProtocolHHTTrigMode = ProtocolFunctionHHTBase + 0,
    ProtocolHHTTrigOutputEnabled = ProtocolFunctionHHTBase + 1,
    ProtocolHHTTrigOutput = ProtocolFunctionHHTBase + 2,

    // Function-Arm Orientation
    ProtocolFunctionArmOrientationBase = 50,
    ProtocolArmOrientation = ProtocolFunctionArmOrientationBase + 0,

    // End effector
    ProtocolFunctionEndEffectorBase = 60,
    ProtocolEndEffectorParams = ProtocolFunctionEndEffectorBase + 0,
    ProtocolEndEffectorLaser = ProtocolFunctionEndEffectorBase + 1,
    ProtocolEndEffectorSuctionCup = ProtocolFunctionEndEffectorBase + 2,
    ProtocolEndEffectorGripper = ProtocolFunctionEndEffectorBase + 3,

    // Function-JOG
    ProtocolFunctionJOGBase = 70,
    ProtocolJOGJointParams = ProtocolFunctionJOGBase + 0,
    ProtocolJOGCoordinateParams = ProtocolFunctionJOGBase + 1,
    ProtocolJOGCommonParams = ProtocolFunctionJOGBase + 2,
    ProtocolJOGCmd = ProtocolFunctionJOGBase + 3,

    // Function-PTP
    ProtocolFunctionPTPBase = 80,

    ProtocolPTPJointParams = ProtocolFunctionPTPBase + 0,
    ProtocolPTPCoordinateParams = ProtocolFunctionPTPBase + 1,
    ProtocolPTPJumpParams = ProtocolFunctionPTPBase + 2,
    ProtocolPTPCommonParams = ProtocolFunctionPTPBase + 3,
    ProtocolPTPCmd = ProtocolFunctionPTPBase + 4,

    // Function-CP
    ProtocolFunctionCPBase = 90,

    ProtocolCPParams = ProtocolFunctionCPBase + 0,
    ProtocolCPCmd = ProtocolFunctionCPBase + 1,

    // Function-ARC
    ProtocolFunctionARCBase = 100,

    ProtocolARCParams = ProtocolFunctionARCBase + 0,
    ProtocolARCCmd = ProtocolFunctionARCBase + 1,

    // Function-WAIT
    ProtocolFunctionWAITBase = 110,
    ProtocolWAITCmd = ProtocolFunctionWAITBase + 0,

    // Function-TRIG
    ProtocolFunctionTRIGBase = 120,
    ProtocolTRIGCmd = ProtocolFunctionTRIGBase + 0,

    // Function-EIO
    ProtocolFunctionEIOBase = 130,

    ProtocolIOMultiplexing = ProtocolFunctionEIOBase + 0,
    ProtocolIODO = ProtocolFunctionEIOBase + 1,
    ProtocolIOPWM = ProtocolFunctionEIOBase + 2,
    ProtocolIODI = ProtocolFunctionEIOBase + 3,
    ProtocolIOADC = ProtocolFunctionEIOBase + 4,

    // Function-CAL
    ProtocolFunctionCALBase = 140,
    ProtocolAngleSensorStaticError = ProtocolFunctionCALBase + 0,

    // Function-WIFI
    ProtocolFunctionWIFIBase = 150,
    ProtocolWIFIConfigMode = ProtocolFunctionWIFIBase + 0,
    ProtocolWIFISSID = ProtocolFunctionWIFIBase + 1,
    ProtocolWIFIPassword = ProtocolFunctionWIFIBase + 2,
    ProtocolWIFIIPAddress = ProtocolFunctionWIFIBase + 3,
    ProtocolWIFINetmask = ProtocolFunctionWIFIBase + 4,
    ProtocolWIFIGateway = ProtocolFunctionWIFIBase + 5,
    ProtocolWIFIDNS = ProtocolFunctionWIFIBase + 6,
    ProtocolWIFIConnectStatus = ProtocolFunctionWIFIBase + 7,

    // Function-TEST
    ProtocolTESTBase = 220,
    ProtocolUserParams = ProtocolTESTBase + 0,

    // Function-ZDF
    ProtocolZDFBase = 230,
    ProtocolZDFCalibRequest = ProtocolZDFBase + 0,
    ProtocolZDFCalibStatus = ProtocolZDFBase + 1,

    // Function-QueuedCmd
    ProtocolFunctionQueuedCmdBase = 240,
    ProtocolQueuedCmdStartExec = ProtocolFunctionQueuedCmdBase + 0,
    ProtocolQueuedCmdStopExec = ProtocolFunctionQueuedCmdBase + 1,
    ProtocolQueuedCmdForceStopExec = ProtocolFunctionQueuedCmdBase + 2,
    ProtocolQueuedCmdStartDownload = ProtocolFunctionQueuedCmdBase + 3,
    ProtocolQueuedCmdStopDownload = ProtocolFunctionQueuedCmdBase + 4,
    ProtocolQueuedCmdClear = ProtocolFunctionQueuedCmdBase + 5,
    ProtocolQueuedCmdCurrentIndex = ProtocolFunctionQueuedCmdBase + 6,
    ProtocolQueuedCmdLeftSpace = ProtocolFunctionQueuedCmdBase + 7,

    ProtocolMax = 256
} ProtocolID;

#endif
