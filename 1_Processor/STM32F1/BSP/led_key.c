/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: led_key.c
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
* Description: 
*        STM32F1--------------
*        this file define 6 LEDs and KEYs
***********************************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif 

#include "led_key.h"

LED_KEY_DATA led_key_data_r;

#if BSP_CFG_LED_KEY_EN > 0u

/***********************************************************************************************************************
* Function:     static void Set_Led(uint8_t Led_Id , uint8_t Operation)
*
* Scope:        private
*
* Description:  set one LED :Led_Id=0---LED_NUM-1 Operation=0 OFF Operation=1 ON Operation=2 switch state once
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
static void Set_Led(uint8_t Led_Id , uint8_t Operation)   
{
    if( Led_Id >= LED_NUM){return;}
    if(Led_Id == 0) {if( Operation == 0){LED0_OFF();} else if( Operation == 1){LED0_ON();} else if( Operation == 2){LED0_TOGGLE();} }
    if(Led_Id == 1) {if( Operation == 0){LED1_OFF();} else if( Operation == 1){LED1_ON();} else if( Operation == 2){LED1_TOGGLE();} }
    if(Led_Id == 2) {if( Operation == 0){LED2_OFF();} else if( Operation == 1){LED2_ON();} else if( Operation == 2){LED2_TOGGLE();} }
    if(Led_Id == 3) {if( Operation == 0){LED3_OFF();} else if( Operation == 1){LED3_ON();} else if( Operation == 2){LED3_TOGGLE();} }
    if(Led_Id == 4) {if( Operation == 0){LED4_OFF();} else if( Operation == 1){LED4_ON();} else if( Operation == 2){LED4_TOGGLE();} }
    if(Led_Id == 5) {if( Operation == 0){LED5_OFF();} else if( Operation == 1){LED5_ON();} else if( Operation == 2){LED5_TOGGLE();} }
}

/***********************************************************************************************************************
* Function:     static uint8_t Read_Key(uint8_t Key_Id )
*
* Scope:        private
*
* Description:  read the state of one Pin
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
static uint8_t Read_Key(uint8_t Key_Id )
{
    
    if( Key_Id >= KEY_NUM){return 1;}       //not pressed
    if( Key_Id == 0){return READ_KEY0;}
    if( Key_Id == 1){return READ_KEY1;}
    if( Key_Id == 2){return READ_KEY2;}
    if( Key_Id == 3){return READ_KEY3;}
    if( Key_Id == 4){return READ_KEY4;}
    if( Key_Id == 5){return READ_KEY5;}
    return 1;      //not pressed
}

/***********************************************************************************************************************
* Function:     void HF_Led_Key_Init(void)
*
* Scope:        public
*
* Description:
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
* by   mawenke   2015.12.1   creat
* by   LiuDong   2016.1.7
***********************************************************************************************************************/
void HF_Led_Key_Init(void)
{
    uint8_t LED_Init_Num=0 , KEY_Init_Num=0;
    
#if (LED_NUM > 0 || KEY_NUM > 0)
    GPIO_InitTypeDef  GPIO_InitStructure;
#endif  
    
#if LED_NUM > 0
    
    /********************************LED Initialization of Pin*********************************************/
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    if ( LED_Init_Num++ < LED_NUM )       //if enable LED0, initialize this
    {
        RCC_APB2PeriphClockCmd(RCC_LED0 , ENABLE);
        GPIO_InitStructure.GPIO_Pin = GPIO_LED0_Pin ;
        GPIO_Init(GPIO_LED0 , &GPIO_InitStructure);
    }
    
    if ( LED_Init_Num++ < LED_NUM )      //if enable LED1, initialize this
    {
        RCC_APB2PeriphClockCmd(RCC_LED1 , ENABLE);
        GPIO_InitStructure.GPIO_Pin = GPIO_LED1_Pin ;
        GPIO_Init(GPIO_LED1 , &GPIO_InitStructure);
    }
    
    if ( LED_Init_Num++ < LED_NUM )      //if enable LED2, initialize this
    {
        RCC_APB2PeriphClockCmd(RCC_LED2 , ENABLE);
        GPIO_InitStructure.GPIO_Pin = GPIO_LED2_Pin ;
        GPIO_Init(GPIO_LED2 , &GPIO_InitStructure);
    }
    
    if ( LED_Init_Num++ < LED_NUM )      //if enable LED3, initialize this
    {
        RCC_APB2PeriphClockCmd(RCC_LED3 , ENABLE);
        GPIO_InitStructure.GPIO_Pin = GPIO_LED3_Pin ;
        GPIO_Init(GPIO_LED3 , &GPIO_InitStructure);
    }
    
    
    if ( LED_Init_Num++ < LED_NUM )      //if enable LED4, initialize this
    {
        RCC_APB2PeriphClockCmd(RCC_LED4 , ENABLE);
        GPIO_InitStructure.GPIO_Pin = GPIO_LED4_Pin ;
        GPIO_Init(GPIO_LED4 , &GPIO_InitStructure);
    }
    
    
    if ( LED_Init_Num++ < LED_NUM )      //if enable LED5, initialize this
    {
        RCC_APB2PeriphClockCmd(RCC_LED5 , ENABLE);
        GPIO_InitStructure.GPIO_Pin = GPIO_LED5_Pin ;
        GPIO_Init(GPIO_LED5 , &GPIO_InitStructure);
    }
#endif
    
#if KEY_NUM > 0
    /********************************KEY Initialization of Pin*********************************************/
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;     //Pull up input
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    if ( KEY_Init_Num++ < KEY_NUM)      //if enable KEY0, initialize this
    {
        RCC_APB2PeriphClockCmd(RCC_KEY0 , ENABLE);
        GPIO_InitStructure.GPIO_Pin = GPIO_KEY0_Pin ;
        GPIO_Init(GPIO_KEY0 , &GPIO_InitStructure);
    }
    
    if ( KEY_Init_Num++ < KEY_NUM)      //if enable KEY1, initialize this
    {
        RCC_APB2PeriphClockCmd(RCC_KEY1 , ENABLE);
        GPIO_InitStructure.GPIO_Pin = GPIO_KEY1_Pin ;
        GPIO_Init(GPIO_KEY1 , &GPIO_InitStructure);
    }
    
    if ( KEY_Init_Num++ < KEY_NUM)      //if enable KEY2, initialize this
    {
        RCC_APB2PeriphClockCmd(RCC_KEY2 , ENABLE);
        GPIO_InitStructure.GPIO_Pin = GPIO_KEY2_Pin ;
        GPIO_Init(GPIO_KEY2 , &GPIO_InitStructure);
    }
    
    
    if ( KEY_Init_Num++ < KEY_NUM)      //if enable KEY3, initialize this
    {
        RCC_APB2PeriphClockCmd(RCC_KEY3 , ENABLE);
        GPIO_InitStructure.GPIO_Pin = GPIO_KEY3_Pin ;
        GPIO_Init(GPIO_KEY3 , &GPIO_InitStructure);
    }
    
    
    if ( KEY_Init_Num++ < KEY_NUM)      //if enable KEY4, initialize this
    {
        RCC_APB2PeriphClockCmd(RCC_KEY4 , ENABLE);
        GPIO_InitStructure.GPIO_Pin = GPIO_KEY4_Pin ;
        GPIO_Init(GPIO_KEY4 , &GPIO_InitStructure);
    }
    
    
    if ( KEY_Init_Num++ < KEY_NUM)      //if enable KEY5, initialize this
    {
        RCC_APB2PeriphClockCmd(RCC_KEY5 , ENABLE);
        GPIO_InitStructure.GPIO_Pin = GPIO_KEY5_Pin ;
        GPIO_Init(GPIO_KEY5 , &GPIO_InitStructure);
    }
#endif	
    
#if BEEP_EN > 0
    /********************************BEEP Initialization of Pin*********************************************/
    RCC_APB2PeriphClockCmd(RCC_BEEP , ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_BEEP_Pin ;
    GPIO_Init(GPIO_BEEP , &GPIO_InitStructure);
#endif
} 

/***********************************************************************************************************************
* Function:     static void Get_Key_State(void)
*
* Scope:        public
*
* Description:  update state of Pin : 0-->not pressed   1-->pressed. Cycle call every 10ms, and use software to Debounce
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
void HF_Key_Cycle(void)
{	
#if KEY_NUM > 0
    static uint8_t Key_State=0,This_temp=0,Last_temp=0;
    uint8_t i;
    This_temp= Read_Key(0)<<0 | Read_Key(1)<<1 | Read_Key(2)<<2 | Read_Key(3)<<3 | Read_Key(4)<<4 | Read_Key(5)<<5 ;
    Key_State=~(This_temp | Last_temp);    //0-->not pressed   1-->pressed
    Last_temp=This_temp;
    for(i=0 ; i< KEY_NUM ; i++)
    {
        led_key_data_r.Key[i] = ( Key_State & ( (uint8_t)0X01 << i ) ) >> i ;   //  use first bit  0--7
    }
#endif
}

/***********************************************************************************************************************
* Function:     void Set_Led_State(uint8_t Led_Id , uint8_t Operation)
*
* Scope:        public
*
* Description:  set state of LED : Led_Id  Operation= 0,1,2 0 OFF 1ON 2TOGGLE
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
void HF_Set_Led_State(uint8_t Led_Id , uint8_t Operation)  
{
#if LED_NUM > 0
    if( Operation == 0 || Operation == 1)
    { //if state is OFF or ON
        led_key_data_r.Led[Led_Id] = Operation;
        Set_Led(Led_Id , led_key_data_r.Led[Led_Id]);
    }
    else if(Operation == 2)
    {
        led_key_data_r.Led[Led_Id] = (led_key_data_r.Led[Led_Id]==0)?1:0 ;
        Set_Led(Led_Id , led_key_data_r.Led[Led_Id]);
    }
#endif
}

/***********************************************************************************************************************
* Function:     void HF_Set_Beep_State(uint8_t Operation)
*
* Scope:        public
*
* Description:  set state of BEEP
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
* by   mawenke   2015.12.1   creat
* by   LiuDong   2016.1.7
***********************************************************************************************************************/
void HF_Set_Beep_State(uint8_t Operation)  
{
    
#if BEEP_EN > 0
    if( Operation == 0 )
    {
        BEEP_OFF();
    }
    else if( Operation == 1 )
    {
        BEEP_ON();
    }
#endif
    
}

#endif //#if BSP_CFG_LED_KEY_EN > 0u

#ifdef __cplusplus
}
#endif 

