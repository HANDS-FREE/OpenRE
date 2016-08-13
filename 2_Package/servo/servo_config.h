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

#ifndef SERVO_CONFIG_H
#define SERVO_CONFIG_H

#include "main_config.h"
#include "board.h"

//the AX digital servo pose be divided into 1024 unit 0~0X3FF
//counterclockwise is positive
//HEAD  Pitch>0 Look up  ; Pitch<0 Look down ; YAW>0 Look left  ; YAW<0 Look right
#define SERVO_DEBUG_EN     0u      // printf debug info

#endif   // #ifndef SERVO_CONFIG_H

