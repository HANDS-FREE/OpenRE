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

#define  BASE_MATH_FUNC_EN                  1u          //是否编译 math_func            :   some quick caculational function, such as smart_sqrt and so on..

#define  BASE_MATH_MATRIX_EN                1u          //是否编译 math_matrix          :   Eigen + self-defined class/function

#define  BASE_MATH_TRIGONOMETRIC_EN			1u			//是否编译 math_trigonometric   :   Look-up table if USE_ARM_MATH_LIB == 0

#define  BASE_MATH_QUATERNION_EN            1u          //是否编译 math_quaternion      :   Eigen + self-defined class/function

#endif // #ifndef BASE_MATH_CONFIG_H






