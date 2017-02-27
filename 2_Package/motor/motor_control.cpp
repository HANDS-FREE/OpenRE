/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
*
* FileName: motor_driver.cpp
*
* Contact:  QQ Exchange Group -- 521037187
* Version:  V2.0
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

    pid_data.i_error_p = parameter.pid.p2 * pid_data.i_error_now;
    pid_data.i_error_p = dataLimit( pid_data.i_error_p , pwm_range ) ;   //limit the output data ,this is very importan
    if(i_flag == 1 && (inside_expect > 1 || inside_expect < -1) ){
        pid_data.i_error_i += parameter.pid.i2*pid_data.i_error_now * pid_t;
    }
    else  pid_data.i_error_i = 0;
    pid_data.i_error_i = dataLimit( pid_data.i_error_i , pwm_range) ;
    pid_data.i_error_d = parameter.pid.d2*(pid_data.i_error_now-pid_data.i_error_last) * (1/pid_t);
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

    pid_data.o_error_p = parameter.pid.p1 * pid_data.o_error_now;
    if(i_flag == 1 && (inside_expect > 1 || inside_expect < -1)) 	{
        pid_data.o_error_i += parameter.pid.i1 * pid_data.o_error_now * pid_t;
    }
    else  pid_data.o_error_i = 0;
    pid_data.o_error_i = dataLimit( pid_data.o_error_i , pwm_range/2 ) ;
    pid_data.o_error_d = parameter.pid.d1*(pid_data.o_error_now-pid_data.o_error_last) * (1/pid_t);
    // get the outside ring output,and this is inside ring input
    pid_data.o_pidout = pid_data.o_error_p +  pid_data.o_error_i + pid_data.o_error_d;

    pid_data.i_error_before_last = pid_data.i_error_last;
    pid_data.i_error_last = pid_data.i_error_now;
    pid_data.i_error_now = pid_data.o_pidout- inside_measure ;

    pid_data.i_error_p = parameter.pid.p2 * pid_data.i_error_now;
    pid_data.i_error_p = dataLimit( pid_data.i_error_p , pwm_range ) ;   //limit the output data ,this is very importan
    pid_data.i_error_i += parameter.pid.i2*pid_data.i_error_now * pid_t;
    pid_data.i_error_i = dataLimit( pid_data.i_error_i , pwm_range/2) ;
    pid_data.i_error_d = parameter.pid.d2*(pid_data.i_error_now-pid_data.i_error_last) * (1/pid_t);
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
void MotorControl::speedControlCall(void)
{
    control_data.expect_angle_speed = (1 - parameter.speed_low_filter) * control_data.measure_angle_speed +
            parameter.speed_low_filter * expect_angle_speed;
    control_data.measure_unit_encoder =  getEncoderdata(parameter.motor_id);

    //expect unit encoder num in one cycle to pid
    control_data.expect_unit_encoder = ( control_data.expect_angle_speed / 360 ) * parameter.encoder_num * pid_t;
    control_data.expect_total_encoder += control_data.expect_unit_encoder ;   //recording total encoder
    control_data.measure_total_encoder += control_data.measure_unit_encoder ;
    //recording total angle for robot coordinate calculation
    control_data.d_past_angle += (control_data.measure_unit_encoder/parameter.encoder_num)*360;
    control_data.past_total_angle+= (control_data.measure_unit_encoder/parameter.encoder_num)*360;

    //calc motor speed  degree/s
    control_data.measure_angle_speed  = control_data.measure_unit_encoder * 360 / ( parameter.encoder_num*pid_t );

    //motor speed pid control function
    pidOrdinaryCall(control_data.expect_total_encoder , control_data.measure_total_encoder
                    , control_data.expect_unit_encoder , control_data.measure_unit_encoder , parameter.pwm_max);

    control_data.motor_current= getCurrent(parameter.motor_id);
    if(control_data.motor_current > parameter.protect_current){
        IODisable(parameter.motor_id);
        return;
    }
    else if(control_data.motor_current < 0.8*parameter.protect_current){
        IOEnable(parameter.motor_id);
    }

    if( control_enable_flag ==1 ){
        control_data.pwm_output = deadZoneLimit(pid_data.i_pidout , parameter.pwm_dead_zone);
    }
    else if(control_enable_flag == 0){
        control_data.pwm_output = 0;
    }

    setPWM(parameter.motor_id , control_data.pwm_output );

}

