################################################################################  
# stm32f4xx:
#   bsplib
#   
#   
################################################################################
STM32F4_PATH    = $(TOP_PATH)/1_Processor/STM32F4
STLIB_PATH      = $(STM32F4_PATH)/STM32F4xx_DSP_StdPeriph_Lib_V1.8.0
BSPLIB_PATH     = $(STM32F4_PATH)/BSPLIB

ifeq "$(findstring STM32F40_41xxx,$(DDEFS))" "STM32F40_41xxx"
ASM_SRC        	+= $(STLIB_PATH)/Libraries/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc_ride7/startup_stm32f40_41xxx.s
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rng.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_can.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dac.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dcmi.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fsmc.c
endif

C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_adc.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_crc.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dbgmcu.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_exti.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_i2c.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_iwdg.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_pwr.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rtc.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_sdio.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spi.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_syscfg.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_tim.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_usart.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_wwdg.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/misc.c

C_SRC          	+= $(STLIB_PATH)/Libraries/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c
C_SRC          	+= $(wildcard $(BSPLIB_PATH)/*.c)

#Includes
INCDIR += -I$(STM32F4_PATH)/ \
  -I$(BSPLIB_PATH)/ \
  -I$(STLIB_PATH)/Libraries/CMSIS/Device/ST/STM32F4xx/Include/ \
  -I$(STLIB_PATH)/Libraries/CMSIS/Include/ \
  -I$(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/ \
  -I$(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/inc/ \
  
LINKERSCRIPT   	= $(STM32F4_PATH)/LinkScript/stm32f4xx_flash.ld

