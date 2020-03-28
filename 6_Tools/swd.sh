#!/bin/bash

# usage :  sh swd_upload.sh xxx.bin

EXEDIR=`pwd`
BASEDIR=$(dirname $0)
OPENOCD_PATH=$BASEDIR/../5_Development_Toolchain/openocd

sudo $OPENOCD_PATH/src/openocd -s $OPENOCD_PATH/tcl -f interface/jlink.cfg -c "transport select swd" -f target/stm32f4x.cfg -c "init" -c "reset halt" -c "sleep 100" -c "wait_halt 2" -c "flash write_image erase $1 0x08000000" -c "sleep 100" -c "verify_image $1 0x08000000" -c "sleep 100" -c "reset run" -c shutdown


