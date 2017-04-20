#ifndef DEV_HMC5883L_H
#define DEV_HMC5883L_H

#include "imu_config.h"


class HMC5883L
{

public:
    HMC5883L(void){
        device_state = 0;
        data_update_i = 0;
        hmc_normal_offset.x = -0.06f ;
        hmc_normal_offset.y = 0.1f;
        hmc_normal_offset.z = 0.53f;
    }
    unsigned char deviceInit(void);
    void dataUpdate(void);  //50HZ , need time stm32f1 260us
    unsigned char checkDeviceState(void);

    void setOffset(float x , float y,float z){
        hmc_normal_offset.x =x ;
        hmc_normal_offset.y =y ;
        hmc_normal_offset.z =z ;}

    INT16_XYZ  hmc_original;   //original data
    FLOAT_XYZ  hmc_normal;     //normalized data,  unit: gauss
    FLOAT_XYZ  hmc_normal_offset;   //corrective value of normalized data

private:
    unsigned char device_state;   //: 1 device effective  0 invalid
    unsigned char read_buffer[6];
    unsigned int data_update_i;

    void readBuffer(void);
    void writeByte(unsigned char reg_address , unsigned char reg_data);
    unsigned char readByte(unsigned char reg_address);
    void renewLastDate(void);
    void hmcDateNormalize(void);
};

extern HMC5883L hmc5883l;

#endif  // #ifndef HMC5883L_H


