####################################################### system parameters

include	$(TOP_PATH)/0_Project/makefile/configuration.mk
include	$(TOP_PATH)/0_Project/makefile/definition.mk

############################################################# packages, board, os
# Project
include	$(TOP_PATH)/0_Project/project.mk

# Board
include	$(TOP_PATH)/1_Processor/board.mk

#packages
include	$(TOP_PATH)/2_Package/package.mk

#OS
include $(TOP_PATH)/3_OS/os.mk

#LIBS
include $(TOP_PATH)/4_Thirdparty/thirdparty.mk

TOOLS_PATH       = $(TOP_PATH)/0_Project/6_Tools

############################################################# bootloader settings

ifeq "$(strip $(BOOTLOADER_MODE))" "enable"
DDEFS           += -DBOOTLOADER_ENABLE
endif

############################################################### compiler settings
ARMGCC		= $(TOP_PATH)/5_Development_Toolchain/gcc-arm-none-eabi-5_4-2016q2/bin/arm-none-eabi-gcc

ifeq ($(ARMGCC),$(wildcard $(ARMGCC)))
CCPREFIX	?= $(TOP_PATH)/5_Development_Toolchain/gcc-arm-none-eabi-5_4-2016q2/bin/arm-none-eabi-
else
CCPREFIX	?= arm-none-eabi-
endif

CC   		= $(CCPREFIX)gcc
CXX         = $(CCPREFIX)g++
CP   		= $(CCPREFIX)objcopy
AS   		= $(CCPREFIX)gcc -x assembler-with-cpp
GDB		    = $(CCPREFIX)gdb
HEX  		= $(CP) -O ihex
BIN  		= $(CP) -O binary -S

# Define optimisation level here
OPT += -Os
OPT += -fsingle-precision-constant
OPT += -fno-common

#fpu config
ifeq "$(strip $(CPU_TYPE))" "STM32F1"	
FPU_STATE       == disable
endif
ifeq "$(strip $(CPU_TYPE))" "STM32F4"	
FPU_STATE       == enable
endif

ifeq "$(strip $(FPU_STATE))" "enable"	
OPT     += -mfloat-abi=hard
OPT     += -mfpu=fpv4-sp-d16
endif

#run from Flash
DEFS    += $(DDEFS) -DRUN_FROM_FLASH=1 

MCFLAGS += -mcpu=$(MCU)

ASFLAGS  += $(MCFLAGS) $(OPT) -g -gdwarf-2 -mthumb 

CFLAGS   += $(MCFLAGS) $(OPT) -g -gdwarf-2 -mthumb \
	         -fomit-frame-pointer -Wall -fverbose-asm  \
	         $(DEFS)	 
	         
#-std=gnu++0x

CXXFLAGS += $(MCFLAGS) $(OPT) -g -gdwarf-2 -mthumb -std=c++11\
           -fomit-frame-pointer -Wall -fverbose-asm \
           -fno-exceptions -fno-rtti -fno-threadsafe-statics -fvisibility=hidden \
           $(DEFS)	         
           
# "-Xlinker --gc-sections" - removes unused code from the output binary - saves memory
LDFLAGS += $(MCFLAGS) $(OPT) -lm -g -gdwarf-2 -mthumb -nostartfiles -Xlinker --gc-sections -T$(LINKERSCRIPT) \
        -Wl,-Map=$(PROJECT).map,--cref,--no-warn-mismatch \
        $(LIBDIR) $(LIB)

################################################################## makefile rules

OBJS  	= $(filter %.o , $(ASM_SRC:.s=.o)) $(filter %.o , $(ASM_SRC:.asm=.o)) \
          $(C_SRC:.c=.o) $(CXX_SRC:.cpp=.o)

ifeq "$(strip $(BOOTLOADER_MODE))" "enable"

all: $(OBJS) $(PROJECT).elf  $(PROJECT).hex $(PROJECT).bin $(PROJECT).px4
	$(CCPREFIX)size $(PROJECT).elf 
 
else

all: $(OBJS) $(PROJECT).elf  $(PROJECT).hex $(PROJECT).bin
	$(CCPREFIX)size $(PROJECT).elf
 
endif
 
%.o: %.c
	$(CC) -c $(CFLAGS) -I . $(INCDIR) $< -o $@

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) -I . $(INCDIR) $< -o $@

%.o: %.s
	$(AS) -c $(ASFLAGS) $< -o $@

%.o: %.asm
	$(AS) -c $(ASFLAGS) $< -o $@	

%.elf: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(LIBS) -o $@

%.hex: %.elf
	$(HEX) $< $@
    
%.bin: %.elf
	$(BIN)  $< $@
	
%.px4: %.bin
	python $(TOOLS_PATH)/px_mkfw.py --prototype $(TOOLS_PATH)/Images/HANDSFREE_$(BOARD_TYPE).prototype --image $(PROJECT).bin > $(PROJECT).px4
	
################################################################## makefile clean 
clean:
	-rm -rf $(OBJS)
	-rm -rf $(PROJECT).elf
	-rm -rf $(PROJECT).map
	-rm -rf $(PROJECT).hex
	-rm -rf $(PROJECT).bin
	-rm -rf $(PROJECT).px4

########################################################################### flash

include	$(TOP_PATH)/0_Project/makefile/flash.mk
     
