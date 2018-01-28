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
* Lidexin            2016.1.16   V1.58
*LiuDong           2016.12.16                    change some functions
* Description: use to  ADC, and use DMA
*        STM32F4--------------
<<<<<<< HEAD
*        ADC0   -       PA0	-	ADC_IN0
*        ADC1	-	PA1	-	ADC_IN1
*        ADC2	-	PA2	-	ADC_IN2
*        ADC3	-	PA3	-	ADC_IN3
*        ADC4	-	PA4	-	ADC_IN4
*        ADC5	-	PA5	-	ADC_IN5
*        ADC6	-	PA6	-	ADC_IN6
*        ADC7	-	PA7	-	ADC_IN7
*        ADC8	-	PB0	-	ADC_IN8
*        ADC9	-	PB1	-	ADC_IN9
***********************************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "adc_dac.h"

#define ADC1_DR_Address    ((u32)0x40012400+0x4c)
volatile unsigned int ADC_Sample_Value[32];
float Reference_Voltage;
float cpu_temperature;
uint8_t ADC_EN_NUM;

/***********************************************************************************************************************
* Function:     void HF_ADC_Moder_Init(uint16_t hf_adc_channel , uint8_t adc_num)
*
* Scope:        public
*
* Description:  ADC initialize
*
* Arguments:  hf_adc_channel represents the channel you want enable ,  0x0001 ~ 0xffff (16 bit) represents 16 channels ,
*                        adc_num represents how many channels you want enable.
*                        Attention : this code only support 15 channels, which means you can only use "0x0001~0x7fff" here.
*
* Return:
*
* Cpu_Time:
*
* History:
***********************************************************************************************************************/
void HF_ADC_Moder_Init(uint16_t hf_adc_channel , uint8_t adc_num , float Reference_Voltage_ )
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;

    /**********************************************************************************************************************/
    DMA_InitTypeDef DMA_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;
    uint8_t ADC_Channel_Num;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
    /**********************************************************************************************************************/

    ADC_EN_NUM = adc_num;
    Reference_Voltage = Reference_Voltage_;

    DMA_DeInit(DMA1_Channel1);
    DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;	 //ADC address
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)ADC_Sample_Value;//RAM address
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = adc_num+1;//plus 1 is for the temperature adc.
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//Peripherals fixed address
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //RAM fixed address
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;		//cycle transmission
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);


    DMA_Cmd(DMA1_Channel1, ENABLE);

    /* ADC1 configuration */
    ADC_InitStructure.ADC_Mode = ADC_Mode_RegSimult;	//indepedent ADC mode
    ADC_InitStructure.ADC_ScanConvMode = ENABLE ; 	 //enable scan mode, scan mode used by multi-channel collect
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//enable continuous convert mode
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//not use external interrupt to start convert
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; 	//collect data Align Right
    ADC_InitStructure.ADC_NbrOfChannel = adc_num+1;	 	//number of channel need be convert
    ADC_Init(ADC1, &ADC_InitStructure);
    /*configure ADC clock, the frequency must below 14MHz*/
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    ADC_DMACmd(ADC1, ENABLE);
    ADC_Cmd(ADC1, ENABLE);

    ADC_Channel_Num=0;

    //if ADC0 enable
    if( ( (hf_adc_channel >> 0) & 0x0001) == 1) {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        ADC_RegularChannelConfig(ADC1, ADC_Channel_0, ++ADC_Channel_Num , ADC_SampleTime_55Cycles5);
    }

    //if ADC1 enable
    if( ( (hf_adc_channel >> 1) & 0x0001) == 1) {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        ADC_RegularChannelConfig(ADC1, ADC_Channel_1, ++ADC_Channel_Num , ADC_SampleTime_55Cycles5);
    }

    //if ADC2 enable
    if( ( (hf_adc_channel >> 2) & 0x0001) == 1) {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        ADC_RegularChannelConfig(ADC1, ADC_Channel_2, ++ADC_Channel_Num , ADC_SampleTime_55Cycles5);
    }

    //if ADC3 enable
    if( ( (hf_adc_channel >> 3) & 0x0001) == 1) {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        ADC_RegularChannelConfig(ADC1, ADC_Channel_3, ++ADC_Channel_Num , ADC_SampleTime_55Cycles5);
    }

    //if ADC4 enable
    if( ( (hf_adc_channel >> 4) & 0x0001) == 1) {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        ADC_RegularChannelConfig(ADC1, ADC_Channel_4, ++ADC_Channel_Num , ADC_SampleTime_55Cycles5);
    }

    //if ADC5 enable
    if( ( (hf_adc_channel >> 5) & 0x0001) == 1) {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        ADC_RegularChannelConfig(ADC1, ADC_Channel_5, ++ADC_Channel_Num , ADC_SampleTime_55Cycles5);
    }

    //if ADC6 enable
    if( ( (hf_adc_channel >> 6) & 0x0001) == 1) {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        ADC_RegularChannelConfig(ADC1, ADC_Channel_6, ++ADC_Channel_Num , ADC_SampleTime_55Cycles5);
    }

    //if ADC7 enable
    if( ( (hf_adc_channel >> 7) & 0x0001) == 1) {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        ADC_RegularChannelConfig(ADC1, ADC_Channel_7, ++ADC_Channel_Num , ADC_SampleTime_55Cycles5);
    }

    //if ADC8 enable
    if( ( (hf_adc_channel >> 8) & 0x0001) == 1) {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
        ADC_RegularChannelConfig(ADC1, ADC_Channel_8, ++ADC_Channel_Num , ADC_SampleTime_55Cycles5);
    }

    //if ADC9 enable
    if( ( (hf_adc_channel >> 9) & 0x0001) == 1) {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
        ADC_RegularChannelConfig(ADC1, ADC_Channel_9, ++ADC_Channel_Num , ADC_SampleTime_55Cycles5);
    }

    //if ADC10 enable
    if( ( (hf_adc_channel >> 10) & 0x0001) == 1) {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
        ADC_RegularChannelConfig(ADC1, ADC_Channel_10, ++ADC_Channel_Num , ADC_SampleTime_55Cycles5);
    }

    //if ADC11 enable
    if( ( (hf_adc_channel >> 11) & 0x0001) == 1) {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
        ADC_RegularChannelConfig(ADC1, ADC_Channel_11, ++ADC_Channel_Num , ADC_SampleTime_55Cycles5);
    }

    //if ADC12 enable
    if( ( (hf_adc_channel >> 12) & 0x0001) == 1) {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
        ADC_RegularChannelConfig(ADC1, ADC_Channel_12, ++ADC_Channel_Num , ADC_SampleTime_55Cycles5);
    }

    //if ADC13 enable
    if( ( (hf_adc_channel >> 13) & 0x0001) == 1) {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
        ADC_RegularChannelConfig(ADC1, ADC_Channel_13, ++ADC_Channel_Num , ADC_SampleTime_55Cycles5);
    }

    //if ADC14 enable
    if( ( (hf_adc_channel >> 14) & 0x0001) == 1) {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
        ADC_RegularChannelConfig(ADC1, ADC_Channel_14, ++ADC_Channel_Num , ADC_SampleTime_55Cycles5);
    }

    //if ADC15 enable
    if( ( (hf_adc_channel >> 15) & 0x0001) == 1) {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
        ADC_RegularChannelConfig(ADC1, ADC_Channel_15, ++ADC_Channel_Num , ADC_SampleTime_55Cycles5);
    }


    //the channel16 is always enable
    //set collect channel IN16,set collect time
    ADC_RegularChannelConfig(ADC1, ADC_Channel_16, ++ADC_Channel_Num , ADC_SampleTime_239Cycles5);	  //set collect channel IN16,set collect time
    ADC_TempSensorVrefintCmd(ENABLE);   //enable inner standard voltage and temperture sensor

    ADC_DMACmd(ADC1, ENABLE);
    ADC_Cmd(ADC1, ENABLE);

    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));

    ADC_SoftwareStartConvCmd(ADC1, ENABLE); 	/* because not using external interrupt to start collect, using software to start */

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

#define ADC1_DR_Address    ((u32)0x40012400+0x4c)
#define V25  0x6EE
#define AVG_SLOPE 0x05

float HF_Get_CPU_Temperature(void)
{
    cpu_temperature = 0.8f*cpu_temperature + 0.2f*(((float)V25- HF_Get_ADC_Output(ADC_EN_NUM + 1)) / (float)AVG_SLOPE+25) ;
    return cpu_temperature;
}

/***********************************************************************************************************************
***                                                                                                                  ***
***                                          DAC Initialization                                                      ***
***                                                                                                                  ***
************************************************************************************************************************/
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

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	  //enable PORTA clock
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE );	    //enable DAC clock

    DAC_InitType.DAC_Trigger=DAC_Trigger_None;	   //disable trigger, TEN1=0
    DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;//disable wave generate
    DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//mask amplitude set
    DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;	//disable DAC1  output cache,  BOFF1=1

    if(channel_x == DAC_Channel_1)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;				 // GPIO configuration
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;    //Analog Input
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        GPIO_SetBits(GPIOA,GPIO_Pin_4)	;       //PA.4 High output

        DAC_Init(DAC_Channel_1,&DAC_InitType);	 //initialize DAC output channel1
        DAC_Cmd(DAC_Channel_1, ENABLE);
        DAC_SetChannel1Data(DAC_Align_12b_R, 0);  //12 Bits align right mode to set value of DAC

    }
    else if(channel_x == DAC_Channel_2)
    {

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 // GPIO Configuration
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;    //Analog Input
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        GPIO_SetBits(GPIOA,GPIO_Pin_5)	;       //PA.4 High output

        DAC_Init(DAC_Channel_2,&DAC_InitType);	 //initialize DAC output channel1
        DAC_Cmd(DAC_Channel_2, ENABLE);
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
