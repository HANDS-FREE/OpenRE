#ifndef ROBOT_ABSTRACT_H
#define ROBOT_ABSTRACT_H

// ROBOT_WHEEL_MODEL : robot type
// 2: 2 wheel robot  balance car  2WD
// 3: 3 universal wheel robot 3WD
// 4: 4 mecanum wheels wheel robot 4WD

//UGV_JILONG_3WD  ID=1
//UGV_JILONG_2WD  ID=2
//UGV_STONE_2WD   ID=3
//UGV_STONE_2WD_PLUS ID=4

#ifndef HF_ROBOT_ID
#define  HF_ROBOT_ID   3
#endif

#if HF_ROBOT_ID == 1
#define ROBOT_WHEEL_MODEL 3
#endif

#if HF_ROBOT_ID == 2
#define ROBOT_WHEEL_MODEL 2
#endif

#if HF_ROBOT_ID == 3
#define ROBOT_WHEEL_MODEL 2
#endif

#if HF_ROBOT_ID == 4
#define ROBOT_WHEEL_MODEL 2
#endif

//MSG struct is the  unit of communication , also is the unit of robot abstract
struct MSGServo4{
    float  servo1;
    float  servo2;
    float  servo3;
    float  servo4;};

struct MSGServo6{
    float  servo1;
    float  servo2;
    float  servo3;
    float  servo4;
    float  servo5;
    float  servo6;};

struct MSGCoord{
    float  x;
    float  y;
    float  z;};

struct MSGPose{
    float  pitch;
    float  roll;
    float  yaw;};

struct MSGSystemInfo{
    float  system_time;
    float  cpu_temperature;
    float  cpu_usage;
    float  battery_voltage;};

struct MSGRobotParameters{
    float robot_wheel_radius;
    float robot_body_radius;
    float speed_low_filter;
};

struct MSGMotorParameters{
    float p1;
    float i1;
    float d1;
    float p2;
    float i2;
    float d2;
};

//unit  distances : metres
//      angle： radian   
class RobotAbstract
{
public:
    RobotAbstract()
    {
        expect_global_speed.x=0;
        expect_global_speed.y=0;
        expect_global_speed.z=0;

        measure_global_speed.x=0;
        measure_global_speed.y=0;
        measure_global_speed.z=0;

        expect_robot_speed.x=0;
        expect_robot_speed.y=0;
        expect_robot_speed.z=0;

        measure_robot_speed.x =0;
        measure_robot_speed.y =0;
        measure_robot_speed.z =0;

        expect_motor_speed.servo1=0;
        expect_motor_speed.servo2=0;
        expect_motor_speed.servo3=0;

        measure_motor_speed.servo1=0;
        measure_motor_speed.servo2=0;
        measure_motor_speed.servo3=0;

        measure_motor_mileage.servo1=0;
        measure_motor_mileage.servo2=0;
        measure_motor_mileage.servo3=0;

        measure_global_coordinate.x=0;
        measure_global_coordinate.y=0;
        measure_global_coordinate.z=0;

        measure_robot_coordinate.x=0;
        measure_robot_coordinate.y=0;
        measure_robot_coordinate.z=0;

        expect_arm1_state.servo1=0;
        expect_arm1_state.servo2=0;
        expect_arm1_state.servo3=0;
        expect_arm1_state.servo4=0;
        expect_arm1_state.servo5=0;
        expect_arm1_state.servo6=0;

        measure_arm1_state.servo1=0;
        measure_arm1_state.servo2=0;
        measure_arm1_state.servo3=0;
        measure_arm1_state.servo4=0;
        measure_arm1_state.servo5=0;
        measure_arm1_state.servo6=0;

        expect_arm2_state.servo1=0;
        expect_arm2_state.servo2=0;
        expect_arm2_state.servo3=0;
        expect_arm2_state.servo4=0;
        expect_arm2_state.servo5=0;
        expect_arm2_state.servo6=0;

        measure_arm2_state.servo1=0;
        measure_arm2_state.servo2=0;
        measure_arm2_state.servo3=0;
        measure_arm2_state.servo4=0;
        measure_arm2_state.servo5=0;
        measure_arm2_state.servo6=0;

        expect_head1_state.pitch=0;
        expect_head1_state.yaw=0;
        measure_head1_state.pitch=0;
        measure_head1_state.yaw=0;

        expect_head2_state.pitch=0;
        expect_head2_state.yaw=0;
        measure_head2_state.pitch=0;
        measure_head2_state.yaw=0;

        measure_imu_euler_angle.pitch=0;
        measure_imu_euler_angle.roll=0;
        measure_imu_euler_angle.yaw=0;

        robot_system_info.battery_voltage=0;
        robot_system_info.cpu_temperature=0;
        robot_system_info.cpu_usage=0;
        robot_system_info.system_time=0;

#if HF_ROBOT_ID == 1
        robot_parameters.robot_wheel_radius=0.0290;
        robot_parameters.robot_body_radius=0.1610;
#endif
#if HF_ROBOT_ID == 2
        robot_parameters.robot_wheel_radius=0.03245;
        robot_parameters.robot_body_radius=0.1460;
#endif
#if HF_ROBOT_ID == 3
        robot_parameters.robot_wheel_radius=0.0320;
        robot_parameters.robot_body_radius=0.1592;
#endif
#if HF_ROBOT_ID == 4
        robot_parameters.robot_wheel_radius=0.03245;
        robot_parameters.robot_body_radius=0.1460;
#endif

        robot_parameters.speed_low_filter=0.4;
    }

    /************************************Chassis***************************************/
    MSGCoord   expect_global_speed;  //(x,y,w)(meter/s,meter/s,radian/s) reference system:global such as /map /odmo ;
    MSGCoord   measure_global_speed;
    MSGCoord   expect_robot_speed;   //(x,y,w)(meter/s,meter/s,radian/s) reference system:robot
    MSGCoord   measure_robot_speed;
    MSGServo4  expect_motor_speed;   //(x1,x2,x3)(radian/s,radian/s,radian/s)
    MSGServo4  measure_motor_speed;
    MSGServo4  measure_motor_mileage; //(x1,x2,x3)(radian,radian,radian)
    MSGCoord   measure_global_coordinate; //(x,y,w)(meter,meter,radian)
    MSGCoord   measure_robot_coordinate;
    /************************************arm***************************************/
    MSGServo6 expect_arm1_state;
    MSGServo6 measure_arm1_state;
    MSGServo6 expect_arm2_state;
    MSGServo6 measure_arm2_state;
    /************************************head***************************************/
    MSGPose   expect_head1_state;  //(pitch,roll,yaw)(radian,radian,radian)
    MSGPose   measure_head1_state;
    MSGPose   expect_head2_state;
    MSGPose   measure_head2_state;
    /************************************IMU Sensors***************************************/
    MSGPose   measure_imu_euler_angle; //(pitch,roll,yaw)(radian,radian,radian)

    /************************************system info***************************************/
    MSGSystemInfo robot_system_info;   //(meter,meter,factor(0~1))

    /************************************parameters***************************************/
    MSGRobotParameters robot_parameters;
    MSGMotorParameters motor_parameters;
};

#endif // ROBOT_ABSTRACT_H

