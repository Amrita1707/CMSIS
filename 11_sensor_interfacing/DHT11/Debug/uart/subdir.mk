################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../uart/main.c 

OBJS += \
./uart/main.o 

C_DEPS += \
./uart/main.d 


# Each subdirectory must supply rules for building sources it contributes
uart/%.o uart/%.su uart/%.cyclo: ../uart/%.c uart/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"C:/CMSIS/11_sensor_interfacing/DHT11/Core/Include" -I"C:/CMSIS/11_sensor_interfacing/DHT11/Device/ST/STM32F4xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-uart

clean-uart:
	-$(RM) ./uart/main.cyclo ./uart/main.d ./uart/main.o ./uart/main.su

.PHONY: clean-uart

