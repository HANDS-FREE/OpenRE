#
# Common Makefile for the PX4 bootloaders
#

#
# Paths to common dependencies
#
export BL_BASE		?= $(wildcard .)
export LIBOPENCM3	?= $(wildcard libopencm3)
export TOP_PATH        =  ../..

#
# Tools
#
CCPREFIX	     ?= $(TOP_PATH)/Tools/gcc-arm-none-eabi-5_4-2016q2/bin/arm-none-eabi-
export CC		 = $(CCPREFIX)gcc
export OBJCOPY   = $(CCPREFIX)objcopy

#
# Common configuration
#
export FLAGS		 = -std=gnu99 \
			   -Os \
			   -g \
			   -Wundef \
			   -Wall \
			   -fno-builtin \
			   -I$(LIBOPENCM3)/include \
			   -ffunction-sections \
			   -nostartfiles \
			   -lnosys \
			   -Wl,-gc-sections \
			   -Werror

export COMMON_SRCS	 = bl.c cdcacm.c  usart.c

#
# Bootloaders to build
#

TARGETS			 = handsfree_cu_v1 handsfree_cu_v2
#TARGETS			 = px4fmu_bl px4fmuv2_bl px4fmuv4_bl px4flow_bl px4discovery_bl px4aerocore_bl px4io_bl px4mavstation_bl

# px4io_bl px4flow_bl

all:	$(TARGETS)


clean:
	rm -f *.elf *.bin

#
# Specific bootloader targets.
#

handsfree_cu_v1: $(MAKEFILE_LIST) $(LIBOPENCM3)
	make -f Makefile.f4 TARGET_HW=HANDSFREE_CU_V1 LINKER_FILE=stm32f4.ld TARGET_FILE_NAME=$@

handsfree_cu_v2: $(MAKEFILE_LIST) $(LIBOPENCM3)
	make -f Makefile.f4 TARGET_HW=HANDSFREE_CU_V2  LINKER_FILE=stm32f4.ld TARGET_FILE_NAME=$@
	
px4fmu_bl: $(MAKEFILE_LIST) $(LIBOPENCM3)
	make -f Makefile.f4 TARGET_HW=PX4_FMU_V1 LINKER_FILE=stm32f4.ld TARGET_FILE_NAME=$@

px4fmuv2_bl: $(MAKEFILE_LIST) $(LIBOPENCM3)
	make -f Makefile.f4 TARGET_HW=PX4_FMU_V2  LINKER_FILE=stm32f4.ld TARGET_FILE_NAME=$@

px4fmuv4_bl: $(MAKEFILE_LIST) $(LIBOPENCM3)
	make -f Makefile.f4 TARGET_HW=PX4_FMU_V4  LINKER_FILE=stm32f4.ld TARGET_FILE_NAME=$@

px4discovery_bl: $(MAKEFILE_LIST) $(LIBOPENCM3)
	make -f Makefile.f4 TARGET_HW=PX4_DISCOVERY_V1  LINKER_FILE=stm32f4.ld TARGET_FILE_NAME=$@

px4flow_bl: $(MAKEFILE_LIST) $(LIBOPENCM3)
	make -f Makefile.f4 TARGET_HW=PX4_FLOW_V1  LINKER_FILE=stm32f4.ld TARGET_FILE_NAME=$@

px4aerocore_bl: $(MAKEFILE_LIST) $(LIBOPENCM3)
	make -f Makefile.f4 TARGET_HW=PX4_AEROCORE_V1 LINKER_FILE=stm32f4.ld TARGET_FILE_NAME=$@

# Default bootloader delay is *very* short, just long enough to catch
# the board for recovery but not so long as to make restarting after a 
# brownout problematic.
#
px4io_bl: $(MAKEFILE_LIST) $(LIBOPENCM3)
	make -f Makefile.f1 TARGET_HW=PX4_PIO_V1 LINKER_FILE=stm32f1.ld TARGET_FILE_NAME=$@

px4mavstation_bl: $(MAKEFILE_LIST) $(LIBOPENCM3)
	make -f Makefile.f1 TARGET_HW=PX4_MAVSTATION_V1 LINKER_FILE=12K-stm32f1.ld TARGET_FILE_NAME=$@

#
# Binary management
#
.PHONY: deploy
deploy:
	zip Bootloader.zip *.bin

#
# Submodule management
#

$(LIBOPENCM3): 
	make -C $(LIBOPENCM3) lib
	
burn_handsfree_cu_v1: all	
	make burn -f $(TOP_PATH)/flash.mk PROJECT=handsfree_cu_v1 

burn_handsfree_cu_v2: all
	make burn -f $(TOP_PATH)/flash.mk PROJECT=handsfree_cu_v2 

