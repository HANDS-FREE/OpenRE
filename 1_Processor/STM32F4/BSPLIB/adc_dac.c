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
* Lidexin       2016.1.16   V1.58
*
* Description: use to  ADC, and use DMA
*        STM32F4--------------
*        ADC0 - PA0	-	ADC_IN0
*        ADC1	-	PA1	-	ADC_IN1
*        ADC2	-	PA2	-	ADC_IN2
*        ADC3	-	PA3	-	ADC_IN3
*        ADC4	-	PA4	-	ADC_IN4
*        ADC5	-	PA5	-	ADC_IN5
*        ADC6	-	PA6	-	ADC_IN6
*        ADC7	-	PA7	-	ADC_IN7
*
*        ADC8	-	PB0	-	ADC_IN8
*        ADC9	-	PB1	-	ADC_IN9
***********************************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "adc_dac.h"
//#include "delay.h"

volatile unsigned int ADC_Sample_Value[32];
float Reference_Voltage;
uint8_t ADC_EN_NUM;

#define ADC1_DR_Address   ((u32)0x4001204c)

/***********************************************************************************************************************
* Function:     void HF_ADC_Moder_Init(uint16_t hf_adc_channel , uint8_t adc_num)
*
* Scope:        public
*
* Description:  ADC initialize
*
* Arguments:  hf_adc_channel represents the channel you want enable ,
*             0x00 ~ 0xff (16 bit) represents 16 channels , adc_num represents how many channels you want enable
*
*
* Return:
*
* Cpu_Time:
*
* History:
***********************************************************************************************************************/
void HF_ADC_Moder_Init(uint16_t hf_adc_channel , uint8_t adc_num , float Reference_Voltage_ )
{

    DMA_InitTypeDef DMA_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;
    ADC_CommonInitTypeDef ADC_CommonInitStructure;
    uint8_t ADC_Channel_Num;

    /**********************************************************************************************************************/
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;   //analog input
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//no pull up or down
    /**********************************************************************************************************************/

    ADC_EN_NUM = adc_num;
    Reference_Voltage = Reference_Voltage_;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
    DMA_DeInit(DMA2_Stream0);
    DMA_InitStructure.DMA_Channel = DMA_Channel_0;
    DMA_InitStructure.DMA_PeripheralBaseAddr =ADC1_DR_Address;
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)ADC_Sample_Value;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
    DMA_InitStructure.DMA_BufferSize = adc_num+1;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_Init(DMA2_Stream0, &DMA_InitStructure);
    DMA_Cmd(DMA2_Stream0 , ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 , ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1 , ENABLE);	  //ADC1 reset
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1 , DISABLE);  //end reset
    ADC_CommonInitStructure.ADC_Mode = ADC_DualMode_RegSimult; //ADC_Mode_Independent;indepedent ADC mode
    //delay 5 clock period between 2 collection
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
    ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_1; //DMA enable
    /*configure ADC clock, the frequency must below 36MHz*/
    ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;
    ADC_CommonInit(&ADC_CommonInitStructure);

    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12 BIT mode
    ADC_InitStructure.ADC_ScanConvMode = ENABLE; //DISABLE;//disable scan mode
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//enable continuous convert mode
    //not use external interrupt to start convert
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_T1_CC1;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//align right
    ADC_InitStructure.ADC_NbrOfConversion = adc_num+1;//number of channel need be convert
    ADC_Init(ADC1, &ADC_InitStructure);//ADC initialize

    ADC_Channel_Num=0;

    //if ADC0 enable
    if( ( (hf_adc_channel >> 0) & 0x0001) == 1) {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        ADC_RegularChannelConfig(ADC1, ADC_Channel_0, ++ADC_Channel_Num , ADC_SampleTime_84Cycles);
    }

    //if ADC1 enable
    if( ( (hf_adc_channel >> 1) & 0x0001) == 1) {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        ADC_RegularChannelConfig(ADC1, ADC_Channel_1, ++ADC_Channel_Num , ADC_SampleTime_84Cycles);
    }

    //if ADC2 enable
    if( ( (hf_adc_channel >> 2) & 0x0001) == 1) {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        ADC_RegularChannelConfig(ADC1, ADC_Channel_2,  ++ADC_Channel_Num , ADC_SampleTime_84Cycles);
    }

    //if ADC3 enable
    if( ( (hf_adc_channel >> 3) & 0x0001) == 1) {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        ADC_RegularChannelConfig(ADC1, ADC_Channel_3,  ++ADC_Channel_Num , ADC_SampleTime_84Cycles);
    }

    //if ADC4 enable
    if( ( (hf_adc_channel >> 4) & 0x0001) == 1) {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        ADC_RegularChannelConfig(ADC1, ADC_Channel_4,  ++ADC_Channel_Num , ADC_SampleTime_84Cycles);
    }

    //if ADC5 enable
    if( ( (hf_adc_channel >> 5) & 0x0001) == 1) {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        ADC_RegularChannelConfig(ADC1, ADC_Channel_5,  ++ADC_Channel_Num , ADC_SampleTime_84Cycles);
    }

    //if ADC6 enable
    if( ( (hf_adc_channel >> 6) & 0x0001) == 1) {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        ADC_RegularChannelConfig(ADC1, ADC_Channel_6,  ++ADC_Channel_Num , ADC_SampleTime_84Cycles);
    }

    //if ADC7 enable
    if( ( (hf_adc_channel >> 7) & 0x0001) == 1) {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        ADC_RegularChannelConfig(ADC1, ADC_Channel_7,  ++ADC_Channel_Num , ADC_SampleTime_84Cycles);
    }

    //if ADC8 enable
    if( ( (hf_adc_channel >> 8) & 0x0001) == 1) {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
        ADC_RegularChannelConfig(ADC1, ADC_Channel_8,  ++ADC_Channel_Num , ADC_SampleTime_84Cycles);
    }

    //if ADC9 enable
    if( ( (hf_adc_channel >> 9) & 0x0001) == 1) {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
        ADC_RegularChannelConfig(ADC1, ADC_Channel_9,  ++ADC_Channel_Num , ADC_SampleTime_84Cycles);
    }

    //if ADC10 enable
    if( ( (hf_adc_channel >> 10) & 0x0001) == 1) {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
        ADC_RegularChannelConfig(ADC1, ADC_Channel_10,  ++ADC_Channel_Num , ADC_SampleTime_84Cycles);
    }

    //if ADC11 enable
    if( ( (hf_adc_channel >> 11) & 0x0001) == 1) {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
        ADC_RegularChannelConfig(ADC1, ADC_Channel_11,  ++ADC_Channel_Num , ADC_SampleTime_84Cycles);
    }

    //if ADC12 enable
    if( ( (hf_adc_channel >> 12) & 0x0001) == 1) {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
        ADC_RegularChannelConfig(ADC1, ADC_Channel_12,  ++ADC_Channel_Num , ADC_SampleTime_84Cycles);
    }

    //if ADC13 enable
    if( ( (hf_adc_channel >> 13) & 0x0001) == 1) {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
        ADC_RegularChannelConfig(ADC1, ADC_Channel_13,  ++ADC_Channel_Num , ADC_SampleTime_84Cycles);
    }

    //if ADC14 enable
    if( ( (hf_adc_channel >> 14) & 0x0001) == 1) {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
        ADC_RegularChannelConfig(ADC1, ADC_Channel_14,  ++ADC_Channel_Num , ADC_SampleTime_84Cycles);
    }

    //if ADC15 enable
    if( ( (hf_adc_channel >> 15) & 0x0001) == 1) {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
        ADC_RegularChannelConfig(ADC1, ADC_Channel_15,  ++ADC_Channel_Num , ADC_SampleTime_84Cycles);
    }

    //the channel16 is always enable
    //set collect channel IN16,set collect time
    ADC_RegularChannelConfig(ADC1, ADC_Channel_16,  ++ADC_Channel_Num , ADC_SampleTime_84Cycles);
    //enable inner standard voltage and temperture sensor
    ADC_TempSensorVrefintCmd(ENABLE);

    //Enable DMA request after last transfer(Sing-ADC mode)
    ADC_MultiModeDMARequestAfterLastTransferCmd(ENABLE);
    ADC_DMARequestAfterLastTransferCmd (ADC1,ENABLE);
    ADC_DMACmd(ADC1, ENABLE);
    ADC_Cmd(ADC1, ENABLE);  //enable ADC
    ADC_SoftwareStartConv(ADC1);

}

/***********************************************************************************************************************
* Function:     float HF_Get_ADC_Output(uint8_t x)
*
* Scope:        public
*
* Description:  get the adc output value
*
* Arguments:   n > 0 , represents the n-th adc value
*
* Return:      0~3.3 v
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
float HF_Get_ADC_Output(uint8_t n)
{
    float ADC_Standard_Value = 0;
    if(n <= ADC_EN_NUM + 1)
    {
        ADC_Standard_Value = ( (float)ADC_Sample_Value[n-1]/4096 ) * (float)Reference_Voltage;
    }
    return ADC_Standard_Value;
}

float cpu_temperature;
// °C
float HF_Get_CPU_Temperature(void)
{
    cpu_temperature = 0.8f*cpu_temperature + 0.2f*((HF_Get_ADC_Output( ADC_EN_NUM + 1) - 0.76f ) / 0.0025f +25) ;
    return cpu_temperature;
}

/***********************************************************************************************************************
* Function:     void Dac_Init(unsigned int DAC_Channel_x)
*
* Scope:        public
*
* Description:  DAC Output Initialization
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
void HF_DAC_Init(uint8_t channel_x)
{
    
    GPIO_InitTypeDef GPIO_InitStructure;
    DAC_InitTypeDef DAC_InitType;
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE );	  //enable PORTA clock
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE );      //enable DAC clock
    
    DAC_InitType.DAC_Trigger=DAC_Trigger_None;	              //disable trigger, TEN1=0
    DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;  //disable wave generate
    DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//mask amplitude set
    DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;  //disable DAC1  output cache,  BOFF1=1
    
    if(channel_x == DAC_Channel_1)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;         // GPIO configuration
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;      //Analog Input
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;    //pull down
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        
        DAC_Init(DAC_Channel_1,&DAC_InitType);    //initialize DAC output channel1
        DAC_Cmd(DAC_Channel_1, ENABLE);           //enable DAC1
        DAC_SetChannel1Data(DAC_Align_12b_R, 0);  //12 Bits align right mode to set value of DAC
        
    }
    else if(channel_x == DAC_Channel_2)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;		   //GPIO Configuration
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;       //Analog Input
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;     //pull down
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        
        DAC_Init(DAC_Channel_2,&DAC_InitType);	  //initialize DAC output channel1
        DAC_Cmd(DAC_Channel_2, ENABLE);           //enable DAC1
        DAC_SetChannel2Data(DAC_Align_12b_R, 0);  //12 Bits align right mode to set value of DAC
        
    }
    
}

/***********************************************************************************************************************
* Function:     void Dac_Set_Vol(unsigned int DAC_Channel_x , unsigned  short int  vol) 
*
* Scope:        public
*
* Description:  DAC_Channel_x = DAC_Channel_1|| DAC_Channel_2 vol:0~3300,  represent : 0~3.3V
*               set voltage of output Channelx
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
void HF_DAC_Set_Vol(uint8_t channel_x , uint16_t vol)
{  
    float temp=vol;
    temp/=1000;
    temp=temp*4096/(float)3.3;
    if( channel_x == DAC_Channel_1){
        DAC_SetChannel1Data(DAC_Align_12b_R,temp);//12 Bits align right mode to set value of DAC
    }
    else if(channel_x == DAC_Channel_2){
        DAC_SetChannel2Data(DAC_Align_12b_R,temp);//12 Bits align right mode to set value of DAC
    }
}

#ifdef __cplusplus
}
#endif 

