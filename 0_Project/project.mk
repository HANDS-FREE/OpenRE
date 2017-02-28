# Project
ROBOT_MODEL_PATH = $(TOP_PATH)/0_Project/include/robot_model
INCDIR    	+= -I$(TOP_PATH)/0_Project/

ifeq "$(strip $(DEBUG_PRINTF_INTERFACE))" "null"

else
INCDIR    	+= -I$(ROBOT_MODEL_PATH)/$(ROBOT_MODEL)/
endif

