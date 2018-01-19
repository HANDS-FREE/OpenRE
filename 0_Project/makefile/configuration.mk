####################################################### 
# system parameters , the user can modify the following configurations

ifeq "$(strip $(BOARD_TYPE))" "control_unit_v1"
####select the usartx for board debug info printf : usart_interface_x,usb_slave  
DEBUG_PRINTF_INTERFACE ?= usart_interface_1
#### Tips: this means to map the usart_interface_1 on the board to an debug printf interface

####select the usartxfor pc communications (hf_link) : usart_interface_x,usb_slave 
PC_INTERFACE ?= usart_interface_1
####select the usartx for remote control (hf_link) : usart_interface_x  
RADIO_INTERFACE ?= usart_interface_4
endif

ifeq "$(strip $(BOARD_TYPE))" "control_unit_v2"
####select the usartx for board debug info printf : usart_interface_x,usb_slave  
DEBUG_PRINTF_INTERFACE ?= usart_interface_1
####select the usartxfor pc communications (hf_link) : usart_interface_x,usb_slave 
PC_INTERFACE ?= usart_interface_4
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

####select the motor interface of the control_unit_board for robot motor id : motor1, motor2, motor3, motor4  
ROBOT_MOTOR1 ?= motor_interface_1
#### Tips: this means to map motor_interface_1 on the board to No.1 motor of robot
ROBOT_MOTOR2 ?= motor_interface_2
ROBOT_MOTOR3 ?= motor_interface_3
ROBOT_MOTOR4 ?= motor_interface_4

