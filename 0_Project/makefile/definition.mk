####################################################### 
# add definition , the user does not need to change the following definitions

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

ifeq "$(strip $(ROBOT_MOTOR1))" "motor_interface_1"
DDEFS           += -DROBOT_MOTOR1=1
endif
ifeq "$(strip $(ROBOT_MOTOR1))" "motor_interface_2"
DDEFS           += -DROBOT_MOTOR1=2
endif
ifeq "$(strip $(ROBOT_MOTOR1))" "motor_interface_3"
DDEFS           += -DROBOT_MOTOR1=3
endif
ifeq "$(strip $(ROBOT_MOTOR1))" "motor_interface_4"
DDEFS           += -DROBOT_MOTOR1=4
endif

ifeq "$(strip $(ROBOT_MOTOR2))" "motor_interface_1"
DDEFS           += -DROBOT_MOTOR2=1
endif
ifeq "$(strip $(ROBOT_MOTOR2))" "motor_interface_2"
DDEFS           += -DROBOT_MOTOR2=2
endif
ifeq "$(strip $(ROBOT_MOTOR2))" "motor_interface_3"
DDEFS           += -DROBOT_MOTOR2=3
endif
ifeq "$(strip $(ROBOT_MOTOR2))" "motor_interface_4"
DDEFS           += -DROBOT_MOTOR2=4
endif

ifeq "$(strip $(ROBOT_MOTOR3))" "motor_interface_1"
DDEFS           += -DROBOT_MOTOR3=1
endif
ifeq "$(strip $(ROBOT_MOTOR3))" "motor_interface_2"
DDEFS           += -DROBOT_MOTOR3=2
endif
ifeq "$(strip $(ROBOT_MOTOR3))" "motor_interface_3"
DDEFS           += -DROBOT_MOTOR3=3
endif
ifeq "$(strip $(ROBOT_MOTOR3))" "motor_interface_4"
DDEFS           += -DROBOT_MOTOR3=4
endif

ifeq "$(strip $(ROBOT_MOTOR4))" "motor_interface_1"
DDEFS           += -DROBOT_MOTOR4=1
endif
ifeq "$(strip $(ROBOT_MOTOR4))" "motor_interface_2"
DDEFS           += -DROBOT_MOTOR4=2
endif
ifeq "$(strip $(ROBOT_MOTOR4))" "motor_interface_3"
DDEFS           += -DROBOT_MOTOR4=3
endif
ifeq "$(strip $(ROBOT_MOTOR4))" "motor_interface_4"
DDEFS           += -DROBOT_MOTOR4=4
endif

