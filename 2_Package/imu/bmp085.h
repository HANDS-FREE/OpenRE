#ifndef BMP085_H
#define BMP085_H

#include "imu_config.h"

class BMP085
{
public:

    BMP085(void){
        device_state = 0;
        data_update_i = 0;
    }
    unsigned char deviceInit(void);
    void dataUpdate(void);  //need time stm32f1  140us
    unsigned char checkDeviceState(void);

    float  temperature; //unit ℃
    float  pressure;   //unit PA
    float  altitude;   //unit M

private:
    unsigned char device_state;     //: 1 device effective  0 invalid
    unsigned int data_update_i;

    void readBuffer(void);
    void writeByte(unsigned char reg_address , unsigned char reg_data);
    unsigned char readByte(unsigned char reg_address);

    short int ac1,ac2,ac3,ac4,ac5,ac6;
    short b1,b2,mb,mc,md;
    int ut,up;
    int x1, x2, b5, b6, x3, b3, p;
    unsigned int b4, b7;
};

extern BMP085 bmp085;

#endif  // #ifndef BMP085_H


