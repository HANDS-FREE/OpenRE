#!/bin/bash

EXEDIR=`pwd`
BASEDIR=$(dirname $0)
ADDRESS=$2

#$BASEDIR/openocd/src/openocd -s $BASEDIR/openocd/tcl -f interface/jlink.cfg -c "transport select swd" -f target/stm32f4x.cfg -c "init" -c "reset halt" -c "sleep 100" -c "wait_halt 2" -c "flash write_image erase $1 0x08000000" -c "sleep 100" -c "verify_image $1 0x08000000" -c "sleep 100" -c "reset run" -c shutdown

$BASEDIR/openocd/src/openocd -s $BASEDIR/openocd/tcl -f interface/jlink.cfg -c "transport select swd" -f target/stm32f4x.cfg -c "init" -c "reset halt" -c "sleep 100" -c "wait_halt 2" -c "flash write_image erase $1 $ADDRESS" -c "sleep 100" -c "verify_image $1 $ADDRESS" -c "sleep 100" -c "reset run" -c shutdown

