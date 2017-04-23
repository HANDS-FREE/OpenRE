#######################################################system parameters
#
ifeq "$(strip $(BOARD_TYPE))" "control_unit_v1"
####select the usartx for board debug info printf : usart_interface_x,usb_slave  
DEBUG_PRINTF_INTERFACE ?= usart_interface_1
####select the usartxfor pc communications (hf_link) : usart_interface_x,usb_slave 
PC_INTERFACE ?= usart_interface_1
####select the usartx for remote control (hf_link) : usart_interface_x  
RADIO_INTERFACE ?= usart_interface_4
endif

ifeq "$(strip $(BOARD_TYPE))" "control_unit_v2"
####select the usartx for board debug info printf : usart_interface_x,usb_slave  
DEBUG_PRINTF_INTERFACE ?= usart_interface_1
####select the usartxfor pc communications (hf_link) : usart_interface_x,usb_slave 
PC_INTERFACE ?= usart_interface_1
####select the usartx for remote control (hf_link) : usart_interface_x  
RADIO_INTERFACE ?= usart_interface_4
endif

ifeq "$(strip $(BOARD_TYPE))" "control_unit_mini"
####select the usartx for board debug info printf : usart_interface_x,usb_slave  
DEBUG_PRINTF_INTERFACE ?= usart_interface_4
####select the usartxfor pc communications (hf_link) : usart_interface_x,usb_slave 
PC_INTERFACE ?= usart_interface_4
####select the usartx for remote control (hf_link) : usart_interface_x  
RADIO_INTERFACE ?= usart_interface_5
endif

ifeq "$(strip $(ROBOT_SIMULATION_MODE))" "enable"
DDEFS           += -DROBOT_SIMULATION_MODE=1
else
DDEFS           += -DROBOT_SIMULATION_MODE=0
endif

ifeq "$(strip $(DEBUG_PRINTF_INTERFACE))" "usart_interface_1"
DDEFS           += -DDEBUG_PRINTF_INTERFACE=1
endif
ifeq "$(strip $(DEBUG_PRINTF_INTERFACE))" "usart_interface_2"
DDEFS           += -DDEBUG_PRINTF_INTERFACE=2
endif
ifeq "$(strip $(DEBUG_PRINTF_INTERFACE))" "usart_interface_3"
DDEFS           += -DDEBUG_PRINTF_INTERFACE=3
endif
ifeq "$(strip $(DEBUG_PRINTF_INTERFACE))" "usart_interface_4"
DDEFS           += -DDEBUG_PRINTF_INTERFACE=4
endif
ifeq "$(strip $(DEBUG_PRINTF_INTERFACE))" "usart_interface_5"
DDEFS           += -DDEBUG_PRINTF_INTERFACE=5
endif
ifeq "$(strip $(DEBUG_PRINTF_INTERFACE))" "usart_interface_6"
DDEFS           += -DDEBUG_PRINTF_INTERFACE=6
endif
ifeq "$(strip $(DEBUG_PRINTF_INTERFACE))" "usb_slave"
DDEFS           += -DDEBUG_PRINTF_INTERFACE=10
endif

ifeq "$(strip $(PC_INTERFACE))" "usart_interface_1"
DDEFS           += -DPC_INTERFACE=1
endif
ifeq "$(strip $(PC_INTERFACE))" "usart_interface_2"
DDEFS           += -DPC_INTERFACE=2
endif
ifeq "$(strip $(PC_INTERFACE))" "usart_interface_3"
DDEFS           += -DPC_INTERFACE=3
endif
ifeq "$(strip $(PC_INTERFACE))" "usart_interface_4"
DDEFS           += -DPC_INTERFACE=4
endif
ifeq "$(strip $(PC_INTERFACE))" "usart_interface_5"
DDEFS           += -DPC_INTERFACE=5
endif
ifeq "$(strip $(PC_INTERFACE))" "usart_interface_6"
DDEFS           += -DPC_INTERFACE=6
endif
ifeq "$(strip $(PC_INTERFACE))" "usb_slave"
DDEFS           += -DPC_INTERFACE=10
endif

ifeq "$(strip $(RADIO_INTERFACE))" "usart_interface_1"
DDEFS           += -DRADIO_INTERFACE=1
endif
ifeq "$(strip $(RADIO_INTERFACE))" "usart_interface_2"
DDEFS           += -DRADIO_INTERFACE=2
endif
ifeq "$(strip $(RADIO_INTERFACE))" "usart_interface_3"
DDEFS           += -DRADIO_INTERFACE=3
endif
ifeq "$(strip $(RADIO_INTERFACE))" "usart_interface_4"
DDEFS           += -DRADIO_INTERFACE=4
endif
ifeq "$(strip $(RADIO_INTERFACE))" "usart_interface_5"
DDEFS           += -DRADIO_INTERFACE=5
endif
ifeq "$(strip $(RADIO_INTERFACE))" "usart_interface_6"
DDEFS           += -DRADIO_INTERFACE=6
endif

