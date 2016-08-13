/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: imu_ms611.h
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
* Description:
*
***********************************************************************************************************************/

#include "ms611.h"
#include "math.h"

MS611 ms611;


#define CMD_RESET               0x1E  // ADC reset command
#define CMD_ADC_READ            0x00  // ADC read command
#define CMD_ADC_CONV            0x40  // ADC translate command

#define CMD_ADC_D1              0x00  // ADC D1 conversion
#define CMD_ADC_D2              0x10  // ADC D2 conversion
#define CMD_ADC_256             0x00  // ADC OSR=256
#define CMD_ADC_512             0x02  // ADC OSR=512
#define CMD_ADC_1024            0x04  // ADC OSR=1024
#define CMD_ADC_2048            0x06  // ADC OSR=2048
#define CMD_ADC_4096            0x08  // ADC OSR=4096

#define CMD_PROM_RD             0xA0  // Prom read command
#define PROM_NB                 8
#define MS5611_OSR				0x08  //CMD_ADC_4096

#define MS_ADDR             	0xee  // 0x77

void MS611::readBuffer(void)
{
    unsigned char fastmode = 0; //1 : i2c high speed mode  0 : low speed mode
    board.imuI2CReadBuf(MS_ADDR , CMD_ADC_READ , read_buffer , 3 , fastmode);
}
void MS611::writeByte(unsigned char reg_address , unsigned char reg_data)
{
    unsigned char fastmode = 0;
    board.imuI2CWriteByte(MS_ADDR, reg_address, reg_data, fastmode);
}
unsigned char MS611::readByte(unsigned char reg_address)
{
    unsigned char fastmode = 0;
    return( board.imuI2CReadByte(MS_ADDR, reg_address, fastmode) );
}

void MS611::start_t(void)
{
    writeByte(CMD_ADC_CONV + CMD_ADC_D2 + MS5611_OSR , 1);
}
void MS611::start_p(void)
{
    writeByte(CMD_ADC_CONV + CMD_ADC_D1 + MS5611_OSR, 1);
}

/***********************************************************************************************************************
* Function:    	unsigned char MS611::deviceCheck(void)
*
* Scope:        public
*
* Description: 	 device_state : 1 device effective  0 invalid
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
* chenyingbing  2015.10.1   V1.0      creat
***********************************************************************************************************************/
unsigned char MS611::checkDeviceState(void)
{
    device_state = 1;
    return device_state;
}

/***********************************************************************************************************************
* Function:    	unsigned char MS611::deviceCheck(void)
*
* Scope:        public
*
* Description: 	 device_state : 1 device effective  0 invalid
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
* chenyingbing  2015.10.1   V1.0      creat
***********************************************************************************************************************/
void MS611::altCalculate(void)
{
    int32_t temperature_ ;
    int32_t off2 = 0, sens2 = 0, delt;

    ms5611_ut = (t_buffer[0] << 16) | (t_buffer[1] << 8) | t_buffer[2];
    ms5611_up = (p_buffer[0] << 16) | (p_buffer[1] << 8) | p_buffer[2];

    int32_t dT = ms5611_ut - ((uint32_t)ms5611_prom[5] << 8);
    int64_t off = ((uint32_t)ms5611_prom[2] << 16) + (((int64_t)dT * ms5611_prom[4]) >> 7);
    int64_t sens = ((uint32_t)ms5611_prom[1] << 15) + (((int64_t)dT * ms5611_prom[3]) >> 8);
    temperature_ = 2000 + (((int64_t)dT * ms5611_prom[6]) >> 23);
    temperature  = (float)temperature_/100;
    if (temperature_ < 2000) {   //temperature lower than 20degC
        delt = temperature_ - 2000;
        delt = delt * delt;
        off2 = (5 * delt) >> 1;
        sens2 = (5 * delt) >> 2;
        if (temperature_ < -1500) { //temperature lower than -15degC
            delt = temperature_ + 1500;
            delt = delt * delt;
            off2  += 7 * delt;
            sens2 += (11 * delt) >> 1;
        }
    }
    off  -= off2;
    sens -= sens2;
    pressure = (((ms5611_up * sens ) >> 21) - off) >> 15;
    altitude =  ((1.0f - pow(pressure / 101325.0f, 0.190295f)) * 4433000.0f); // centimeter
    height = altitude - altitude_offset;

    if(data_update_k < 100)
    {
        data_update_k++;
        alt_sum_temp += altitude;

        if(data_update_k == 100)
            altitude_offset = alt_sum_temp/100 ;
    }

}

/***********************************************************************************************************************
* Function:    unsigned char MS611::deviceInit(void)
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
* mawenke  2015.10.1   V1.0  creat
***********************************************************************************************************************/
unsigned char MS611::deviceInit(void)
{
    unsigned char rxbuf[2];
    unsigned char i;
    char sta = 1;
    delay_ms(10);
    writeByte(CMD_RESET, 1); //reset
    delay_ms(10);
    for (i = 0; i < PROM_NB; i++)
    {
        sta &= board.imuI2CReadBuf(MS_ADDR , CMD_PROM_RD + i*2 , rxbuf , 2 , 0);
        ms5611_prom[i] = rxbuf[0] << 8 | rxbuf[1];
    }
    if(sta){
        device_state = 1;
    }else{
        device_state = 0;
    }
    start_t();
    //checkDeviceState();
    return device_state;
}

/***********************************************************************************************************************
* Function:      void MS611::dataUpdate(void)
*
* Scope:         public
*
* Description:   100HZ
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
void MS611::dataUpdate(void)
{
    if(data_update_j){
        readBuffer();
        p_buffer[0] = read_buffer[0];
        p_buffer[1] = read_buffer[1];
        p_buffer[2] = read_buffer[2];
        start_t();
        altCalculate();
        data_update_j = 0;
    }
    else
    {
        readBuffer();
        t_buffer[0] = read_buffer[0];
        t_buffer[1] = read_buffer[1];
        t_buffer[2] = read_buffer[2];
        start_p();
        data_update_j = 1;
    }
}
