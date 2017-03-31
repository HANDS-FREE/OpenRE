#!/bin/bash
sudo usermod -a -G dialout $USER
sudo apt-get install lib32ncurses5 libtool libusb-1.0 libftdi-dev python python-serial python-empy libpython2.7:i386
sudo apt-get remove modemmanager

