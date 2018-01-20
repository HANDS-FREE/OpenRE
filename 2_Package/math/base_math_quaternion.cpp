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
* chenyingbing  2017.4.17   V1.0           creat this file
* Description:
*  Matrix_Cb2n: body frame to reference frame.
*
*  c(pitch)c(yaw)  s(pitch)s(roll)c(yaw)-c(roll)s(yaw)     s(pitch)c(roll)c(yaw)+s(roll)s(yaw)     px
*  c(pitch)s(yaw)  s(pitch)s(roll)s(yaw)+c(roll)c(yaw)     s(pitch)c(roll)s(yaw)-s(roll)c(yaw)     py
*  -s(pitch)       c(pitch)s(roll)                         c(pitch)c(roll)                         pz
*  0               0                                       0                                       1.0
*
*  qw*qw + qx*qx - qy*qy - qz*qz   2*qx*qy - 2*qw*qz               2*qx*qz + 2*qw*qy               px
*  2*qx*qy + 2*qw*qz               qw*qw - qx*qx + qy*qy - qz*qz   2*qy*qz - 2*qw*qx               py
*  2*qx*qz - 2*qw*qy               2*qy*qz + 2*qw*qx               qw*qw - qx*qx - qy*qy + qz*qz   pz
*  0                               0                               0                               1.0
*
*  c(yaw)  -s(yaw)     0     px
*  s(yaw)  c(yaw)      0     py
*  0       0           1     pz
*  0       0           0     1.0
*
***********************************************************************************************************************/

#include "base_math_quaternion.h"

static BASE_MATH_TRIGONOMETRIC bm_tool;

void func_euler2quaternion(Eigen::Vector3f &in_euler, Eigen::Quaternionf &out_q)
{
    float p,r,y;
    p = in_euler.data()[0] * 0.5f,
     r = in_euler.data()[1] * 0.5f,
      y = in_euler.data()[2] * 0.5f;

    out_q.coeffs()[3] = bm_tool.m_cos(r)*bm_tool.m_cos(p)*bm_tool.m_cos(y) + bm_tool.m_sin(r)*bm_tool.m_sin(p)*bm_tool.m_sin(y);	//When yaw: 	cos(yaw*0.5f)
    out_q.coeffs()[0] = bm_tool.m_sin(r)*bm_tool.m_cos(p)*bm_tool.m_cos(y) - bm_tool.m_cos(r)*bm_tool.m_sin(p)*bm_tool.m_sin(y);	//		0
    out_q.coeffs()[1] = bm_tool.m_cos(r)*bm_tool.m_sin(p)*bm_tool.m_cos(y) + bm_tool.m_sin(r)*bm_tool.m_cos(p)*bm_tool.m_sin(y);	//		0
    out_q.coeffs()[2] = bm_tool.m_cos(r)*bm_tool.m_cos(p)*bm_tool.m_sin(y) - bm_tool.m_sin(r)*bm_tool.m_sin(p)*bm_tool.m_cos(y);	//		sin(yaw*0.5f)

    out_q.normalize();
}

void func_quaternion2euler(Eigen::Quaternionf &in_q, Eigen::Vector3f &out_euler)
{
    #define qw      in_q.w()
    #define qx      in_q.x()
    #define qy      in_q.y()
    #define qz      in_q.z()

    out_euler.data()[1] = bm_tool.m_atan2(2*qy*qz + 2*qw*qx, 1 - (qx*qx + qy*qy)*2.0f);	// A6/A10
    out_euler.data()[0] = bm_tool.m_asin(2*qw*qy - 2*qx*qz);                            // A2
    out_euler.data()[2] = bm_tool.m_atan2(2*qx*qy + 2*qw*qz, 1 - (qy*qy + qz*qz)*2.0f);	// A1/A0
}

void func_dquaternion(Eigen::Quaternionf &in_q, Eigen::Vector3f &in_u, Eigen::Quaternionf &out_dq)
{
    #define qw      in_q.w()
    #define qx      in_q.x()
    #define qy      in_q.y()
    #define qz      in_q.z()

    #define gx      in_u.data()[0]
    #define gy      in_u.data()[1]
    #define gz      in_u.data()[2]

    out_dq.coeffs()[3] =        - gx*qx - gy*qy - gz*qz,
    out_dq.coeffs()[0] =  gx*qw         + gz*qy - gy*qz,
    out_dq.coeffs()[1] =  gy*qw - gz*qx         + gx*qz,
    out_dq.coeffs()[2] =  gz*qw + gy*qx - gx*qy        ;
}






