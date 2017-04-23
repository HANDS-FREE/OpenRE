#ifndef BASE_MATH_QUATERNION_H
#define BASE_MATH_QUATERNION_H

#include "base_math_config.h"

#if BASE_MATH_QUATERNION_EN == 1u
    #include "Eigen3/Eigen/Core"
    #include "Eigen3/Eigen/Geometry"
    #include "base_math_trigonometric.h"
    using namespace Eigen;

    void func_euler2quaternion(Eigen::Vector3f &in_euler, Eigen::Quaternionf &out_q);
    void func_quaternion2euler(Eigen::Quaternionf &in_q, Eigen::Vector3f &out_euler);

    void func_dquaternion(Eigen::Quaternionf &in_q, Eigen::Vector3f &in_u, Eigen::Quaternionf &out_dq);
#endif


#endif // #ifndef BASE_MATH_QUATERNION_H

