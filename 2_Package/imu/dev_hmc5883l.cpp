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
* Description:  本文件封装了IMU中 三轴磁力计模块hmc5883l的驱动代码
*
***********************************************************************************************************************/

#include "dev_hmc5883l.h"
#include "math.h"

#define HMC5883L_ADDRESS  0x3C
#define HMC_POS_BIAS 1
#define HMC_NEG_BIAS 2

//HMC58X3 register map. For details see HMC58X3 datasheet
#define HMC58X3_R_CONFA 0x00
#define HMC58X3_R_CONFB 0x01
#define HMC58X3_R_MODE  0x02

#define HMC58X3_R_XM 0x03   //!< Register address for XM.
#define HMC58X3_R_XL 0x04   //!< Register address for XL.
#define HMC58X3_R_ZM 0x05   //!< Register address for ZM.
#define HMC58X3_R_ZL 0x06   //!< Register address for ZL.
#define HMC58X3_R_YM 0x07   //!< Register address for YM.
#define HMC58X3_R_YL 0x08   //!< Register address for YL.

#define HMC58X3_R_STATUS 0X09

#define HMC58X3_R_IDA 0X10
#define HMC58X3_R_IDB 0X11
#define HMC58X3_R_IDC 0X12

HMC5883L hmc5883l;

void HMC5883L::readBuffer(void)
{
    unsigned char fastmode = 1;	 //1 : i2c high speed mode  0 : low speed mode
    Board::getInstance()->iicDeviceReadBuf(IIC_IMU , HMC5883L_ADDRESS , HMC58X3_R_XM , read_buffer , 6 , fastmode);
}
void HMC5883L::writeByte(unsigned char reg_address,unsigned char reg_data)
{
    unsigned char fastmode = 1;
    Board::getInstance()->iicDeviceWriteByte(IIC_IMU , HMC5883L_ADDRESS , reg_address , reg_data , fastmode);
}
unsigned char HMC5883L::readByte(unsigned char reg_address)
{
    unsigned char fastmode = 1;
    return( Board::getInstance()->iicDeviceReadByte(IIC_IMU , HMC5883L_ADDRESS , reg_address , fastmode) );
}

/***********************************************************************************************************************
*
*
*
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function:    	void HMC5883L::deviceCheck(void)
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
unsigned char HMC5883L::checkDeviceState(void)
{
    if(readByte(0x01)==0xE0)
    {
        device_state  = 1;
    }else{
        device_state  = 0;
    }
    return device_state ;
}

/***********************************************************************************************************************
* Function:      
*
* Scope:         
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
void HMC5883L::renewLastDate(void)
{
    readBuffer();
    hmc_original.x = read_buffer[0] << 8 | read_buffer[1]; //Combine MSB and LSB of X Data output register  -2048~~2047
    hmc_original.z = read_buffer[2] << 8 | read_buffer[3];
    hmc_original.y = read_buffer[4] << 8 | read_buffer[5];

}

void HMC5883L::hmcDateNormalize(void)
{
    hmc_normal.x = (float)(hmc_original.x*0.00435f);    // /230;
    hmc_normal.z = (float)(hmc_original.z*0.00435f);    // /230;
    hmc_normal.y = (float)(hmc_original.y*0.00435f);    // /230;

    hmc_normal.x += hmc_normal_offset.x;
    hmc_normal.y += hmc_normal_offset.y;
    hmc_normal.z += hmc_normal_offset.z;
}

/***********************************************************************************************************************
* Function:    void HMC5883L::HMC_Init(void) 
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
***********************************************************************************************************************/
unsigned char HMC5883L::deviceInit(void)
{
    //writeByte(0x00,0x60);     //配置寄存器A：系统默认
    writeByte(0x02,0x00);       //模式寄存器： 连续测量模式
    delay_ms(2);
    writeByte(0x01,0xE0);       //配置寄存器B：增益控制  +- 8.1Ga  增益230
    delay_ms(2);

    checkDeviceState();
    return device_state;
}

/***********************************************************************************************************************
* Function:      void HMC5883L::dataUpdate(void)
*
* Scope:         public
*
* Description:   50HZ
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
void HMC5883L::dataUpdate(void)  //need time stm32f1--260us
{
    renewLastDate();       //need time stm32f1--96us  stm32f4--43us
    hmcDateNormalize();    //need time stm32f1--40us  stm32f4--6us
}
