# https://github.com/texane/stlink
STLINK_PATH     	= $(TOP_PATH)/5_Development_Toolchain/stlink 
# https://github.com/ntfreak/openocd
OPENOCD			= $(TOP_PATH)/5_Development_Toolchain/openocd

ifeq ($(OPENOCD),$(wildcard $(OPENOCD)))
OPENOCD_PATH    	= $(TOP_PATH)/5_Development_Toolchain/openocd/src/
OPENOCD_TCL_PATH	= $(TOP_PATH)/5_Development_Toolchain/openocd/
else
OPENOCD_PATH 		=
OPENOCD_TCL_PATH	=
endif

ifeq "$(strip $(BOOTLOADER_MODE))" "enable"
BURN_TYPE       	= usbttl_bootloader_upload 
else
# (stlink/swd/jlink)_(stlink/openocd)_flash  "device"_"driver"_flash
BURN_TYPE      	 	= swd_openocd_flash
DEBUG_TYPE		= swd_openocd_debug
ERASE_TYPE		= swd_openocd_erase
endif

##################################################################flash 
burn: $(BURN_TYPE)
debug: $(DEBUG_TYPE)
erase: $(ERASE_TYPE)

##################################################################
ifeq "$(strip $(CPU_TYPE))" "STM32F1"
BURN_CONFIG_FILE = stm32f1x
endif
ifeq "$(strip $(CPU_TYPE))" "STM32F2"
BURN_CONFIG_FILE = stm32f2x
endif
ifeq "$(strip $(CPU_TYPE))" "STM32F3"
BURN_CONFIG_FILE = stm32f3x
endif
ifeq "$(strip $(CPU_TYPE))" "STM32F4"
BURN_CONFIG_FILE = stm32f4x
endif

swd_openocd_flash:$(PROJECT).bin 
	sudo $(OPENOCD_PATH)openocd -s $(OPENOCD_TCL_PATH)tcl -f interface/jlink.cfg -c "transport select swd" -f target/$(BURN_CONFIG_FILE).cfg -c "init" -c "reset halt" -c "sleep 100" -c "wait_halt 2" -c "flash write_image erase $(PROJECT).bin 0x08000000" -c "sleep 100" -c "verify_image $(PROJECT).bin 0x08000000" -c "sleep 100" -c "reset run" -c shutdown

swd_openocd_debug:$(PROJECT).bin 
	sudo xterm -e $(OPENOCD_PATH)openocd -s $(OPENOCD_TCL_PATH)tcl -f interface/jlink.cfg -c "transport select swd" -f target/$(BURN_CONFIG_FILE).cfg -c "init" -c "halt" -c "reset halt" &
	$(GDB) --eval-command="target remote localhost:3333" $(PROJECT).elf 

swd_openocd_erase:	
	sudo $(OPENOCD_PATH)openocd -s $(OPENOCD_TCL_PATH)tcl -f interface/jlink.cfg -c "transport select swd" -f target/$(BURN_CONFIG_FILE).cfg  -c "init" -c "reset halt" -c "sleep 100" -c "stm32f4x mass_erase 0" -c "sleep 100" -c shutdown 
##################################################################
stlink_openocd_flash: $(PROJECT).bin
	sudo $(OPENOCD_PATH)openocd -s $(OPENOCD_TCL_PATH)tcl -f interface/stlink-v2.cfg -f target/$(BURN_CONFIG_FILE)_stlink.cfg -c "init" -c "reset halt" -c "sleep 100" -c "wait_halt 2" -c "flash write_image erase $(PROJECT).bin 0x08000000" -c "sleep 100" -c "verify_image $(PROJECT).bin 0x08000000" -c "sleep 100" -c "reset run" -c shutdown

stlink_openocd_debug: $(PROJECT).elf stlink_openocd_flash
	xterm -e $(OPENOCD_PATH)openocd -s $(OPENOCD_TCL_PATH)tcl -f interface/stlink-v2.cfg -f target/$(BURN_CONFIG_FILE)_stlink.cfg -c "init" -c "halt" -c "reset halt" &
	$(GDB) --eval-command="target remote localhost:3333" $(PROJECT).elf 
		
stlink_openocd_erase:
	sudo $(OPENOCD_PATH)openocd -s $(OPENOCD_TCL_PATH)tcl -f interface/stlink-v2.cfg -f target/$(BURN_CONFIG_FILE)_stlink.cfg -c "init" -c "reset halt" -c "sleep 100" -c "stm32f4x mass_erase 0" -c "sleep 100" -c shutdown 
##################################################################
stlink_stlink_flash: $(PROJECT).bin
	$(STLINK_PATH)/st-flash write $(PROJECT).bin 0x8000000

stlink_stlink_debug: $(PROJECT).elf
	xterm -e $(STLINK_PATH)/st-util &
	$(GDB) --eval-command="target remote localhost:4242"  $(PROJECT).elf -ex 'load'
	
stlink_stlink_erase:
	$(STLINK_PATH)/st-flash erase	
##################################################################	

##################################################################
usbttl_bootloader_upload: 
	sh $(TOOLS_PATH)/upload.sh $(PROJECT).px4	
##################################################################
