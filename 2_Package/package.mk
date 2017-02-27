################################################################################  
# package modules: 
#            
#           
#
################################################################################  

PACKAGE_PATH 	= $(TOP_PATH)/2_Package
CXX_SRC         += $(foreach n,$(PAKG),$(wildcard $(PACKAGE_PATH)/$(n)/*.cpp))
C_SRC           += $(foreach n,$(PAKG),$(wildcard $(PACKAGE_PATH)/$(n)/*.c))
INCDIR          += $(foreach n,$(PAKG),-I$(PACKAGE_PATH)/$(n))
INCDIR          +=-I$(TOP_PATH)/2_Package/

