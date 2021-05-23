################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32.s 

OBJS += \
./startup/startup_stm32.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -I"C:/Users/Oleg/workspace/stm32f103rbt6_pwm/HAL_Driver/Inc/Legacy" -I"C:/Users/Oleg/workspace/stm32f103rbt6_pwm/inc" -I"C:/Users/Oleg/workspace/stm32f103rbt6_pwm/CMSIS/device" -I"C:/Users/Oleg/workspace/stm32f103rbt6_pwm/CMSIS/core" -I"C:/Users/Oleg/workspace/stm32f103rbt6_pwm/HAL_Driver/Inc" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


