################################################################################  
# UCOSII:
################################################################################  
OS_PATH			= $(TOP_PATH)/3_OS/STM32F4

ifeq "$(USE_UCOSII)" "UCOSII"

UCOSII_PATH     = $(OS_PATH)/RTOS/uCOS-II
DDEFS           += -DUSE_UCOSII

ifeq "$(strip $(FPU_STATE))" "enable"	
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

UCOSIII_PATH     = $(OS_PATH)/RTOS/uCOS-III
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


ifeq "$(strip $(FPU_STATE))" "enable"	
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

