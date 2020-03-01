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
* mawenke       2015.10.1   V1.0           creat this file
* chenyingbing  2015.12.1   V1.6           update
* mawenke       2016.7.1    V2.0           update
* Description:  
*
***********************************************************************************************************************/

#include "imu_top.h"

/***********************************************************************************************************************
* Function:      void IMU::topInit(uint8_t mpu , uint8_t bmp , uint8_t hmc ,
                  uint8_t ms6 , uint8_t gps)
*
* Scope:         public
*
* Description:   IMU device initialization
*
* Arguments:
*
* Return:
*
* Cpu_Time:    
*
* History:
***********************************************************************************************************************/
void IMU::init(uint8_t mpu , uint8_t bmp , uint8_t hmc ,
               uint8_t ms6 , uint8_t gps ,uint8_t debug)
{

    uint8_t temp;

    Board::getInstance()->iicDeviceInit(IIC_IMU , I2C_Sensor_Type_Typical_Fast);
    debug_en = debug;

    if(mpu == 1)
    {
        mpu6050_en = 1;
        mpu6050 = MPU6050();
        temp = mpu6050.deviceInit();
        if( (temp == 1)&&(debug_en==1) ) printf("mpu6050 initialize success \r\n");
        else if( (temp == 0)&&(debug_en==1) ) printf("mpu6050 initialize failed \r\n");
    }
    if(bmp == 1)
    {
        bmp085_en = 1;
        bmp085 = BMP085();
        temp = bmp085.deviceInit();
        if( (temp == 1)&&(debug_en==1) ) printf("bmp085 initialize success \r\n");
        else if( (temp == 0)&&(debug_en==1) ) printf("bmp085 initialize failed \r\n");
    }
    if(hmc == 1)
    {
        hmc085_en = 1;
        hmc5883l = HMC5883L();
        temp = hmc5883l.deviceInit();
        if( (temp == 1)&&(debug_en==1) ) printf("hmc5883l initialize success \r\n");
        else if( (temp == 0)&&(debug_en==1) ) printf("hmc5883l initialize failed \r\n");
    }
    if(ms6 == 1)
    {
        ms611_en = 1;
        temp = ms611.deviceInit();
        if( (temp == 1)&&(debug_en==1) ) printf("ms611 initialize success \r\n");
        else if( (temp == 0)&&(debug_en==1) ) printf("ms611 initialize failed \r\n");
    }
    if(gps == 1)
    {
        gps_en = 1;
        gps_nmea = GPS_NMEA();
        gps_nmea.GPS_Init();
    }

}

/***********************************************************************************************************************
* Function:      void IMU::topCall(void)
*
* Scope:         public
*
* Description:   imu data updata ,  1000HZ call
*
* Arguments:
*
* Return:
*
* Cpu_Time:  stm32f1(unknow us)  stm32f4+nofpu(unknow us) stm32f4+fpu(631 us)   
*
* History:
* mawenke       2015.10.1   V1.0           creat 
* chenyingbing  2015.12.1   V1.6           update
***********************************************************************************************************************/
void IMU::loopCall(void)
{
    imu_call_1++;
    imu_call_2++;
    imu_call_3++;
    imu_call_4++;
    imu_call_5++;
    static float last_time = 0;

    if( imu_call_1 >= 4 ) //250HZ
    {   // mup6050 filters require sample_acc_hz, sample_gyro_hz <= 256hz.
        imu_call_1=0;
        mpu6050.dataUpdate();
    }

    if( imu_call_2 >= 5 ) //200HZ
    {
        if(hmc085_en == 1) hmc5883l.dataUpdate();
        imu_call_2=0;
    }

    if( imu_call_3 >= 10 ) //100HZ
    {
        imu_call_3 = 0;
        if(bmp085_en == 1) bmp085.dataUpdate();
        if(ms611_en == 1) ms611.dataUpdate();

        float d_time = (HF_Get_System_Time() - last_time)/1000000;
        last_time = HF_Get_System_Time();
        if (d_time > 0.02) return;

        imu_fmodel_frame.model_data_update(mpu6050.mpu_data_ready,
                                           mpu6050.acc_normal_long_filter, mpu6050.acc_covariance_long_fliter,
                                           mpu6050.gyro_normal, mpu6050.gyro_covariance,
                                           hmc5883l.hmc_normal); //60us(stm32f1) 15us(stm32f4 nofpu)

        //imu_fmodel_frame.model_updates(0.01);
        imu_fmodel_frame.model_updates(d_time); //1316us(stm32f1) 410us(stm32f4 nofpu)
    }

    if( imu_call_4 >= 20 ) //50HZ
    {
        imu_call_4=0;

    }

    if( imu_call_5 >= 50 ) //20HZ
    {
        imu_call_5=0;
        if( debug_en )
        {
            /*
            printf("cov: %f, %f, %f ", mpu6050.acc_covariance_long_fliter.x,
                                      mpu6050.acc_covariance_long_fliter.y,
                                      mpu6050.acc_covariance_long_fliter.z);    */

            printf("time: %f pitch: %f roll: %f yaw: %f \r\n", HF_Get_System_Time(), imu_fmodel_frame.s_pryaw.pitch,
                   imu_fmodel_frame.s_pryaw.roll,
                   imu_fmodel_frame.s_pryaw.yaw);

            // imu_fmodel_frame.test();
            // printf("mpuaccx = %f  mpuaccy = %f mpuaccz = %f \r\n" , mpu6050.acc_normal.x , mpu6050.acc_normal.y,mpu6050.acc_normal.z);
            // printf("mpugyrox = %.4f  mpugyroy = %.4f mpugyroz = %.4f\r\n" , mpu6050.gyro_normal.x , mpu6050.gyro_normal.y,mpu6050.gyro_normal.z);
            // printf("hmc_normalx = %.4f  hmc_normaly = %.4f hmc_normalz = %.4f\r\n" , hmc5883l.hmc_normal.x , hmc5883l.hmc_normal.y , hmc5883l.hmc_normal.z);
            // printf("temperature = %.4f pressure = %.4f altitude = %.4f altitude_offset = %.4f\r\n" , ms611.temperature , ms611.pressure , ms611.altitude , ms611.altitude_offset);
        }
    }

}

