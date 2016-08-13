#ifndef MPU6050_H
#define MPU6050_H

#include "imu_config.h"

#define FILTER_ACC_LONG         100			//size of sliding window for acc filter  2ms*100 = 200ms
#define FILTER_ACC_LONG_AVR     0.01f
#define FILTER_ACC_SHORT        25			//2ms*25 = 50ms
#define FILTER_ACC_SHORT_AVR    0.04f

#define FILTER_GYRO_LONG        10          //2ms*10 = 20ms
#define FILTER_GYRO_LONG_AVR    0.1f
#define FILTER_GYRO_SHORT       5           //2ms*5 = 10ms
#define FILTER_GYRO_SHORT_AVR   0.2f

class MPU6050
{
public:
    MPU6050(void)
    {
        device_state = 0;
        data_update_i = 0 ;
        data_update_j = 0;
        gyro_offset_read_enable = 1;
        acc_offset_read_enable =1 ;
    }
    unsigned char deviceInit(void);
    void dataUpdate(void);  //need time stm32f1 380us
    unsigned char checkDeviceState(void);

    unsigned char gyro_offset_flag , acc_offset_flag;  //零漂读取完毕标志 1
    FLOAT_XYZ acc_normal , gyro_normal;	 //normalized data
    FLOAT_XYZ acc_normal_long_filter,acc_normal_short_filter;    //平均滤波后acc归一化数据
    FLOAT_XYZ gyro_normal_long_filter,gyro_normal_short_filter;  //平均滤波后gyro归一化数据
    FLOAT_XYZ acc_covariance_long_fliter , acc_covariance_short_fliter;	//平均滤波里计算的acc的协方差
    FLOAT_XYZ gyro_covariance;  //平均滤波里计算的gyro的协方差

private:
    unsigned char device_state;     //: 1 device effective  0 invalid
    unsigned char read_buffer[14];
    unsigned char gyro_offset_read_enable , acc_offset_read_enable ; //是否使能0漂读取 1是
    INT16_XYZ gyro_offset , acc_offset;  //零漂
    INT16_XYZ acc_last , gyro_last;      //最新一次减去0漂的值
    unsigned int data_update_i , data_update_j;

    void readBuffer(void);
    void writeByte(unsigned char reg_address , unsigned char reg_data);
    unsigned char readByte(unsigned char reg_address);


    void readGyroDrift(int16_t count);
    void readAccDrift(int16_t count);
    void renewLastDate(void);         //updated original data, need time stm32f1  170us
    void gyroDateNormalize(void);     //normalized data GYRO  need time stm32f1  20us
    void accDateNormalize(void);      //normalized data  ACC  need time stm32f1  20us
    void gyroDateNormalizeFilter(void);  //need time stm32f1  50us
    void accDateNormalizeFilter(void);   //need time stm32f1  50us

};

extern MPU6050 mpu6050;

#endif  //#ifndef MPU6050_H

