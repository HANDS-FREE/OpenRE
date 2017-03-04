#!/bin/bash
sudo usermod -a -G dialout $USER
sudo apt-get install lib32ncurses5
sudo apt-get install libtool libusb-1.0 libftdi-dev
sudo apt-get remove modemmanager
sudo apt-get install python python-serial python-empy
sudo apt-get install libpython2.7:i386

