################################################################################  
# CONTROL_UNIT_V1:
#   STM32F407VG ...
#   MPU6050 ...
#   ...
################################################################################

ifeq "$(strip $(BOARD_TYPE))" "CONTROL_UNIT_V1"

DDEFS           += -DCONTROL_UNIT_V1 -DHARDWARE_PLATFORM=4 
DDEFS           += -DHSE_VALUE=25000000 -DUSE_STDPERIPH_DRIVER 
DDEFS           += -DSTM32F4XX 
MCU             ?= cortex-m4  
CPU_TYPE        ?= STM32F4

STLIB_PATH      = $(TOP_PATH)/1_Processor/$(CPU_TYPE)/STM32F4-Discovery_FW_V1.1.0
BSPLIB_PATH     = $(TOP_PATH)/1_Processor/$(CPU_TYPE)/BSPLIB

ASM_SRC        	+= $(STLIB_PATH)/Libraries/CMSIS/ST/STM32F4xx/Source/Templates/gcc_ride7/startup_stm32f4xx.s

C_SRC          	+= $(STLIB_PATH)/Libraries/CMSIS/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c
C_SRC          	+= $(wildcard $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/*.c)
C_SRC          	+= $(wildcard $(BSPLIB_PATH)/*.c)

CXX_SRC        	+= $(wildcard $(TOP_PATH)/1_Processor/BoardAbstract/*.cpp)
	
#Includes
INCDIR += -I. \
  -I$(STLIB_PATH)/Libraries/CMSIS/ST/STM32F4xx/Include/ \
  -I$(STLIB_PATH)/Libraries/CMSIS/Include/ \
  -I$(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/ \
  -I$(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/inc/ \
  -I$(TOP_PATH)/1_Processor/STM32F4/ \
  -I$(TOP_PATH)/1_Processor/STM32F4/BSPLIB/ \
  -I$(TOP_PATH)/1_Processor/BoardAbstract/ 

LINKERSCRIPT   	= $(TOP_PATH)/1_Processor/LinkScript/stm32f4xx_flash.ld

endif

################################################################################  
# CONTROL_UNIT_V2:
#   STM32F407VE ...
#   MPU6050 ...
#   ...
################################################################################  

ifeq "$(strip $(BOARD_TYPE))" "CONTROL_UNIT_V2"

DDEFS           += -DCONTROL_UNIT_V2 -DHARDWARE_PLATFORM=4 
DDEFS           += -DHSE_VALUE=8000000 -DUSE_STDPERIPH_DRIVER 
DDEFS           += -DSTM32F4XX 
MCU             ?= cortex-m4  
CPU_TYPE        ?= STM32F4

STLIB_PATH      = $(TOP_PATH)/1_Processor/$(CPU_TYPE)/STM32F4-Discovery_FW_V1.1.0
BSPLIB_PATH     = $(TOP_PATH)/1_Processor/$(CPU_TYPE)/BSPLIB

ASM_SRC        	+= $(STLIB_PATH)/Libraries/CMSIS/ST/STM32F4xx/Source/Templates/gcc_ride7/startup_stm32f4xx.s

C_SRC          	+= $(STLIB_PATH)/Libraries/CMSIS/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c
C_SRC          	+= $(wildcard $(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/src/*.c)
C_SRC          	+= $(wildcard $(BSPLIB_PATH)/*.c)

CXX_SRC        	+= $(wildcard $(TOP_PATH)/1_Processor/BoardAbstract/*.cpp)
	
#Includes
INCDIR += -I. \
  -I$(STLIB_PATH)/Libraries/CMSIS/ST/STM32F4xx/Include/ \
  -I$(STLIB_PATH)/Libraries/CMSIS/Include/ \
  -I$(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/ \
  -I$(STLIB_PATH)/Libraries/STM32F4xx_StdPeriph_Driver/inc/ \
  -I$(TOP_PATH)/1_Processor/STM32F4/ \
  -I$(TOP_PATH)/1_Processor/STM32F4/BSPLIB/ \
  -I$(TOP_PATH)/1_Processor/BoardAbstract/ 

LINKERSCRIPT   	= $(TOP_PATH)/1_Processor/LinkScript/stm32f4xx_flash.ld

endif


