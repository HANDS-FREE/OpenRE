/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: pwm_in.c
* Contact:  QQ Exchange Group -- 521037187
* Version:  V2.0
*
* LICENSING TERMS:  
* The Hands Free is licensed generally under a permissive 3-clause BSD license. 
* Contributions are requiredto be made under the same license.
*
* History: 
* <author>      <time>      <version>      <desc>
* mawenke       2015.10.1   V1.0           creat this file
*
* Description: capturing PWM can be realized by timer or external interrupt
*              this file take external interrupt to realize capturing, and define 5 channels
*              STM32F4--PC0 PC1 PC2 PC3 PC4
***********************************8***********************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif 

#include "pwm_in.h"
#include "nvic.h"
#include "delay.h"

volatile float PWM_Input_CH[5]; //current input value of PWM (Unit:us)

/***********************************************************************************************************************
* Function:     void HF_PwmIn_Init(void) 
*
* Scope:        public
*
* Description:  configure input of PWM,and capture the time of high level. 
*                PC0 PC1 PC2 PC3 PC4  external interrupt line of Pin.
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
void HF_PWMIN_Init(uint16_t hf_pwmin_channel , uint8_t pwmin_num)
{

    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    
    //if pwmin_channel0 enable
    if( ( (hf_pwmin_channel >> 0) & 0x0001) == 1) {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;   //if enable this channel
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;       //normal input mode
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;  //100M
        GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN ;	// pull down input
        GPIO_Init(GPIOB, &GPIO_InitStructure);

        SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource0);   //PXX connect to interrupt lineX
        EXTI_InitStructure.EXTI_Line = EXTI_Line0;
        EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;             //interrupt mode
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;  //enable rising and falling interrupt mode
        EXTI_InitStructure.EXTI_LineCmd = ENABLE;                       //enable interrupt
        EXTI_Init(&EXTI_InitStructure);

        EXTI0_NVIC_Configuration();
    }

    //if pwmin_channel1 enable
    if( ( (hf_pwmin_channel >> 1) & 0x0001) == 1) {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;//normal input mode
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
        GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN ;
        GPIO_Init(GPIOC, &GPIO_InitStructure);

        SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource1);
        EXTI_InitStructure.EXTI_Line = EXTI_Line1;
        EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
        EXTI_InitStructure.EXTI_LineCmd = ENABLE;
        EXTI_Init(&EXTI_InitStructure);

        EXTI1_NVIC_Configuration();
    }
    
    //if pwmin_channel2 enable
    if( ( (hf_pwmin_channel >> 2) & 0x0001) == 1) {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
        GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN ;
        GPIO_Init(GPIOC, &GPIO_InitStructure);

        SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource2);
        EXTI_InitStructure.EXTI_Line = EXTI_Line2;
        EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
        EXTI_InitStructure.EXTI_LineCmd = ENABLE;
        EXTI_Init(&EXTI_InitStructure);

        EXTI2_NVIC_Configuration();
    }
    
    //if pwmin_channel3 enable
    if( ( (hf_pwmin_channel >> 3) & 0x0001) == 1) {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
        GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN ;
        GPIO_Init(GPIOC, &GPIO_InitStructure);

        SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource3);
        EXTI_InitStructure.EXTI_Line = EXTI_Line3;
        EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
        EXTI_InitStructure.EXTI_LineCmd = ENABLE;
        EXTI_Init(&EXTI_InitStructure);

        EXTI3_NVIC_Configuration();
    }
    
    //if pwmin_channel4 enable
    if( ( (hf_pwmin_channel >> 4) & 0x0001) == 1) {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
        GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN ;
        GPIO_Init(GPIOC, &GPIO_InitStructure);

        SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource4);
        EXTI_InitStructure.EXTI_Line = EXTI_Line4;
        EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
        EXTI_InitStructure.EXTI_LineCmd = ENABLE;
        EXTI_Init(&EXTI_InitStructure);

        EXTI4_NVIC_Configuration();
    }
    
}

float HF_Get_PWM_Value(uint8_t channel_x)
{
  return PWM_Input_CH[channel_x];
}

/***********************************************************************************************************************
* Function:   
*
* Scope:        public
*
* Description:  realization function of capturing PWM by external interrupt
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
void EXTI0_IRQHandler(void)
{
    static float FallingTime=0 , RisingTime =0;
    if( GPIO_ReadInputDataBit(GPIOB , GPIO_Pin_0) ) //if( GPIOB->IDR & 0x0001)
    {    //if rising
        RisingTime = HF_Get_System_Time(); //get time of rising T1
    }
    else
    {    //if falling
        FallingTime = HF_Get_System_Time(); //get time T2
        if(FallingTime < RisingTime){return ; } //over time and return
        else
        {
            PWM_Input_CH[0] = FallingTime - RisingTime; //T2-T1
            //ppm.PPM_IRQ(PWM_Input_CH[0]);
        }
    }
    EXTI_ClearITPendingBit(EXTI_Line0); //EXTI->PR=1<<0; //clear interrupt flag
}

void EXTI1_IRQHandler(void)
{
    static float FallingTime=0 , RisingTime =0;
    if( GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_1) ) //( GPIOC->IDR & 0x0002)
    {
        RisingTime = HF_Get_System_Time();
    }
    else
    {
        FallingTime = HF_Get_System_Time();
        if(FallingTime < RisingTime){ return ;}
        else
        {
            PWM_Input_CH[1] = FallingTime - RisingTime;
        }
    }
    EXTI_ClearITPendingBit(EXTI_Line1);//EXTI->PR=1<<1; //clear interrupt flag
}

void EXTI2_IRQHandler(void)
{
    static float FallingTime=0 , RisingTime =0;
    if( GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_2) ) //if( GPIOC->IDR & 0x0004)
    {
        RisingTime = HF_Get_System_Time();
    }
    else
    {
        FallingTime = HF_Get_System_Time();
        if(FallingTime < RisingTime){return ;}
        else
        {
            PWM_Input_CH[2] = FallingTime - RisingTime;
        }
    }
    EXTI_ClearITPendingBit(EXTI_Line2);// EXTI->PR=1<<2; //clear interrupt flag
}

void EXTI3_IRQHandler(void)
{
    static float FallingTime=0 , RisingTime =0;
    if( GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_3) ) //if( GPIOC->IDR & 0x0008)
    {
        RisingTime = HF_Get_System_Time();
    }
    else
    {
        FallingTime = HF_Get_System_Time();
        if(FallingTime < RisingTime){ return ;}
        else
        {
            PWM_Input_CH[3] = FallingTime - RisingTime;
        }
    }
    EXTI_ClearITPendingBit(EXTI_Line3);// EXTI->PR=1<<3;  //clear interrupt flag
}

void EXTI4_IRQHandler(void)
{
    static float FallingTime=0 , RisingTime =0;
    if( GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_4) ) //if( GPIOC->IDR & 0x0010)
    {
        RisingTime = HF_Get_System_Time();
    }
    else
    {
        FallingTime = HF_Get_System_Time();
        if(FallingTime < RisingTime){ return ;}
        else
        {
            PWM_Input_CH[4] = FallingTime - RisingTime;
        }
    }
    EXTI_ClearITPendingBit(EXTI_Line4);// EXTI->PR=1<<4; //clear interrupt flag
}

#ifdef __cplusplus
}
#endif
