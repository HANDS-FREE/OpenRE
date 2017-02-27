#ifndef SBUS_PPM_H
#define SBUS_PPM_H

#include "board.h"

#define   SBUS_D_TIME		    3000	  //us Sbus message Time interval

class SBUS
{
public:
    SBUS(DeviceType device_)
    {
        device = device_;

        sbus_rx_update=0;
        sbus_channel[0]=0;
        sbus_state=0;

        sbus_frequency=0;
        sbus_mes_count_=0;
        sbus_rx_buffer_[0]=0;
        last_time=0;
        this_time=0;
        d_time_new=0;
        d_time=0;
        last_time_=0;
        this_time_=0;
        d_time_=0;
        sbus_bufi_=0;
        sbus_mes_i_=0;

        board.usartDeviceInit(device , 100000);
    }

    void receiveByteAnl(unsigned char receive_byte);  //put this function in serial port interrupt
    DeviceType device;
    float sbus_frequency;
    unsigned char   sbus_rx_update;
    unsigned short int  sbus_channel[16];     //temp sbus decode channel data
    unsigned char   sbus_state;

private:
    void sbusDataAnl(void);

    unsigned char sbus_flag;  //flag of sbus remote control signal
    float sbus_mes_count_;
    unsigned char sbus_rx_buffer_[25];
    float last_time,this_time,d_time_new,d_time;
    float last_time_,this_time_,d_time_;
    unsigned char sbus_bufi_,sbus_mes_i_;
    float sbusFrequencyMeasure(void);
};
extern SBUS sbus ;

class PPM
{
public:
    PPM(){ }
    void receiveFloatAnl(float pwm_value);
    unsigned short int 	ppm_rc_value[16];
private:
    uint8_t ch_;
};

#endif // #ifndef SBUS_PPM_H

