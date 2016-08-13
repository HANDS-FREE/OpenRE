/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: fft_test.c
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
* Description:
*
***********************************************************************************************************************/

#include "fft_test.h"

#define FFT_LENGTH		1024		//FFT长度，默认是1024点FFT
float fft_inputbuf[FFT_LENGTH*2];	//FFT输入数组
float fft_outputbuf[FFT_LENGTH];	//FFT输出数组
float fft_timeuse1,fft_timeuse2;
arm_cfft_radix4_instance_f32 scfft;

void FFT_Test(void)
{
    static unsigned char Init=0;
    int i;

    if(Init ==0)
    {
        Init=1;
        arm_cfft_radix4_init_f32(&scfft,FFT_LENGTH,0,1);//初始化scfft结构体，设定FFT相关参数
    }

    for(i=0;i<FFT_LENGTH;i++)//生成信号序列
    {
        fft_inputbuf[2*i]=100+
                10*arm_sin_f32(2*PI*i/FFT_LENGTH)+
                30*arm_sin_f32(2*PI*i*4/FFT_LENGTH)+
                50*arm_cos_f32(2*PI*i*8/FFT_LENGTH);	//生成输入信号实部
        fft_inputbuf[2*i+1]=0;//虚部全部为0
    }

    fft_timeuse1=GET_System_time();
    arm_cfft_radix4_f32(&scfft,fft_inputbuf);	//FFT计算（基4）
    fft_timeuse2=GET_System_time()-fft_timeuse1; //计算FFT所花的时间  64点0.025ms  256点 0.123ms  1000点 0.584ms

    //	arm_cmplx_mag_f32(fft_inputbuf,fft_outputbuf,FFT_LENGTH);	//把运算结果复数求模得幅值
    	printf("\r\n %d point FFT runtime:%f us \r\n",FFT_LENGTH,fft_timeuse2);
    //	printf("FFT Result:\r\n");
    //	for(i=0;i<FFT_LENGTH;i++)
    //	{
    //	 printf("fft_outputbuf[%d]:%f\r\n",i,fft_outputbuf[i]);
    //	}

}

