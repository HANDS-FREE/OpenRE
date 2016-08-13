################################################################################  
# OS modules: RTOS   : UCOSII UCOSIII NUTTX 
#             GUI    : EMWIN  STEMWIN
#             FATFS
#
################################################################################  

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

################################################################################  
# UCOSII:
################################################################################  
ifeq "$(USE_UCOSII)" "UCOSII"

UCOSII_PATH     = $(TOP_PATH)/3_OS/$(CPU_TYPE)/RTOS/uCOS-II
DDEFS           += -DUSE_UCOSII

ifeq "$(strip $(FPU_STATE))" "ENABLE"	
ASM_SRC     += $(UCOSII_PATH)/PORT/gnu_os_cpu_a_fpu.s
else
ASM_SRC     += $(UCOSII_PATH)/PORT/gnu_os_cpu_a.s
endif

C_SRC     	+= $(wildcard $(UCOSII_PATH)/CORE/*.c)
C_SRC       += $(UCOSII_PATH)/PORT/os_cpu_c.c

#Includes
INCDIR      += -I$(UCOSII_PATH)/CONFIG -I$(UCOSII_PATH)/CORE \
        -I$(UCOSII_PATH)/PORT 

endif

################################################################################  
# UCOSIII:
################################################################################  
ifeq "$(USE_UCOSIII)" "UCOSIII"

UCOSIII_PATH     = $(TOP_PATH)/3_OS/$(CPU_TYPE)/RTOS/uCOS-III
DDEFS           += -DUSE_UCOSIII
           
C_SRC     	+= $(UCOSIII_PATH)/UCOS-BSP/bsp.c 

ASM_SRC     += $(UCOSIII_PATH)/uC-CPU/ARM-Cortex-M4/GNU/cpu_a.s 
C_SRC     	+= $(UCOSIII_PATH)/uC-CPU/cpu_core.c \
               $(UCOSIII_PATH)/uC-CPU/ARM-Cortex-M4/GNU/cpu_c.c 

ASM_SRC     += $(UCOSIII_PATH)/uC-LIB/Ports/ARM-Cortex-M4/GNU/lib_mem_a.s \               
C_SRC     	+= $(UCOSIII_PATH)/uC-LIB/lib_ascii.c \
               $(UCOSIII_PATH)/uC-LIB/lib_math.c \
               $(UCOSIII_PATH)/uC-LIB/lib_mem.c \
               $(UCOSIII_PATH)/uC-LIB/lib_str.c                              
               
C_SRC       += $(wildcard $(UCOSIII_PATH)/uCOS-III/Source/*.c) 


ifeq "$(strip $(FPU_STATE))" "ENABLE"	
ASM_SRC     += $(UCOSIII_PATH)/uCOS-III/Ports/ARM-Cortex-M4/Generic/GNU/gnu_os_cpu_a_fpu.s
else
ASM_SRC     += $(UCOSIII_PATH)/uCOS-III/Ports/ARM-Cortex-M4/Generic/GNU/gnu_os_cpu_a.s
endif
C_SRC     	+= $(UCOSIII_PATH)/uCOS-III/Ports/ARM-Cortex-M4/Generic/GNU/os_cpu_c.c

C_SRC     	+= $(UCOSIII_PATH)/uCOS-CONFIG/os_app_hooks.c 

#Includes
INCDIR      += -I$(UCOSIII_PATH)/uC-CPU \
            -I$(UCOSIII_PATH)/uC-CPU/ARM-Cortex-M4/GNU \
            -I$(UCOSIII_PATH)/uC-LIB \
            -I$(UCOSIII_PATH)/uC-LIB/Ports/ARM-Cortex-M4/GNU \
            -I$(UCOSIII_PATH)/uCOS-III/Ports/ARM-Cortex-M4/Generic/GNU  \
            -I$(UCOSIII_PATH)/uCOS-III/Source \
            -I$(UCOSIII_PATH)/UCOS-BSP \
            -I$(UCOSIII_PATH)/uCOS-CONFIG \
        
endif

################################################################################  
# GUI:
################################################################################  
ifeq "$(USE_GUI)" "GUI"


endif

################################################################################  
# UCOSIII:
################################################################################  
ifeq "$(USE_FATFS)" "FATFS"


endif

endif


################################################################################  
# 
#if use STM32F1xx 
#
################################################################################  
ifeq "$(strip $(CPU_TYPE))" "STM32F1"

endif


