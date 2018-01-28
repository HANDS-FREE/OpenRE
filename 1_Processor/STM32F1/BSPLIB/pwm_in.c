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
* Description:  capturing PWM can be realized by timer or external interrupt
*               this file take external interrupt to realize capturing, and define 5 channels
*               STM32F1--------------
*               PC0 PC1 PC2 PC3 PC4
***********************************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif 

#include "pwm_in.h"
#include "nvic.h"
#include "delay.h"

static float PWM_Input_CH[5];  //current input value of PWM (Unit:us)
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
* by   mawenke    2015.12.1                          creat
* by   LiuDong    2016.1.8       V1.57       update the name of function
***********************************************************************************************************************/
void HF_PwmIn_Init(uint8_t pwmin_channel)
{
    
    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO,ENABLE);
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    
    //if enable this channel
    if( pwmin_channel == 0) {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	 // input  pull down
        GPIO_Init(GPIOC, &GPIO_InitStructure);

        GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource0); /* EXTI line(PC0) mode config */
        EXTI_InitStructure.EXTI_Line = EXTI_Line0;
        EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	//interrupt mode
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //enable interrupt of posedge and negedge
        EXTI_InitStructure.EXTI_LineCmd = ENABLE;           //enable interrupt
        EXTI_Init(&EXTI_InitStructure);

        EXTI0_NVIC_Configuration() ;
    }

    //if enable this channel
    if( pwmin_channel == 1) {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	 //input  pull down
        GPIO_Init(GPIOC, &GPIO_InitStructure);

        GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource1); /* EXTI line(PC0) mode config */
        EXTI_InitStructure.EXTI_Line = EXTI_Line1;
        EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	//interrupt mode
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //enable interrupt of posedge and negedge
        EXTI_InitStructure.EXTI_LineCmd = ENABLE;           //enable interrupt
        EXTI_Init(&EXTI_InitStructure);

        EXTI1_NVIC_Configuration() ;
    }
    
    //if enable this channel
    if( pwmin_channel == 2) {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	 // input  pull down
        GPIO_Init(GPIOC, &GPIO_InitStructure);

        GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource2); /* EXTI line(PC0) mode config */
        EXTI_InitStructure.EXTI_Line = EXTI_Line2;
        EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	//interrupt mode
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //enable interrupt of posedge and negedge
        EXTI_InitStructure.EXTI_LineCmd = ENABLE;           //enable interrupt
        EXTI_Init(&EXTI_InitStructure);

        EXTI2_NVIC_Configuration() ;
    }
    
    //if enable this channel
    if( pwmin_channel == 3) {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	     // input  pull down
        GPIO_Init(GPIOC, &GPIO_InitStructure);

        GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource3); /* EXTI line(PC0) mode config */
        EXTI_InitStructure.EXTI_Line = EXTI_Line3;
        EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	//interrupt mode
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //enable interrupt of posedge and negedge
        EXTI_InitStructure.EXTI_LineCmd = ENABLE;           //enable interrupt
        EXTI_Init(&EXTI_InitStructure);

        EXTI3_NVIC_Configuration() ;
    }

    //if enable this channel
    if( pwmin_channel == 4) {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	   // input  pull down
        GPIO_Init(GPIOC, &GPIO_InitStructure);

        GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource4); /* EXTI line(PC0) mode config */
        EXTI_InitStructure.EXTI_Line = EXTI_Line4;
        EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	//interrupt mode
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //enable interrupt of posedge and negedge
        EXTI_InitStructure.EXTI_LineCmd = ENABLE;           //enable interrupt
        EXTI_Init(&EXTI_InitStructure);

        EXTI4_NVIC_Configuration() ;
    }
    
}

float HF_Get_PWM_Value(uint8_t channel_x)
{
    return PWM_Input_CH[channel_x];
}
/***********************************************************************************************************************
* Function:     void EXTIx_IRQHandler(void)
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
* by   mawenke   2015.12.1   creat
***********************************************************************************************************************/
//interrupt program of interrupt line1
void EXTI1_IRQHandler(void)
{
    static float FallingTime=0 , RisingTime =0;
    if( GPIOC->IDR & 0x0002)
    {
        RisingTime = HF_Get_System_Time();
    }
    else
    {
        FallingTime = HF_Get_System_Time();
        if(FallingTime < RisingTime){ return ;}
        else
        {
            PWM_Input_CH[0] = FallingTime - RisingTime;
        }
    }
    EXTI->PR=1<<1;  //clear interrupt flag
}


//interrupt program of interrupt line2
void EXTI2_IRQHandler(void)
{
    static float FallingTime=0 , RisingTime =0;
    if( GPIOC->IDR & 0x0004)
    {
        RisingTime = HF_Get_System_Time();
    }
    else
    {
        FallingTime = HF_Get_System_Time();
        if(FallingTime < RisingTime){return ;}
        else
        {
            PWM_Input_CH[1] = FallingTime - RisingTime;
        }
    }
    EXTI->PR=1<<2;  //clear interrupt flag
}

//interrupt program of interrupt line3
void EXTI3_IRQHandler(void)
{
    static float FallingTime=0 , RisingTime =0;
    if( GPIOC->IDR & 0x0008)
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
    EXTI->PR=1<<3;  //clear interrupt flag
}


//interrupt program of interrupt line4
void EXTI4_IRQHandler(void)
{
    static float FallingTime=0 , RisingTime =0;
    if( GPIOC->IDR & 0x0010)
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
    EXTI->PR=1<<4;  //clear interrupt flag
}


#ifdef __cplusplus
}
#endif

