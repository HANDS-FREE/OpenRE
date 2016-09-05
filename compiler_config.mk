#############################################################packages, board, os

# Board
include	$(TOP_PATH)/1_Processor/board.mk

#package
PACKAGE_PATH 	= $(TOP_PATH)/2_Package
CXX_SRC         += $(foreach n,$(PAKG),$(wildcard $(PACKAGE_PATH)/$(n)/*.cpp))
C_SRC           += $(foreach n,$(PAKG),$(wildcard $(PACKAGE_PATH)/$(n)/*.c))
INCDIR          += $(foreach n,$(PAKG),-I$(PACKAGE_PATH)/$(n))

ifeq "$(strip $(ROBOT_MODEL))" "2WD"
DDEFS           += -DROBOT_WHEEL_MODEL=2
endif
ifeq "$(strip $(ROBOT_MODEL))" "3WD"
DDEFS           += -DROBOT_WHEEL_MODEL=3
endif
ifeq "$(strip $(ROBOT_MODEL))" "4WD"
DDEFS           += -DROBOT_WHEEL_MODEL=4
endif

#OS
include $(TOP_PATH)/3_OS/os.mk

#############################################################bootloader settings

ifeq "$(strip $(BOOTLOADER_MODE))" "ENABLE"
BOOT_PATH       = $(TOP_PATH)/0_Project/Bootloader/Tools
DDEFS           += -DBOOTLOADER_ENABLE
endif

###############################################################compiler settings

CCPREFIX	?= $(TOP_PATH)/Tools/gcc-arm-none-eabi-5_4-2016q2/bin/arm-none-eabi-
#CCPREFIX	?= arm-none-eabi-
CC   		= $(CCPREFIX)gcc
CXX         = $(CCPREFIX)g++
CP   		= $(CCPREFIX)objcopy
AS   		= $(CCPREFIX)gcc -x assembler-with-cpp
GDBTUI      = $(CCPREFIX)gdbtui
HEX  		= $(CP) -O ihex
BIN  		= $(CP) -O binary -S

# Define optimisation level here
OPT += -Os

#IF FPU ENABLE 
ifeq "$(strip $(FPU_STATE))" "ENABLE"	
OPT     += -mfloat-abi=hard
OPT     += -mfpu=fpv4-sp-d16
endif

#
OPT += -fsingle-precision-constant
OPT += -fno-common

#run from Flash
DEFS    += $(DDEFS) -DRUN_FROM_FLASH=1 

MCFLAGS += -mcpu=$(MCU)

ASFLAGS  += $(MCFLAGS) $(OPT) -g -gdwarf-2 -mthumb 

CFLAGS   += $(MCFLAGS) $(OPT) -g -gdwarf-2 -mthumb \
	         -fomit-frame-pointer -Wall -fverbose-asm  \
	         $(DEFS)	 
	         
CXXFLAGS += $(MCFLAGS) $(OPT) -g -gdwarf-2 -mthumb -std=gnu++0x\
           -fomit-frame-pointer -Wall -fverbose-asm \
           -fno-exceptions -fno-rtti -fno-threadsafe-statics -fvisibility=hidden \
           $(DEFS)	         
           
# "-Xlinker --gc-sections" - removes unused code from the output binary - saves memory
LDFLAGS += $(MCFLAGS) $(OPT) -lm -g -gdwarf-2 -mthumb -nostartfiles -Xlinker --gc-sections -T$(LINKERSCRIPT) \
        -Wl,-Map=$(PROJECT).map,--cref,--no-warn-mismatch \
        $(LIBDIR) $(LIB)

##################################################################makefile rules

OBJS  	= $(filter %.o , $(ASM_SRC:.s=.o)) $(filter %.o , $(ASM_SRC:.asm=.o)) \
          $(C_SRC:.c=.o) $(CXX_SRC:.cpp=.o)

ifeq "$(strip $(BOOTLOADER_MODE))" "ENABLE"

all: $(OBJS) $(PROJECT).elf  $(PROJECT).hex $(PROJECT).bin $(PROJECT).px4
	$(CCPREFIX)size $(PROJECT).elf 
 
else

all: $(OBJS) $(PROJECT).elf  $(PROJECT).hex $(PROJECT).bin
	$(CCPREFIX)size $(PROJECT).elf
 
endif
 
%o: %c
	$(CC) -c $(CFLAGS) -I . $(INCDIR) $< -o $@

%o: %cpp
	$(CXX) -c $(CXXFLAGS) -I . $(INCDIR) $< -o $@

%o: %s
	$(AS) -c $(ASFLAGS) $< -o $@

%o: %asm
	$(AS) -c $(ASFLAGS) $< -o $@	

%elf: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(LIBS) -o $@

%hex: %elf
	$(HEX) $< $@
    
%bin: %elf
	$(BIN)  $< $@
	
%px4: %bin
	python $(BOOT_PATH)/px_mkfw.py --prototype $(BOOT_PATH)/Images/HANDSFREE_$(BOARD_TYPE).prototype --image $(PROJECT).bin > $(PROJECT).px4
	
##################################################################makefile clean 
clean:
	-rm -rf $(OBJS)
	-rm -rf $(PROJECT).elf
	-rm -rf $(PROJECT).map
	-rm -rf $(PROJECT).hex
	-rm -rf $(PROJECT).bin
	-rm -rf $(PROJECT).px4
	
###########################################################################flash
 	
include	$(TOP_PATH)/flash.mk 	
     
