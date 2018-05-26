######################################define project name, board type, and path

#####ROBOT_MODEL :  
ROBOT_MODEL     ?= null
#####BOARD_TYPE: openre_board_mini openre_board_v2
BOARD_TYPE		?= openre_board_v2
#####project name
PROJECT			=  imu_test_$(ROBOT_MODEL)_$(BOARD_TYPE)
TOP_PATH        =  ../../../..

#############################################################parameters

#####ROBOT_SIMULATION_MODE  : enable disable . enable this mode then you don't need a real robot.
ROBOT_SIMULATION_MODE ?= disable
#####BOOTLOADER  : enable disable
BOOTLOADER_MODE ?= disable

##########################################################################source

CXX_SRC			+= ../src/main.cpp 

#Includes
INCDIR	+= -I. -I../src/ 
	
#########################################################################package

#PAKG: common robot_abstract math imu .....
PAKG        = common math imu
              
#OS_MODULE: UCOSII UCOSIII GUI FAT
OS_MODULE =           

#LIB_MODULE: EIGEN MATRIX  etc
THIRDPARTY_MODULE = Eigen3

###################################################################include rules

include $(TOP_PATH)/0_Project/makefile/compiler.mk


