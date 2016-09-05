# https://github.com/texane/stlink
STLINK_PATH     = $(TOP_PATH)/Tools/stlink 
# https://github.com/ntfreak/openocd
OPENOCD_PATH    = $(TOP_PATH)/Tools/openocd

ifeq "$(strip $(BOOTLOADER_MODE))" "ENABLE"
BURN_TYPE       = usbttl_bootloader_upload 
else
# (stlink/swd/jlink)_(stlink/openocd)_flash  "device"_"driver"_flash
BURN_TYPE       = swd_openocd_flash
endif

##################################################################flash 
burn: $(BURN_TYPE)

##################################################################
swd_openocd_flash:$(PROJECT).bin
	$(OPENOCD_PATH)/src/openocd -s $(OPENOCD_PATH)/tcl -f interface/jlink.cfg -c "transport select swd" -f target/stm32f4x.cfg -c "init" -c "reset halt" -c "sleep 100" -c "wait_halt 2" -c "flash write_image erase $(PROJECT).bin 0x08000000" -c "sleep 100" -c "verify_image $(PROJECT).bin 0x08000000" -c "sleep 100" -c "reset run" -c shutdown

swd_openocd_debug:$(PROJECT).bin

swd_openocd_erase:	
##################################################################
stlink_openocd_flash: $(PROJECT).bin
	$(OPENOCD_PATH)/src/openocd -s $(OPENOCD_PATH)/tcl -f interface/stlink-v2.cfg -f target/stm32f4x_stlink.cfg -c "init" -c "reset halt" -c "sleep 100" -c "wait_halt 2" -c "flash write_image erase $(PROJECT).bin 0x08000000" -c "sleep 100" -c "verify_image $(PROJECT).bin 0x08000000" -c "sleep 100" -c "reset run" -c shutdown

stlink_openocd_debug: $(PROJECT).elf stlink_openocd_flash
	xterm -e $(STLINK_PATH)/openocd  -s $(STLINK_PATH)/tcl -f interface/stlink-v2.cfg -f target/stm32f0x_stlink.cfg -c "init" -c "halt" -c "reset halt" &
	$(GDBTUI) --eval-command="target remote localhost:3333" $(PROJECT).elf 
		
stlink_openocd_erase:
	$(OPENOCD_PATH)/src/openocd -s $(OPENOCD_PATH)/tcl -f interface/stlink-v2.cfg -f target/stm32f4x_stlink.cfg -c "init" -c "reset halt" -c "sleep 100" -c "stm32f4x mass_erase 0" -c "sleep 100" -c shutdown 
##################################################################
stlink_stlink_flash: $(PROJECT).bin
	$(STLINK_PATH)/st-flash write $(PROJECT).bin 0x8000000

stlink_stlink_debug: $(PROJECT).elf
	xterm -e $(STLINK_PATH)/st-util &
	$(GDBTUI) --eval-command="target remote localhost:4242"  $(PROJECT).elf -ex 'load'
	
stlink_stlink_erase:
	$(STLINK_PATH)/st-flash erase	
##################################################################	

##################################################################
usbttl_bootloader_upload: 
	python $(BOOT_PATH)/px_uploader.py --port dev/ttyUSB0 $(PROJECT).px4
##################################################################

