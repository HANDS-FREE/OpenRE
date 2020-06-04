#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "motor_parameters.h"
#include "string.h"
#include "motor_interface.h"

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

    MotorControl(){}

    MotorControl(const MotorParameters *para_ , MotorControlData *control_data_, unsigned char driver_type_id_ = 0)
    {
        driver_type_id = driver_type_id_;
        encoder_error_cnt = 0;
        degree_to_radian = 0.017453f;
        radian_to_degree = 57.2958f;
        motor_static_damping = 0;
        para = para_;
        control_data = control_data_;
        init(para);
        memset(&pid_data , 0 , sizeof(pid_data));
    }

    //expect_speed ; motor degree/s
    void loopCall(void);
    void setAngleSpeed(float expect_angle_speed_ ){control_data->expect_angle_speed = expect_angle_speed_ ;}
    float get_d_past_angel(void){    //recording d angle for robot coordinate calculation
        float temp=control_data->d_past_angle;
        control_data->d_past_angle=0;
        return temp;
    }
    void clear_past_total_odom(void){
        control_data->expect_total_encoder = 0;
        control_data->measure_total_encoder = 0;
        control_data->past_total_angle = 0;
    }
    void controlEnable(void){control_data->enable_flag =1;}
    void controlDisable(void){control_data->enable_flag =0;}

    void setParameter(const MotorParameters *para_)
    {
        init(para_);
    }
    const MotorParameters* getParameter(void)
    {
        return para;
    }
    const MotorControlData* getControlData(void)
    {
        return control_data;
    }

private:
    void init(const MotorParameters *para_)
    {
        para = para_;
        motor_interface.init(para->driver_type, para->simulation_model);
        motor_interface.interfaceInit(driver_type_id , para->pwm_max);
        motor_interface.IOEnable(driver_type_id);
        motor_interface.setPWM(driver_type_id , 0);
        controlEnable();
    }

private:
    const MotorParameters *para;
    MotorControlData *control_data;
    MotorPIDData pid_data;
    MotorInterface motor_interface;
    unsigned char driver_type_id;
    unsigned short int encoder_error_cnt;
    float degree_to_radian , radian_to_degree;
    float motor_static_damping;
    float dataLimit(float data , float range);
    float deadZoneLimit(float data , float dead_zone);
    void pidOrdinaryCall(float outside_expect , float outside_measure
                         , float inside_expect , float inside_measure , float pwm_range);
    void pidSeriesCall(float outside_expect , float outside_measure ,
                       float inside_expect , float inside_measure , float pwm_range);
};

#endif // #ifndef MOTOR_CONTROL_H

