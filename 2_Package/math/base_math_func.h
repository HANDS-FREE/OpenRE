#ifndef BASE_MATH_FUNC
#define BASE_MATH_FUNC

#include "base_math_config.h"

#if BASE_MATH_FUNC_EN == 1u
    #include <math.h>

    float smart_sqrt(float number);
#endif

#endif // #ifndef BASE_MATH_FUNC

