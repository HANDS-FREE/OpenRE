#ifndef ADC_DAC_H
#define ADC_DAC_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "stm32f4xx.h"

void HF_ADC_Moder_Init(uint16_t hf_adc_channel , uint8_t adc_num);
float HF_Get_ADC_Output(uint8_t n);

void HF_DAC_Init(uint8_t channel_x);
//DAC output initialization, DAC_Channel_x = DAC_Channel_1 PA4 || DAC_Channel_2 PA5
//DAC_Channel_x = DAC_Channel_1|| DAC_Channel_2 vol:0~3300,  represet : 0~3.3V //set voltage of output Channelx

void HF_DAC_Set_Vol(uint8_t channel_x , uint16_t vol);

#ifdef __cplusplus
}
#endif 

#endif // #ifndef ADC_DAC_H

