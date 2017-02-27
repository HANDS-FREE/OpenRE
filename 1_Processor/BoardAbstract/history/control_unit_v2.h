#ifndef CONTROL_UNIT_V2_H
#define CONTROL_UNIT_V2_H

#include "board_abstract.h"

class ControlUnitV2 : public BoardAbstract
{

public:
    ControlUnitV2();

public:
    /*****system support functions*********************************************************************************************/
    void setLedState(uint8_t led_id, uint8_t operation); //operation: 0 off , 1 on , 2 toggle
    void setBeepState(uint8_t operation);  //operation: 0 off , 1 on , 2 toggle
    /****hardwareinterface -- motor********************************************************************************************/
    //mode = 1 (enable pwm1 pwm2)  ; mode = 2 (pwm , IOA , IOB)
    void motorInterfaceInit(uint8_t motor_id , uint8_t mode , float motor_pwm_t);
    void motorEnable(uint8_t motor_id , uint8_t mode);
    void motorDisable(uint8_t motor_id , uint8_t mode);
    void motorSetPWM(uint8_t motor_id , int pwm_value);
    float getMotorEncoderCNT(uint8_t motor_id);
    float getMotorCurrent(uint8_t motor_id);
    /*****hardwareinterface -- digital servo**************************************************************************************/
    void axServoTxModel(void);
    void axServoRxModel(void);
    /******hardwareinterface -- pwmoutput**************************************************************************************/
    //mode=0 high frequency control motor mode
    //mode=1 for electric modulation analog servo mode
    void pwmInterfaceInit(uint8_t channel_x , uint8_t mode);
    void setPWMInterfaceValue(uint8_t channel_x , uint16_t pwm_value);
    uint16_t readPWMInterfaceValue(uint8_t channel_x);


private:
    float getBatteryVoltage(void);
    void getCPUInfo(void);
    void adcInit(void);
    void timerInit(void);
    void ledInit(void);
    void keyInit(void);
    void keyStateRenew(void);  //100HZ
    void beepInit(void);

};

extern ControlUnitV2 board;

#endif // CONTROL_UNIT_V2_H
