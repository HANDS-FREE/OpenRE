#ifndef IMU_TOP_H
#define IMU_TOP_H

#include "imu_config.h"

#include "dev_mpu6050.h"
#include "dev_bmp085.h"
#include "dev_ms611.h"
#include "dev_hmc5883l.h"
#include "dev_gps.h"

#include "al_fmodel_frame.h"

class IMU
{
public:
    IMU() {
        imu_call_1 = 0;
        imu_call_2 = 0;
        imu_call_3 = 0;
        imu_call_4 = 0;
        imu_call_5 = 0;
    }
    void topInit(uint8_t mpu , uint8_t bmp , uint8_t hmc ,
                 uint8_t ms6 , uint8_t gps , uint8_t debug);
    void topCall(void);  //1000HZ
private:
    uint8_t mpu6050_en , bmp085_en , ms611_en , hmc085_en , gps_en , debug_en ;
    uint8_t imu_call_1 , imu_call_2 , imu_call_3 , imu_call_4 , imu_call_5;

};
extern IMU imu;

#endif  //#ifndef IMU_TOP_H

