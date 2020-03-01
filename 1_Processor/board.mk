################################################################################  
# openre_board_v1:
#   STM32F407VG ...
#  
# 
################################################################################

ifeq "$(strip $(BOARD_TYPE))" "openre_board_v1"

DDEFS           += -DOPENRE_BOARD_V1 -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER 
DDEFS           += -DHSE_VALUE=25000000 
MCU             ?= cortex-m4  
CPU_TYPE        ?= STM32F4
BOARD_ABSTRACT  ?= $(TOP_PATH)/1_Processor/BoardAbstract/openre_board_v1.cpp

endif

################################################################################  
# openre_board_v2:
#   STM32F407VE ...
#   
#   
################################################################################  

ifeq "$(strip $(BOARD_TYPE))" "openre_board_v2"

DDEFS           += -DOPENRE_BOARD_V2 -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER 
DDEFS           += -DHSE_VALUE=8000000  
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

DDEFS           += -DMALLBOT_BOARD_V1 -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER 
DDEFS           += -DHSE_VALUE=8000000 
MCU             ?= cortex-m4  
CPU_TYPE        ?= STM32F4
BOARD_ABSTRACT  += $(TOP_PATH)/1_Processor/BoardAbstract/mallbot_board_v1.cpp

endif

################################################################################  
# openre_board_mini:
#   
#   
#   
################################################################################  
ifeq "$(strip $(BOARD_TYPE))" "openre_board_mini"

DDEFS           += -DOPENRE_BOARD_MINI -DSTM32F10X_HD -DUSE_STDPERIPH_DRIVER 
DDEFS           += -DHSE_VALUE=8000000 -DSYSCLK_FREQ_72MHz=72000000 
#-DSYSCLK_FREQ_24MHz=24000000 -DSYSCLK_FREQ_36MHz=36000000 -Ddefine SYSCLK_FREQ_48MHz=48000000 
#-DSYSCLK_FREQ_56MHz=56000000 -DSYSCLK_FREQ_72MHz=72000000 
MCU             ?= cortex-m3 
CPU_TYPE        ?= STM32F1
BOARD_ABSTRACT  += $(TOP_PATH)/1_Processor/BoardAbstract/openre_board_mini.cpp

endif

################################################################################  
# alientek_mini:
#   
#   
#   
################################################################################  
ifeq "$(strip $(BOARD_TYPE))" "alientek_mini"

DDEFS           += -DALIENTEK_MINI -DSTM32F10X_HD -DUSE_STDPERIPH_DRIVER 
DDEFS           += -DHSE_VALUE=8000000 -DSYSCLK_FREQ_72MHz=72000000 
#-DSYSCLK_FREQ_24MHz=24000000 -DSYSCLK_FREQ_36MHz=36000000 -Ddefine SYSCLK_FREQ_48MHz=48000000 
#-DSYSCLK_FREQ_56MHz=56000000 -DSYSCLK_FREQ_72MHz=72000000 
MCU             ?= cortex-m3 
CPU_TYPE        ?= STM32F1
BOARD_ABSTRACT  += $(TOP_PATH)/1_Processor/BoardAbstract/alientek_mini.cpp

endif

################################################################################  
# :
#   
#   
#   
################################################################################  

BOARD_ABSTRACT += $(TOP_PATH)/1_Processor/BoardAbstract/board_abstract.cpp
CXX_SRC        += $(BOARD_ABSTRACT) 
INCDIR         += -I$(TOP_PATH)/1_Processor/BoardAbstract/ 

################################################################################  

ifeq "$(strip $(CPU_TYPE))" "STM32F1"

include         $(TOP_PATH)/1_Processor/STM32F1/bsplib.mk
CXX_SRC         +=$(TOP_PATH)/1_Processor/Interrupt/stm32f10x_it.cpp

endif

ifeq "$(strip $(CPU_TYPE))" "STM32F4"

include         $(TOP_PATH)/1_Processor/STM32F4/bsplib.mk
CXX_SRC         +=$(TOP_PATH)/1_Processor/Interrupt/stm32f4xx_it.cpp

endif

