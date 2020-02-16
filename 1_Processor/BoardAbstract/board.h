#ifndef BOARD_H
#define	BOARD_H

#include "board_abstract.h"

class Board : public BoardAbstract
{

private:
    Board();

public:
    static Board* getInstance()
    {
        static Board instance;
        return &instance;
    }

    /*****system support functions*********************************************************************************************/
    //operation: 0 off , 1 on , 2 toggle
    void setLedState(uint8_t led_id, uint8_t operation);
    //operation: 0 off , 1 on , 2 toggle
    void setBeepState(uint8_t operation);
    /****hardwareinterface -- motor********************************************************************************************/
    //mode = 0 (enable pwm1 pwm2)  ; mode = 1 (pwm , IOA , IOB)
    void motorInterfaceInit(uint8_t mode , uint8_t motor_id , float motor_pwm_t);
    void motorEnable(uint8_t mode , uint8_t motor_id);
    void motorDisable(uint8_t mode , uint8_t motor_id);
    void motorSetPWM(uint8_t mode , uint8_t motor_id , int pwm_value);
    float getMotorEncoderCNT(uint8_t motor_id);
    float getMotorCurrent(uint8_t motor_id);
    /*****hardwareinterface -- digital servo**************************************************************************************/
    void axServoInterfaceInit(void);
    void axServoTxModel(void);
    void axServoRxModel(void);
    /******hardwareinterface -- pwmoutput**************************************************************************************/
    //mode=0 high frequency control motor mode
    //mode=1 for electric modulation analog servo mode
    void pwmInterfaceInit(uint8_t channel_x , uint8_t mode);
    void setPWMInterfaceValue(uint8_t channel_x , uint16_t pwm_value);
    uint16_t readPWMInterfaceValue(uint8_t channel_x);
    float getADCInterfaceValue(uint8_t channel_x);

public:
    void ioDeviceInit(DeviceType io_device_type) {return;}
    float getIODeviceData(DeviceType io_device_type) {return 0;}

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


#endif // #ifndef BOARD_H

