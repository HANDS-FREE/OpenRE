/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: adc_dac.c
* Contact:  QQ Exchange Group -- 521037187
* Version:  V2.0
*
* LICENSING TERMS:  
* The Hands Free is licensed generally under a permissive 3-clause BSD license. 
* Contributions are requiredto be made under the same license.
*
* History: 
* <author>    <time>      <version >       <desc>
* mawenke     2015.10.1   V1.0             creat
* LiuDong     2016.1.8    V1.57            update the name of function
*
* Description: use to  ADC, and use DMA
*        STM32F1--------------
*        ADC0 	- PA0	-	ADC12_IN0
*        ADC1	-	PA1	-	ADC12_IN1
*        ADC2	-	PA2	-	ADC12_IN2
*        ADC3	-	PA3	-	ADC12_IN3
*        ADC4	-	PA4	-	ADC12_IN4
*        ADC5	-	PA5	-	ADC12_IN5
*        ADC6	-	PA6	-	ADC12_IN6
*        ADC7	-	PA7	-	ADC12_IN7
*
*        ADC8	-	PB0	-	ADC12_IN8
*        ADC9	-	PB1	-	ADC12_IN9
**********************************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif 

#include "adc_dac.h"

ADC_DAC_Data adc_dac_data_r;

#if BSP_CFG_ADC_DAC_EN  > 0u	

/************************************************************************************************************************
***                                                                                                                   ***
***                                          ADC Initialization                                                       ***
***                                                                                                                   ***
*************************************************************************************************************************/

#define ADC1_DR_Address    ((u32)0x40012400+0x4c)
#define V25  0x6EE    //4.3mV every temperature degree, correspond 0x05 every temperture degree
#define AVG_SLOPE 0x05 

/***********************************************************************************************************************
* Function:     static void ADC1_GPIO_Config(void)
*
* Scope:        private
*
* Description:  ADC GPIO configuration
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
* by   mawenke   2015.12.1   creat
***********************************************************************************************************************/
static void ADC_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
    
    //RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    
#if ADC12_IN0 == 1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif
    
#if ADC12_IN1 == 1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif
    
#if ADC12_IN2 == 1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif
    
#if ADC12_IN3 == 1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif
    
#if ADC12_IN4 == 1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif
    
#if ADC12_IN5 == 1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif
    
#if ADC12_IN6 == 1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif
    
#if ADC12_IN7 == 1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif
    
#if ADC12_IN8 == 1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
#endif
    
#if ADC12_IN9 == 1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
#endif
    
    
}

/***********************************************************************************************************************
* Function:     static void ADC_Mode_Config(void)
*
* Scope:        private
*
* Description:  configure working mode of ADC in MDA mode
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
* by   mawenke   2015.12.1   creat
***********************************************************************************************************************/
static void ADC_Mode_Config(void)
{
    DMA_InitTypeDef DMA_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;
    unsigned char ADC_ADC_Channel;
    
    //////
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);  //reset ADC1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,DISABLE);   //end reset
    //////
    
    DMA_DeInit(DMA1_Channel1);
    DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;	 //ADC address
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&adc_dac_data_r.ADC_Converted_Value;//RAM address
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = ADC_NUM;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//Peripherals fixed address
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //RAM fixed address
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	//half word
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;		//cycle transmission
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);
    
    
    DMA_Cmd(DMA1_Channel1, ENABLE);
    
    /* ADC1 configuration */
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//indepedent ADC mode
    ADC_InitStructure.ADC_ScanConvMode = DISABLE ; 	 //disable scan mode, scan mode used by multi-channel collect
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//enable continuous convert mode
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//not use external interrupt to start convert
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; 	//collect data Align Right
    ADC_InitStructure.ADC_NbrOfChannel = ADC_NUM;	 	//number of channel need be convert
    ADC_Init(ADC1, &ADC_InitStructure);
    /*configure ADC clock, the frequency must below 14MHz*/
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    ADC_DMACmd(ADC1, ENABLE);
    ADC_Cmd(ADC1, ENABLE);
    
    ADC_ADC_Channel = 0;
    
#if ADC12_IN0 == 1
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, ++ADC_ADC_Channel , ADC_SampleTime_55Cycles5);
#endif
    
#if ADC12_IN1 == 1
    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, ++ADC_ADC_Channel , ADC_SampleTime_55Cycles5);
#endif
    
#if ADC12_IN2 == 1
    ADC_RegularChannelConfig(ADC1, ADC_Channel_2,  ++ADC_ADC_Channel , ADC_SampleTime_55Cycles5);
#endif
    
#if ADC12_IN3 == 1
    ADC_RegularChannelConfig(ADC1, ADC_Channel_3,  ++ADC_ADC_Channel , ADC_SampleTime_55Cycles5);
#endif
    
#if ADC12_IN4 == 1
    ADC_RegularChannelConfig(ADC1, ADC_Channel_4,  ++ADC_ADC_Channel , ADC_SampleTime_55Cycles5);
#endif
    
#if ADC12_IN5 == 1
    ADC_RegularChannelConfig(ADC1, ADC_Channel_5,  ++ADC_ADC_Channel , ADC_SampleTime_55Cycles5);
#endif
    
#if ADC12_IN6 == 1
    ADC_RegularChannelConfig(ADC1, ADC_Channel_6,  ++ADC_ADC_Channel , ADC_SampleTime_55Cycles5);
#endif
    
#if ADC12_IN7 == 1
    ADC_RegularChannelConfig(ADC1, ADC_Channel_7,  ++ADC_ADC_Channel , ADC_SampleTime_55Cycles5);
#endif
    
#if ADC12_IN8 == 1
    ADC_RegularChannelConfig(ADC1, ADC_Channel_8,  ++ADC_ADC_Channel , ADC_SampleTime_55Cycles5);
#endif
    
#if ADC12_IN9 == 1
    ADC_RegularChannelConfig(ADC1, ADC_Channel_9,  ++ADC_ADC_Channel , ADC_SampleTime_55Cycles5);
#endif
    
    ADC_RegularChannelConfig(ADC1, ADC_Channel_16, ++ADC_ADC_Channel , ADC_SampleTime_239Cycles5);	  //set collect channel IN16,set collect time
    ADC_TempSensorVrefintCmd(ENABLE);   //enable inner standard voltage and temperture sensor
    
    //	ADC_DMACmd(ADC1, ENABLE);
    //	ADC_Cmd(ADC1, ENABLE);
    //	ADC_ResetCalibration(ADC1);
    //	while(ADC_GetResetCalibrationStatus(ADC1));
    //	ADC_StartCalibration(ADC1);
    //	while(ADC_GetCalibrationStatus(ADC1));
    
    //	ADC_SoftwareStartConvCmd(ADC1, ENABLE); 	/* because not using external interrupt to start collect, using software to start */
}

/***********************************************************************************************************************
* Function:     void ADC_Moder_Init(void)
*
* Scope:        public
*
* Description:  ADC initialization
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
* by   mawenke   2015.12.1                        creat
* by   LiuDong   2016.1.8       V1.57       update the name of function
***********************************************************************************************************************/
void HF_ADC_Moder_Init(void)
{
    ADC_GPIO_Config();
    ADC_Mode_Config();
}

/***********************************************************************************************************************
* Function:     void ADC_Data_Anl(void)
*
* Scope:        public
*
* Description:  external call, data will update once be called.  Suggest call it every 10ms.
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
* by   mawenke   2015.12.1                        creat
* by   LiuDong   2016.1.8       V1.57       update the name of function
***********************************************************************************************************************/
void HF_ADC_Data_Anl(void)
{
    uint8_t i;
    for(i=0 ; i<ADC_NUM ; i++){
        adc_dac_data_r.ADC_Standard_Value[i] = ( (float)adc_dac_data_r.ADC_Converted_Value [i]/4096 ) * 3.3;
    }
    
    adc_dac_data_r.Cpu_Standard_T = ( (float)V25- adc_dac_data_r.ADC_Converted_Value[ADC_NUM-1] ) / (float)AVG_SLOPE+25;
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
* by   mawenke   2015.12.1                        creat
* by   LiuDong   2016.1.8       V1.57       update the name of function
***********************************************************************************************************************/
void HF_Dac_Init(unsigned int DAC_Channel_x)
{
    
    GPIO_InitTypeDef GPIO_InitStructure;
    DAC_InitTypeDef DAC_InitType;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	  //enable PORTA clock
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE );	    //enable DAC clock
    
    DAC_InitType.DAC_Trigger=DAC_Trigger_None;	   //disable trigger, TEN1=0
    DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;//disable wave generate
    DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//mask amplitude set
    DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;	//disable DAC1  output cache,  BOFF1=1
    
    if(DAC_Channel_x == DAC_Channel_1)
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
    else if(DAC_Channel_x == DAC_Channel_2)
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
    
    adc_dac_data_r.DAC_C_1 = 0;
    adc_dac_data_r.DAC_C_2 = 0;
}

/***********************************************************************************************************************
* Function:     void Dac_Set_Vol(unsigned int DAC_Channel_x , unsigned  short int  vol)
*
* Scope:        public
*
* Description:  DAC_Channel_x = DAC_Channel_1|| DAC_Channel_2 vol:0~3300,  represent : 0~3.3V //set voltage of output Channelx
*               DAC_Channel_x = DAC_Channel_1 PA4 || DAC_Channel_2 PA5
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
* by   mawenke   2015.12.1                        creat
* by   LiuDong   2016.1.8       V1.57       update the name of function
***********************************************************************************************************************/
void HF_Dac_Set_Vol(unsigned int DAC_Channel_x , unsigned  short int  vol) 
{
    
    float temp=vol;
    temp/=1000;
    temp=temp*4096/3.3;
    if( DAC_Channel_x == DAC_Channel_1){
        DAC_SetChannel1Data(DAC_Align_12b_R,temp);//12 Bits align right mode to set value of DAC
        adc_dac_data_r.DAC_C_1 = vol ;
    }
    else if(DAC_Channel_x == DAC_Channel_2){
        DAC_SetChannel2Data(DAC_Align_12b_R,temp);//12 Bits align right mode to set value of DAC
        adc_dac_data_r.DAC_C_2 = vol ;
    }
    
}

#endif  // #if BSP_CFG_ADC_DAC_EN  > 0u	

#ifdef __cplusplus
}
#endif 

