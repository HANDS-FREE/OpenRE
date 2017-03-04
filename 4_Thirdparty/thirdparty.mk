################################################################################  
# thirdparty modules: 
#             
#      
#
################################################################################  

USE_EIGEN   = $(strip $(filter Eigen3 , $(THIRDPARTY_MODULE)))
USE_MATRIX  = $(strip $(filter Matrix , $(THIRDPARTY_MODULE)))
USE_DOBOT	= $(strip $(filter Dobot , $(THIRDPARTY_MODULE)))
INCDIR      += -I$(TOP_PATH)/4_Thirdparty/

ifeq "$(USE_EIGEN)" "Eigen3"

endif

################################################################################  

ifeq "$(USE_MATRIX)" "Matrix"

endif


ifeq "$(USE_DOBOT)" "Dobot"

include $(TOP_PATH)/4_Thirdparty/Dobot/dobot.mk

endif

