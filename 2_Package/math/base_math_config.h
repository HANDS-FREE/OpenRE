/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: base_math_config.h
* Contact:  QQ Exchange Group -- 521037187
* Version:  V2.0
*
* LICENSING TERMS:
* The Hands Free is licensed generally under a permissive 3-clause BSD license. 
* Contributions are requiredto be made under the same license.
*
* History:
* <author>      <time>      <version>      <desc>
* chenyingbing  2015.12.1   V1.6           creat this file
* Description:  基本的数学包的配置文件
*
***********************************************************************************************************************/

#ifndef BASE_MATH_CONFIG_H
#define BASE_MATH_CONFIG_H

#include "main_config.h"

//是否使用ARM的数学库，如果使用，则数学计算尽可能使用ARM的数学库，若不使能，则使用math.h库
#define  USE_ARM_MATH_LIB     				  0u      
#define  BASE_MATH_MATRIX_EN     				1u      //是否编译math_matrix
#define  BASE_MATH_TRIGONOMETRIC_EN			1u			//是否编译math_trigonometric

#endif // #ifndef BASE_MATH_CONFIG_H






