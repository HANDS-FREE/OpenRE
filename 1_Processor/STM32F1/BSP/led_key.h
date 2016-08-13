#ifndef __led_key_H__
#define __led_key_H__


#ifdef __cplusplus
extern "C" {
#endif 

#include "stm32f10x.h"
#include "main_config.h"

/*******************LED0************************/
#define GPIO_LED0           GPIOD
#define RCC_LED0            RCC_APB2Periph_GPIOD
#define GPIO_LED0_Pin       GPIO_Pin_13
#define LED0_ON()           GPIO_ResetBits(GPIO_LED0 , GPIO_LED0_Pin)
#define LED0_OFF()          GPIO_SetBits(GPIO_LED0 , GPIO_LED0_Pin)
#define LED0_TOGGLE()       (GPIO_LED0->ODR) ^= GPIO_LED0_Pin
/*********************************************/

/*******************LED1************************/
#define GPIO_LED1           GPIOG
#define RCC_LED1            RCC_APB2Periph_GPIOG
#define GPIO_LED1_Pin       GPIO_Pin_14
#define LED1_ON()           GPIO_ResetBits(GPIO_LED1 , GPIO_LED1_Pin)
#define LED1_OFF()          GPIO_SetBits(GPIO_LED1 , GPIO_LED1_Pin)
#define LED1_TOGGLE()       (GPIO_LED1->ODR) ^= GPIO_LED1_Pin
/*********************************************/

/*******************LED2************************/
#define GPIO_LED2           GPIOC
#define RCC_LED2            RCC_APB2Periph_GPIOC
#define GPIO_LED2_Pin       GPIO_Pin_4
#define LED2_ON()           GPIO_ResetBits(GPIO_LED2 , GPIO_LED2_Pin)
#define LED2_OFF()          GPIO_SetBits(GPIO_LED2 , GPIO_LED2_Pin)
#define LED2_TOGGLE()       (GPIO_LED2->ODR) ^= GPIO_LED2_Pin
/*********************************************/

/*******************LED3************************/
#define GPIO_LED3           GPIOB
#define RCC_LED3            RCC_APB2Periph_GPIOB
#define GPIO_LED3_Pin       GPIO_Pin_1
#define LED3_ON()           GPIO_ResetBits(GPIO_LED3 , GPIO_LED3_Pin)
#define LED3_OFF()          GPIO_SetBits(GPIO_LED3 , GPIO_LED3_Pin)
#define LED3_TOGGLE()       (GPIO_LED3->ODR) ^= GPIO_LED3_Pin
/*********************************************/

/*******************LED4************************/
#define GPIO_LED4           GPIOA
#define RCC_LED4            RCC_APB2Periph_GPIOA
#define GPIO_LED4_Pin       GPIO_Pin_4
#define LED4_ON()           GPIO_ResetBits(GPIO_LED4 , GPIO_LED4_Pin)
#define LED4_OFF()          GPIO_SetBits(GPIO_LED4 , GPIO_LED4_Pin)
#define LED4_TOGGLE()       (GPIO_LED4->ODR) ^= GPIO_LED4_Pin
/*********************************************/

/*******************LED5************************/
#define GPIO_LED5           GPIOA
#define RCC_LED5            RCC_APB2Periph_GPIOA
#define GPIO_LED5_Pin       GPIO_Pin_4
#define LED5_ON()           GPIO_ResetBits(GPIO_LED5 , GPIO_LED5_Pin)
#define LED5_OFF()          GPIO_SetBits(GPIO_LED5 , GPIO_LED5_Pin)
#define LED5_TOGGLE()       (GPIO_LED5->ODR) ^= GPIO_LED5_Pin
/*********************************************/

/*******************KEY0************************/
#define GPIO_KEY0           GPIOA
#define RCC_KEY0            RCC_APB2Periph_GPIOA
#define GPIO_KEY0_Pin       GPIO_Pin_0
#define READ_KEY0           GPIO_ReadInputDataBit(GPIO_KEY0  , GPIO_KEY0_Pin)
/*********************************************/

/*******************KEY1************************/
#define GPIO_KEY1           GPIOC
#define RCC_KEY1            RCC_APB2Periph_GPIOC
#define GPIO_KEY1_Pin       GPIO_Pin_13
#define READ_KEY1           GPIO_ReadInputDataBit(GPIO_KEY1  , GPIO_KEY1_Pin)
/*********************************************/


/*******************KEY2************************/
#define GPIO_KEY2           GPIOE
#define RCC_KEY2            RCC_APB2Periph_GPIOE
#define GPIO_KEY2_Pin       GPIO_Pin_0
#define READ_KEY2           GPIO_ReadInputDataBit(GPIO_KEY2  , GPIO_KEY2_Pin)
/*********************************************/

/*******************KEY3************************/
#define GPIO_KEY3           GPIOA
#define RCC_KEY3            RCC_APB2Periph_GPIOA
#define GPIO_KEY3_Pin       GPIO_Pin_4
#define READ_KEY3           GPIO_ReadInputDataBit(GPIO_KEY3  , GPIO_KEY3_Pin)
/*********************************************/

/*******************KEY4************************/
#define GPIO_KEY4           GPIOA
#define RCC_KEY4            RCC_APB2Periph_GPIOA
#define GPIO_KEY4_Pin       GPIO_Pin_4
#define READ_KEY4           GPIO_ReadInputDataBit(GPIO_KEY4  , GPIO_KEY4_Pin)
/*********************************************/

/*******************KEY5************************/
#define GPIO_KEY5           GPIOA
#define RCC_KEY5            RCC_APB2Periph_GPIOA
#define GPIO_KEY5_Pin       GPIO_Pin_4
#define READ_KEY5           GPIO_ReadInputDataBit(GPIO_KEY5  , GPIO_KEY5_Pin)
/*********************************************/

/*******************BEEP************************/
#define RCC_BEEP            RCC_APB2Periph_GPIOC
#define GPIO_BEEP           GPIOC
#define GPIO_BEEP_Pin       GPIO_Pin_15
#define BEEP_ON()           GPIO_SetBits(GPIO_BEEP , GPIO_BEEP_Pin)
#define BEEP_OFF()          GPIO_ResetBits(GPIO_BEEP , GPIO_BEEP_Pin)
/*********************************************/

#define LED_NUM         2      //the number of enable LED 0--6
#define KEY_NUM         2      //the number of enable KEY 0--6
#define BEEP_EN         1       //if enable beep
typedef struct LED_KEY_DATA{
    uint8_t BEEP_State;	     //read variable 0 OFF  1ON
#if LED_NUM > 0
    uint8_t Led[LED_NUM];    //read variable 0 OFF  1ON
#endif

#if KEY_NUM > 0
    uint8_t Key[KEY_NUM];  //read variable : 0-->not pressed, 1-->pressed
#endif	
}LED_KEY_DATA;

extern LED_KEY_DATA led_key_data_r;

void HF_Led_Key_Init(void);
void HF_Key_Cycle(void);   //10ms cycle call, update data of KEY
void HF_Set_Led_State(uint8_t Led_Id, uint8_t Operation); // 0 off 1on  2 TOGGLE
void HF_Set_Beep_State(uint8_t Operation);                    // 0 OFF  1ON
#ifdef __cplusplus
}
#endif 

#endif //__led_key_H__


