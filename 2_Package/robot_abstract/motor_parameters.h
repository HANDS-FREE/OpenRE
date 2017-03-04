#ifndef MOTOR_PARAMETERS_H
#define MOTOR_PARAMETERS_H

//enum MotorType{
//    HFMOTORTYPE1,
//    HFMOTORTYPE2,
//    HFMOTORTYPE3,
//    HFMOTORTYPE4,
//    OTHERS };

enum MotorDriverType{
    MotorDriver_PWM12_AND_IO = 0,
    MotorDriver_PWM_AND_IOAB = 1,
};

typedef struct{
    float p1;                         //1 is pid outside ring parameters : mileage loop
    float i1;
    float d1;
    float p2;                         //2 is pid inside ring parameters : speed loop
    float i2;
    float d2;
}MotorPID;

typedef struct {
    unsigned char motor_id;
    MotorDriverType driver_type;
    float encoder_num;    //the encoder sensor count when the  motor turning one circle
    float pwm_max;          //set the max value for pwm
    float pwm_dead_zone;     //when the pwm in this zone , the motor disable
    float speed_low_filter;      //0~1;  default = 0.3
    float protect_current;      //unit : A default = 1
    MotorPID pid;
}MotorParameters;

#endif // MOTOR_PARAMETERS_H
