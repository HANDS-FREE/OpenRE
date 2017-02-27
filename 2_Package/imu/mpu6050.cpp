/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: imu_mpu6050_driver.h
* Contact:  QQ Exchange Group -- 521037187
* Version:  V2.0
*
* LICENSING TERMS:
* The Hands Free is licensed generally under a permissive 3-clause BSD license.
* Contributions are requiredto be made under the same license.
*
* History:
* <author>      <time>      <version>      <desc>
* mawenke       2015.10.1   V1.0           creat this file
* chenyingbing  2015.12.1   V1.6           update
* Description:  本文件封装了IMU 中三轴加速计和三轴陀螺仪模块mpu6050驱动代码
*
***********************************************************************************************************************/

#include "mpu6050.h"
#include "math.h"

#define pi            3.1415926f
#define angletorad    0.01745329252f   //angle  to radian
#define radtoangle    57.295779513f	   //radian to angle

#define MPU6050_ADDRESS 0xD0    //mpu6050 address

#define	SMPLRT_DIV		0x19
#define	CONFIG	      0x1A
#define	GYRO_CONFIG		0x1B
#define	ACCEL_CONFIG	0x1C
#define	ACCEL_XOUT_H	0x3B
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40
#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42
#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48
#define	PWR_MGMT_1		0x6B
#define	WHO_AM_I	    0x75

MPU6050 mpu6050;

void MPU6050::readBuffer(void)
{
    unsigned char fastmode = 1;	//1 : i2c high speed mode  0 : low speed mode
    board.iicDeviceReadBuf(IIC_IMU , MPU6050_ADDRESS , ACCEL_XOUT_H , read_buffer , 14, fastmode);
}
void MPU6050::writeByte(unsigned char reg_address,unsigned char reg_data)
{
    unsigned char fastmode = 1;
    board.iicDeviceWriteByte(IIC_IMU , MPU6050_ADDRESS , reg_address , reg_data, fastmode);
}
unsigned char MPU6050::readByte(unsigned char reg_address)
{
    unsigned char fastmode = 1;
    return( board.iicDeviceReadByte(IIC_IMU , MPU6050_ADDRESS , reg_address , fastmode) );
}

/***********************************************************************************************************************
*
*
*
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function:    		void MPU6050::deviceCheck(void)
*
* Scope:        	public
*
* Description:   	device_state : 1 device effective  0 invalid
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
*
* chenyingbing  2015.12.1   V1.6      creat
***********************************************************************************************************************/
unsigned char MPU6050:: checkDeviceState(void)
{
    if(readByte(WHO_AM_I) == 104)
    {
        device_state = 1;
    }else{
        device_state = 0;
    }
    return device_state;
}

/***********************************************************************************************************************
* Function:      void MPU6050::readGyroDrift(int16_t count)
*
* Scope:         private
*
* Description:
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
* mawenke  2015.10.1   V1.0      creat
***********************************************************************************************************************/
void MPU6050::readGyroDrift(int16_t count)
{
    static int16_t read_x=0, read_y=0, read_z=0;
    static int32_t tempgx=0, tempgy=0, tempgz=0;
    static uint16_t cnt_g=0;

    readBuffer();
    read_x = ((((int16_t)read_buffer[8]) << 8) | read_buffer[9]); //read gyroscope values
    read_y = ((((int16_t)read_buffer[10]) << 8) | read_buffer[11]);
    read_z = ((((int16_t)read_buffer[12]) << 8) | read_buffer[13]);
    if(cnt_g==0)
    {
        gyro_offset.x = 0;
        gyro_offset.y = 0;
        gyro_offset.z = 0;
        tempgx = 0;
        tempgy = 0;
        tempgz = 0;
        cnt_g = 1;
        return;
    }
    tempgx+= read_x;
    tempgy+= read_y;
    tempgz+= read_z;
    if(cnt_g >= count)
    {
        gyro_offset.x = tempgx/cnt_g;
        gyro_offset.y = tempgy/cnt_g;
        gyro_offset.z = tempgz/cnt_g;
        cnt_g=0;
        gyro_offset_flag = 1;
        return ;
    }
    cnt_g++;

}

/***********************************************************************************************************************
* Function:      void MPU6050::readAccDrift(int16_t count)
*
* Scope:         private
*
* Description:
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
* mawenke  2015.10.1   V1.0      creat
***********************************************************************************************************************/
void MPU6050::readAccDrift(int16_t count)
{
    static int16_t read_x=0, read_y=0, read_z=0;
    static int32_t tempax=0,tempay=0,tempaz=0;
    static uint16_t cnt_a=0;

    readBuffer();
    read_x = ((((int16_t)read_buffer[0]) << 8) | read_buffer[1]); //read acceleration values
    read_y = ((((int16_t)read_buffer[2]) << 8) | read_buffer[3]);
    read_z = ((((int16_t)read_buffer[4]) << 8) | read_buffer[5]);
    if(cnt_a==0)
    {
        acc_offset.x = 0;
        acc_offset.y = 0;
        acc_offset.z = 0;
        tempax = 0;
        tempay = 0;
        tempaz = 0;
        cnt_a = 1;
        return ;
    }
    tempax+= read_x;
    tempay+= read_y;
    tempaz+= read_z;
    if(cnt_a >= count)
    {
        acc_offset.x=tempax/cnt_a;
        acc_offset.y=tempay/cnt_a;
        acc_offset.z=tempaz/cnt_a-4096;
        acc_offset_flag = 1;
        cnt_a = 0;
        return ;
    }
    cnt_a++;

}

/***********************************************************************************************************************
* Function:      void MPU6050::renewLastDate(void)
*
* Scope:         private
*
* Description:   updated original data, need time stm32f1  170us
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
* mawenke  2015.10.1   V1.0      creat
***********************************************************************************************************************/
void MPU6050::renewLastDate(void)
{
    readBuffer();

    //read acceleration values
    acc_last.x=((((int16_t)read_buffer[0]) << 8) | read_buffer[1]) - acc_offset.x;
    acc_last.y=((((int16_t)read_buffer[2]) << 8) | read_buffer[3]) - acc_offset.y;
    acc_last.z=((((int16_t)read_buffer[4]) << 8) | read_buffer[5]) - acc_offset.z;
    //skip the temperature ADC
    //read gyroscope values
    gyro_last.x=((((int16_t)read_buffer[8]) << 8) | read_buffer[9]) - gyro_offset.x;
    gyro_last.y=((((int16_t)read_buffer[10]) << 8) | read_buffer[11]) - gyro_offset.y;
    gyro_last.z=((((int16_t)read_buffer[12]) << 8) | read_buffer[13]) - gyro_offset.z;

}

/***********************************************************************************************************************
* Function:      void MPU6050::gyroDateNormalize(void)
*
* Scope:         private
*
* Description:   normalized data GYRO  need time stm32f1  20us
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
* mawenke  2015.10.1   V1.0      creat
***********************************************************************************************************************/
void MPU6050::gyroDateNormalize(void)
{
    // 250deg/s--131   500deg/s--65.5 1000deg/s--32.8 2000deg/s--16.4
    gyro_normal.x = (float)gyro_last.x *0.061f;// /16.4f;
    gyro_normal.y = (float)gyro_last.y *0.061f;// /16.4f;
    gyro_normal.z = (float)gyro_last.z *0.061f;// /16.4f;

    //printf(" gyro_normal.x = %f \n" , gyro_normal.x);
}

/***********************************************************************************************************************
* Function:      void MPU6050::accDateNormalize(void)
*
* Scope:         private
*
* Description:   normalized data  ACC  need time stm32f1  20us
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
* mawenke  2015.10.1   V1.0      creat
***********************************************************************************************************************/
void MPU6050::accDateNormalize(void)
{
    acc_normal.x = (float)acc_last.x*0.000244f;// /4096.0f;  //+-2g--16384 +-4g--8192 +-8g--4096 +-16g--2048
    acc_normal.y = (float)acc_last.y*0.000244f;// /4096.0f;
    acc_normal.z = (float)acc_last.z*0.000244f;// /4096.0f;
}


/***********************************************************************************************************************
* Function:      void MPU6050::gyroDateNormalizeFilter(void)
*
* Scope:         private
*
* Description:
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
* mawenke  2015.10.1   V1.0      creat
* chenyingbing  2015.12.1   V1.6      update
***********************************************************************************************************************/
void MPU6050::gyroDateNormalizeFilter(void)
{
    static 	unsigned char filter_cnt=0;
    static float GYRO_X_BUF[FILTER_GYRO_LONG],GYRO_Y_BUF[FILTER_GYRO_LONG],GYRO_Z_BUF[FILTER_GYRO_LONG];

    static unsigned char i;
    static float temp_l1,temp_l2,temp_l3;
    static float temp_s1,temp_s2,temp_s3;

    temp_l1 = 0; temp_l2 = 0; temp_l3 = 0;
    temp_s1 = 0; temp_s2 = 0; temp_s3 = 0;

    //FIFO
    for(i=0;i<(FILTER_GYRO_LONG-1);i++)
    {
        GYRO_X_BUF[i] = GYRO_X_BUF[i+1];
        GYRO_Y_BUF[i] = GYRO_Y_BUF[i+1];
        GYRO_Z_BUF[i] = GYRO_Z_BUF[i+1];

        //Long_Avr_Process
        temp_l1 += GYRO_X_BUF[i] * FILTER_GYRO_LONG_AVR;
        temp_l2 += GYRO_Y_BUF[i] * FILTER_GYRO_LONG_AVR;
        temp_l3 += GYRO_Z_BUF[i] * FILTER_GYRO_LONG_AVR;

        //Short_Avr_Process
        if(i > (FILTER_GYRO_LONG-FILTER_GYRO_SHORT)){
            temp_s1 += GYRO_X_BUF[i] * FILTER_GYRO_SHORT_AVR;
            temp_s2 += GYRO_Y_BUF[i] * FILTER_GYRO_SHORT_AVR;
            temp_s3 += GYRO_Z_BUF[i] * FILTER_GYRO_SHORT_AVR;
        }
    }

    //The New
    GYRO_X_BUF[FILTER_GYRO_LONG-1] = gyro_normal.x;
    GYRO_Y_BUF[FILTER_GYRO_LONG-1] = gyro_normal.y;
    GYRO_Z_BUF[FILTER_GYRO_LONG-1] = gyro_normal.z;

    //Replenish the New
    temp_l1 += GYRO_X_BUF[FILTER_GYRO_LONG-1] * FILTER_GYRO_LONG_AVR;
    temp_l2 += GYRO_Y_BUF[FILTER_GYRO_LONG-1] * FILTER_GYRO_LONG_AVR;
    temp_l3 += GYRO_Z_BUF[FILTER_GYRO_LONG-1] * FILTER_GYRO_LONG_AVR;

    temp_s1 += GYRO_X_BUF[FILTER_GYRO_LONG-1] * FILTER_GYRO_SHORT_AVR;
    temp_s2 += GYRO_Y_BUF[FILTER_GYRO_LONG-1] * FILTER_GYRO_SHORT_AVR;
    temp_s3 += GYRO_Z_BUF[FILTER_GYRO_LONG-1] * FILTER_GYRO_SHORT_AVR;

    //Get Avr
    gyro_normal_long_filter.x = temp_l1;
    gyro_normal_long_filter.y = temp_l2;
    gyro_normal_long_filter.z = temp_l3;

    gyro_normal_short_filter.x = temp_s1;
    gyro_normal_short_filter.y = temp_s2;
    gyro_normal_short_filter.z = temp_s3;

    filter_cnt++;
    if(filter_cnt==FILTER_GYRO_LONG)	filter_cnt=0;

    //由于gyro误差很小，也没必要去计算，赋予常值即可。单位化 1,1，1
    gyro_covariance.x = 1;
    gyro_covariance.y = 1;
    gyro_covariance.z = 1;
}

/***********************************************************************************************************************
* Function:      void MPU6050::accDateNormalizeFilter(void)
*
* Scope:         private
*
* Description:
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
* mawenke  2015.10.1   V1.0      creat
* chenyingbing  2015.12.1   V1.6      update
***********************************************************************************************************************/
void MPU6050::accDateNormalizeFilter(void)
{
    static 	unsigned char filter_cnt=0;
    static float	ACC_X_BUF[FILTER_ACC_LONG],ACC_Y_BUF[FILTER_ACC_LONG],ACC_Z_BUF[FILTER_ACC_LONG];

    static unsigned char i;
    static float temp_l1,temp_l2,temp_l3;
    static float temp_s1,temp_s2,temp_s3;

    static float cova_deal;
    static float cova_l1,cova_l2,cova_l3;
    static float cova_s1,cova_s2,cova_s3;

    temp_l1 = 0; temp_l2 = 0; temp_l3 = 0;
    temp_s1 = 0; temp_s2 = 0; temp_s3 = 0;

    //FIFO
    for(i=0;i<(FILTER_ACC_LONG-1);i++)
    {
        ACC_X_BUF[i] = ACC_X_BUF[i+1];
        ACC_Y_BUF[i] = ACC_Y_BUF[i+1];
        ACC_Z_BUF[i] = ACC_Z_BUF[i+1];

        //Long_Avr_Process
        temp_l1 += ACC_X_BUF[i] * FILTER_ACC_LONG_AVR;
        temp_l2 += ACC_Y_BUF[i] * FILTER_ACC_LONG_AVR;
        temp_l3 += ACC_Z_BUF[i] * FILTER_ACC_LONG_AVR;

        //Short_Avr_Process
        if(i > (FILTER_ACC_LONG-FILTER_ACC_SHORT)){
            temp_s1 += ACC_X_BUF[i] * FILTER_ACC_SHORT_AVR;
            temp_s2 += ACC_Y_BUF[i] * FILTER_ACC_SHORT_AVR;
            temp_s3 += ACC_Z_BUF[i] * FILTER_ACC_SHORT_AVR;
        }
    }

    //The New
    ACC_X_BUF[FILTER_ACC_LONG-1] = acc_normal.x;
    ACC_Y_BUF[FILTER_ACC_LONG-1] = acc_normal.y;
    ACC_Z_BUF[FILTER_ACC_LONG-1] = acc_normal.z;

    //Replenish the New
    temp_l1 += ACC_X_BUF[FILTER_ACC_LONG-1] * FILTER_ACC_LONG_AVR;
    temp_l2 += ACC_Y_BUF[FILTER_ACC_LONG-1] * FILTER_ACC_LONG_AVR;
    temp_l3 += ACC_Z_BUF[FILTER_ACC_LONG-1] * FILTER_ACC_LONG_AVR;

    temp_s1 += ACC_X_BUF[FILTER_ACC_LONG-1] * FILTER_ACC_SHORT_AVR;
    temp_s2 += ACC_Y_BUF[FILTER_ACC_LONG-1] * FILTER_ACC_SHORT_AVR;
    temp_s3 += ACC_Z_BUF[FILTER_ACC_LONG-1] * FILTER_ACC_SHORT_AVR;

    //Get Avr
    acc_normal_long_filter.x = temp_l1;
    acc_normal_long_filter.y = temp_l2;
    acc_normal_long_filter.z = temp_l3;

    acc_normal_short_filter.x = temp_s1;
    acc_normal_short_filter.y = temp_s2;
    acc_normal_short_filter.z = temp_s3;

    filter_cnt++;
    if(filter_cnt==FILTER_ACC_LONG)	filter_cnt=0;

    //计算方差
    cova_l1 = 0; cova_l2 = 0; cova_l3 = 0;
    cova_s1 = 0; cova_s2 = 0; cova_s3 = 0;
    for(i=0;i<FILTER_ACC_LONG;i++)
    {
        //Long_Avr_Process
        cova_deal = (ACC_X_BUF[i]-acc_normal_long_filter.x);
        cova_l1 += cova_deal*cova_deal * FILTER_ACC_LONG_AVR;
        cova_deal = (ACC_Y_BUF[i]-acc_normal_long_filter.y);
        cova_l2 += cova_deal*cova_deal * FILTER_ACC_LONG_AVR;
        cova_deal = (ACC_Z_BUF[i]-acc_normal_long_filter.z);
        cova_l3 += cova_deal*cova_deal * FILTER_ACC_LONG_AVR;

        //Short_Avr_Process
        if(i > (FILTER_ACC_LONG-FILTER_ACC_SHORT)){
            cova_deal = (ACC_X_BUF[i]-acc_normal_short_filter.x);
            cova_s1 += cova_deal*cova_deal * FILTER_ACC_SHORT_AVR;
            cova_deal = (ACC_Y_BUF[i]-acc_normal_short_filter.y);
            cova_s2 += cova_deal*cova_deal * FILTER_ACC_SHORT_AVR;
            cova_deal = (ACC_Z_BUF[i]-acc_normal_short_filter.z);
            cova_s3 += cova_deal*cova_deal * FILTER_ACC_SHORT_AVR;
        }
    }

    cova_l1 = cova_l1;
    cova_l2 = cova_l2;
    cova_l3 = cova_l3;
    cova_s1 = cova_s1;
    cova_s2 = cova_s2;
    cova_s3 = cova_s3;

    acc_covariance_long_fliter.x = cova_l1;
    acc_covariance_long_fliter.y = cova_l2;
    acc_covariance_long_fliter.z = cova_l3;
    acc_covariance_short_fliter.x = cova_s1;
    acc_covariance_short_fliter.y = cova_s2;
    acc_covariance_short_fliter.z = cova_s3;
}

/***********************************************************************************************************************
* Function:     unsigned char MPU6050::deviceInit(void)
*
* Scope:        public
*
* Description:
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
* mawenke  2015.10.1   V1.0      creat
* chenyingbing  2015.12.1   V1.6      update
***********************************************************************************************************************/
unsigned char MPU6050::deviceInit(void)
{            
    // 1000hz_sample_rate  42hzlpf
    writeByte(PWR_MGMT_1, 0x80); // 设备复位
    delay_ms(5);
    writeByte(PWR_MGMT_1, 0x01); //设置设备时钟源
    delay_ms(5);
    writeByte(CONFIG , 0x03);    //低通滤波 42hz
    delay_ms(5);
    writeByte(SMPLRT_DIV, 0x00);//1KHz sample rate,acc output rate is 1KHz,so is the gyro
    delay_ms(5);
    //2000deg/s for full scale range,without self-test   00<<3 250deg/s
    //01<<3 500deg/s  10<<3 1000deg/s 11<<3 2000deg/s
    writeByte(GYRO_CONFIG, 0x18);
    delay_ms(5);
    //+-8g for full scale range,without self-test  00<<3 2g  01<<3 4g  10<<3 8g 11<<3 16g
    writeByte(ACCEL_CONFIG, 0x10);
    delay_ms(5);

    writeByte(PWR_MGMT_1,0x00);      //进入工作状态
    writeByte(0X6A,0X00);            //不让MPU6050控制AUXI2C
    delay_ms(5);
    //writeByte(0X37,0X01);          //主控制器的I2C与AUXI2C直通
    writeByte(0x37,0x02);            //使能后面的hmc5883l
    delay_ms(5);

    checkDeviceState();
    return device_state;
}

/***********************************************************************************************************************
* Function:      void MPU6050::dataUpdate(void)
*
* Scope:         public
*
* Description:   500HZ ~ 1000HZ
*
* Arguments:
*
* Return:
*
* Cpu_Time:  stm32f4 -- 280us(fpu) s
*
* History:
* mawenke  2015.10.1   V1.0      creat
* chenyingbing  2015.12.1   V1.6      update
***********************************************************************************************************************/
void MPU6050::dataUpdate(void)
{

    if( data_update_j <= 500)  //上电开始前500次读的数据无效
    {
        data_update_j++;
        renewLastDate();
        return;
    }
    if(gyro_offset_read_enable == 1)
    {
        if(gyro_offset_flag != 1) { readGyroDrift(200);  return;}
    }
    if(acc_offset_read_enable == 1)
    {
        if(acc_offset_flag != 1) { readAccDrift(200); return;}
    }

    renewLastDate();            //stm32f1 170us	stm32f4 78us
    gyroDateNormalize();        //stm32f1 20us stm32f4 1us
    accDateNormalize();         //stm32f1 20us stm32f4 1us
    accDateNormalizeFilter();   //stm32f4 2us/16us
    gyroDateNormalizeFilter();  //stm32f4 2us

}
