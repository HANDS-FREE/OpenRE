#ifndef BOARD_H
#define	BOARD_H

#ifndef HARDWARE_PLATFORM
//The value 4 means using STM32F4 Processor,and 1 means using STM32F1 Processor
#define HARDWARE_PLATFORM  4

#endif


#ifdef __cplusplus
extern "C" {
#endif

#if HARDWARE_PLATFORM == 1
#include "../STM32F1/bsplib.h"
#elif HARDWARE_PLATFORM == 4
#include "../STM32F4/bsplib.h"

#endif

#ifdef __cplusplus
}
#endif 

class Board
{
public:
    float cpu_temperature;
    float cpu_usage;
    float battery_voltage;
    float system_time;   //system working time (unit:us), start after power-on
    uint8_t system_init; //state of system: 0-->not initialize  1-->initialized
    uint16_t cnt_1ms;
    uint16_t cnt_2ms;
    uint16_t cnt_5ms;
    uint16_t cnt_10ms;
    uint16_t cnt_20ms;
    uint16_t cnt_50ms;
    uint16_t cnt_500ms;
    uint32_t chipUniqueID[3];
    uint16_t flashSize;    //Unit: KB

public:
    Board();
    void boardBasicInit(void);
    void boardBasicCall(void);
    /**********************************************************************************************************************/
    void debugPutChar(uint8_t tx_byte_);  //system support functions
    void setLedState(uint8_t led_id, uint8_t operation);
    void setBeepState(uint8_t operation);
    uint8_t getKeyState(uint8_t key_id){return key_state[key_id] ;}
    /**********************************************************************************************************************/
    void motorInterfaceInit(uint8_t motor_id , float motor_pwm_T); //package "PAKG_MOTOR" support functions
    void motorEnable(uint8_t motor_id);
    void motorDisable(uint8_t motor_id);
    float getMotorEncoderCNT(uint8_t motor_id);
    float getMotorCurrent(uint8_t motor_id);
    void motorSetPWM(uint8_t motor_id , int pwm_value);
    /**********************************************************************************************************************/
    void axServoInterfaceInit(void); //package " PAKG_SERVO" support  functions
    void axServoTxModel(void);
    void axServoRxModel(void);
    void axServoSendTxByte(uint8_t tx_byte);
    uint8_t axServoGetRxByte(uint8_t *error);
    /**********************************************************************************************************************/
    void sbusInterfaceInit(void); //package " SBUS_PPM" support  functions
    void ppmInterfaceInit(void);
    /**********************************************************************************************************************/
    void imuI2CInit(void); //package "PAKG_IMU" support  functions
    void imuI2CWriteByte(uint8_t equipment_address , uint8_t reg_address ,
                         uint8_t reg_data , uint8_t fastmode);
    uint8_t imuI2CReadByte(uint8_t equipment_address , uint8_t reg_address , uint8_t fastmode);
    uint8_t imuI2CWriteBuf(uint8_t equipment_address,uint8_t reg_address,
                        uint8_t* pt_char , uint8_t size , uint8_t fastmode);
    uint8_t imuI2CReadBuf(uint8_t equipment_address,uint8_t reg_address,
                       uint8_t * pt_char , uint8_t size , uint8_t fastmode);

    void gpsInterfaceInit(void);
    void gpsSendTxByte(uint8_t tx_byte);
    /**********************************************************************************************************************/
    void eepromI2CInit(void); //package "AT24Cxx" support functions
    void eepromI2CWriteByte(uint8_t equipment_address , uint8_t reg_address ,
                            uint8_t reg_data , uint8_t fastmode);
    uint8_t eepromI2CReadByte(uint8_t equipment_address , uint8_t reg_address , uint8_t fastmode);
    uint8_t eepromI2CWriteBuf(uint8_t equipment_address,uint8_t reg_address,
                           uint8_t* pt_char , uint8_t size , uint8_t fastmode);
    uint8_t eepromI2CReadBuf(uint8_t equipment_address,uint8_t reg_address,
                          uint8_t * pt_char , uint8_t size , uint8_t fastmode);
    /**********************************************************************************************************************/
    //extend interface support functions
    void extendI2CInit(void);   // extend iic interface is using for extend other sensors
    void extendI2CWriteByte(uint8_t equipment_address , uint8_t reg_address ,
                            uint8_t reg_data , uint8_t fastmode);
    uint8_t extendI2CReadByte(uint8_t equipment_address , uint8_t reg_address , uint8_t fastmode);
    uint8_t extendI2CWriteBuf(uint8_t equipment_address,uint8_t reg_address,
                           uint8_t* pt_char , uint8_t size , uint8_t fastmode);
    uint8_t extendI2CReadBuf(uint8_t equipment_address,uint8_t reg_address,
                          uint8_t* pt_char , uint8_t size , uint8_t fastmode);

    //extend spi interface
    //extend can interface
    //extend PWM interface
    //mode=1 high frequency control   ; mode = 2 for  electric modulation
    void pwmInterfaceInit(uint8_t mode , float pwm_t);
    void setPWMValue(uint8_t channel_x , float pwm_value);  //channel_x 1~6
    /**********************************************************************************************************************/\

private:
    float battery_voltage_;
    float battery_voltage_alarm_ ;
    float battery_proportion_ ;
    float temperature_;
    uint16_t beep_alarm_cnt_ ;
    uint16_t board_call_i , board_call_j , board_call_k;
    uint8_t key_state[5];

    void systemMonitoring(void);
    void ledInit(void);
    void keyInit(void);
    void keyStateRenew(void);
    void beepInit(void);

    void debugInterfaceInit(void);
    float getBatteryVoltage(void);
    float getCPUUsage(void);
    float getCPUTemperature(void);
    void getCPUInfo(void);
};

extern Board board;

#endif // #ifndef BOARD_H

