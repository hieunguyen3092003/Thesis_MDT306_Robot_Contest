################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/adc.c \
../Core/Src/button.c \
../Core/Src/buzzer.c \
../Core/Src/display.c \
../Core/Src/dma.c \
../Core/Src/encoder.c \
../Core/Src/follow_line.c \
../Core/Src/gamepad.c \
../Core/Src/gpio.c \
../Core/Src/i2c.c \
../Core/Src/line_sensor.c \
../Core/Src/main.c \
../Core/Src/module_mke_m15.c \
../Core/Src/motor.c \
../Core/Src/pid.c \
../Core/Src/robot_firmware.c \
../Core/Src/servo.c \
../Core/Src/software_timer.c \
../Core/Src/spi.c \
../Core/Src/step_motor.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/switch.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c \
../Core/Src/tim.c \
../Core/Src/uart.c \
../Core/Src/usart.c \
../Core/Src/utils.c 

OBJS += \
./Core/Src/adc.o \
./Core/Src/button.o \
./Core/Src/buzzer.o \
./Core/Src/display.o \
./Core/Src/dma.o \
./Core/Src/encoder.o \
./Core/Src/follow_line.o \
./Core/Src/gamepad.o \
./Core/Src/gpio.o \
./Core/Src/i2c.o \
./Core/Src/line_sensor.o \
./Core/Src/main.o \
./Core/Src/module_mke_m15.o \
./Core/Src/motor.o \
./Core/Src/pid.o \
./Core/Src/robot_firmware.o \
./Core/Src/servo.o \
./Core/Src/software_timer.o \
./Core/Src/spi.o \
./Core/Src/step_motor.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/switch.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o \
./Core/Src/tim.o \
./Core/Src/uart.o \
./Core/Src/usart.o \
./Core/Src/utils.o 

C_DEPS += \
./Core/Src/adc.d \
./Core/Src/button.d \
./Core/Src/buzzer.d \
./Core/Src/display.d \
./Core/Src/dma.d \
./Core/Src/encoder.d \
./Core/Src/follow_line.d \
./Core/Src/gamepad.d \
./Core/Src/gpio.d \
./Core/Src/i2c.d \
./Core/Src/line_sensor.d \
./Core/Src/main.d \
./Core/Src/module_mke_m15.d \
./Core/Src/motor.d \
./Core/Src/pid.d \
./Core/Src/robot_firmware.d \
./Core/Src/servo.d \
./Core/Src/software_timer.d \
./Core/Src/spi.d \
./Core/Src/step_motor.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/switch.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d \
./Core/Src/tim.d \
./Core/Src/uart.d \
./Core/Src/usart.d \
./Core/Src/utils.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/adc.cyclo ./Core/Src/adc.d ./Core/Src/adc.o ./Core/Src/adc.su ./Core/Src/button.cyclo ./Core/Src/button.d ./Core/Src/button.o ./Core/Src/button.su ./Core/Src/buzzer.cyclo ./Core/Src/buzzer.d ./Core/Src/buzzer.o ./Core/Src/buzzer.su ./Core/Src/display.cyclo ./Core/Src/display.d ./Core/Src/display.o ./Core/Src/display.su ./Core/Src/dma.cyclo ./Core/Src/dma.d ./Core/Src/dma.o ./Core/Src/dma.su ./Core/Src/encoder.cyclo ./Core/Src/encoder.d ./Core/Src/encoder.o ./Core/Src/encoder.su ./Core/Src/follow_line.cyclo ./Core/Src/follow_line.d ./Core/Src/follow_line.o ./Core/Src/follow_line.su ./Core/Src/gamepad.cyclo ./Core/Src/gamepad.d ./Core/Src/gamepad.o ./Core/Src/gamepad.su ./Core/Src/gpio.cyclo ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/i2c.cyclo ./Core/Src/i2c.d ./Core/Src/i2c.o ./Core/Src/i2c.su ./Core/Src/line_sensor.cyclo ./Core/Src/line_sensor.d ./Core/Src/line_sensor.o ./Core/Src/line_sensor.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/module_mke_m15.cyclo ./Core/Src/module_mke_m15.d ./Core/Src/module_mke_m15.o ./Core/Src/module_mke_m15.su ./Core/Src/motor.cyclo ./Core/Src/motor.d ./Core/Src/motor.o ./Core/Src/motor.su ./Core/Src/pid.cyclo ./Core/Src/pid.d ./Core/Src/pid.o ./Core/Src/pid.su ./Core/Src/robot_firmware.cyclo ./Core/Src/robot_firmware.d ./Core/Src/robot_firmware.o ./Core/Src/robot_firmware.su ./Core/Src/servo.cyclo ./Core/Src/servo.d ./Core/Src/servo.o ./Core/Src/servo.su ./Core/Src/software_timer.cyclo ./Core/Src/software_timer.d ./Core/Src/software_timer.o ./Core/Src/software_timer.su ./Core/Src/spi.cyclo ./Core/Src/spi.d ./Core/Src/spi.o ./Core/Src/spi.su ./Core/Src/step_motor.cyclo ./Core/Src/step_motor.d ./Core/Src/step_motor.o ./Core/Src/step_motor.su ./Core/Src/stm32f1xx_hal_msp.cyclo ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_it.cyclo ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/switch.cyclo ./Core/Src/switch.d ./Core/Src/switch.o ./Core/Src/switch.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.cyclo ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su ./Core/Src/tim.cyclo ./Core/Src/tim.d ./Core/Src/tim.o ./Core/Src/tim.su ./Core/Src/uart.cyclo ./Core/Src/uart.d ./Core/Src/uart.o ./Core/Src/uart.su ./Core/Src/usart.cyclo ./Core/Src/usart.d ./Core/Src/usart.o ./Core/Src/usart.su ./Core/Src/utils.cyclo ./Core/Src/utils.d ./Core/Src/utils.o ./Core/Src/utils.su

.PHONY: clean-Core-2f-Src

