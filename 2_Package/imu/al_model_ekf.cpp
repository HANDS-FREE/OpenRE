/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: imu_gps_driver.cpp
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
* chenyingbing  2017.4.17   V1.7           update: using eigen
* Description:
*   ekf model to correct the pitch, roll according to sensor accelerometer.
*
***********************************************************************************************************************/


#include "al_model_ekf.h"

#include "Eigen3/Eigen/Dense"
#include "Eigen3/Eigen/Geometry"

/// >------------------------------
/// public
static float imut_2;
void MODEL_EKF::fill_data(float imu_t,
                          Eigen::Quaternionf &q, Eigen::Vector3f g,
                          Eigen::Vector3f &u_cov, Eigen::Vector3f z_cov)
{
    imut_2 = imu_t * 0.5f;
    g *= imut_2;

    /// f_dx 4x4
    /*
    f_dx << 0,              -g.data()[0],   -g.data()[1],   -g.data()[2],
            g.data()[0],    0,              g.data()[2],    -g.data()[1],
            g.data()[1],    -g.data()[2],   0,              g.data()[0],
            g.data()[2],    g.data()[1],    -g.data()[0],   0;          */

    f_dx.data()[0] = 0,            f_dx.data()[4] = -g.data()[0], f_dx.data()[8]  = -g.data()[1],	f_dx.data()[12] = -g.data()[2],
    f_dx.data()[1] = g.data()[0],  f_dx.data()[5] = 0,            f_dx.data()[9]  = g.data()[2],    f_dx.data()[13] = -g.data()[1],
    f_dx.data()[2] = g.data()[1],  f_dx.data()[6] = -g.data()[2], f_dx.data()[10] = 0,              f_dx.data()[14] = g.data()[0],
    f_dx.data()[3] = g.data()[2],  f_dx.data()[7] = g.data()[1],  f_dx.data()[11] = -g.data()[0],	f_dx.data()[15] = 0;

    /// h_dx 3x4
    static float dq0, dq1, dq2, dq3;

    dq0 = q.w() * 2,
    dq1 = q.x() * 2,
    dq2 = q.y() * 2,
    dq3 = q.z() * 2;

    /*
    h_dx << -dq2,   dq3,    -dq0,   dq1,
            dq1,    dq0,    dq3,    dq2,
            dq0,    -dq1,   -dq2,   dq3;    */

    h_dx.data()[0] = -dq2,  h_dx.data()[3] = dq3,   h_dx.data()[6] = -dq0,  h_dx.data()[9] = dq1,
    h_dx.data()[1] = dq1,   h_dx.data()[4] = dq0,   h_dx.data()[7] = dq3,   h_dx.data()[10] = dq2,
    h_dx.data()[2] = dq0,   h_dx.data()[5] = -dq1,  h_dx.data()[8] = -dq2,  h_dx.data()[11] = dq3;

    /// pre_cov 4x4
    dq0 = q.w(),
    dq1 = q.x(),
    dq2 = q.y(),
    dq3 = q.z();

    pre_cov.data()[0]  = u_cov.data()[0],
    pre_cov.data()[5]  = u_cov.data()[0],
    pre_cov.data()[10] = u_cov.data()[1],
    pre_cov.data()[15] = u_cov.data()[2];

    /// mes_cov 3x3
    static float zcov_min[3] = {0.01, 0.01, 0.01};
    if(z_cov.data()[0] < zcov_min[0]) z_cov.data()[0] = zcov_min[0];
    if(z_cov.data()[1] < zcov_min[1]) z_cov.data()[1] = zcov_min[1];
    if(z_cov.data()[2] < zcov_min[2]) z_cov.data()[2] = zcov_min[2];

    mes_cov.data()[0] = z_cov.data()[0],
    mes_cov.data()[4] = z_cov.data()[1],
    mes_cov.data()[8] = z_cov.data()[2];
}

Eigen::Quaternionf MODEL_EKF::ekf_process(Eigen::Quaternionf &q_pre,
                                          Eigen::Vector3f &z, Eigen::Vector3f &z_i)
{
    /* -------------------------------
        Eigen::Matrix4f P, P_pre;

    ------------------------------- */

    static Eigen::Quaternionf q_r;
    static Eigen::Vector4f vq, vq_pre, dq;

    vq_pre.data()[0] = q_pre.w(),
     vq_pre.data()[1] = q_pre.x(),
      vq_pre.data()[2] = q_pre.y(),
       vq_pre.data()[3] = q_pre.z();

    /// update ekf
    u_update(); // P_pre = f_dx * P + P * f_dx.transpose() + pre_cov;
    z_update(); // Kk = P_pre * h_dx_T * (h_dx * P_pre * h_dx_T + mes_cov).inverse();
    p_update(); // P = (mat_I - Kk * h_dx) * P_pre;

    /// update return q
    // 4x1 = 4x3 * (3x1 - 3x1)
    dq = Kk * (z - z_i);
    vq = vq_pre + dq;

    q_r.coeffs()[3] = vq.data()[0],
     q_r.coeffs()[0] = vq.data()[1],
      q_r.coeffs()[1] = vq.data()[2],
       q_r.coeffs()[2] = vq.data()[3];

    //printf("pre_cov: %f, %f, %f, %f \r\n", pre_cov.data()[0], pre_cov.data()[5], pre_cov.data()[10], pre_cov.data()[15]);

    //printf("test0: %f, %f, %f \r\n", mes_cov.data()[0], mes_cov.data()[4], mes_cov.data()[8]);

    //printf("test0: %f, %f, %f, %f \r\n", dq.data()[0], dq.data()[1], dq.data()[2], dq.data()[3]);

    /*
    printf("t: %f, %f, %f \r\n   %f, %f, %f \r\n   %f, %f, %f \r\n   %f, %f, %f \r\n",
                                                Kk.data()[0], Kk.data()[4], Kk.data()[8],       // change much
                                                Kk.data()[1], Kk.data()[5], Kk.data()[9],
                                                Kk.data()[2], Kk.data()[6], Kk.data()[10],
                                                Kk.data()[3], Kk.data()[7], Kk.data()[11]);     // change much

    */

    return q_r;
}

/// >------------------------------
/// private
inline void MODEL_EKF::u_update(void)
{
    //4x4   = 4x4 * 4x4 + 4x4 * 4x4 + 4x4
    P_pre = f_dx*P + P*(f_dx.transpose()) + pre_cov;
}

inline void MODEL_EKF::z_update(void)
{
    static Eigen::Matrix<float, 4, 3> h_dx_T;
    h_dx_T = h_dx.transpose();

    static Eigen::Matrix3f mat_d;
    //3x3 = 3x4 * 4x4 * 4*3 + 3x3
    mat_d = (h_dx * P_pre * h_dx_T + mes_cov).inverse();

    //4x3 = 4x4 * 4x3 * (3x3^-1)
    Kk = P_pre * h_dx_T * mat_d;
}

inline void MODEL_EKF::p_update(void)
{
    static Eigen::Matrix4f D;

    // 4x4 = (4x4 - 4x3*3x4) * 4x4
    D = mat_I - Kk * h_dx;
    P = D * P_pre;

    static unsigned debug = 0;
    if(debug > 0)
    {
        --debug;
        printf("D: %f, %f, %f, %f \r\n   %f, %f, %f, %f \r\n   %f, %f, %f, %f \r\n   %f, %f, %f, %f \r\n",
                                                    D.data()[0], D.data()[4], D.data()[8],  D.data()[12],
                                                    D.data()[1], D.data()[5], D.data()[9],  D.data()[13],
                                                    D.data()[2], D.data()[6], D.data()[10], D.data()[14],
                                                    D.data()[3], D.data()[7], D.data()[11], D.data()[15]);

        printf("P_pre: %f, %f, %f, %f \r\n       %f, %f, %f, %f \r\n       %f, %f, %f, %f \r\n       %f, %f, %f, %f \r\n",
                                                    P_pre.data()[0], P_pre.data()[4], P_pre.data()[8],  P_pre.data()[12],
                                                    P_pre.data()[1], P_pre.data()[5], P_pre.data()[9],  P_pre.data()[13],
                                                    P_pre.data()[2], P_pre.data()[6], P_pre.data()[10], P_pre.data()[14],
                                                    P_pre.data()[3], P_pre.data()[7], P_pre.data()[11], P_pre.data()[15]);

        printf("Pre_C: %f, %f, %f, %f \r\n       %f, %f, %f, %f \r\n       %f, %f, %f, %f \r\n       %f, %f, %f, %f \r\n",
                                                    pre_cov.data()[0], pre_cov.data()[4], pre_cov.data()[8],  pre_cov.data()[12],
                                                    pre_cov.data()[1], pre_cov.data()[5], pre_cov.data()[9],  pre_cov.data()[13],
                                                    pre_cov.data()[2], pre_cov.data()[6], pre_cov.data()[10], pre_cov.data()[14],
                                                    pre_cov.data()[3], pre_cov.data()[7], pre_cov.data()[11], pre_cov.data()[15]);

        printf("P: %f, %f, %f, %f \r\n   %f, %f, %f, %f \r\n   %f, %f, %f, %f \r\n   %f, %f, %f, %f \r\n",
                                                    P.data()[0], P.data()[4], P.data()[8],  P.data()[12],
                                                    P.data()[1], P.data()[5], P.data()[9],  P.data()[13],
                                                    P.data()[2], P.data()[6], P.data()[10], P.data()[14],
                                                    P.data()[3], P.data()[7], P.data()[11], P.data()[15]);

    }
}



