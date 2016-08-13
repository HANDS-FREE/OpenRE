/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: base_math_trigonometric.cpp
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
* Description:  本文件封装了基本的数学三角函数
*
***********************************************************************************************************************/

#include "base_math_trigonometric.h"

BASE_MATH_TRIGONOMETRIC base_math_trigonometic;

#if BASE_MATH_TRIGONOMETRIC_EN  > 0u

BASE_MATH_TRIGONOMETRIC::BASE_MATH_TRIGONOMETRIC(void)
{
}

/***********************************************************************************************************************
* Function:    
*
* Scope:        public
*
* Description:	handsfree 基本数学函数库
*
* Arguments:
*
* Return:
*
* Cpu_Time:    
*
* History:
* by   chenyingbing  2015.12.1   creat
***********************************************************************************************************************/
float BASE_MATH_TRIGONOMETRIC::m_sin(float angle_radian)
{
#if USE_ARM_MATH_LIB >0u
    return arm_sin_f32(angle_radian);
#else
    return sin(angle_radian);
#endif
}

float BASE_MATH_TRIGONOMETRIC::m_cos(float angle_radian)
{
#if USE_ARM_MATH_LIB >0u
    return arm_cos_f32(angle_radian);
#else
    return cos(angle_radian);
#endif
}

float BASE_MATH_TRIGONOMETRIC::m_tan(float angle_radian)
{
#if USE_ARM_MATH_LIB >0u
    return (arm_sin_f32(angle_radian)/arm_cos_f32(angle_radian));
#else
    return tan(angle_radian);
#endif
}

float BASE_MATH_TRIGONOMETRIC::m_asin(float value)
{
    return asin(value);
}

float BASE_MATH_TRIGONOMETRIC::m_acos(float value)
{
    return acos(value);
}

float BASE_MATH_TRIGONOMETRIC::m_atan2(float deal1, float deal2)
{
    return atan2(deal1,deal2);
}

#endif  //#if BASE_MATH_TRIGONOMETRIC_EN  > 0u

