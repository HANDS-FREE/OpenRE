#ifndef AL_FMODEL_FRAME_H
#define AL_FMODEL_FRAME_H

    #include "imu_config.h"

    #include "math/base_math_top.h"

    #include "al_model_ekf.h"
    #include "al_model_typicalcorrect.h"

    void floatxyz_norm(FLOAT_XYZ &data);
    void floatpry_norm(FLOAT_PRY &data);
    void floatvector_norm(Eigen::Vector3f &data);
    void quaternion_add(Eigen::Quaternionf &q_ad1, Eigen::Quaternionf &q_ad2, Eigen::Quaternionf &q_sum);
    void quaternion_quaternion_xk(float k, Eigen::Quaternionf &out_q);

    class IMU_MODEL
    {
    public:

        IMU_MODEL(){
            update_en = false;

            mtool.init();

            s_pryaw.pitch = 0, s_pryaw.roll = 0, s_pryaw.yaw = 0;

            x_q.coeffs()[3] = 1, x_q.coeffs()[0] = 0, x_q.coeffs()[1] = 0, x_q.coeffs()[2] = 0;
            x_qpre.coeffs()[3] = 1, x_qpre.coeffs()[0] = 0, x_qpre.coeffs()[1] = 0, x_qpre.coeffs()[2] = 0;
            dq.coeffs()[3] = 1, dq.coeffs()[0] = 0, dq.coeffs()[1] = 0, dq.coeffs()[2] = 0;

            z_acc.setZero(), z_gyro.setZero(), z_hmc.setZero();
            z_acc_norm.setZero(), z_hmc_norm.setZero();

            z_acc_i.setZero(), z_hmc_i.setZero();
            z_acc_i_norm.setZero(), z_hmc_i_norm.setZero();

            acc_norm_ref.setZero(), acc_norm_ref.data()[2] = 1.0f;

            float *mat_data;
            mat_data = Cn2b.mat.data();
            mat_data[0] = 1.0f, mat_data[3] = 0.0f, mat_data[6] = 0.0f;
            mat_data[1] = 0.0f, mat_data[4] = 1.0f, mat_data[7] = 0.0f;
            mat_data[2] = 0.0f, mat_data[5] = 0.0f, mat_data[8] = 1.0f;

            mat_data = Cb2n.mat.data();
            mat_data[0] = 1.0f, mat_data[3] = 0.0f, mat_data[6] = 0.0f;
            mat_data[1] = 0.0f, mat_data[4] = 1.0f, mat_data[7] = 0.0f;
            mat_data[2] = 0.0f, mat_data[5] = 0.0f, mat_data[8] = 1.0f;
        }

        /// system port **************************************
        FLOAT_PRY s_pryaw;                // {pitch, roll, yaw}

        void debug(void);

        void model_data_update(bool havedrift,
                               FLOAT_XYZ &zdta_acc, FLOAT_XYZ &zdta_acc_cov,
                               FLOAT_XYZ &zdta_gyro, FLOAT_XYZ &zdta_gyro_cov,
                               FLOAT_XYZ &zdta_hmc);

        void model_updates(float imu_t);

    private:
        /// sta ***********************************************
        bool update_en;

        /// tools *********************************************
        BASE_MATH_TRIGONOMETRIC mtool;

        MODEL_EKF model_ekf;
        MODEL_TCORRECT model_tcorrect;

        Eigen::Vector3f tmp_mes_pry;
        void model_mes_pry(void);
        void model_update_xpre(float imu_t);
        void model_update_sta(void);

        /// system state **************************************
        /// x: prefix of system states.
        /// s: prefix of port states.
        /// u: prefix of control variable.
        /// z: prefix of obeserve variable.
        /// _ref    : suffix to identify the reference data
        /// _pre    : suffix to identify the prediction data
        /// _fus    : suffix to identify the fusion data

        BMATH_RMAT Cn2b, Cb2n;

        Eigen::Quaternionf x_q;           // {x, y, z, w}
        Eigen::Quaternionf x_qpre;
        Eigen::Quaternionf dq;

        // if the bobal variable is declared here, it may cause the problem that, some s
        Eigen::Vector3f z_acc, z_gyro, z_hmc;
        Eigen::Vector3f z_acc_norm, z_hmc_norm;
        Eigen::Vector3f zacc_cov, zgyro_cov;

        Eigen::Vector3f acc_norm_ref, hmc_norm_ref;

        Eigen::Vector3f z_acc_i, z_hmc_i;
        Eigen::Vector3f z_acc_i_norm, z_hmc_i_norm;

        /// system processes **********************************


    };

    // [ERROR]: if the bobal variable is declared here, it may cause the problem that, the members
    // in IMU_MODEL can't call their own construct function successfully.

#endif  // #ifndef AL_FMODEL_FRAME_H
