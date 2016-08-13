######################################define project name, board type, and path

TOP_PATH        = ../../../..
BOARD_TYPE      ?= CONTROL_UNIT_V1
PROJECT         = stm32f4_Template_NO_RTOS_$(BOARD_TYPE)
#OS_MODULE      = RTOS GUI FATFS

##########################################################################source

CXX_SRC         += ../src/main.cpp ../src/stm32f4xx_it.cpp

#Includes
INCDIR  += -I. -I../src/ 
	
#########################################################################package

PAKG        = common robot_abstract math imu motor sbus_ppm servo \
            robot_wheel hf_link
              
###################################################################include rules

include $(TOP_PATH)/compiler_config.mk



