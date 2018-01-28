/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* Contact:  QQ Exchange Group -- 521037187
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
* Description:
*        STM32F1--------------
*        occupy hardware source : timer2 timer3 timer4
*        TIM2 CHI1 CHI2---PA0 PA1;
*        TIM3 CHI1 CHI2---PA6 PA7;  || TIM3 CHI1 CHI2---PB4 PB5;
*        TIM4 CHI1 CHI2---PB6 PB7; 
***********************************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif 

#include "encoder.h"
#include "nvic.h"

/***********************************************************************************************************************
* Function:     void Encoder_Init(TIM_TypeDef* TIMx)
*
* Scope:        public
*
* Description:  Initialize encoder mode, input parameter TIM1 TIM2 TIM3
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
* by   mawenke    2015.12.1     creat
***********************************************************************************************************************/
void HF_Encoder_Init(TIM_TypeDef* TIMx , unsigned char GPIO_AF)	      //Initialize encoder mode, input parameter TIM1 TIM2 TIM3
{
    TIM_ICInitTypeDef TIM_ICInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    if( TIMx == TIM2){
        
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE); /* enable clock */
        if(GPIO_AF == 0){
            //---------------------------------------------------------------TIM2 CHI1 CHI2---PA0 PA1;
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
            GPIO_StructInit(&GPIO_InitStructure);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
        else if(GPIO_AF == 1){
            //---------------------------------------------------------------TIM2 CHI1 CHI2---PA15 PB3;
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO , ENABLE);
            GPIO_PinRemapConfig(GPIO_FullRemap_TIM2,ENABLE);
            GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);// This is very important!

            GPIO_StructInit(&GPIO_InitStructure);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
            
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
        }
        TIM2_NVIC_Configuration();    //enable interrupt
    }
    
    else if( TIMx == TIM3){
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA , ENABLE); /* enable clock */
        if(GPIO_AF == 0){
            //---------------------------------------------------------------TIM3 CHI1 CHI2---PA6 PA7;
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
            GPIO_StructInit(&GPIO_InitStructure);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
        else if (GPIO_AF == 1){
            //---------------------------------------------------------------TIM3 CHI1 CHI2---PB4 PB5;
            GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
            GPIO_StructInit(&GPIO_InitStructure);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
        }
        TIM3_NVIC_Configuration();                            //enable interrupt
        
    }
    
    else if( TIMx == TIM4){
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 , ENABLE); /* enable clock */
        if(GPIO_AF == 0){
            //---------------------------------------------------------------TIM4 CHI1 CHI2---PB6 PB7;
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
            GPIO_StructInit(&GPIO_InitStructure);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
        }
        else if (GPIO_AF == 1){
            //---------------------------------------------------------------TIM4 CHI1 CHI2---PD12 PD13;
            GPIO_PinRemapConfig(GPIO_Remap_TIM4,ENABLE);
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD , ENABLE);
            GPIO_StructInit(&GPIO_InitStructure);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            GPIO_Init(GPIOD, &GPIO_InitStructure);
            
        }
        TIM4_NVIC_Configuration();

    }
    else if( TIMx == TIM5){

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5 , ENABLE);

        if(GPIO_AF == 0){
            //---------------------------------------------------------------TIM5 CHI1 CHI2---PA0 PA1;
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
            GPIO_StructInit(&GPIO_InitStructure);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
        TIM5_NVIC_Configuration();
    }
    
    TIM_EncoderInterfaceConfig(TIMx, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 1;
    TIM_ICInit(TIMx, &TIM_ICInitStructure);
    TIM_Cmd(TIMx, ENABLE);
    TIMx->CNT = 0x7fff;
}

float HF_Get_Encode_TIM2(void)
{
    float cnt;
    cnt  = (float)((uint16_t)0x7fff) - (float)((uint16_t)(TIM2->CNT)) ;  //! (float) is must
    TIM2->CNT = 0x7fff;
    return cnt;
}

float HF_Get_Encode_TIM3(void)
{
    float cnt;
    cnt  = (float)((uint16_t)0x7fff) - (float)((uint16_t)(TIM3->CNT)) ;
    TIM3->CNT = 0x7fff;
    return cnt;
}

float HF_Get_Encode_TIM4(void)
{
    float cnt;
    cnt  = (float)((uint16_t)0x7fff) - (float)((uint16_t)(TIM4->CNT)) ;
    TIM4->CNT = 0x7fff;
    return cnt;
}

float HF_Get_Encode_TIM5(void)
{
    float cnt;
    cnt  = (float)((uint16_t)0x7fff) - (float)((uint16_t)(TIM5->CNT)) ;
    TIM5->CNT = 0x7fff;
    return cnt;
}

#ifdef __cplusplus
}
#endif 
