/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: imu_bmp085_driver.h
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
* Description:  本文件封装了IMU中 气压计模块bmp085的驱动代码
*
***********************************************************************************************************************/

#include "bmp085.h"
#include "math.h"		

#define BMP085_ADDRESS  0xee
#define OSS 0

BMP085 bmp085;

void BMP085::readBuffer(void)
{

}
void BMP085::writeByte(unsigned char reg_address,unsigned char reg_data)
{
    unsigned char fastmode = 1;
    Board::getInstance()->iicDeviceWriteByte(IIC_IMU ,  BMP085_ADDRESS, reg_address, reg_data, fastmode);
}  
unsigned char BMP085::readByte(unsigned char reg_address)
{
    unsigned char fastmode = 1;
    return(Board::getInstance()->iicDeviceReadByte(IIC_IMU , BMP085_ADDRESS, reg_address, fastmode) );
}

/***********************************************************************************************************************
*
*
*
***********************************************************************************************************************/

//滑动平均滤波  算术平均滤波算法 输入最近采样值，返回最近NUM个值的平均值   NUM < 30 
#define AAF_NUM_MAX 30   
template<typename TYPE>  TYPE Arithmetic_Average_F ( TYPE new_value , unsigned short int NUM)   
{   
    static TYPE value_buf[AAF_NUM_MAX];
    static unsigned short int count;
    TYPE SUM;
    unsigned short int i;

    value_buf[count] = new_value;
    count++;
    if(count >= NUM) count=0;      //滑动更新窗口

    for ( i=0;i<NUM;i++)
    {
        SUM += value_buf[i];
    }
    return SUM/NUM;
} 

unsigned char BMP085::checkDeviceState(void)
{
    device_state = 1;
    return device_state;
}

/***********************************************************************************************************************
* Function:    void BMP085::deviceInit(void)
*
* Scope:       public
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
unsigned char BMP085::deviceInit(void)
{

    ac1 = readByte(0xAA);
    ac1 = (ac1<<8)|readByte(0xAB);
    ac2 = readByte(0xAC);
    ac2 = (ac2<<8)| readByte(0xAD);
    ac3 = readByte(0xAE);
    ac3 = (ac3<<8)| readByte(0xAF);
    ac4 = readByte(0xB0);
    ac4 = (ac4<<8)| readByte(0xB1);
    ac5 = readByte(0xB2);
    ac5 = (ac5<<8)| readByte(0xB3);
    ac6 = readByte(0xB4);
    ac6 = (ac6<<8)| readByte(0xB5);
    b1 = readByte(0xB6);
    b1 = (b1<<8)| readByte(0xB7);
    b2 = readByte(0xB8);
    b2 = (b2<<8)| readByte(0xB9);
    mb = readByte(0xBA);
    mb = (mb<<8)| readByte(0xBB);
    mc = readByte(0xBC);
    mc = (mc<<8)| readByte(0xBD);
    md = readByte(0xBE);
    md = (md<<8)| readByte(0xBF);

    writeByte(0xF4,0x2E); //选择了BMP085模块，写入读温度指令

    checkDeviceState();
    return device_state;
}

/***********************************************************************************************************************
* Function:      void BMP085::dataUpdate(void)
*
* Scope:         private
*
* Description:   处理BMP的数据  循环调用  建议5ms 运行一次(200hz)   气压和温度更新速度各为100hz
*
* Arguments:
*
* Return:
*
* Cpu_Time:  stm32f1(140 us)  stm32f4+nofpu(unknow us) stm32f4+fpu(unknow us)
*
* History:
* mawenke  2015.10.1   V1.0      creat
***********************************************************************************************************************/
void BMP085::dataUpdate(void)
{

    if(data_update_i == 0)
    {
        data_update_i = 1;
        ut = ( readByte(0xF6) <<8 ) | readByte(0xF7);  //读取数据低八位
        writeByte(0xF4,0x34); //选择了BMP085模块,写入读气压指令
    }
    else
    {
        data_update_i = 0;
        up = ( readByte(0xF6) <<8 ) |  readByte(0xF7);
        up &= 0x0000FFFF;
        writeByte(0xF4,0x2E); //选择了BMP085模块,写入读温度指令

        //以下为温补代码
        x1 = ((int)ut - ac6) * ac5 >> 15;
        x2 = ((int) mc << 11) / (x1 + md);
        b5 = x1 + x2;
        temperature = (b5 + 8) >> 4;
        temperature = temperature/10 ;

        b6 = b5 - 4000;
        x1 = (b2 * (b6 * b6 >> 12)) >> 11;
        x2 = ac2 * b6 >> 11;
        x3 = x1 + x2;
        b3 = (((int)ac1 * 4 + x3) + 2)/4;
        x1 = ac3 * b6 >> 13;
        x2 = (b1 * (b6 * b6 >> 12)) >> 16;
        x3 = ((x1 + x2) + 2) >> 2;
        b4 = (ac4 * (unsigned int) (x3 + 32768)) >> 15;
        b7 = ((unsigned int) up - b3) * (50000 >> OSS);
        if( b7 < 0x80000000)
            p = (b7 * 2) / b4 ;
        else
            p = (b7 / b4) * 2;
        x1 = (p >> 8) * (p >> 8);
        x1 = (x1 * 3038) >> 16;
        x2 = (-7357 * p) >> 16;
        pressure = p + ((x1 + x2 + 3791) >> 4);

        //以下为计算海拔的代码
        altitude = (float)44330.0 * (1 - pow( (float)( pressure / (float)101325 ) , (float)0.1903 ) );
        //altitude = Arithmetic_Average_F ( altitude , 10);
    }
}
