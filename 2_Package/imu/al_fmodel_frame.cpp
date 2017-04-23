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
* chenyingbing  2017.4.17   V1.7           update: using eigen, add yaw correction.
* Description:  the model of filtering.
*
***********************************************************************************************************************/

#include "al_fmodel_frame.h"

/// >-----------------------------------------------------------------------------------------------------------------------------
/// basic func
void floatxyz_norm(FLOAT_XYZ &data)
{
    static float norm;
    norm = 1.0f / smart_sqrt(data.x * data.x + data.y * data.y + data.z * data.z);

    data.x *= norm;
    data.y *= norm;
    data.z *= norm;
}

void floatpry_norm(FLOAT_PRY &data)
{
    static float norm;
    norm = 1.0f / smart_sqrt(data.pitch * data.pitch + data.roll * data.roll + data.yaw * data.yaw);

    data.pitch *= norm;
    data.roll *= norm;
    data.yaw *= norm;
}

void floatvector_norm(Eigen::Vector3f &data)
{
    static float norm;
    norm = 1.0f / smart_sqrt(data.data()[0] * data.data()[0] + data.data()[1] * data.data()[1] + data.data()[2] * data.data()[2]);

    data.data()[0] *= norm;
    data.data()[1] *= norm;
    data.data()[2] *= norm;
}

void quaternion_add(Eigen::Quaternionf &q_ad1, Eigen::Quaternionf &q_ad2, Eigen::Quaternionf &q_sum)
{
    q_sum.coeffs()[0] = q_ad1.coeffs()[0] + q_ad2.coeffs()[0];
    q_sum.coeffs()[1] = q_ad1.coeffs()[1] + q_ad2.coeffs()[1];
    q_sum.coeffs()[2] = q_ad1.coeffs()[2] + q_ad2.coeffs()[2];
    q_sum.coeffs()[3] = q_ad1.coeffs()[3] + q_ad2.coeffs()[3];
}

void quaternion_quaternion_xk(float k, Eigen::Quaternionf &out_q)
{
    out_q.coeffs()[0] *= k;
    out_q.coeffs()[1] *= k;
    out_q.coeffs()[2] *= k;
    out_q.coeffs()[3] *= k;
}

/// >-----------------------------------------------------------------------------------------------------------------------------
/// IMU_MODEL Debug
void IMU_MODEL::debug(void)
{
    Eigen::Vector3f data, data1, data_ans;
    Eigen::Quaternionf q_l, q_r, q_ans;

    data.data()[0] = 0, data.data()[1] = 0, data.data()[2] = 0.5;
    data1.data()[0] = 0, data1.data()[1] = 0, data1.data()[2] = 0.3;

    /// void func_euler2quaternion(Eigen::Vector3f &in_euler, Eigen::Quaternionf &out_q);
    /// void func_quaternion2euler(Eigen::Quaternionf &in_q, Eigen::Vector3f &out_euler);

    /// q_ans.coeffs()[3]
    /// q_ans.normalize
    /// data_ans = data.cross(data1);
    /// int d_ans = data.dot(data1);

    // printf("ans1: %f, %f, %f \r\n", data_ans.data()[0], data_ans.data()[1], data_ans.data()[2]);
    // printf("ans2: %f, %f, %f, %f \r\n", q_ans.coeffs()[0], q_ans.coeffs()[1], q_ans.coeffs()[2], q_ans.coeffs()[3]);

}

/// >-----------------------------------------------------------------------------------------------------------------------------
/// IMU_MODEL Tools
void IMU_MODEL::model_mes_pry(void)
{
    static float p, r, y;
    static float d1, d2;

    p = -mtool.m_asin(z_acc_norm.data()[0]);
    r = mtool.m_atan2(z_acc_norm.data()[1], z_acc_norm.data()[2]);

    d1 = z_hmc_norm.data()[1] * mtool.m_cos(r) - z_hmc_norm.data()[2] * mtool.m_sin(r);
    d2 = z_hmc_norm.data()[0] * mtool.m_cos(p) + z_hmc_norm.data()[1] * mtool.m_sin(p) * mtool.m_sin(r) + z_hmc_norm.data()[2] * mtool.m_sin(p) * mtool.m_cos(r);
    y =  -mtool.m_atan2(d1,d2);

    tmp_mes_pry.data()[0] = p;
    tmp_mes_pry.data()[1] = r;
    tmp_mes_pry.data()[2] = y;
}

void IMU_MODEL::model_update_xpre(float imu_t)
{
    Eigen::Vector3f gyro_t = z_gyro * imu_t * 0.5f;

    func_dquaternion(x_q, gyro_t, dq);

    quaternion_add(x_q, dq, x_qpre);

    //x_q = x_qpre;
}

void IMU_MODEL::model_update_sta(void)
{
    #define radian2degree   57.3f

    Eigen::Vector3f out_euler;
    func_quaternion2euler(x_q, out_euler);

    s_pryaw.pitch = out_euler.data()[0] * radian2degree,
     s_pryaw.roll = out_euler.data()[1] * radian2degree,
      s_pryaw.yaw = out_euler.data()[2] * radian2degree;
}

/// >-----------------------------------------------------------------------------------------------------------------------------
/// IMU_MODEL Portfunc
//  time cost [stm32f4]: 0.3ms
void IMU_MODEL::model_data_update(bool havedrift,
                                  FLOAT_XYZ &zdta_acc, FLOAT_XYZ &zdta_acc_cov,
                                  FLOAT_XYZ &zdta_gyro, FLOAT_XYZ &zdta_gyro_cov,
                                  FLOAT_XYZ &zdta_hmc)
{
    static bool fisrt_init = true;

    if(havedrift)
    {
        z_acc.data()[0] = zdta_acc.x,
         z_acc.data()[1] = zdta_acc.y,
          z_acc.data()[2] = zdta_acc.z;

        zacc_cov.data()[0] = zdta_acc_cov.x,
         zacc_cov.data()[1] = zdta_acc_cov.y,
          zacc_cov.data()[2] = zdta_acc_cov.z;

        z_gyro.data()[0] = zdta_gyro.x,
         z_gyro.data()[1] = zdta_gyro.y,
          z_gyro.data()[2] = zdta_gyro.z;

        zgyro_cov.data()[0] = zdta_gyro_cov.x,
         zgyro_cov.data()[1] = zdta_gyro_cov.y,
          zgyro_cov.data()[2] = zdta_gyro_cov.z;

        z_hmc.data()[0] = zdta_hmc.x,
         z_hmc.data()[1] = zdta_hmc.y,
          z_hmc.data()[2] = zdta_hmc.z;

        z_acc_norm = z_acc, floatvector_norm(z_acc_norm);
        z_hmc_norm = z_hmc, floatvector_norm(z_hmc_norm);

        if(fisrt_init)
        {
            hmc_norm_ref = z_hmc_norm;

            fisrt_init = false;
        }

        update_en = true;
    }
}

//  time cost [stm32f4]: 0.65ms(acc/ekf) + 0.05ms(hmc/error correct)
void IMU_MODEL::model_updates(float imu_t)
{
    if(update_en)
    {
        Cn2b.fufill_Cn2b(x_q);
        Cb2n.mat = Cn2b.mat.transpose();

        z_acc_i = Cn2b.mat * acc_norm_ref;
        z_acc_i_norm = z_acc_i;
        floatvector_norm(z_acc_i_norm);

        z_hmc_i = Cn2b.mat * hmc_norm_ref;
        z_hmc_i_norm = z_hmc_i;
        floatvector_norm(z_hmc_i_norm);

        /// model_tcorrect
        model_tcorrect.gyro_yawcorrect(imu_t,
                                       z_gyro,
                                       z_hmc_norm,
                                       z_hmc_i_norm);
        /// model procession predict
        model_update_xpre(imu_t);

        /// model_ekf
        model_ekf.fill_data(imu_t,
                            x_q, z_gyro,
                            zgyro_cov, zacc_cov);

        x_q = model_ekf.ekf_process(x_qpre, z_acc_norm, z_acc_i_norm), x_q.normalize();

        /// norm the state, and refresh the port variable: s_pryaw
        x_q.normalize();
        model_update_sta();

        //printf("Test0: %f, %f, %f \r\n", zacc_cov.data()[0], zacc_cov.data()[1], zacc_cov.data()[2]);
        //printf("test1: %f, %f, %f \r\n", z_acc_i_norm.data()[0], z_acc_i_norm.data()[1], z_acc_i_norm.data()[2]);

        //printf("dq: %f, %f, %f, %f \r\n", dq.w(), dq.x(), dq.y(), dq.z());

        //printf("xq: %f, %f, %f, %f \r\n", x_q.w(), x_q.x(), x_q.y(), x_q.z());
        //printf("dg: %f, %f, %f \r\n", z_gyro.data()[0], z_gyro.data()[1], z_gyro.data()[2]);

    }
}




