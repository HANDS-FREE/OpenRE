#include "board_abstract.h"

BoardAbstract::BoardAbstract()
{
    cpu_temperature = cpu_usage = battery_voltage = system_time = 0;
    date_year = date_month = date_day = date_week = 0;
    time_hour = time_min = time_sec = time_ampm = 0;
    system_init = 0;
    cnt_1ms = cnt_2ms = cnt_10ms = cnt_20ms = cnt_50ms = cnt_500ms = 0;
    flashSize = 0;

    battery_voltage_ = cpu_temperature_ = 0;
    battery_voltage_alarm_ = 10.50 ;
    battery_proportion_ = 11.00 ;
    cpu_temperature_alarm_ = 0;
    beep_model = beep_alarm_cnt_ = 0;
    board_call_5ms = board_call_20ms = board_call_1s = board_call_2s =  0 ;

    usart_debug = 0x10;
    usart_pc = 0x10;
    usart_radio = 0x40;
    usart_gps = 0x32;
    usart_sbus = 0x21;
    usart_digital_servo = 0x32;
    usart_imu = 0x60;
    iic_dev_imu = 0x10;
    iic_dev_at24cxx = 0x10;
    iic_dev_oled = 0x00;
    spi_dev_imu = 0x00;
    spi_dev_nrf24l01 = 0x00;
    spi_dev_lcd = 0x00;
    can_dev_imu = 0x00;
    can_dev_pan_and_tilt = 0x00;
    usart1_queue=Queue();
    usart2_queue=Queue();
    usart3_queue=Queue();
    usart4_queue=Queue();
    usart5_queue=Queue();
    usart6_queue=Queue();
}

/***********************************************************************************************************************
* Function:     void Board::boardBasicInit(void)
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
***********************************************************************************************************************/
void BoardAbstract::boardBasicInit(void)
{
    int i;
    for(i=0;i<0x8fff;i++);

    systemClockInit();
    debugInterfaceInit();
    ledInit();
    keyInit();
    beepInit();
    adcInit();
    timerInit();

    //HF_RTC_Init();                //Initialize the RTC, if return 0:failed,else if return 1:succeeded
    //HF_IWDG_Init();               //Initialize the independed watch dog, system will reset if not feeding dog over 1s

    setBeepState(1);
    delay_ms(500);
    setBeepState(0);
}

/***********************************************************************************************************************
* Function:     void Board::boardBasicCall(void)
*
* Scope:        public
*
* Description:  update the underlying hardware information,Suggest calling every 10us
*
* Arguments:
*
* Return:
*
* Cpu_Time:  stm32f1(35 us)  stm32f4+nofpu(unknow us) stm32f4+fpu(unknow us)
*
* History:
***********************************************************************************************************************/
void BoardAbstract::boardBasicCall(void)   //100HZ
{
    board_call_5ms++;
    board_call_20ms++;
    board_call_1s++;
    board_call_2s++;

    keyStateRenew();
    beepStateRenew();

    if(board_call_5ms >= 5) //20hz
    {
        board_call_5ms = 0;
        //HF_IWDG_Feed(); //feed dog
        system_time = getClock();  //system working time (unit:us)
        battery_voltage = getBatteryVoltage();
        cpu_usage = getCPUUsage();
        cpu_temperature = getCPUTemperature();
    }
    if(board_call_20ms >= 20) //5HZ
    {
        board_call_20ms = 0;
    }
    if(board_call_1s >= 100) //1hz
    {
        board_call_1s=0;
        //updateLocalTime()
    }
    if(board_call_2s >= 200) //wait 2s for a stable battery_voltage
    {
        board_call_2s = 0;
        if( (battery_voltage > 7) && (battery_voltage < battery_voltage_alarm_) )
        {
            if(beep_model != 4)
            {
                setBeepModel(4);
            }
        }
        else if( battery_voltage > (battery_voltage_alarm_+0.2f) )
        {
            if(beep_model == 4)  setBeepModel(0);
        }
    }
}

/***********************************************************************************************************************
* Function:
*
* Scope:
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
***********************************************************************************************************************/

void BoardAbstract::deviceAnaly(DeviceType device_type_ , uint8_t* device_channel_,
                                uint8_t* device_mapping_)
{

    uint8_t device;

    switch (device_type_) {
    case USART_DEBUG:
        device = usart_debug;
        break;
    case USART_PC:
        device = usart_pc;
        break;
    case USART_RADIO:
        device = usart_radio;
        break;
    case USART_GPS:
        device = usart_gps;
        break;
    case USART_SBUS:
        device = usart_sbus;
        break;
    case USART_DIGITAL_SERVO:
        device = usart_digital_servo;
        break;
    case USART_IMU:
        device = usart_imu;
        break;
    case IIC_IMU:
        device = iic_dev_imu;
        break;
    case IIC_AT24CXX:
        device = iic_dev_at24cxx;
        break;
    case IIC_OLED:
        device = iic_dev_oled;
        break;
    case SPI_IMU:
        device = spi_dev_imu;
        break;
    case SPI_NRF24L01:
        device = spi_dev_nrf24l01;
        break;
    case SPI_LCD:
        device = spi_dev_lcd;
        break;
    case CAN_IMU:
        device = can_dev_imu;
        break;
    case CAN_PAN_AND_TILT:
        device = can_dev_pan_and_tilt;
        break;
    default:
        break;
    }

    *device_channel_ = getByteHighFourBit(device);
    *device_mapping_ = getByteLowFourBit(device);
}

/***********************************************************************************************************************
* Function:
*
* Scope:
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
***********************************************************************************************************************/
Queue* BoardAbstract::getUsartQueue(uint8_t channel)
{
    if(channel ==1) return &usart1_queue;
    else if(channel ==2)return &usart2_queue;
    else if(channel ==3)return &usart3_queue;
    else if(channel ==4)return &usart4_queue;
    else if(channel ==5)return &usart5_queue;
    else if(channel ==6)return &usart6_queue;
    else return NULL;
}

void BoardAbstract::usartDeviceInit(DeviceType usart_device_type ,  uint32_t baudrate)
{
    uint8_t device_channel , device_mapping;

    deviceAnaly(usart_device_type , &device_channel , &device_mapping);

    if(usart_device_type == USART_DEBUG){
        if(baudrate == 0) baudrate=921600;
    }
    else if(usart_device_type == USART_PC){
        if(baudrate == 0) baudrate=921600;
    }
    else if(usart_device_type == USART_RADIO){
        if(baudrate == 0) baudrate=115200;
    }
    else if(usart_device_type == USART_GPS){
        if(baudrate == 0) baudrate=9600;
    }
    else if(usart_device_type == USART_SBUS){
        if(baudrate == 0) baudrate=100000;
    }
    else if(usart_device_type == USART_DIGITAL_SERVO){
        axServoInterfaceInit();
        if(baudrate == 0) baudrate=1000000;
    }
    else if(usart_device_type == USART_IMU){
        if(baudrate == 0) baudrate=115200;
    }
    else {
        return;
    }

    HF_USART_Init(device_channel , baudrate , device_mapping);
}

void BoardAbstract::usartDeviceWriteByte(DeviceType usart_device_type , uint8_t reg_data)
{
    uint8_t device_channel = 0 , device_mapping = 0;

    deviceAnaly(usart_device_type , &device_channel , &device_mapping);
    HF_USART_Put_Char(device_channel , reg_data);
}


Queue* BoardAbstract::usartDeviceReadData(DeviceType usart_device_type)
{
    Queue* temp;
    uint8_t device_channel=0 , device_mapping=0;

    deviceAnaly(usart_device_type , &device_channel , &device_mapping);
    temp = getUsartQueue(device_channel);
    return temp;
}

/***********************************************************************************************************************
* Function:
*
* Scope:
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
***********************************************************************************************************************/
void BoardAbstract::iicDeviceInit(DeviceType iic_device_type)
{
    uint8_t device_channel=0 , device_mapping=0;

    deviceAnaly(iic_device_type , &device_channel , &device_mapping);
    HF_Simulat_I2C_Init(device_channel) ;
}

void BoardAbstract::iicDeviceWriteByte(DeviceType iic_device_type , uint8_t equipment_address,
                                       uint8_t reg_address , uint8_t reg_data , uint8_t fastmode)
{
    uint8_t device_channel=0 , device_mapping=0;

    deviceAnaly(iic_device_type , &device_channel , &device_mapping);
    HF_Simulat_I2C_Write_Byte( device_channel , equipment_address , reg_address,
                               reg_data , fastmode);
}

uint8_t BoardAbstract::iicDeviceReadByte(DeviceType iic_device_type , uint8_t equipment_address,
                                         uint8_t reg_address , uint8_t fastmode)
{
    uint8_t device_channel=0 , device_mapping=0;
    uint8_t temp = 0;

    deviceAnaly(iic_device_type , &device_channel , &device_mapping);
    temp = HF_Simulat_I2C_Read_Byte( device_channel , equipment_address,
                                     reg_address , fastmode) ;
    return temp;
}

uint8_t BoardAbstract::iicDeviceWriteBuf(DeviceType iic_device_type , uint8_t equipment_address,
                                         uint8_t reg_address , uint8_t* pt_char , uint8_t size , uint8_t fastmode)
{
    uint8_t device_channel=0 , device_mapping=0;
    uint8_t temp = 0;

    deviceAnaly(iic_device_type , &device_channel , &device_mapping);
    temp = HF_Simulat_I2C_Write_Buf( device_channel , equipment_address , reg_address , pt_char , size , fastmode);
    return temp;
}

uint8_t BoardAbstract::iicDeviceReadBuf(DeviceType iic_device_type , uint8_t equipment_address,
                                        uint8_t reg_address , uint8_t* pt_char , uint8_t size , uint8_t fastmode)
{
    uint8_t device_channel=0 , device_mapping=0;
    uint8_t temp = 0;

    deviceAnaly(iic_device_type , &device_channel , &device_mapping);
    temp = HF_Simulat_I2C_Read_Buf( device_channel , equipment_address , reg_address,
                                    pt_char , size , fastmode);
    return temp;
}

/***********************************************************************************************************************
* Function:
*
* Scope:
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
***********************************************************************************************************************/
void BoardAbstract::spiDeviceInit(DeviceType spi_device_type)
{
    uint8_t device_channel=0 , device_mapping=0;

    deviceAnaly(spi_device_type , &device_channel , &device_mapping);
    HF_SPI_Init(device_channel , device_mapping);
}

uint8_t BoardAbstract::spiDeviceReadWriteByte(DeviceType spi_device_type , uint8_t byte)
{
    uint8_t device_channel = 0 , device_mapping = 0;

    deviceAnaly(spi_device_type , &device_channel , &device_mapping);
    return  HF_SPI_ReadWriteByte(device_channel ,  byte);
}

/***********************************************************************************************************************
* Function:
*
* Scope:
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
***********************************************************************************************************************/
void BoardAbstract::canDeviceInit(DeviceType can_device_type)
{
    uint8_t device_channel=0 , device_mapping=0;

    deviceAnaly(can_device_type , &device_channel , &device_mapping);
    HF_CAN_Init(device_channel , device_mapping);
}

void BoardAbstract::canDeviceSendMessage(DeviceType can_device_type , uint8_t sender_id, uint8_t receiver_id,
                                         uint8_t *txbuf, uint8_t length)
{
    uint8_t device_channel = 0 , device_mapping = 0;

    device_mapping = device_mapping; // avoid not use warning

    deviceAnaly(can_device_type , &device_channel , &device_mapping);
    HF_CANTX_Message(device_channel , sender_id , receiver_id , txbuf , length);
}

float BoardAbstract::getCPUUsage(void)
{
    float cpu_usage_ = 0;
#if  SYSTEM_SUPPORT_OS > 0u
#ifdef 	OS_CRITICAL_METHOD        //support UCOSII
    cpu_usage_ = 0.001 * OSCPUUsage;
#endif

#ifdef 	CPU_CFG_CRITICAL_METHOD   //support UCOSIII
    cpu_usage_ = 0.001 * OSStatTaskCPUUsage;
#endif
#endif
    return cpu_usage_;
}

float BoardAbstract::getCPUTemperature(void)
{
    cpu_temperature_ = 0.8 * HF_Get_CPU_Temperature() + 0.2 * cpu_temperature_;
    return cpu_temperature_;
}

//100HZ
void BoardAbstract::beepStateRenew(void){
    uint16_t toggle_cnt_;
    beep_alarm_cnt_ ++ ;
    if(beep_model <= 2){
        setBeepState(beep_model);
        return;
    }
    else if(beep_model == 3) toggle_cnt_ = 5;
    else if(beep_model == 4) toggle_cnt_ = 25;
    else if (beep_model == 5) toggle_cnt_ = 100;
    else if(beep_model == 6){
        setBeepState(1);
        return;
    }
    else return;
    if(beep_alarm_cnt_ >= toggle_cnt_)
    {
        beep_alarm_cnt_ = 0;
        setBeepState(2);
    }
}

