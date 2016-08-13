#ifndef __adc_dac_H__
#define __adc_dac_H__

#ifdef __cplusplus
extern "C" {
#endif 

#include "stm32f10x.h"
#include "main_config.h"

#define ADC12_IN0   0      // If use this ADC channel   PA0 
#define ADC12_IN1   0      // If use this ADC channel   PA1
#define ADC12_IN2   0      // If use this ADC channel   PA2
#define ADC12_IN3   0      // If use this ADC channel   PA3
#define ADC12_IN4   0      // If use this ADC channel   PA4
#define ADC12_IN5   0      // If use this ADC channel   PA5
#define ADC12_IN6   0      // If use this ADC channel   PA6  
#define ADC12_IN7   0      // If use this ADC channel   PA7
#define ADC12_IN8   0      // If use this ADC channel   PB0
#define ADC12_IN9   0      // If use this ADC channel   PB1

#define ADC_NUM     1      // ENABLE ADC channel add 1, and last channel to collect inner voltage to calculate CPU temperature

typedef struct ADC_DAC_Data{
    volatile unsigned short int ADC_Converted_Value[ADC_NUM + 1];   //adding 1 is to avoid compiler erroring
    float    ADC_Standard_Value[ADC_NUM + 1];                       //adding 1 is to avoid compiler erroring
    float    Cpu_Standard_T;                                        //standard CPU temperture
    unsigned int   DAC_C_1;               // vol:0~3300,  represet : 0~3.3V
    unsigned int   DAC_C_2;               // vol:0~3300,  represet : 0~3.3V
}ADC_DAC_Data;
extern ADC_DAC_Data adc_dac_data_r;       //ADC data interface


void HF_ADC_Moder_Init(void);            //ADC channel initialization,
void HF_ADC_Data_Anl(void);              //external call, data will update once be called
void HF_Dac_Init(unsigned int DAC_Channel_x); //DAC output initialization, DAC_Channel_x = DAC_Channel_1 PA4 || DAC_Channel_2 PA5
//DAC_Channel_x = DAC_Channel_1|| DAC_Channel_2 vol:0~3300,  represet : 0~3.3V //set voltage of output Channelx
void HF_Dac_Set_Vol(unsigned int DAC_Channel_x, unsigned  short int  vol);

#ifdef __cplusplus
}
#endif 

#endif //#ifndef __adc_dac_H__

