# OpenRE -- The Open Source Robot Embedded Library 
## keywords: moblile robotics , STM32 , c++ , makefiles , ROS 

------------------------------------------------------------------------------
## Description

This is a C++ embedded library for robotics base on STM32 and intended to provide GNU Makefiles.    

### [OpenRE Tutorial](https://github.com/HANDS-FREE/HANDS-FREE.github.io/wiki/6.-OpenRE-Tutorial)
    
###  Website: 
- QQ Group: 521037187（Hands Free Community）
- [HandsFree baiduyun](https://pan.baidu.com/s/1nuSvs7Z#list) 
- [HandsFree Website](https://hands-free.github.io/)
- [Introduction](http://www.rosclub.cn/post-14.html)
- [Robot Navigation Show ](http://v.youku.com/v_show/id_XMTUyODk4NTUzNg==.htm)    
- [HandsFree Highlight Show](http://v.youku.com/v_show/id_XMTU0NzgwNzc3Mg==.html?from=y1.7-1.2) 

###  Folder structure
- ├── ** 0_Project **   ----  some demos base on this library  
- │   ├── examples   ----   stm32fxx examples project of openre
- │   ├── firmware  ----  firmware projects of handsfree robots
- │   ├── etc..
- ├── ** 1_Processor **   --- the board-level abstraction layer ,   support handsfree countrol_unit_v1 , countrol_unit_v2, countrol_unit_mini , stm32f407_discovery     
- │   ├── BoardAbstract
- │   ├── board.mk
- │   ├── Interrupt
- │   ├── STM32F1
- │   └── STM32F4
- │   ├── etc..
- ├── ** 2_Package **  ----  this dir include many tool packs . you can use it for moblile robotics, fly control etc..    
- │   ├── common
- │   ├── hf_link
- │   ├── imu
- │   ├── motor
- │   ├── robot_abstract
- │   ├── robot_control
- │   ├── tf
- │   ├── etc..
- ├── ** 3_OS **  : OpenRE support RTOS(ucosII ucosIII nuttx), GUI(STEMWIN) , FATFS   
- ├── ** 4_Thirdparty **
- │   ├── Dobot 
- │   ├── Eigen3
 -│   ├── libs_include.h
- │   ├── Matrix
- │   └── thirdparty.mk
- ├── ** 5_Development_Toolchain **
- ├── ** 6_Tools **
- │   ├── env_config.sh
- │   ├── swd_upload.sh
- │   ├── tarall.sh
- │   └── tar.sh
- ├── ** 7_Documentation **
- ├── clean_build_linux.sh
- ├── clean_build_win.bat
- ├── HANDS_FREE_OpenRE_F1.pro
- ├── HANDS_FREE_OpenRE_F4.pro
- └── README.md

## Installation
------------------------------------------------------------------------------
### Resources   
  * Download the latest code with:      
  
            git clone https://github.com/HANDS-FREE/OpenRE      
            cd 6_Tools      
            sh env_config.sh       

### OpenRE  Toolchain         
#### Method1: (recommended)
            sudo add-apt-repository ppa:terry.guo/gcc-arm-embedded  
            sudo apt-get update          
            sudo apt-get install openocd  gcc-arm-none-eabi    
            sudo usermod -a -G dialout $USER    
            sudo apt-get install lib32ncurses5 libtool libusb-1.0 libftdi-dev python python-serial python-empy libpython2.7:i386    
            sudo apt-get remove modemmanager    
            
#### Method2:
- get toolchain it in [Development_Toolchain](https://pan.baidu.com/s/1nuSvs7Z#list/path=%2FHANDSFREE%2FHands_Free_Release%2F3_Software%2FEmbedded_Development_Toolchain&parentPath=%2FHANDSFREE)
- put these softwares in OpenRE/5_Development_Toolchain     
- open a terminal and run:  ** sh install.sh **     
- sudo usermod -a -G dialout $USER      
- sudo apt-get install lib32ncurses5 libtool libusb-1.0 libftdi-dev python python-serial python-empy libpython2.7:i386     
- sudo apt-get remove modemmanager    

## Usage and Examples
---

### A Simple Demo 
    * Led toggle:     
            cd 0_Project/examples/handsfree_simple_app/linux    
            
 **check the makefile config matching your main control board **      
             
            make clean
            make    
            make burn   

### Robot Firmware

            cd 0_Project/firmware/handsfree_wheel_robot/linux

 ** check the makefile config  matching your main control board **      
             
            make clean
            make
            make burn

---
 Lots of examples are provided in folder 0_Project and you can get some manuals in folder 7_Documentation.

## License

--- 
OpenRE is licensed generally under a permissive 3-clause BSD license. Contributions are required to be made under the same license.            
            
## Contact    

---
If you have any problem, or you have some suggestions for this code, please contact WenKe Ma by 315261982@qq.com, thank you very much!  
