#ifndef  MS611_H
#define  MS611_H

#include "imu_config.h"

class MS611
{
public:
    MS611(){
        device_state = 0;
        data_update_i = 0;
    }
    unsigned char deviceInit(void);
    void dataUpdate(void);  //need time stm32f1  140us
    unsigned char checkDeviceState(void);

    float height , altitude , altitude_offset;
    float temperature , pressure;

private:
    uint16_t ms5611_prom[8];
    uint8_t read_buffer[3] , p_buffer[3] , t_buffer[3];
    uint32_t ms5611_ut , ms5611_up;
    float alt_sum_temp;
    unsigned char device_state;     //: 1 device effective  0 invalid
    unsigned int data_update_i , data_update_j , data_update_k;
    void readBuffer(void);
    void writeByte(unsigned char reg_address , unsigned char reg_data);
    unsigned char readByte(unsigned char reg_address);
    void start_t(void);
    void start_p(void);
    void altCalculate(void);
};

extern MS611 ms611;

#endif // #ifdef MS611_H
