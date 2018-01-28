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
* chenyingbing  2017.4.17   V1.7           creat this file
* Description:
*   ekf model to correct the yaw according to sensor magnetometer.
*
***********************************************************************************************************************/
#include "al_model_typicalcorrect.h"

void MODEL_TCORRECT::gyro_yawcorrect(float imu_t,
                                     Eigen::Vector3f &gyro_c,
                                     Eigen::Vector3f &z_hmc,
                                     Eigen::Vector3f &z_i)
{
    const float const_pid[3] = {0.025f, 0.0f, 0.005f};
    static Eigen::Vector3f cross_error[3];

    cross_error[2] = cross_error[1],
     cross_error[1] = cross_error[0],
      cross_error[0] = z_hmc.cross(z_i);

    static Eigen::Vector3f pid_data[3];
    pid_data[0] = cross_error[0] - cross_error[1],
    pid_data[1] = cross_error[0],
    pid_data[2] = cross_error[0] - cross_error[1]*2 + cross_error[2];

    static Eigen::Vector3f pid_out;
    pid_out += ( const_pid[0] * pid_data[0] +                               // p * e(t)
                 const_pid[0] * const_pid[1] * pid_data[1] * imu_t +        // p * dt * e(t)
                 const_pid[0] * const_pid[2] * pid_data[2] / imu_t
               );

    /// only correct the gyro_z data (when nearby the horizontal, it is effective)
    pid_out.data()[0] = 0,
    pid_out.data()[1] = 0;

    gyro_c += pid_out;
}
