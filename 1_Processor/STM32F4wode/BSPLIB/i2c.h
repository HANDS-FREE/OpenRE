#ifndef I2C_H
#define I2C_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "stm32f4xx.h"

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
#define RCC_I2C1_SCL        RCC_AHB1Periph_GPIOB
#define GPIO_I2C1_SCL      GPIOB
#define I2C1_PIN_SCL          GPIO_Pin_6

#define RCC_I2C1_SDA         RCC_AHB1Periph_GPIOB
#define GPIO_I2C1_SDA       GPIOB
#define I2C1_PIN_SDA           GPIO_Pin_7

#define SCL1_H           GPIO_I2C1_SCL->BSRRL  = I2C1_PIN_SCL
#define SCL1_L            GPIO_I2C1_SCL->BSRRH  = I2C1_PIN_SCL
#define SDA1_H           GPIO_I2C1_SDA->BSRRL  = I2C1_PIN_SDA
#define SDA1_L            GPIO_I2C1_SDA->BSRRH  = I2C1_PIN_SDA
#define SCL1_READ      GPIO_I2C1_SCL->IDR  & I2C1_PIN_SCL
#define SDA1_READ     GPIO_I2C1_SDA->IDR  & I2C1_PIN_SDA
/*********************************************************************************************************************/

/*************************HF_Simulation_I2C2**************************************************************************/
#define RCC_I2C2_SCL          RCC_AHB1Periph_GPIOB
#define GPIO_I2C2_SCL        GPIOB
#define I2C2_PIN_SCL           GPIO_Pin_10

#define RCC_I2C2_SDA         RCC_AHB1Periph_GPIOB
#define GPIO_I2C2_SDA       GPIOB
#define I2C2_PIN_SDA          GPIO_Pin_11

#define SCL2_H         GPIO_I2C2_SCL->BSRRL  = I2C2_PIN_SCL
#define SCL2_L          GPIO_I2C2_SCL->BSRRH  = I2C2_PIN_SCL
#define SDA2_H         GPIO_I2C2_SDA->BSRRL  = I2C2_PIN_SDA
#define SDA2_L          GPIO_I2C2_SDA->BSRRH  = I2C2_PIN_SDA
#define SCL2_READ      GPIO_I2C2_SCL->IDR  & I2C2_PIN_SCL
#define SDA2_READ      GPIO_I2C2_SDA->IDR  & I2C2_PIN_SDA
/*********************************************************************************************************************/

/*************************HF_Simulation_I2C3**************************************************************************/
#define RCC_I2C3_SCL       RCC_AHB1Periph_GPIOA
#define GPIO_I2C3_SCL     GPIOA
#define I2C3_PIN_SCL        GPIO_Pin_8

#define RCC_I2C3_SDA       RCC_AHB1Periph_GPIOC
#define GPIO_I2C3_SDA     GPIOC
#define I2C3_PIN_SDA        GPIO_Pin_9

#define SCL3_H           GPIO_I2C3_SCL->BSRRL  = I2C3_PIN_SCL
#define SCL3_L            GPIO_I2C3_SCL->BSRRH  = I2C3_PIN_SCL
#define SDA3_H           GPIO_I2C3_SDA->BSRRL  = I2C3_PIN_SDA
#define SDA3_L            GPIO_I2C3_SDA->BSRRH  = I2C3_PIN_SDA
#define SCL3_READ      GPIO_I2C3_SCL->IDR  & I2C3_PIN_SCL
#define SDA3_READ      GPIO_I2C3_SDA->IDR  & I2C3_PIN_SDA
/*********************************************************************************************************************/

void HF_Simulat_I2C_Init(uint8_t HF_I2Cx);
void HF_Simulat_I2C_Write_Byte(uint8_t HF_I2Cx , uint8_t Equipment_Address ,
                               uint8_t REG_Address , uint8_t REG_data , uint8_t I2C_FastMode);
uint8_t HF_Simulat_I2C_Read_Byte(uint8_t HF_I2Cx , uint8_t Equipment_Address ,
                                 uint8_t REG_Address , uint8_t I2C_FastMode) ;
uint8_t HF_Simulat_I2C_Write_Buf(uint8_t HF_I2Cx , uint8_t Equipment_Address,uint8_t REG_Address,
                             uint8_t *ptChar , uint8_t size , uint8_t I2C_FastMode);
uint8_t HF_Simulat_I2C_Read_Buf(uint8_t HF_I2Cx , uint8_t Equipment_Address,uint8_t REG_Address,
                      uint8_t * ptChar , uint8_t size , uint8_t I2C_FastMode);


#ifdef __cplusplus
}
#endif 

#endif // #ifndef I2C_H


