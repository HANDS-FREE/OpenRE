################################################################################  
# OS modules: RTOS   : UCOSII UCOSIII NUTTX 
#             GUI    : EMWIN  STEMWIN
#             FATFS
#
################################################################################  

INCDIR          +=-I$(TOP_PATH)/3_OS/

USE_UCOSII   = $(strip $(filter UCOSII , $(OS_MODULE)))
USE_UCOSIII  = $(strip $(filter UCOSIII, $(OS_MODULE)))
USE_GUI      = $(strip $(filter GUI , $(OS_MODULE)))
USE_FATFS    = $(strip $(filter FATFS , $(OS_MODULE)))

# check whether use multiple OSs
ifeq "$(USE_UCOSII)$(USE_UCOSIII)" "UCOSIIUCOSIII"
$(error Please just select one OS)
endif

################################################################################  
# 
#if use STM32F4xx 
#
################################################################################  
ifeq "$(strip $(CPU_TYPE))" "STM32F4"

include	$(TOP_PATH)/3_OS/STM32F4/stm32f4.mk

endif


################################################################################  
# 
#if use STM32F1xx 
#
################################################################################  
ifeq "$(strip $(CPU_TYPE))" "STM32F1"

include	$(TOP_PATH)/3_OS/STM32F1/stm32f1.mk

endif


