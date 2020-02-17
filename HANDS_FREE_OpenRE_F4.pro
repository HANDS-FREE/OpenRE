######################################################################
# Automatically generated by qmake (3.0) ?? 1? 19 01:13:01 2016
######################################################################

TEMPLATE = app
TARGET = HNADS-FREE-F4

INCLUDEPATH += . \
                0_Project/examples/handsfree_simple_app/src \
                0_Project/examples/handsfree_robot_test/src \
                0_Project/examples/handsfree_ucosII/src \
                0_Project/examples/handsfree_ucosIII/src \
                0_Project/examples/hwtest/src \
                0_Project/firmware/handsfree_wheel_robot/src \
                0_Project/firmware/handsfree_wheel_robot_ucosIII/src \
                0_Project/include \
                0_Project/include/robot_model/mini \
                0_Project/include/robot_model/stone \
                0_Project/include/robot_model/giraffe \
                0_Project/include/robot_model/template_differential \
                0_Project/include/robot_model/template_omni3 \
                0_Project/include/robot_model/template_mecanum4 \
                1_Processor/Interrupt \
                1_Processor/BoardAbstract \
                1_Processor/STM32F4 \
                1_Processor/STM32F4/BSPLIB \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/CMSIS/ST/STM32F4xx/Include \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/CMSIS/Include \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/inc \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver \
                2_Package \
                2_Package/24cxx \
                2_Package/common \
                2_Package/dsp \
                2_Package/robolink \
                2_Package/iap \
                2_Package/imu \
                2_Package/lcd \
                2_Package/math \
                2_Package/motor \
                2_Package/nrf24l01 \
                2_Package/oled \
                2_Package/robot_abstract \
                2_Package/robot_control \
                2_Package/sbus_ppm \
                2_Package/sd_card \
                2_Package/servo \
                2_Package/tf \
                2_Package/touch_screen \
                2_Package/sensors \
                3_OS \
                3_OS/STM32F4/RTOS/uCOS-II/CONFIG \
                3_OS/STM32F4/RTOS/uCOS-II/CORE \
                3_OS/STM32F4/RTOS/uCOS-II/PORT \
                3_OS/STM32F4/RTOS/uCOS-III/uC-CPU \
                3_OS/STM32F4/RTOS/uCOS-III/uC-CPU/ARM-Cortex-M4/GNU \
                3_OS/STM32F4/RTOS/uCOS-III/uC-LIB \
                3_OS/STM32F4/RTOS/uCOS-III/uC-LIB/Ports/ARM-Cortex-M4/GNU \
                3_OS/STM32F4/RTOS/uCOS-III/uCOS-III/Ports/ARM-Cortex-M4/Generic/GNU  \
                3_OS/STM32F4/RTOS/uCOS-III/uCOS-III/Source \
                3_OS/STM32F4/RTOS/uCOS-III/UCOS-BSP \
                3_OS/STM32F4/RTOS/uCOS-III/uCOS-CONFIG \
                4_Thirdparty \
                4_Thirdparty/Dobot

# Input
HEADERS += 0_Project/examples/handsfree_simple_app/src/main_config.h \
                0_Project/examples/handsfree_imu_test/src/main_config.h \
                0_Project/examples/handsfree_robot_test/src/main_config.h \
                0_Project/examples/handsfree_ucosII/src/main_config.h  \
                0_Project/examples/handsfree_ucosIII/src/main_config.h  \
                0_Project/examples/hwtest/src/main_config.h  \
                0_Project/firmware/handsfree_wheel_robot/src/main_config.h  \
                0_Project/firmware/handsfree_wheel_robot_ucosIII/src/main_config.h \
                0_Project/include/robot_model/mini/robot_model.h \
                0_Project/include/robot_model/stone/robot_model.h \
                0_Project/include/robot_model/giraffe/robot_model.h \
                0_Project/include/robot_model/template_differential/robot_model.h \
                0_Project/include/robot_model/template_omni3/robot_model.h \
                0_Project/include/robot_model/template_mecanum4/robot_model.h \
                1_Processor/Interrupt/stm32f10x_it.h \
                1_Processor/Interrupt/stm32f4xx_it.h \
                1_Processor/BoardAbstract/board_abstract.h \
                1_Processor/BoardAbstract/board.h \
                1_Processor/STM32F4/bsplib.h \
                1_Processor/STM32F4/BSPLIB/adc_dac.h \
                1_Processor/STM32F4/BSPLIB/can.h \
                1_Processor/STM32F4/BSPLIB/delay.h \
                1_Processor/STM32F4/BSPLIB/encoder.h \
                1_Processor/STM32F4/BSPLIB/flash.h \
                1_Processor/STM32F4/BSPLIB/i2c.h \
                1_Processor/STM32F4/BSPLIB/nvic.h \
                1_Processor/STM32F4/BSPLIB/pwm_in.h \
                1_Processor/STM32F4/BSPLIB/pwm_out.h \
                1_Processor/STM32F4/BSPLIB/rtc.h \
                1_Processor/STM32F4/BSPLIB/spi.h \
                1_Processor/STM32F4/BSPLIB/sram.h \
                1_Processor/STM32F4/BSPLIB/timer.h \
                1_Processor/STM32F4/BSPLIB/usart.h \
                1_Processor/STM32F4/BSPLIB/wdg_wkup.h \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/stm32f4xx_conf.h \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/CMSIS/core_cm4.h \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/CMSIS/core_cm4_simd.h \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/CMSIS/core_cmFunc.h \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/CMSIS/core_cmInstr.h \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/CMSIS/stm32f4xx.h \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/CMSIS/system_stm32f4xx.h \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/inc/misc.h \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_adc.h \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_can.h \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_crc.h \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_cryp.h \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_dac.h \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_dbgmcu.h \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_dcmi.h \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_dma.h \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_dma2d.h \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_exti.h \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_flash.h \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_flash_ramfunc.h \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_fmc.h \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_fsmc.h \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_gpio.h \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_hash.h \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_i2c.h \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_iwdg.h \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_ltdc.h \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_pwr.h \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_rcc.h \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_rng.h \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_rtc.h \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_sai.h \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_sdio.h \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_spi.h \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_syscfg.h \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_tim.h \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_usart.h \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_wwdg.h \
                2_Package/package_include.h \
                2_Package/24cxx/24cxx_config.h \
                2_Package/24cxx/24cxx_driver.h \
                2_Package/24cxx/24cxx_iic_bsp.h \
                2_Package/24cxx/24cxx_test.h \
                2_Package/common/queue.h \
                2_Package/dsp/fft_test.h \
                2_Package/robolink/robolink.h \
                2_Package/robolink/platform.h \
                2_Package/robolink/state_machine.h \
                2_Package/iap/hf_HF_Bootloader.h \
                2_Package/imu/imu_config.h \
                2_Package/imu/dev_mpu6050.h \
                2_Package/imu/dev_bmp085.h \
                2_Package/imu/dev_ms611.h  \
                2_Package/imu/dev_hmc5883l.h \
                2_Package/imu/dev_gps.h \
                2_Package/imu/al_fmodel_frame.h \
                2_Package/imu/al_model_ekf.h \
                2_Package/imu/al_model_typicalcorrect.h \
                2_Package/lcd/font.h \
                2_Package/lcd/fsmc_lcd_driver.h \
                2_Package/math/base_math_config.h \
                2_Package/math/base_math_top.h \
                2_Package/math/base_math_func.h \
                2_Package/math/base_math_matrix.h \
                2_Package/math/base_math_trigonometric.h \
                2_Package/math/base_math_quaternion.h \
                2_Package/motor/motor_control.h \
                2_Package/motor/motor_top.h \
                2_Package/motor/virtual_motor.h \
                2_Package/motor/motor_interface.h \
                2_Package/motor/motor_abstract.h \
                2_Package/motor/typical_dc_motor.h \
                2_Package/nrf24l01/nrf24l01_config.h \
                2_Package/nrf24l01/nrf24l01_driver.h \
                2_Package/nrf24l01/nrf24l01_stack.h \
                2_Package/nrf24l01/nrf24l01_test.h \
                2_Package/oled/codetab.h \
                2_Package/oled/oled_iic_driver.h \
                2_Package/oled/oled_spi_driverc.h \
                2_Package/oled/oled_top.h \
                2_Package/robot_abstract/arm_parameters.h \
                2_Package/robot_abstract/chassis_parameters.h \
                2_Package/robot_abstract/head_parameters.h \
                2_Package/robot_abstract/motor_parameters.h \
                2_Package/robot_abstract/robot_abstract.h \
                2_Package/robot_abstract/system_info.h \
                2_Package/robot_abstract/sensor_data.h \
                2_Package/robot_control/robot_control.h \
                2_Package/robot_control/chassis.h \
                2_Package/robot_control/head.h \
                2_Package/robot_control/arm.h \
                2_Package/sbus_ppm/sbus_ppm.h \
                2_Package/sd_card/sdio_config.h \
                2_Package/sd_card/sdio_driver_f1.h \
                2_Package/sd_card/sdio_driver_f4.h \
                2_Package/sd_card/sdio_top.h \
                2_Package/servo/servo_digital.h \
                2_Package/tf/tfrobot.h \
                2_Package/tf/tfdifferential.h \
                2_Package/tf/tfcarlike.h \
                2_Package/tf/tfomni3.h \
                2_Package/tf/tfomni4.h \
                2_Package/tf/tfmecanum4.h \
                2_Package/touch_screen/ctiic.h \
                2_Package/touch_screen/ft5206.h \
                2_Package/touch_screen/gt9147.h \
                2_Package/touch_screen/ott2001a.h \
                2_Package/touch_screen/touch_top.h \
                2_Package/sensors/sensors.h \
                3_OS/os_include.h \
                3_OS/STM32F4/RTOS/uCOS-II/CONFIG/includes.h \
                3_OS/STM32F4/RTOS/uCOS-II/CONFIG/os_cfg.h \
                3_OS/STM32F4/RTOS/uCOS-II/CORE/os_cfg_r.h \
                3_OS/STM32F4/RTOS/uCOS-II/CORE/ucos_ii.h \
                3_OS/STM32F4/RTOS/uCOS-II/PORT/os_cpu.h \
                3_OS/STM32F4/RTOS/uCOS-III/uC-CPU/cpu_core.h \
                3_OS/STM32F4/RTOS/uCOS-III/uC-CPU/cpu_def.h \
                3_OS/STM32F4/RTOS/uCOS-III/uC-LIB/lib_ascii.h \
                3_OS/STM32F4/RTOS/uCOS-III/uC-LIB/lib_def.h \
                3_OS/STM32F4/RTOS/uCOS-III/uC-LIB/lib_math.h \
                3_OS/STM32F4/RTOS/uCOS-III/uC-LIB/lib_mem.h \
                3_OS/STM32F4/RTOS/uCOS-III/uC-LIB/lib_str.h \
                3_OS/STM32F4/RTOS/uCOS-III/UCOS-BSP/bsp.h \
                3_OS/STM32F4/RTOS/uCOS-III/uCOS-CONFIG/app_cfg.h \
                3_OS/STM32F4/RTOS/uCOS-III/uCOS-CONFIG/cpu_cfg.h \
                3_OS/STM32F4/RTOS/uCOS-III/uCOS-CONFIG/includes.h \
                3_OS/STM32F4/RTOS/uCOS-III/uCOS-CONFIG/lib_cfg.h \
                3_OS/STM32F4/RTOS/uCOS-III/uCOS-CONFIG/os_app_hooks.h \
                3_OS/STM32F4/RTOS/uCOS-III/uCOS-CONFIG/os_cfg.h \
                3_OS/STM32F4/RTOS/uCOS-III/uCOS-CONFIG/os_cfg_app.h \
                3_OS/STM32F4/RTOS/uCOS-III/uCOS-III/Source/os.h \
                3_OS/STM32F4/RTOS/uCOS-III/uCOS-III/Source/os_type.h \
                3_OS/STM32F4/RTOS/uCOS-III/uC-CPU/ARM-Cortex-M4/GNU/cpu.h \
                3_OS/STM32F4/RTOS/uCOS-III/uCOS-III/Ports/ARM-Cortex-M4/Generic/GNU/os_cpu.h \
                4_Thirdparty/libs_include.h \

SOURCES += 0_Project/examples/handsfree_simple_app/src/main.cpp \
                0_Project/examples/handsfree_imu_test/src/main.cpp \
                0_Project/examples/handsfree_robot_test/src/main.cpp \
                0_Project/examples/handsfree_ucosII/src/main.cpp  \
                0_Project/examples/handsfree_ucosIII/src/main.cpp \
                0_Project/examples/hwtest/src/main.cpp  \
                0_Project/firmware/handsfree_wheel_robot/src/main.cpp  \
                0_Project/firmware/handsfree_wheel_robot_ucosIII/src/main.cpp  \
                1_Processor/Interrupt/stm32f10x_it.cpp \
                1_Processor/Interrupt/stm32f4xx_it.cpp \
                1_Processor/BoardAbstract/board_abstract.cpp \
                1_Processor/BoardAbstract/openre_board_v1.cpp \
                1_Processor/BoardAbstract/openre_board_v2.cpp \
                1_Processor/BoardAbstract/openre_board_mini.cpp \
                1_Processor/BoardAbstract/alientek_mini.cpp \
                1_Processor/STM32F4/BSPLIB/adc_dac.c \
                1_Processor/STM32F4/BSPLIB/can.c \
                1_Processor/STM32F4/BSPLIB/delay.c \
                1_Processor/STM32F4/BSPLIB/encoder.c \
                1_Processor/STM32F4/BSPLIB/flash.c \
                1_Processor/STM32F4/BSPLIB/i2c.c \
                1_Processor/STM32F4/BSPLIB/nvic.c \
                1_Processor/STM32F4/BSPLIB/pwm_in.c \
                1_Processor/STM32F4/BSPLIB/pwm_out.c \
                1_Processor/STM32F4/BSPLIB/rtc.c \
                1_Processor/STM32F4/BSPLIB/spi.c \
                1_Processor/STM32F4/BSPLIB/sram.c \
                1_Processor/STM32F4/BSPLIB/timer.c \
                1_Processor/STM32F4/BSPLIB/usart.c \
                1_Processor/STM32F4/BSPLIB/wdg_wkup.c \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/CMSIS/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/src/misc.c \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_adc.c \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_can.c \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_crc.c \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp.c \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_aes.c \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_des.c \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_tdes.c \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dac.c \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dbgmcu.c \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dcmi.c \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma.c \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma2d.c \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_exti.c \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash.c \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash_ramfunc.c \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fmc.c \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fsmc.c \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.c \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash.c \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_md5.c \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_sha1.c \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_i2c.c \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_iwdg.c \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_ltdc.c \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_pwr.c \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.c \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rng.c \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rtc.c \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_sai.c \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_sdio.c \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spi.c \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_syscfg.c \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_tim.c \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_usart.c \
                1_Processor/STM32F4/STM32F4-Discovery_FW_V1.1.0/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_wwdg.c \
                2_Package/24cxx/24cxx_driver.cpp \
                2_Package/24cxx/24cxx_iic_bsp.cpp \
                2_Package/24cxx/24cxx_test.cpp \
                2_Package/common/queue.cpp \
                2_Package/common/hfprinf.cpp \
                2_Package/dsp/fft_test.cpp \
                2_Package/robolink/state_machine.cpp \
                2_Package/robolink/robolink.cpp \
                2_Package/iap/hf_HF_Bootloader.c \
                2_Package/imu/dev_mpu6050.cpp \
                2_Package/imu/dev_bmp085.cpp \
                2_Package/imu/dev_ms611.cpp  \
                2_Package/imu/dev_hmc5883l.cpp \
                2_Package/imu/dev_gps.cpp \
                2_Package/imu/al_fmodel_frame.cpp \
                2_Package/imu/al_model_ekf.cpp \
                2_Package/imu/al_model_typicalcorrect.cpp \
                2_Package/imu/imu_top.cpp \
                2_Package/lcd/fsmc_lcd_driver.c \
                2_Package/math/base_math_top.cpp \
                2_Package/math/base_math_func.cpp \
                2_Package/math/base_math_matrix.cpp \
                2_Package/math/base_math_trigonometric.cpp \
                2_Package/math/base_math_quaternion.cpp \
                2_Package/motor/motor_control.cpp \
                2_Package/motor/motor_top.cpp \
                2_Package/motor/typical_dc_motor.cpp \
                2_Package/nrf24l01/nrf24l01_driver.cpp \
                2_Package/nrf24l01/nrf24l01_stack.cpp \
                2_Package/nrf24l01/nrf24l01_test.cpp \
                2_Package/oled/oled_iic_driver.c \
                2_Package/oled/oled_spi_driverc.c \
                2_Package/oled/oled_top.c \
                2_Package/robot_control/robot_control.cpp \
                2_Package/robot_control/tfrobot.cpp \
                2_Package/robot_control/chassis.cpp \
                2_Package/robot_control/head.cpp \
                2_Package/robot_control/arm.cpp \
                2_Package/sbus_ppm/sbus_ppm.cpp \
                2_Package/sd_card/sdio_driver_f1.c \
                2_Package/sd_card/sdio_driver_f4.c \
                2_Package/sd_card/sdio_top.c \
                2_Package/servo/servo_digital.cpp \
                2_Package/touch_screen/ctiic.c \
                2_Package/touch_screen/ft5206.c \
                2_Package/touch_screen/gt9147.c \
                2_Package/touch_screen/ott2001a.c \
                2_Package/touch_screen/touch_top.c \
                2_Package/sensors/sensors.cpp \
                3_OS/STM32F4/RTOS/uCOS-II/CORE/os_core.c \
                3_OS/STM32F4/RTOS/uCOS-II/CORE/os_dbg_r.c \
                3_OS/STM32F4/RTOS/uCOS-II/CORE/os_flag.c \
                3_OS/STM32F4/RTOS/uCOS-II/CORE/os_mbox.c \
                3_OS/STM32F4/RTOS/uCOS-II/CORE/os_mem.c \
                3_OS/STM32F4/RTOS/uCOS-II/CORE/os_mutex.c \
                3_OS/STM32F4/RTOS/uCOS-II/CORE/os_q.c \
                3_OS/STM32F4/RTOS/uCOS-II/CORE/os_sem.c \
                3_OS/STM32F4/RTOS/uCOS-II/CORE/os_task.c \
                3_OS/STM32F4/RTOS/uCOS-II/CORE/os_time.c \
                3_OS/STM32F4/RTOS/uCOS-II/CORE/os_tmr.c \
                3_OS/STM32F4/RTOS/uCOS-II/PORT/os_cpu_c.c \
                3_OS/STM32F4/RTOS/uCOS-II/PORT/os_dbg.c \
                3_OS/STM32F4/RTOS/uCOS-II/PORT/os_dbg_r.c \
                3_OS/STM32F4/RTOS/uCOS-III/uC-CPU/cpu_core.c \
                3_OS/STM32F4/RTOS/uCOS-III/uC-LIB/lib_ascii.c \
                3_OS/STM32F4/RTOS/uCOS-III/uC-LIB/lib_math.c \
                3_OS/STM32F4/RTOS/uCOS-III/uC-LIB/lib_mem.c \
                3_OS/STM32F4/RTOS/uCOS-III/uC-LIB/lib_str.c \
                3_OS/STM32F4/RTOS/uCOS-III/UCOS-BSP/bsp.c \
                3_OS/STM32F4/RTOS/uCOS-III/uCOS-CONFIG/os_app_hooks.c \
                3_OS/STM32F4/RTOS/uCOS-III/uCOS-III/Source/os_cfg_app.c \
                3_OS/STM32F4/RTOS/uCOS-III/uCOS-III/Source/os_core.c \
                3_OS/STM32F4/RTOS/uCOS-III/uCOS-III/Source/os_dbg.c \
                3_OS/STM32F4/RTOS/uCOS-III/uCOS-III/Source/os_flag.c \
                3_OS/STM32F4/RTOS/uCOS-III/uCOS-III/Source/os_int.c \
                3_OS/STM32F4/RTOS/uCOS-III/uCOS-III/Source/os_mem.c \
                3_OS/STM32F4/RTOS/uCOS-III/uCOS-III/Source/os_msg.c \
                3_OS/STM32F4/RTOS/uCOS-III/uCOS-III/Source/os_mutex.c \
                3_OS/STM32F4/RTOS/uCOS-III/uCOS-III/Source/os_pend_multi.c \
                3_OS/STM32F4/RTOS/uCOS-III/uCOS-III/Source/os_prio.c \
                3_OS/STM32F4/RTOS/uCOS-III/uCOS-III/Source/os_q.c \
                3_OS/STM32F4/RTOS/uCOS-III/uCOS-III/Source/os_sem.c \
                3_OS/STM32F4/RTOS/uCOS-III/uCOS-III/Source/os_stat.c \
                3_OS/STM32F4/RTOS/uCOS-III/uCOS-III/Source/os_task.c \
                3_OS/STM32F4/RTOS/uCOS-III/uCOS-III/Source/os_tick.c \
                3_OS/STM32F4/RTOS/uCOS-III/uCOS-III/Source/os_time.c \
                3_OS/STM32F4/RTOS/uCOS-III/uCOS-III/Source/os_tmr.c \
                3_OS/STM32F4/RTOS/uCOS-III/uCOS-III/Source/os_var.c \
                3_OS/STM32F4/RTOS/uCOS-III/uC-CPU/ARM-Cortex-M4/GNU/cpu_c.c \
                3_OS/STM32F4/RTOS/uCOS-III/uCOS-III/Ports/ARM-Cortex-M4/Generic/GNU/os_cpu_c.c

