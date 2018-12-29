#!/bin/bash

# install command
install_command="sudo apt-get install -y"

sudo apt-get remove modemmanager  

wget http://handsfree-mv.oss-cn-shenzhen.aliyuncs.com/handsfree_download/OpenRE_Development_Toolchain/gcc-arm-none-eabi-5_4-2016q2.tar.bz2
wget http://handsfree-mv.oss-cn-shenzhen.aliyuncs.com/handsfree_download/OpenRE_Development_Toolchain/openocd.tar.bz2
wget http://handsfree-mv.oss-cn-shenzhen.aliyuncs.com/handsfree_download/OpenRE_Development_Toolchain/stlink.tar.bz2

$install_command lib32ncurses5 libtool libusb-1.0 libftdi-dev python python-serial python-empy libpython2.7:i386     
tar -jxvf gcc-arm-none-eabi-5_4-2016q2.tar.bz2
tar -jxvf openocd.tar.bz2
tar -jxvf stlink.tar.bz2
cd openocd/
./configure
make clean
make
cd ../stlink/
make clean
make
cd ../

sudo usermod -a -G dialout $USER      
  
