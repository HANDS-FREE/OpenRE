####################################################### 
# system parameters , the user can modify the following configurations

ifeq "$(strip $(ROBOT_MODEL))" "mini"
BOARD_TYPE      ?= openre_board_mini
endif
ifeq "$(strip $(ROBOT_MODEL))" "stone"
BOARD_TYPE      ?= openre_board_v2
endif
ifeq "$(strip $(ROBOT_MODEL))" "stone_omni3"
BOARD_TYPE      ?= openre_board_v2
endif
ifeq "$(strip $(ROBOT_MODEL))" "giraffe"
BOARD_TYPE      ?= openre_board_v2
endif

ifeq "$(strip $(BOARD_TYPE))" "openre_board_v1"
####select the usartx for board debug info printf : usart_interface_x,usb_slave  
DEBUG_PRINTF_INTERFACE ?= usart_interface_1
#### Tips: this means to map the usart_interface_1 on the board to an debug printf interface

####select the usartxfor pc communications (hf_link) : usart_interface_x,usb_slave 
PC_INTERFACE ?= usart_interface_1
####select the usartx for remote control (hf_link) : usart_interface_x  
RADIO_INTERFACE ?= usart_interface_4
endif

ifeq "$(strip $(BOARD_TYPE))" "openre_board_v2"
####select the usartx for board debug info printf : usart_interface_x,usb_slave  
DEBUG_PRINTF_INTERFACE ?= usart_interface_1
####select the usartxfor pc communications (hf_link) : usart_interface_x,usb_slave 
PC_INTERFACE ?= usart_interface_1
####select the usartx for remote control (hf_link) : usart_interface_x  
RADIO_INTERFACE ?= usart_interface_4
endif

ifeq "$(strip $(BOARD_TYPE))" "openre_board_mini"
####select the usartx for board debug info printf : usart_interface_x,usb_slave  
DEBUG_PRINTF_INTERFACE ?= usart_interface_4
####select the usartxfor pc communications (hf_link) : usart_interface_x,usb_slave 
PC_INTERFACE ?= usart_interface_4
####select the usartx for remote control (hf_link) : usart_interface_x  
RADIO_INTERFACE ?= usart_interface_5
endif

ifeq "$(strip $(BOARD_TYPE))" "mallbot_board_v1"
####select the usartx for board debug info printf : usart_interface_x,usb_slave  
DEBUG_PRINTF_INTERFACE ?= usart_interface_1
####select the usartxfor pc communications (hf_link) : usart_interface_x,usb_slave 
PC_INTERFACE ?= usart_interface_1
####select the usartx for remote control (hf_link) : usart_interface_x  
RADIO_INTERFACE ?= usart_interface_4
endif

####select the motor interface of the openre_board_board for robot motor id : motor1, motor2, motor3, motor4  
ROBOT_MOTOR1 ?= motor_interface_1
#### Tips: this means to map motor_interface_1 on the board to No.1 motor of robot
ROBOT_MOTOR2 ?= motor_interface_2
ROBOT_MOTOR3 ?= motor_interface_3
ROBOT_MOTOR4 ?= motor_interface_4

