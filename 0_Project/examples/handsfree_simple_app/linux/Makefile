######################################define project name, board type, and path

#####ROBOT_MODEL : jilong jilong_omni3 stone    
ROBOT_MODEL     ?= stone
#####BOARD_TYPE: control_unit_mini control_unit_v1 control_unit_v2
BOARD_TYPE		?= control_unit_v2
#####project name
PROJECT			=  simple_app_$(ROBOT_MODEL)_$(BOARD_TYPE)
TOP_PATH        =  ../../../..

#############################################################parameters

#####ROBOT_SIMULATION_MODE  : enable disable . enable this mode then you don't need a real robot.
ROBOT_SIMULATION_MODE ?= disable
#####BOOTLOADER  : enable disable
BOOTLOADER_MODE ?= disable
####select the usartx for board debug info printf : usart_interface_x,usb_slave  x= 1~3
DEBUG_PRINTF_INTERFACE ?= usart_interface_1
####select the usartxfor pc communications (hf_link) : usart_interface_x,usb_slave  x= 1~6
PC_INTERFACE ?= usart_interface_1
####select the usartx for remote control (hf_link) : usart_interface_x  x= 1~6
RADIO_INTERFACE ?= usart_interface_4

##########################################################################source

CXX_SRC			+= ../src/main.cpp 

#Includes
INCDIR	+= -I. -I../src/ 
	
#########################################################################package

#PAKG: common robot_abstract math imu .....
PAKG        = common 
              
#OS_MODULE: UCOSII UCOSIII GUI FAT
OS_MODULE =           

#LIB_MODULE: EIGEN MATRIX  etc
LIB_MODULE =     

###################################################################include rules

include $(TOP_PATH)/compiler_config.mk


