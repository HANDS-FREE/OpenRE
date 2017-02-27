#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "motor_config.h"
#include "motor_parameters.h"
#include "string.h"

class MotorControl
{
public:
    typedef struct {
        float o_error_now;
        float o_error_last;
        float o_error_before_last;
        float o_error_p;
        float o_error_i;
        float o_error_d;
        float o_pidout;
        float i_error_now;
        float i_error_last;
        float i_error_before_last;
        float i_error_p;
        float i_error_i;
        float i_error_d;
        float i_pidout;
    }MotorPIDData;

    typedef struct {
        float  expect_angle_speed;   //degree/s
        float  expect_unit_encoder;
        float  expect_total_encoder;
        float  measure_unit_encoder;
        float  measure_total_encoder;
        float  measure_angle_speed;   //degree/s
        float  d_past_angle;  //recording d angle for robot coordinate calculation
        float  past_total_angle;
        float motor_current;
        float pwm_output;
    }MotorControlData;

    MotorControl()
    {
        i_flag = 1;
        degree_to_radian = 0.017453f;
        radian_to_degree = 57.2958f;
        pid_t = 0;
        expect_angle_speed = 0;
    }

    void controlInit(float pid_t_ , const MotorParameters*  motor_init_structure)
    {
        memset(&parameter , 0 , sizeof(parameter));
        memset(&pid_data , 0 , sizeof(pid_data));
        memset(&control_data , 0 , sizeof(control_data));
        pid_t = pid_t_;
        setParameters(motor_init_structure);
    }

    void setParameters(const MotorParameters*  motor_init_structure)
    {
        parameter = *motor_init_structure;
        interfaceInit(parameter.motor_id , parameter.pwm_max);
        IOEnable(parameter.motor_id);
        setPWM(parameter.motor_id , 0);
        controlEnable();
    }

    // expect_speed  ; motor degree/s
    void speedControlCall(void);
    void setAngleSpeed(float expect_angle_speed_ ){expect_angle_speed = expect_angle_speed_ ;}
    float get_d_past_angel(void){    //recording d angle for robot coordinate calculation
        float temp=control_data.d_past_angle;
        control_data.d_past_angle=0;
        return temp;
    }
    void  clear_past_total_angle(void){ control_data.past_total_angle = 0 ; }
    void controlEnable(void){control_enable_flag =1 ; }
    void controlDisable(void){control_enable_flag =0 ; }
    unsigned char getmotorState(void){return control_enable_flag ; }

    void setPID(const MotorPID*  pid)
    {
        parameter.pid = *pid;
    }
    const MotorParameters* getParameter(void)
    {
        return &parameter;
    }
    const MotorControlData* getControlData(void)
    {
        return &control_data;
    }

public:
    virtual void interfaceInit(unsigned char motor_id_ , float pwm_max) = 0;
    virtual void IOEnable(unsigned char motor_id_ ) = 0;
    virtual void IODisable(unsigned char motor_id_ ) = 0;
    virtual void setPWM(unsigned char motor_id_ , float  pwm) = 0;
    virtual float getEncoderdata(unsigned char motor_id_ ) = 0;
    virtual float getCurrent(unsigned char motor_id_ ) = 0;

private:
    MotorParameters parameter;
    MotorControlData control_data;
    MotorPIDData pid_data;
    unsigned char i_flag;      //pid Integral enable falg
    unsigned char control_enable_flag;
    float pid_t;
    float expect_angle_speed;
    float degree_to_radian , radian_to_degree;
    float dataLimit(float data , float range);
    float deadZoneLimit(float data , float dead_zone);
    void pidOrdinaryCall(float outside_expect , float outside_measure
                         , float inside_expect , float inside_measure , float pwm_range);
    void pidSeriesCall(float outside_expect , float outside_measure ,
                       float inside_expect , float inside_measure , float pwm_range);
};

#endif // #ifndef MOTOR_CONTROL_H

