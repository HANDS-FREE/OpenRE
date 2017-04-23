#ifndef AL_MODEL_EKF_H
#define AL_MODEL_EKF_H

    #include "imu_config.h"

    #include "math/base_math_top.h"

    class MODEL_EKF
    {
    public:
        MODEL_EKF(void)
        {
            #define Pk_k    P.data()
            Pk_k[0] = 0.1f;  	Pk_k[1] = 0;		Pk_k[2] = 0;			Pk_k[3] = 0;
            Pk_k[4] = 0;		Pk_k[5] = 0.1f;	    Pk_k[6] = 0;			Pk_k[7] = 0;
            Pk_k[8] = 0;		Pk_k[9] = 0;		Pk_k[10] = 0.1f;	    Pk_k[11] = 0;
            Pk_k[12] = 0;		Pk_k[13] = 0;		Pk_k[14] = 0;			Pk_k[15] = 0.1f;

            pre_cov.setZero();
            mes_cov.setZero();

            mat_I.setZero();
            mat_I.data()[0] = 1, mat_I.data()[5] = 1, mat_I.data()[10] = 1, mat_I.data()[15] = 1;
        }

        /// For more details, please refer to the wikipedia: https://en.wikipedia.org/wiki/Extended_Kalman_filter
        /// P:      Pk|k        P_pre: Pk|k-1
        /// h_dx:   dh / dx

        void fill_data(float imu_t,                                                 /// dt
                       Eigen::Quaternionf &q, Eigen::Vector3f g,                    /// state, gyro
                       Eigen::Vector3f &u_cov, Eigen::Vector3f z_cov);              /// gyro_cov, acc_cov

        Eigen::Quaternionf ekf_process(Eigen::Quaternionf &q_pre,                   /// the predicted state
                                       Eigen::Vector3f &z, Eigen::Vector3f &z_i);   /// acc, acc_ideal

        Eigen::Matrix4f P, P_pre;

        Eigen::Matrix4f f_dx;
        Eigen::Matrix<float, 3, 4> h_dx;

        Eigen::Matrix4f pre_cov;
        Eigen::Matrix3f mes_cov;

        Eigen::Matrix<float, 4, 3> Kk;

    private:

        Eigen::Matrix4f mat_I;

        void u_update(void);
        void z_update(void);
        void p_update(void);

    };

#endif  // #ifndef AL_MODEL_EKF_H
