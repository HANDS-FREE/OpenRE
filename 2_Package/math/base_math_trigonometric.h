#ifndef BASE_MATH_TRIGONOMETRIC_H
#define BASE_MATH_TRIGONOMETRIC_H

#include "base_math_config.h"
#include "math.h"

#if USE_ARM_MATH_LIB >0u
#include "arm_math.h" 
#endif

class BASE_MATH_TRIGONOMETRIC
{	

public:
    BASE_MATH_TRIGONOMETRIC(void);

    float m_sin(float angle_radian);
    float m_cos(float angle_radian);
    float m_tan(float angle_radian);

    float m_asin(float value);
    float m_acos(float value);
    float m_atan2(float deal1, float deal2);

private:

};

extern BASE_MATH_TRIGONOMETRIC base_math_trigonometic;

#endif // #ifndef BASE_MATH_TRIGONOMETRIC_H
