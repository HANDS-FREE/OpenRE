/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: imu_config.h
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
* chenyingbing  2015.12.1   V1.6           update
* Description:  
*
***********************************************************************************************************************/

#ifndef IMU_CONFIG_H
#define IMU_CONFIG_H

#include "main_config.h"
#include "board.h"

#ifdef PAKG_MATH
#include "base_math_top.h"
#endif


// 算法类
#define SYSTEM_SUPPROT_FUSION_ARITHMETIC		    1u		//是否使能IMU融合算法

#if SYSTEM_SUPPROT_FUSION_ARITHMETIC > 0u

#if ((SYSTEM_SUPPORT_IMU_MPU6050||SYSTEM_SUPPORT_IMU_HMC5883l)) > 0
#define ACTIVE_CALCULATE_MESANGLE						1u		  	//动态 计算加速度计/磁罗盘 测量角度
#endif

#if (SYSTEM_SUPPORT_IMU_MPU6050&&SYSTEM_SUPPORT_IMU_HMC5883l) > 0
#define ARITHMETIC_MPUHMC5883_EGyroCorrect	1u				//使能 基于 叉积误差修正的融合算法 > Yaw
#endif

#if (SYSTEM_SUPPORT_IMU_MPU6050) > 0
#define ARITHMETIC_MPU6050_EXTENDEDKALMAN		1u				//使能 基于 加速度计陀螺仪的扩展卡尔曼滤波融合算法 > Pitch Roll
#endif

#endif

typedef struct INT16_XYZ{
	short int  x;
	short int  y;
	short int  z;}INT16_XYZ;

typedef struct FLOAT_XYZ{
    float x;
    float y;
    float z;}FLOAT_XYZ;

typedef struct FLOAT_PRY{
    float pitch;
    float roll;
    float yaw;}FLOAT_PRY;


#endif  //#ifndef IMU_CONFIG_H


