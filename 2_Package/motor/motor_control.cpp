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


/***********************************************************************************************************************
* Function:     float MotorControl::dataLimit(float data , float range)
*
* Scope:        private
*
* Description:  data limited
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
float MotorControl::dataLimit(float data , float range)
{
    if( data > range ) return range;
    else  if( data <-range ) return -range;
    else return data;
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
    pid_parameters_.i_error_before_last = pid_parameters_.i_error_last;
    pid_parameters_.i_error_last = pid_parameters_.i_error_now;
    pid_parameters_.i_error_now = inside_expect - inside_measure;

    pid_parameters_.i_error_p = pid_parameters_.p2 * pid_parameters_.i_error_now;
    pid_parameters_.i_error_p = dataLimit( pid_parameters_.i_error_p , pwm_range ) ;   //limit the output data ,this is very importan
    if(pid_parameters_.i_flag == 1 && (inside_expect > 1 || inside_expect < -1) )
        pid_parameters_.i_error_i += pid_parameters_.i2*pid_parameters_.i_error_now * pid_t;
    else  pid_parameters_.i_error_i = 0;
    pid_parameters_.i_error_i = dataLimit( pid_parameters_.i_error_i , pwm_range) ;
    pid_parameters_.i_error_d = pid_parameters_.d2*(pid_parameters_.i_error_now-pid_parameters_.i_error_last) * (1/pid_t);
    //pid_parameters_.i_error_d = pid_parameters_.d2*(pid_parameters_.i_error_now-2*pid_parameters_.i_error_last+pid_parameters_.i_error_before_last) * (1/pid_t);
    pid_parameters_.i_error_d = dataLimit( pid_parameters_.i_error_d , pwm_range ) ;

    pid_parameters_.i_pidout = pid_parameters_.i_error_p +  pid_parameters_.i_error_i + pid_parameters_.i_error_d;
    pid_parameters_.i_pidout = dataLimit( pid_parameters_.i_pidout , pwm_range ) ;

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

    pid_parameters_.o_error_before_last = pid_parameters_.o_error_last;
    pid_parameters_.o_error_last = pid_parameters_.o_error_now;
    pid_parameters_.o_error_now = outside_expect - outside_measure;

    pid_parameters_.o_error_p = pid_parameters_.p1 * pid_parameters_.o_error_now;
    if(pid_parameters_.i_flag == 1 && (inside_expect > 1 || inside_expect < -1)) 	pid_parameters_.o_error_i += pid_parameters_.i1 * pid_parameters_.o_error_now * pid_t;
    else  pid_parameters_.o_error_i = 0;
    pid_parameters_.o_error_i = dataLimit( pid_parameters_.o_error_i , pwm_range/2 ) ;
    pid_parameters_.o_error_d = pid_parameters_.d1*(pid_parameters_.o_error_now-pid_parameters_.o_error_last) * (1/pid_t);
    // get the outside ring output,and this is inside ring input
    pid_parameters_.o_pidout = pid_parameters_.o_error_p +  pid_parameters_.o_error_i + pid_parameters_.o_error_d;

    pid_parameters_.i_error_before_last = pid_parameters_.i_error_last;
    pid_parameters_.i_error_last = pid_parameters_.i_error_now;
    pid_parameters_.i_error_now = pid_parameters_.o_pidout- inside_measure ;

    pid_parameters_.i_error_p = pid_parameters_.p2 * pid_parameters_.i_error_now;
    pid_parameters_.i_error_p = dataLimit( pid_parameters_.i_error_p , pwm_range ) ;   //limit the output data ,this is very importan
    pid_parameters_.i_error_i += pid_parameters_.i2*pid_parameters_.i_error_now * pid_t;
    pid_parameters_.i_error_i = dataLimit( pid_parameters_.i_error_i , pwm_range/2) ;
    pid_parameters_.i_error_d = pid_parameters_.d2*(pid_parameters_.i_error_now-pid_parameters_.i_error_last) * (1/pid_t);
    pid_parameters_.i_error_d = dataLimit( pid_parameters_.i_error_d , pwm_range ) ;

    pid_parameters_.i_pidout = pid_parameters_.i_error_p +  pid_parameters_.i_error_i + pid_parameters_.i_error_d;
    pid_parameters_.i_pidout = dataLimit( pid_parameters_.i_pidout , pwm_range ) ;

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
* float pid_parameters_.i_pidout ;  this is motor control pwm
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
float MotorControl::speedControl(float expect_speed , float unit_count)
{

    expect_angle_speed = expect_speed;

    if(motor_simulation_model == 1)
    {
        measure_unit_encoder = (simulation_max_angel_speed/360.0f)
                *( pid_parameters_.i_pidout/pwm_max ) * encoder_num * pid_t;
    }
    else
    {
        measure_unit_encoder =  unit_count;  //if you using real motor
    }

    //expect unit encoder num in one cycle to pid
    expect_unit_encoder = ( expect_angle_speed / 360 ) * encoder_num * pid_t;
    expect_total_encoder += expect_unit_encoder ;   //recording total encoder
    measure_total_encoder += measure_unit_encoder ;
    //recording total angle for robot coordinate calculation
    d_past_angle += (measure_unit_encoder/encoder_num)*360;
    past_total_angle+=(measure_unit_encoder/encoder_num)*360;

    //calc motor speed  degree/s
    measure_angle_speed  = measure_unit_encoder * 360 / ( encoder_num*pid_t);

    //motor speed pid control function
    pidOrdinaryCall(expect_total_encoder , measure_total_encoder
                    , expect_unit_encoder , measure_unit_encoder , pwm_max);

    return  pid_parameters_.i_pidout;
}

