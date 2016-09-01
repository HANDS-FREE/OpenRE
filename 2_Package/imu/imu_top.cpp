/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: imu_top.cpp
* Contact:  QQ Exchange Group -- 521037187
* Version:  V2.0
*
* LICENSING TERMS:
* The Hands Free is licensed generally under a permissive 3-clause BSD license. 
* Contributions are requiredto be made under the same license.
*
* History:
* <author>      <time>      <version>      <desc>
* mawenke       2015.10.1   V1.0           creat this file
* chenyingbing  2015.12.1   V1.6           update
* mawenke       2016.7.1    V2.0           update
* Description:  
*
***********************************************************************************************************************/

#include "imu_top.h"

IMU imu;

/***********************************************************************************************************************
* Function:      void IMU::topInit(uint8_t mpu , uint8_t bmp , uint8_t hmc ,
                  uint8_t ms6 , uint8_t gps)
*
* Scope:         public
*
* Description:   IMU device initialization
*
* Arguments:
*
* Return:
*
* Cpu_Time:    
*
* History:
***********************************************************************************************************************/
void IMU::topInit(uint8_t mpu , uint8_t bmp , uint8_t hmc ,
                  uint8_t ms6 , uint8_t gps ,uint8_t debug)
{

    uint8_t temp;

    board.imuI2CInit();
    debug_en = debug;

    if(mpu == 1)
    {
        mpu6050_en = 1;
        mpu6050 = MPU6050();
        temp = mpu6050.deviceInit();
        if( (temp == 1)&&(debug_en==1) ) printf("mpu6050 initialize success \r\n");
        else if( (temp == 0)&&(debug_en==1) ) printf("mpu6050 initialize failed \r\n");
    }
    if(bmp == 1)
    {
        bmp085_en = 1;
        bmp085 = BMP085();
        temp = bmp085.deviceInit();
        if( (temp == 1)&&(debug_en==1) ) printf("bmp085 initialize success \r\n");
        else if( (temp == 0)&&(debug_en==1) ) printf("bmp085 initialize failed \r\n");
    }
    if(hmc == 1)
    {
        hmc085_en = 1;
        hmc5883l = HMC5883L();
        temp = hmc5883l.deviceInit();
        if( (temp == 1)&&(debug_en==1) ) printf("hmc5883l initialize success \r\n");
        else if( (temp == 0)&&(debug_en==1) ) printf("hmc5883l initialize failed \r\n");
    }
    if(ms6 == 1)
    {
        ms611_en = 1;
        temp = ms611.deviceInit();
        if( (temp == 1)&&(debug_en==1) ) printf("ms611 initialize success \r\n");
        else if( (temp == 0)&&(debug_en==1) ) printf("ms611 initialize failed \r\n");
    }
    if(gps == 1)
    {
        gps_en = 1;
        gps_nmea = GPS_NMEA();
        gps_nmea.GPS_Init();
    }

}

/***********************************************************************************************************************
* Function:      void IMU::topCall(void)
*
* Scope:         public
*
* Description:   imu data updata ,  1000HZ call
*
* Arguments:
*
* Return:
*
* Cpu_Time:  stm32f1(unknow us)  stm32f4+nofpu(unknow us) stm32f4+fpu(631 us)   
*
* History:
* mawenke       2015.10.1   V1.0           creat 
* chenyingbing  2015.12.1   V1.6           update
***********************************************************************************************************************/
void IMU::topCall(void)
{

    imu_call_1++;
    imu_call_2++;
    imu_call_3++;
    imu_call_4++;
    imu_call_5++;

    if( imu_call_1 >= 2 ) //500HZ
    {
        imu_call_1=0;
        mpu6050.dataUpdate();   //stm32f4--280us(fcu)
    }

    if( imu_call_2 >= 5 ) //200HZ
    {
        imu_call_2=0;
    }

    if( imu_call_3 >= 10 ) //100HZ
    {
        imu_call_3 = 0;
        if(bmp085_en == 1) bmp085.dataUpdate();
        if(ms611_en == 1) ms611.dataUpdate();
    }

    if( imu_call_4 >= 20 ) //50HZ
    {
        imu_call_4=0;
        if(hmc085_en == 1) hmc5883l.dataUpdate();  // stm32f4--50us
    }

    if( imu_call_5 >= 50 ) //20HZ
    {
        imu_call_5=0;
        if( debug_en == 1)
        {
//            printf("mpuaccx = %.4f  mpuaccy = %.4f mpuaccz = %.4f\r\n" , mpu6050.acc_normal.x , mpu6050.acc_normal.y,mpu6050.acc_normal.z);
//            printf("hmc_normalx = %.4f  hmc_normaly = %.4f hmc_normalz = %.4f\r\n" , hmc5883l.hmc_normal.x , hmc5883l.hmc_normal.y , hmc5883l.hmc_normal.z);
//            printf("temperature = %.4f pressure = %.4f altitude = %.4f altitude_offset = %.4f\r\n" , ms611.temperature , ms611.pressure , ms611.altitude , ms611.altitude_offset);
        }
    }

}

//void IMU::topCall(void)
//{

//    imu_call_1++;
//    imu_call_2++;
//    imu_call_3++;
//    imu_call_4++;
//    imu_call_5++;
//    if( imu_call_1 >= 2 ) //T=2ms
//    {
//        imu_call_1=0;

//        mpu6050.dataUpdate();  // stm32f4--280us(fcu)

//#if SYSTEM_SUPPROT_FUSION_ARITHMETIC > 0u

//        // 通用	更新
//        imu_arithmetic_model.Set_ModelInitial();	 							// stm32f4--2us(fcu) instantly > 45us
//        imu_arithmetic_model.ModelCommanState_Update();							// stm32f4--35us(fpu)

//        if(imu_arithmetic_model.Imu_Top_fusion_HavingInitial == 1)	  // 已初始化条件
//        {
//            imu_arithmetic_model.XState1_Predict(0.002f);							// stm32f4--54us(fpu)
//            imu_arithmetic_model.XState2_Predict(0.002f);							// stm32f4--54us(fpu)

//#if ARITHMETIC_MPU6050_EXTENDEDKALMAN > 0u
//            // 算法1
//            imu_arithmetic_model.ExtendedKalman_State_Update1();			// stm32f4--37us(fpu)
//            imu_arithmetic_model.XState_KalmanFusionCall_Process1();	    // stm32f4--55us(fpu)

//#endif

//#if ARITHMETIC_MPUHMC5883_EGyroCorrect > 0u
//            // 算法2
//            imu_arithmetic_model.YawError_Correct_State_Update2();	// stm32f4--37us(fpu)
//            imu_arithmetic_model.YawError_Correct_Process2();  // stm32f4--3us(fpu)

//#endif

//            // 接口变量更新
//            imu_arithmetic_model.UpdateState_to_PortVariable();	// stm32f4--35us(fpu)

//        }
//#endif

//    }

//    if( imu_call_2 >= 5 ) //T=5ms
//    {
//        imu_call_2=0;
//        if(hmc085_en == 1) hmc5883l.dataUpdate();  // stm32f4--50us
//        if(bmp085_en == 1) bmp085.dataUpdate();
//        if(ms611_en == 1) ms611.dataUpdate();
//    }

//    if( imu_call_3 >= 10 ) //T=10ms
//    {
//        imu_call_3 = 0;
//    }

//    if( imu_call_4 >= 25 ) //T=25ms
//    {
//        imu_call_4=0;
//        if( mpu6050.getDeviceState() && hmc5883l.getDeviceState() ){
//            imu_arithmetic_model.Fusion_State = 1;
//        }else{
//            imu_arithmetic_model.Fusion_State = 0;
//        }
//#if SYSTEM_SUPPROT_FUSION_ARITHMETIC > 0u
//        //普通量测
//#if ACTIVE_CALCULATE_MESANGLE > 0u
//        imu_arithmetic_model.GetAccHmc_MesAngle_dgree(2);	// stm32f4--9us(fcu)
//#endif

//#endif
//    }

//    if( imu_call_5 >= 50 ) //T=50ms
//    {
//        imu_call_5=0;
//        if( debug_en == 1)
//        {
////            printf("mpustate=%d  hmcstate=%d \r\n" , mpu6050.getDeviceState() , hmc5883l.getDeviceState());
////            printf("%lf %lf %lf \r\n",imu_arithmetic_model.Fus_Angle.pitch
////                   ,imu_arithmetic_model.Fus_Angle.roll,imu_arithmetic_model.Fus_Angle.yaw);
//        }
//    }

//}

