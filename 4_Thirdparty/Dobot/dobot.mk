
DOBOT_PATH		= $(TOP_PATH)/4_Thirdparty/Dobot
INCDIR          +=-I$(DOBOT_PATH)
INCDIR          +=-I$(DOBOT_PATH)/ComPlatform

CXX_SRC         += $(wildcard $(DOBOT_PATH)/*.cpp)
C_SRC           += $(wildcard $(DOBOT_PATH)/*.c)
CXX_SRC         += $(wildcard $(DOBOT_PATH)/ComPlatform/*.cpp)
C_SRC           += $(wildcard $(DOBOT_PATH)/ComPlatform/*.c)



