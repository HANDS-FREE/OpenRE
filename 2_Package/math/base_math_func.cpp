#include "base_math_func.h"

float smart_sqrt(float number)
{
    long i;
    float x2, y;
    const float threehalfs = 1.5f;
    float deal;

    x2 = number * 0.5f;
    y   = number;
    i   = * ( long * ) &y;
    i   = 0x5f3759df - ( i >> 1 );
    y   = * ( float * ) &i;
    y   = y * ( threehalfs - ( x2 * y * y ) ); 	// 1st iteration
    // y   = y * ( threehalfs - ( x2 * y * y ) ); // 2nd iteration, this can be removed

    deal = 1/y;

    return deal;
}


