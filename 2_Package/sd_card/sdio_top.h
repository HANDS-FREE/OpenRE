#ifndef __sdio_lib_H__
#define __sdio_lib_H__

#include "sdio_config.h"
#include "bsplib.h"

#if Hardware_Platform == 1    //STM32 F1xx
#include "sdio_driver_f1.h"
#endif
#if Hardware_Platform == 4    //STM32 F4xx
#include "sdio_driver_f4.h"
#endif


#if  SYSTEM_SUPPORT_SD_CARD  ==1
unsigned char SD_Card_Init(void) ;   //检测初始化是否成功  返回1成功  0失败


#if  SYSTEM_SUPPORT_SD_CARD_TEST==1
void SD_Card_Test(void);            //SD卡读写测试  ，串口打印信息  注意 会格式化SD卡文件全部
#endif


#endif   //SD_ENABLE

#endif  //sdio.h

