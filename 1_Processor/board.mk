################################################################################  
# CONTROL_UNIT_V1:
#   STM32F407VG ...
#  
# 
################################################################################

ifeq "$(strip $(BOARD_TYPE))" "openre_board_v1"

DDEFS           += -DCONTROL_UNIT_V1 -DSTM32F4XX 
DDEFS           += -DHSE_VALUE=25000000 -DUSE_STDPERIPH_DRIVER 
MCU             ?= cortex-m4  
CPU_TYPE        ?= STM32F4
BOARD_ABSTRACT  ?= $(TOP_PATH)/1_Processor/BoardAbstract/openre_board_v1.cpp

endif

################################################################################  
# CONTROL_UNIT_V2:
#   STM32F407VE ...
#   
#   
################################################################################  

ifeq "$(strip $(BOARD_TYPE))" "openre_board_v2"

DDEFS           += -DCONTROL_UNIT_V2 -DSTM32F4XX 
DDEFS           += -DHSE_VALUE=8000000 -DUSE_STDPERIPH_DRIVER 
MCU             ?= cortex-m4  
CPU_TYPE        ?= STM32F4
BOARD_ABSTRACT  += $(TOP_PATH)/1_Processor/BoardAbstract/openre_board_v2.cpp

endif

################################################################################  
# mallbot_board_v1:
#   STM32F407VE ...
#   
#   
################################################################################  

ifeq "$(strip $(BOARD_TYPE))" "mallbot_board_v1"

DDEFS           += -DCONTROL_UNIT_V2 -DSTM32F4XX 
DDEFS           += -DHSE_VALUE=8000000 -DUSE_STDPERIPH_DRIVER 
MCU             ?= cortex-m4  
CPU_TYPE        ?= STM32F4
BOARD_ABSTRACT  += $(TOP_PATH)/1_Processor/BoardAbstract/mallbot_board_v1.cpp

endif
################################################################################  
# CONTROL_UNIT_V3:
#   
#   
#   
################################################################################  
ifeq "$(strip $(BOARD_TYPE))" "openre_board_mini"

DDEFS           += -DCONTROL_UNIT_MINI -DSTM32F10X 
DDEFS           += -DHSE_VALUE=8000000 -DUSE_STDPERIPH_DRIVER 
MCU             ?= cortex-m3 
CPU_TYPE        ?= STM32F1
BOARD_ABSTRACT  += $(TOP_PATH)/1_Processor/BoardAbstract/openre_board_mini.cpp

endif


################################################################################  
# :
#   
#   
#   
################################################################################  

BOARD_ABSTRACT += $(TOP_PATH)/1_Processor/BoardAbstract/board_abstract.cpp
CXX_SRC   	+= $(BOARD_ABSTRACT) 
INCDIR    	+= -I$(TOP_PATH)/1_Processor/BoardAbstract/ 

################################################################################  

ifeq "$(strip $(CPU_TYPE))" "STM32F1"

include	  	$(TOP_PATH)/1_Processor/STM32F1/bsplib.mk
CXX_SRC		+=$(TOP_PATH)/1_Processor/Interrupt/stm32f10x_it.cpp

endif

ifeq "$(strip $(CPU_TYPE))" "STM32F4"

include	  	$(TOP_PATH)/1_Processor/STM32F4/bsplib.mk
CXX_SRC		+=$(TOP_PATH)/1_Processor/Interrupt/stm32f4xx_it.cpp

endif

