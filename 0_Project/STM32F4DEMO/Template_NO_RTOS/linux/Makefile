######################################define project name, board type, and path

#ROBOT_MODEL : 2WD 3WD 4WD
ROBOT_MODEL     ?= 2WD
BOARD_TYPE		?= CONTROL_UNIT_V2
#####BOOTLOADER  : ENABLE DISABLE
BOOTLOADER_MODE ?= DISABLE
PROJECT			=  Template_NO_RTOS_$(ROBOT_MODEL)_$(BOARD_TYPE)
#####FPU  : ENABLE DISABLE
FPU_STATE       ?= ENABLE
TOP_PATH        =  ../../../..

##########################################################################source

CXX_SRC			+= ../src/main.cpp ../src/stm32f4xx_it.cpp

#Includes
INCDIR	+= -I. -I../src/ 
	
#########################################################################package
#PAKG: common robot_abstract math imu motor sbus_ppm servo robot_wheel hf_link
PAKG    =
#OS_MODULE: UCOSII UCOSIII GUI FAT
OS_MODULE =         
###################################################################include rules

include $(TOP_PATH)/compiler_config.mk



