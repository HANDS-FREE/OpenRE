# The Open Source Robot Embedded Librarys (OpenRE)  
# keywords: moblile robotics , STM32 , c++ , makefiles , ROS 
------------------------------------------------------------------------------
##1.Introduction
This is a C++ embedded librarys for robotics base on STM32 and intended to provide GNU Makefiles.
OpenRE is licensed generally under a permissive 3-clause BSD license. Contributions are required to be made under the same license.

### 1.1. Website: 
- http://www.rosclub.cn/post-265.html
- QQ Group: 521037187（Hands Free Community）

### 1.2. Folder structure
*OpeRE --- top dir  
-**0_Project** --- some demos base on this library  
---*Application*  --- projects of handsfree robots , Like omni wheel robot(3WD) and differential robot  (2WD)   
---*STM32F1DEMO*  --- demos base on stm32f1xx   
---*STM32F4DEMO*  --- demos base on stm32f4xx     
-**1_Processor**  --- the board-level abstraction layer   
---*ARMLIB*     
---*BoardAbstract*  
---*LinkScript*     
---*STM32F1*     
---*STM32F4*    
-**2_Package**  --- this dir include many tool packs . you can use it for moblile robotics, fly control etc..    
---*imu*    
---*hf_link*    
---*robot_abstract*  
---*robot_wheel*    
---*motor*  
---*math*   
---*motor*  
---*servo*  
---*etc*    
-**3_OS** --- OpenRE support RTOS(ucosII ucosIII nuttx), GUI(STEMWIN) , FATFS   

##2. Resources and Compilation on Linux 
------------------------------------------------------------------------------
###2.1. Resources   
  * Download the latest code with:      
    * Git:  
    
            cd      
            git clone https://github.com/HANDS-FREE/OpenRE
            
    * run command to install toolchain if you have not config your linux development environment    
      (arm-none-eabi-gcc , opencd , stlink)  : 
        
            cd OpenRE/  
            git clone https://github.com/HANDS-FREE/OpenRE-Tools    
            sh setev.sh 
            
###2.2. A Simple Demo 
    * UCOSIII STM32F4 IOToggle:    
            
            cd OpenRE/0_Project/STM32F4DEMO/Template_UCOSIII/linux  
            make    
            make burn   
 
##3. Usage and examples
------------------------------------------------------------------------------
 Lots of examples are provided in folder 0_Project and you cdan get some manuals in folder Documentation.s
            
##4. Contact    
------------------------------------------------------------------------------
If you have any problem, or you have some suggestions for this code, please contact WenKe Ma by 315261982@qq.com, thank you very much!      