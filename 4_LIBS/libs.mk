################################################################################  
# LIB modules: 
#             
#      
#
################################################################################  

USE_EIGEN   = $(strip $(filter EIGEN , $(LIB_MODULE)))
USE_MATRIX  = $(strip $(filter MATRIX , $(LIB_MODULE)))

ifeq "$(USE_EIGEN)" "EIGEN"

EIGEN_PATH      = $(TOP_PATH)/4_LIBS/Eigen3
DDEFS           += 
ASM_SRC         += 
C_SRC     	    += 

#Includes
INCDIR          += -I$(EIGEN_PATH)

endif

################################################################################  

ifeq "$(USE_MATRIX)" "MATRIX"

MATRIX_PATH     = $(TOP_PATH)/4_LIBS/Matrix
DDEFS           += 
ASM_SRC         += 
C_SRC     	    += 

#Includes
INCDIR          += -I$(MATRIX_PATH)  

endif


