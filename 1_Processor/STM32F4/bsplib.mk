################################################################################  
# stm32f4xx:
#   bsplib
#   
#   
################################################################################
STM32F4_PATH    = $(TOP_PATH)/1_Processor/STM32F4
STLIB_PATH      = $(STM32F4_PATH)/STM32F4xx_DSP_StdPeriph_Lib_V1.8.0
BSPLIB_PATH     = $(STM32F4_PATH)/BSPLIB

################################################################################
ifeq "$(findstring STM32F429_439xx,$(DDEFS))" "STM32F429_439xx"
ASM_SRC        	+= $(STLIB_PATH)/Libraries/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc_ride7/startup_stm32f429_439xx.s
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rng.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_can.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dac.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dcmi.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fsmc.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_ltdc.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_sai.c

LINKERSCRIPT   	= $(STM32F4_PATH)/LinkScript/STM32F429ZITx_FLASH.ld
endif

ifeq "$(findstring STM32F446xx,$(DDEFS))" "STM32F446xx"
## ???
ASM_SRC        	+= $(STLIB_PATH)/Libraries/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc_ride7/startup_stm32f40_41xxx.s
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rng.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_can.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dac.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dcmi.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fsmc.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_ltdc.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_sai.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_qspi.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spdifrx.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cec.c

LINKERSCRIPT   	= $(STM32F4_PATH)/LinkScript/STM32F446ZETx_FLASH.ld
endif

ifeq "$(findstring STM32F469_479xx,$(DDEFS))" "STM32F469_479xx"
## ???
ASM_SRC        	+= $(STLIB_PATH)/Libraries/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc_ride7/startup_stm32f40_41xxx.s
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rng.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_can.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dac.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dcmi.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fsmc.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_ltdc.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_sai.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_qspi.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dsi.c

LINKERSCRIPT   	= $(STM32F4_PATH)/LinkScript/STM32F469NIHx_FLASH.ld
endif
################################################################################
ifeq "$(findstring STM32F427_437xx,$(DDEFS))" "STM32F427_437xx"
ASM_SRC        	+= $(STLIB_PATH)/Libraries/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc_ride7/startup_stm32f427_437xx.s
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rng.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_can.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dac.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dcmi.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma2d.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fsmc.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_sai.c

LINKERSCRIPT   	= $(STM32F4_PATH)/LinkScript/STM32F429ZITx_FLASH.ld
endif
################################################################################
ifeq "$(findstring STM32F40_41xxx,$(DDEFS))" "STM32F40_41xxx"
ASM_SRC        	+= $(STLIB_PATH)/Libraries/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc_ride7/startup_stm32f40_41xxx.s
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rng.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_can.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dac.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dcmi.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fsmc.c

LINKERSCRIPT   	= $(STM32F4_PATH)/LinkScript/stm32f407xx_flash.ld
endif
################################################################################
ifeq "$(findstring STM32F401xx,$(DDEFS))" "STM32F401xx"
ASM_SRC        	+= $(STLIB_PATH)/Libraries/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc_ride7/startup_stm32f40_41xxx.s
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rng.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_can.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dac.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dcmi.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fsmc.c

LINKERSCRIPT   	= $(STM32F4_PATH)/LinkScript/stm32f401xx_flash.ld
endif
################################################################################
ifeq "$(findstring STM32F410xx,$(DDEFS))" "STM32F410xx"
ASM_SRC        	+= $(STLIB_PATH)/Libraries/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc_ride7/startup_stm32f40_41xxx.s
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rng.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dac.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_lptim.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fmpi2c.c

LINKERSCRIPT   	= $(STM32F4_PATH)/LinkScript/stm32f410xx_flash.ld
endif
################################################################################
ifeq "$(findstring STM32F411xE,$(DDEFS))" "STM32F411xE"
ASM_SRC        	+= $(STLIB_PATH)/Libraries/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc_ride7/startup_stm32f40_41xxx.s
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash_ramfunc.c

LINKERSCRIPT   	= $(STM32F4_PATH)/LinkScript/stm32f411xx_flash.ld
endif
################################################################################
ifeq "$(findstring STM32F412xG,$(DDEFS))" "STM32F412xG"
ASM_SRC        	+= $(STLIB_PATH)/Libraries/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc_ride7/startup_stm32f40_41xxx.s
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rng.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_can.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_qspi.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fsmc.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dfsdm.c

LINKERSCRIPT   	= $(STM32F4_PATH)/LinkScript/stm32f411xx_flash.ld
endif
################################################################################
ifeq "$(findstring STM32F413_423xx,$(DDEFS))" "STM32F413_423xx"
## ???
ASM_SRC        	+= $(STLIB_PATH)/Libraries/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc_ride7/startup_stm32f40_41xxx.s
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fmpi2c.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rng.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_can.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_qspi.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fsmc.c
C_SRC          	+= $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dfsdm.c

LINKERSCRIPT   	= $(STM32F4_PATH)/LinkScript/stm32f411xx_flash.ld
endif
################################################################################

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

