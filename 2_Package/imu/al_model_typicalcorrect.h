#ifndef AL_MODEL_TCORRECT_H
#define AL_MODEL_TCORRECT_H

    #include "imu_config.h"

    #include "math/base_math_top.h"

    class MODEL_TCORRECT
    {
    public:
        MODEL_TCORRECT(void)
        {

        }

        void gyro_yawcorrect(float imu_t,
                             Eigen::Vector3f &gyro_c,
                             Eigen::Vector3f &z_hmc,
                             Eigen::Vector3f &z_i);

    private:


    };

#endif  // #ifndef AL_MODEL_TCORRECT_H


