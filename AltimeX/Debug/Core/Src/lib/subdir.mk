################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/lib/LPS22HB.cpp \
../Core/Src/lib/altimex.cpp \
../Core/Src/lib/altimex_eeprom.cpp \
../Core/Src/lib/altimex_led_controller.cpp \
../Core/Src/lib/altimex_state_controller.cpp \
../Core/Src/lib/eeprom_storage.cpp \
../Core/Src/lib/led_strip.cpp \
../Core/Src/lib/usb.cpp \
../Core/Src/lib/ws2813b_controller.cpp 

OBJS += \
./Core/Src/lib/LPS22HB.o \
./Core/Src/lib/altimex.o \
./Core/Src/lib/altimex_eeprom.o \
./Core/Src/lib/altimex_led_controller.o \
./Core/Src/lib/altimex_state_controller.o \
./Core/Src/lib/eeprom_storage.o \
./Core/Src/lib/led_strip.o \
./Core/Src/lib/usb.o \
./Core/Src/lib/ws2813b_controller.o 

CPP_DEPS += \
./Core/Src/lib/LPS22HB.d \
./Core/Src/lib/altimex.d \
./Core/Src/lib/altimex_eeprom.d \
./Core/Src/lib/altimex_led_controller.d \
./Core/Src/lib/altimex_state_controller.d \
./Core/Src/lib/eeprom_storage.d \
./Core/Src/lib/led_strip.d \
./Core/Src/lib/usb.d \
./Core/Src/lib/ws2813b_controller.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/lib/%.o Core/Src/lib/%.su Core/Src/lib/%.cyclo: ../Core/Src/lib/%.cpp Core/Src/lib/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-lib

clean-Core-2f-Src-2f-lib:
	-$(RM) ./Core/Src/lib/LPS22HB.cyclo ./Core/Src/lib/LPS22HB.d ./Core/Src/lib/LPS22HB.o ./Core/Src/lib/LPS22HB.su ./Core/Src/lib/altimex.cyclo ./Core/Src/lib/altimex.d ./Core/Src/lib/altimex.o ./Core/Src/lib/altimex.su ./Core/Src/lib/altimex_eeprom.cyclo ./Core/Src/lib/altimex_eeprom.d ./Core/Src/lib/altimex_eeprom.o ./Core/Src/lib/altimex_eeprom.su ./Core/Src/lib/altimex_led_controller.cyclo ./Core/Src/lib/altimex_led_controller.d ./Core/Src/lib/altimex_led_controller.o ./Core/Src/lib/altimex_led_controller.su ./Core/Src/lib/altimex_state_controller.cyclo ./Core/Src/lib/altimex_state_controller.d ./Core/Src/lib/altimex_state_controller.o ./Core/Src/lib/altimex_state_controller.su ./Core/Src/lib/eeprom_storage.cyclo ./Core/Src/lib/eeprom_storage.d ./Core/Src/lib/eeprom_storage.o ./Core/Src/lib/eeprom_storage.su ./Core/Src/lib/led_strip.cyclo ./Core/Src/lib/led_strip.d ./Core/Src/lib/led_strip.o ./Core/Src/lib/led_strip.su ./Core/Src/lib/usb.cyclo ./Core/Src/lib/usb.d ./Core/Src/lib/usb.o ./Core/Src/lib/usb.su ./Core/Src/lib/ws2813b_controller.cyclo ./Core/Src/lib/ws2813b_controller.d ./Core/Src/lib/ws2813b_controller.o ./Core/Src/lib/ws2813b_controller.su

.PHONY: clean-Core-2f-Src-2f-lib

