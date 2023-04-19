################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/lib/bmp581.c \
../Core/Src/lib/led_strip.c \
../Core/Src/lib/ws2813b_controller.c 

OBJS += \
./Core/Src/lib/bmp581.o \
./Core/Src/lib/led_strip.o \
./Core/Src/lib/ws2813b_controller.o 

C_DEPS += \
./Core/Src/lib/bmp581.d \
./Core/Src/lib/led_strip.d \
./Core/Src/lib/ws2813b_controller.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/lib/%.o Core/Src/lib/%.su Core/Src/lib/%.cyclo: ../Core/Src/lib/%.c Core/Src/lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-lib

clean-Core-2f-Src-2f-lib:
	-$(RM) ./Core/Src/lib/bmp581.cyclo ./Core/Src/lib/bmp581.d ./Core/Src/lib/bmp581.o ./Core/Src/lib/bmp581.su ./Core/Src/lib/led_strip.cyclo ./Core/Src/lib/led_strip.d ./Core/Src/lib/led_strip.o ./Core/Src/lib/led_strip.su ./Core/Src/lib/ws2813b_controller.cyclo ./Core/Src/lib/ws2813b_controller.d ./Core/Src/lib/ws2813b_controller.o ./Core/Src/lib/ws2813b_controller.su

.PHONY: clean-Core-2f-Src-2f-lib

