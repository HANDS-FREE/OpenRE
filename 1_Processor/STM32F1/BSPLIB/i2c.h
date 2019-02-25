#ifndef I2C_H
#define I2C_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "stm32f10x.h"

void HF_Hardware_I2C_Init(I2C_TypeDef *I2Cx , uint8_t GPIO_AF);

/******************************************************************************
single byte write
Equipment_Address IIC :equipment address   REG_Address :register write address
REG_data :write address
******************************************************************************/
void HF_Hardware_I2C_Write_Byte(I2C_TypeDef *I2Cx , uint8_t Equipment_Address,uint8_t REG_Address,uint8_t REG_data);

/******************************************************************************
single byte read
Equipment_Address IIC :equipment address   REG_Address :register read address
******************************************************************************/
uint8_t HF_Hardware_I2C_Read_Byte(I2C_TypeDef *I2Cx , uint8_t Equipment_Address,uint8_t REG_Address);

/******************************************************************************
several byte write   24c02 not support contious write
Equipment_Address IIC :equipment address   REG_Address :register write address
*ptChar: 1st address of write data    size: number of write byte    return 1 if succeed
******************************************************************************/
int HF_Hardware_I2C_Write_Buf(I2C_TypeDef *I2Cx , uint8_t Equipment_Address
                           ,uint8_t REG_Address,uint8_t *ptChar,uint8_t size);

/******************************************************************************
several byte read   24c02 not support contious read
Equipment_Address IIC :equipment address   REG_Address :register read address
*ptChar: 1st address of read data    size: number of read byte    return 1 if succeed
******************************************************************************/
int HF_Hardware_I2C_Read_Buf(I2C_TypeDef *I2Cx , uint8_t Equipment_Address
                          ,uint8_t REG_Address,uint8_t * ptChar,uint8_t size);


/*************************HF_Simulation_I2C1**************************************************************************/

#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2))
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr))
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum))

#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08

#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n) //output
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n) //input

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)

/*************************HF_Simulation_I2C1**************************************************************************/
#define RCC_I2C1_SCL       RCC_APB2Periph_GPIOB
#define GPIO_I2C1_SCL      GPIOB
#define I2C1_PIN_SCL       GPIO_Pin_6

#define RCC_I2C1_SDA       RCC_APB2Periph_GPIOB
#define GPIO_I2C1_SDA      GPIOB
#define I2C1_PIN_SDA       GPIO_Pin_7

#define IIC1_SDA_IN()      {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)8<<28;}
#define IIC1_SDA_OUT()     {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)3<<28;}
#define IIC1_SCL           PBout(6)
#define IIC1_SDA           PBout(7)
#define IIC1_READ_SDA      PBin(7)

/*********************************************************************************************************************/

/*************************HF_Simulation_I2C2**************************************************************************/
#define RCC_I2C2_SCL       RCC_APB2Periph_GPIOB
#define GPIO_I2C2_SCL      GPIOB
#define I2C2_PIN_SCL       GPIO_Pin_10

#define RCC_I2C2_SDA       RCC_APB2Periph_GPIOB
#define GPIO_I2C2_SDA      GPIOB
#define I2C2_PIN_SDA       GPIO_Pin_11

#define IIC2_SDA_IN()      {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=(u32)8<<12;}
#define IIC2_SDA_OUT()     {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=(u32)3<<12;}
#define IIC2_SCL           PBout(10)
#define IIC2_SDA           PBout(11)
#define IIC2_READ_SDA      PBin(11)

/*********************************************************************************************************************/

/*************************HF_Simulation_I2C3**************************************************************************/
#define RCC_I2C3_SCL       RCC_APB2Periph_GPIOA
#define GPIO_I2C3_SCL      GPIOA
#define I2C3_PIN_SCL       GPIO_Pin_8

#define RCC_I2C3_SDA       RCC_APB2Periph_GPIOC
#define GPIO_I2C3_SDA      GPIOC
#define I2C3_PIN_SDA       GPIO_Pin_9

#define IIC3_SDA_IN()      {GPIOC->CRH&=0XFFFFFF0F;GPIOC->CRH|=(u32)8<<8;}
#define IIC3_SDA_OUT()     {GPIOC->CRH&=0XFFFFFF0F;GPIOC->CRH|=(u32)3<<8;}
#define IIC3_SCL           PAout(8)
#define IIC3_SDA           PCout(9)
#define IIC3_READ_SDA      PCin(9)

/*********************************************************************************************************************/

typedef enum
{
    I2C_Sensor_Type_Typical_Fast = 0x00,
    I2C_Sensor_Type_Typical_Slow = 0x01,
    I2C_Sensor_Type_KS103 = 0x02
}I2C_Sensor_Type;

void HF_Simulat_I2C_Init(uint8_t HF_I2Cx , I2C_Sensor_Type sensor_type);
void HF_Simulat_I2C_Write_Byte(uint8_t HF_I2Cx , uint8_t Equipment_Address ,
                               uint8_t REG_Address , uint8_t REG_data);
uint8_t HF_Simulat_I2C_Read_Byte(uint8_t HF_I2Cx , uint8_t Equipment_Address ,
                                 uint8_t REG_Address) ;
uint8_t HF_Simulat_I2C_Write_Buf(uint8_t HF_I2Cx , uint8_t Equipment_Address,uint8_t REG_Address,
                             uint8_t *ptChar , uint8_t size);
uint8_t HF_Simulat_I2C_Read_Buf(uint8_t HF_I2Cx , uint8_t Equipment_Address,uint8_t REG_Address,
                      uint8_t * ptChar , uint8_t size);


#ifdef __cplusplus
}
#endif 

#endif // #ifndef I2C_H


