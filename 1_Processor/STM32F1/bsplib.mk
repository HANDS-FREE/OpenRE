################################################################################  
# stm32f1xx:
#   bsplib
#   
#   
################################################################################
STM32F1_PATH    = $(TOP_PATH)/1_Processor/STM32F1
STLIB_PATH      = $(STM32F1_PATH)/STM32F10x_StdPeriph_Driver
BSPLIB_PATH     = $(STM32F1_PATH)/BSPLIB

ASM_SRC        	+= $(STLIB_PATH)/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/gcc_ride7/startup_stm32f10x_hd.s

C_SRC          	+= $(STLIB_PATH)/CMSIS/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.c
C_SRC          	+= $(wildcard $(STLIB_PATH)/src/*.c)
C_SRC          	+= $(wildcard $(STLIB_PATH)/CMSIS/CM3/CoreSupport/*.c)
C_SRC          	+= $(wildcard $(BSPLIB_PATH)/*.c)

#Includes
INCDIR += -I$(STM32F1_PATH)/ \
  -I$(BSPLIB_PATH)/ \
  -I$(STLIB_PATH)/inc/ \
  -I$(STLIB_PATH)/CMSIS/CM3/CoreSupport/ \
  -I$(STLIB_PATH)/CMSIS/CM3/DeviceSupport/ST/STM32F10x \
  -I$(STLIB_PATH)/ \
  
LINKERSCRIPT   	= $(STM32F1_PATH)/LinkScript/stm32f1xx_flash.ld
