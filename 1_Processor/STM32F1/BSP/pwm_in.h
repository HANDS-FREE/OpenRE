#ifndef __pwm_in_H__
#define __pwm_in_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f10x.h"
#include "main_config.h"

#define PWM_Input_CH0_ENABLE 1    // if use this channel to capture PWM  PC0
#define PWM_Input_CH1_ENABLE 0    // if use this channel to capture PWM  PC1
#define PWM_Input_CH2_ENABLE 0    // if use this channel to capture PWM  PC2
#define PWM_Input_CH3_ENABLE 0    // if use this channel to capture PWM  PC3
#define PWM_Input_CH4_ENABLE 0    // if use this channel to capture PWM  PC4

typedef struct PWM_In_Data{
    volatile float PWM_Input_CH0;   //current input value of PWM (us)
    volatile float PWM_Input_CH1;
    volatile float PWM_Input_CH2;
    volatile float PWM_Input_CH3;
    volatile float PWM_Input_CH4;
}PWM_In_Data;
extern PWM_In_Data pwm_in_data_r;

//void PWM_Input_Init(void);
void HF_PwmIn_Init(void);

#ifdef __cplusplus
}
#endif

#endif //__pwm_in_H__


