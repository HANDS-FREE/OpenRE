#ifndef BASE_MATH_MATRIX_H
#define BASE_MATH_MATRIX_H

#include "base_math_config.h"

#if BASE_MATH_MATRIX_EN == 1u
    #include "Eigen3/Eigen/Core"
    #include "Eigen3/Eigen/LU"
    #include "Eigen3/Eigen/Geometry"

    using namespace Eigen;

    class BMATH_RMAT
    {   /// typical rotate matrix3f init.
    public:
        BMATH_RMAT()
        {
            mat << 1, 0, 0,
                   0, 1, 0,
                   0, 0, 1;
        }

        Eigen::Matrix3f mat;

        void fufill_Cb2n(Eigen::Quaternionf &in_q);
        void fufill_Cn2b(Eigen::Quaternionf &in_q);

    private:

    };


#endif

#endif // #ifndef BASE_MATH_MATRIX_H

