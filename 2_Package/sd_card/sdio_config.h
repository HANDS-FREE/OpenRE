#ifndef __sdio_config_H__
#define __sdio_config_H__

#define SYSTEM_SUPPORT_SD_CARD     1u       //是否使能SD卡  1 使能 0不使能

#if  SYSTEM_SUPPORT_SD_CARD  > 0u
#define SYSTEM_SUPPORT_SD_CARD_TEST 1u      //是否使能SD卡的测试代码  1 使能 0不使能
#endif

#endif  //#ifndef __sdio_config_H__

