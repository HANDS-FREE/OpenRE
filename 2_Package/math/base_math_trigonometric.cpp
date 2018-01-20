/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* Contact:  QQ Exchange Group -- 521037187
*
* LICENSING TERMS:
* The Hands Free is licensed generally under a permissive 3-clause BSD license. 
* Contributions are requiredto be made under the same license.
*
* History:
* <author>      <time>      <version>      <desc>
* chenyingbing  2015.12.1   V1.6           creat this file
* chenyingbing  2017.04.17  update: look-up table
* Description:  本文件封装了基本的数学三角函数
*
***********************************************************************************************************************/

#include "base_math_trigonometric.h"
#include "math.h"

#if BASE_MATH_TRIGONOMETRIC_EN  > 0u

BASE_MATH_TRIGONOMETRIC base_math_trigonometic;


#define PI           3.1415926536f
#define PI_2         1.5707963268f
#define C_RADIAN     57.2957795f
#define _C_RADIAN    0.0174533f

#define sin_chart_d     0.25f

bool sin_chart_init(void);
float t_sin(float dtain);
float t_cos(float dtain);

bool BASE_MATH_TRIGONOMETRIC::init(void)
{
    return sin_chart_init();
}

float BASE_MATH_TRIGONOMETRIC::m_sin(float angle_radian)
{
#if USE_ARM_MATH_LIB >0u
    return arm_sin_f32(angle_radian);
#else
    sin_chart_init();
    return t_sin(angle_radian);
#endif
}

float BASE_MATH_TRIGONOMETRIC::m_cos(float angle_radian)
{
#if USE_ARM_MATH_LIB >0u
    return arm_cos_f32(angle_radian);
#else
    sin_chart_init();
    return t_cos(angle_radian);
#endif
}

float BASE_MATH_TRIGONOMETRIC::m_tan(float angle_radian)
{
#if USE_ARM_MATH_LIB >0u
    return (arm_sin_f32(angle_radian)/arm_cos_f32(angle_radian));
#else
    sin_chart_init();
    return (t_sin(angle_radian)/t_cos(angle_radian));
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



static bool chart_init = false;
static double sin_chart[361];

bool sin_chart_init(void)
{
    static float d1 = 0.25f / C_RADIAN;
    if(!chart_init)
    {
        int i;
        float fi;
        for(i=0, fi=0.0f; i<361; i++)
        {
            fi = (float)i * d1;
            sin_chart[i] = sin(fi);
        }

        chart_init = true;
    }
    return chart_init;
}

float t_sin(float dtain)
{
    if( (0<=dtain) && (dtain<=PI_2) )
    {
        dtain *= C_RADIAN;

        float d1, d2;
        d1 = floor(dtain * 4) * 0.25f;
        d2 = dtain - d1;

        int di;
        di = d1 * 4;

        d1 = sin_chart[di];
        if(di < 360)
            d2 = (sin_chart[di+1]-sin_chart[di]) * d2;
        else
            d2 = 0;

        return (d1+d2);
    }else if(dtain > PI_2)
    {
        return t_sin(PI - dtain);
    }else{
        dtain *= -1;
        return -t_sin(dtain);
    }
}

float t_cos(float dtain)
{
    dtain = dtain + PI_2;
    if(dtain > PI) dtain = -2*PI + dtain;

    return t_sin(dtain);
}

#endif  //#if BASE_MATH_TRIGONOMETRIC_EN  > 0u

