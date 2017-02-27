################################################################################  
# stm32f4xx:
#   bsplib
#   
#   
################################################################################
STM32F4_PATH    = $(TOP_PATH)/1_Processor/STM32F4
STLIB_PATH      = $(STM32F4_PATH)/STM32F4-Discovery_FW_V1.1.0
BSPLIB_PATH     = $(STM32F4_PATH)/BSPLIB

ASM_SRC        	+= $(STLIB_PATH)/Libraries/CMSIS/ST/STM32F4xx/Source/Templates/gcc_ride7/startup_stm32f4xx.s

C_SRC          	+= $(STLIB_PATH)/Libraries/CMSIS/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c
C_SRC          	+= $(wildcard $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/*.c)
C_SRC          	+= $(wildcard $(BSPLIB_PATH)/*.c)

#Includes
INCDIR += -I$(STM32F4_PATH)/ \
  -I$(BSPLIB_PATH)/ \
  -I$(STLIB_PATH)/Libraries/CMSIS/ST/STM32F4xx/Include/ \
  -I$(STLIB_PATH)/Libraries/CMSIS/Include/ \
  -I$(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/ \
  -I$(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/inc/ \
  
LINKERSCRIPT   	= $(STM32F4_PATH)/LinkScript/stm32f4xx_flash.ld

