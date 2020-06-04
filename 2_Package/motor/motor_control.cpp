/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
*
*
* Contact:  QQ Exchange Group -- 521037187
*
* LICENSING TERMS:
* The Hands Free is licensed generally under a permissive 3-clause BSD license. 
* Contributions are requiredto be made under the same license.
*
* History:
* <author>      <time>      <version>      <desc>
* mawenke      2015.10.1    V1.0          creat this file
*
* Description:  The file defined a Class for motor PID control
***********************************************************************************************************************/

#include "motor_control.h"

float MotorControl::dataLimit(float data , float range)
{
    if( data > range ) return range;
    else  if( data <-range ) return -range;
    else return data;
}

float MotorControl::deadZoneLimit(float data , float dead_zone)
{
    if( data > dead_zone ) return data;
    else  if( data <-dead_zone ) return data;
    else return 0;
}

/***********************************************************************************************************************
* Function:     pidOrdinaryCall(....)
*
* Scope:        private
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

void MotorControl::pidOrdinaryCall(float outside_expect , float outside_measure
                                   , float inside_expect , float inside_measure , float pwm_range)
{
    pid_data.i_error_before_last = pid_data.i_error_last;
    pid_data.i_error_last = pid_data.i_error_now;
    pid_data.i_error_now = inside_expect - inside_measure;

    pid_data.i_error_p = para->pid.p2 * pid_data.i_error_now;
    pid_data.i_error_p = dataLimit( pid_data.i_error_p , pwm_range ) ;   //limit the output data ,this is very importan
    if( (inside_expect > 1 || inside_expect < -1) ){
        pid_data.i_error_i += para->pid.i2*pid_data.i_error_now * para->pid_t;
    }
    else  pid_data.i_error_i = 0;
    pid_data.i_error_i = dataLimit( pid_data.i_error_i , pwm_range) ;
    pid_data.i_error_d = para->pid.d2*(pid_data.i_error_now-pid_data.i_error_last) * (1/para->pid_t);
    //pid_data.i_error_d = parameter.pid.d2*(pid_data.i_error_now-2*pid_data.i_error_last+pid_data.i_error_before_last) * (1/pid_t);
    pid_data.i_error_d = dataLimit( pid_data.i_error_d , pwm_range ) ;

    pid_data.i_pidout = pid_data.i_error_p +  pid_data.i_error_i + pid_data.i_error_d;
    pid_data.i_pidout = dataLimit( pid_data.i_pidout , pwm_range ) ;
}

/***********************************************************************************************************************
* Function:     pidSeriesCall(....)
*
* Scope:        private
*
* Description:  series pid  function

*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
void MotorControl::pidSeriesCall(float outside_expect , float outside_measure ,
                                 float inside_expect , float inside_measure , float pwm_range)
{
    pid_data.o_error_before_last = pid_data.o_error_last;
    pid_data.o_error_last = pid_data.o_error_now;
    pid_data.o_error_now = outside_expect - outside_measure;

    pid_data.o_error_p = para->pid.p1 * pid_data.o_error_now;
    if( (inside_expect > 1 || inside_expect < -1)) 	{
        pid_data.o_error_i += para->pid.i1 * pid_data.o_error_now * para->pid_t;
    }
    else  pid_data.o_error_i = 0;
    pid_data.o_error_i = dataLimit( pid_data.o_error_i , pwm_range/2 ) ;
    pid_data.o_error_d = para->pid.d1*(pid_data.o_error_now-pid_data.o_error_last) * (1/para->pid_t);
    // get the outside ring output,and this is inside ring input
    pid_data.o_pidout = pid_data.o_error_p +  pid_data.o_error_i + pid_data.o_error_d;

    pid_data.i_error_before_last = pid_data.i_error_last;
    pid_data.i_error_last = pid_data.i_error_now;
    pid_data.i_error_now = pid_data.o_pidout- inside_measure ;

    pid_data.i_error_p = para->pid.p2 * pid_data.i_error_now;
    pid_data.i_error_p = dataLimit( pid_data.i_error_p , pwm_range ) ;   //limit the output data ,this is very importan
    pid_data.i_error_i += para->pid.i2*pid_data.i_error_now * para->pid_t;
    pid_data.i_error_i = dataLimit( pid_data.i_error_i , pwm_range/2) ;
    pid_data.i_error_d = para->pid.d2*(pid_data.i_error_now-pid_data.i_error_last) * (1/para->pid_t);
    pid_data.i_error_d = dataLimit( pid_data.i_error_d , pwm_range ) ;

    pid_data.i_pidout = pid_data.i_error_p +  pid_data.i_error_i + pid_data.i_error_d;
    pid_data.i_pidout = dataLimit( pid_data.i_pidout , pwm_range ) ;
}

/***********************************************************************************************************************
* Function:     float MotorControl::motorControl(float expect_speed , float unit_count)
*
* Scope:        public
*
* Description:  motor speed control function
*
* Arguments:
* float  expect_speed  ; motor degree/s
* float unit_count ; the count of encoder sensor in one control cycle
* Return:
* float pid_data.i_pidout ;  this is motor control pwm
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
void MotorControl::loopCall(void)
{
    motor_static_damping = 0;
    if(control_data->expect_angle_speed > 0 && control_data->expect_angle_speed < 58) //1 radians
    {
        motor_static_damping = 0.1 * para->pwm_max;
        control_data->expect_angle_speed_filter = control_data->expect_angle_speed;
    }
    else if(control_data->expect_angle_speed < 0 && control_data->expect_angle_speed > -58)
    {
        motor_static_damping = -0.1 * para->pwm_max;
        control_data->expect_angle_speed_filter = control_data->expect_angle_speed;
    }
    else if((control_data->expect_angle_speed >= 58 && control_data->expect_angle_speed <= 180)
            || (control_data->expect_angle_speed <= -58 && control_data->expect_angle_speed >= -180)
            ) //3.14 radians/s
    {
        control_data->expect_angle_speed_filter = control_data->expect_angle_speed;
    }
    else
    {
        control_data->expect_angle_speed_filter = (1 - para->speed_low_filter) * control_data->measure_angle_speed +
                para->speed_low_filter * control_data->expect_angle_speed;
    }

    control_data->measure_unit_encoder =  motor_interface.getEncoderdata(driver_type_id);

    //expect unit encoder num in one cycle to pid
    control_data->expect_unit_encoder = ( control_data->expect_angle_speed_filter / 360 ) * para->encoder_num * para->pid_t;
    control_data->expect_total_encoder += control_data->expect_unit_encoder ;   //recording total encoder
    control_data->measure_total_encoder += control_data->measure_unit_encoder ;
    //recording total angle for robot coordinate calculation
    control_data->d_past_angle += (control_data->measure_unit_encoder/para->encoder_num)*360;
    control_data->past_total_angle+= (control_data->measure_unit_encoder/para->encoder_num)*360;

    //calc motor speed  degree/s
    control_data->measure_angle_speed  = control_data->measure_unit_encoder*360 / (para->encoder_num*para->pid_t);

    if(control_data->enable_flag == 1){
        //motor speed pid control function
        pidOrdinaryCall(control_data->expect_total_encoder , control_data->measure_total_encoder
                        , control_data->expect_unit_encoder , control_data->measure_unit_encoder , para->pwm_max);

        control_data->pwm_output = deadZoneLimit(pid_data.i_pidout , para->pwm_dead_zone);
    }
    else if(control_data->enable_flag == 0){
        control_data->pwm_output = 0;
    }

    control_data->motor_current= motor_interface.getCurrent(driver_type_id);
    if(control_data->motor_current > para->protect_current){
        motor_interface.IODisable(driver_type_id);
        control_data->fault_state = control_data->fault_state | 0x01;  //over current
        return;
    }
    else if(control_data->motor_current < 0.3*para->protect_current){
        motor_interface.IOEnable(driver_type_id);
    }

    if(control_data->pwm_output > 0.3 * para->pwm_max || control_data->pwm_output < -0.3 * para->pwm_max)
    {
        float temp_ = control_data->measure_angle_speed / control_data->pwm_output;
        if(temp_ < 50/para->pwm_max) encoder_error_cnt++;
        else
        {
            encoder_error_cnt=0;
        }

        if(encoder_error_cnt > 0.1/para->pid_t)
        {
            encoder_error_cnt = 0;
            control_data->fault_state = control_data->fault_state | 0x04; //encoder error
            memset(&pid_data , 0 , sizeof(pid_data));
            control_data->pwm_output = 0 ; //0.2 * para->pwm_max;
        }
    }

    //printf("i_error_now=%f i_error_p=%f , i_error_i=%f , i_error_d=%f motor_static_damping=%f\r\n" , pid_data.i_error_now ,
    //       pid_data.i_error_p , pid_data.i_error_i ,pid_data.i_error_d , motor_static_damping);

    motor_interface.setPWM(driver_type_id , control_data->pwm_output + motor_static_damping);
}
