################################################################################  
# stm32f1xx:
#   bsplib
#   
#   
################################################################################
STM32F1_PATH    = $(TOP_PATH)/1_Processor/STM32F1
STLIB_PATH      = $(STM32F1_PATH)/STM32F10x_StdPeriph_Lib_V3.5.0
BSPLIB_PATH     = $(STM32F1_PATH)/BSPLIB

$(warning info: STM32_CPU_TYPE = $(findstring STM32F10X_HD,$(DDEFS)))

ifeq "$(findstring STM32F10X_CL,$(DDEFS))" "STM32F10X_CL"
ASM_SRC        	+= $(STLIB_PATH)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/gcc_ride7/startup_stm32f10x_cl.s
endif

ifeq "$(findstring STM32F10X_LD,$(DDEFS))" "STM32F10X_LD"
ASM_SRC        	+= $(STLIB_PATH)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/gcc_ride7/startup_stm32f10x_ld.s
endif

ifeq "$(findstring STM32F10X_LD_VL,$(DDEFS))" "STM32F10X_LD_VL"
ASM_SRC        	+= $(STLIB_PATH)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/gcc_ride7/startup_stm32f10x_ld_vl.s
endif

ifeq "$(findstring STM32F10X_MD,$(DDEFS))" "STM32F10X_MD"
ASM_SRC        	+= $(STLIB_PATH)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/gcc_ride7/startup_stm32f10x_md.s
endif

ifeq "$(findstring STM32F10X_MD_VL,$(DDEFS))" "STM32F10X_MD_VL"
ASM_SRC        	+= $(STLIB_PATH)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/gcc_ride7/startup_stm32f10x_md_vl.s
endif

ifeq "$(findstring STM32F10X_HD,$(DDEFS))" "STM32F10X_HD"
ASM_SRC        	+= $(STLIB_PATH)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/gcc_ride7/startup_stm32f10x_hd.s
endif

ifeq "$(findstring STM32F10X_HD_VL,$(DDEFS))" "STM32F10X_HD_VL"
ASM_SRC        	+= $(STLIB_PATH)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/gcc_ride7/startup_stm32f10x_hd_vl.s
endif

ifeq "$(findstring STM32F10X_XL,$(DDEFS))" "STM32F10X_XL"
ASM_SRC        	+= $(STLIB_PATH)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/gcc_ride7/startup_stm32f10x_xl.s
endif

C_SRC          	+= $(STLIB_PATH)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.c
C_SRC          	+= $(wildcard $(STLIB_PATH)/Libraries/STM32F10x_StdPeriph_Driver/src/*.c)
C_SRC          	+= $(wildcard $(STLIB_PATH)/Libraries/CMSIS/CM3/CoreSupport/*.c)
C_SRC          	+= $(wildcard $(BSPLIB_PATH)/*.c)

#Includes
INCDIR += -I$(STM32F1_PATH)/ \
  -I$(BSPLIB_PATH)/ \
  -I$(STLIB_PATH)/Libraries/STM32F10x_StdPeriph_Driver/inc/ \
  -I$(STLIB_PATH)/Libraries/CMSIS/CM3/CoreSupport/ \
  -I$(STLIB_PATH)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x \
  -I$(STLIB_PATH)/ \
  
LINKERSCRIPT   	= $(STM32F1_PATH)/LinkScript/stm32f1xx_flash.ld
