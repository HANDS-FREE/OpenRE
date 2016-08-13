#ifndef __i2c_H__
#define __i2c_H__

#ifdef __cplusplus
extern "C" {
#endif 

#include "stm32f10x.h"              
#include "main_config.h"

void HF_Hardware_I2C_Init(I2C_TypeDef *I2Cx, unsigned char GPIO_AF);

/******************************************************************************
single byte write
Equipment_Address IIC :equipment address   REG_Address :register write address
REG_data :write address
******************************************************************************/
void Hardware_I2C_Write_Byte(I2C_TypeDef *I2Cx, unsigned char Equipment_Address, unsigned char REG_Address, unsigned char REG_data);

/******************************************************************************
single byte read
Equipment_Address IIC :equipment address   REG_Address :register read address
******************************************************************************/
unsigned char Hardware_I2C_Read_Byte(I2C_TypeDef *I2Cx, unsigned char Equipment_Address, unsigned char REG_Address);

/******************************************************************************
several byte write   24c02 not support contious write
Equipment_Address IIC :equipment address   REG_Address :register write address
*ptChar: 1st address of write data    size: number of write byte    return 1 if succeed
******************************************************************************/
int Hardware_I2C_Write_Buf(I2C_TypeDef *I2Cx, unsigned char Equipment_Address, unsigned char REG_Address, unsigned char *ptChar, unsigned char size);

/******************************************************************************
several byte read   24c02 not support contious read
Equipment_Address IIC :equipment address   REG_Address :register read address
*ptChar: 1st address of read data    size: number of read byte    return 1 if succeed
******************************************************************************/
int Hardware_I2C_Read_Buf(I2C_TypeDef *I2Cx, unsigned char Equipment_Address, unsigned char REG_Address, unsigned char * ptChar, unsigned char size);


/*************************HF_Simulation_I2C1***************************************************************************/
#define RCC_I2C1_SCL		    RCC_APB2Periph_GPIOB
#define GPIO_I2C1_SCL	      GPIOB
#define I2C1_Pin_SCL		    GPIO_Pin_6

#define RCC_I2C1_SDA		    RCC_APB2Periph_GPIOB
#define GPIO_I2C1_SDA	      GPIOB
#define I2C1_Pin_SDA		    GPIO_Pin_7

#define SCL1_H         GPIO_I2C1_SCL->BSRR  = I2C1_Pin_SCL
#define SCL1_L         GPIO_I2C1_SCL->BRR  = I2C1_Pin_SCL
#define SDA1_H         GPIO_I2C1_SDA->BSRR  = I2C1_Pin_SDA
#define SDA1_L         GPIO_I2C1_SDA->BRR  = I2C1_Pin_SDA
#define SCL1_Read      GPIO_I2C1_SCL->IDR  & I2C1_Pin_SCL
#define SDA1_Read      GPIO_I2C1_SDA->IDR  & I2C1_Pin_SDA
/*********************************************************************************************************************/


/*************************HF_Simulation_I2C2***************************************************************************/
#define RCC_I2C2_SCL		    RCC_APB2Periph_GPIOB
#define GPIO_I2C2_SCL	      GPIOB
#define I2C2_Pin_SCL		    GPIO_Pin_6

#define RCC_I2C2_SDA		    RCC_APB2Periph_GPIOB
#define GPIO_I2C2_SDA	      GPIOB
#define I2C2_Pin_SDA		    GPIO_Pin_7

#define SCL2_H         GPIO_I2C2_SCL->BSRR  = I2C2_Pin_SCL
#define SCL2_L         GPIO_I2C2_SCL->BRR  = I2C2_Pin_SCL
#define SDA2_H         GPIO_I2C2_SDA->BSRR  = I2C2_Pin_SDA
#define SDA2_L         GPIO_I2C2_SDA->BRR  = I2C2_Pin_SDA
#define SCL2_Read      GPIO_I2C2_SCL->IDR  & I2C2_Pin_SCL
#define SDA2_Read      GPIO_I2C2_SDA->IDR  & I2C2_Pin_SDA
/*********************************************************************************************************************/

/*************************HF_Simulation_I2C3***************************************************************************/
#define RCC_I2C3_SCL		   RCC_APB2Periph_GPIOB
#define GPIO_I2C3_SCL	     GPIOB
#define I2C3_Pin_SCL		   GPIO_Pin_6

#define RCC_I2C3_SDA		   RCC_APB2Periph_GPIOB
#define GPIO_I2C3_SDA	     GPIOB
#define I2C3_Pin_SDA		   GPIO_Pin_7

#define SCL3_H         GPIO_I2C3_SCL->BSRR  = I2C3_Pin_SCL
#define SCL3_L         GPIO_I2C3_SCL->BRR  = I2C3_Pin_SCL
#define SDA3_H         GPIO_I2C3_SDA->BSRR  = I2C3_Pin_SDA
#define SDA3_L         GPIO_I2C3_SDA->BRR  = I2C3_Pin_SDA
#define SCL3_Read      GPIO_I2C3_SCL->IDR  & I2C3_Pin_SCL
#define SDA3_Read      GPIO_I2C3_SDA->IDR  & I2C3_Pin_SDA
/*********************************************************************************************************************/

void HF_Simulat_I2C_Init(uint8_t HF_I2Cx);
void Simulat_I2C_Write_Byte(uint8_t HF_I2Cx , uint8_t Equipment_Address , 
                            uint8_t REG_Address , uint8_t REG_data , uint8_t I2C_FastMode);
uint8_t Simulat_I2C_Read_Byte(uint8_t HF_I2Cx , uint8_t Equipment_Address , uint8_t REG_Address , uint8_t I2C_FastMode);
int Simulat_I2C_Write_Buf(uint8_t HF_I2Cx , uint8_t Equipment_Address,uint8_t REG_Address,
                          uint8_t *ptChar , uint8_t size , uint8_t I2C_FastMode);
int Simulat_I2C_Read_Buf(uint8_t HF_I2Cx , uint8_t Equipment_Address,uint8_t REG_Address,
                         uint8_t * ptChar , uint8_t size , uint8_t I2C_FastMode);


#ifdef __cplusplus
}
#endif 

#endif //__i2c_H__


