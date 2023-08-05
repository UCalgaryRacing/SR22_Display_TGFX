################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/User/src/gps.c \
../Application/User/src/rpm.c 

C_DEPS += \
./Application/User/src/gps.d \
./Application/User/src/rpm.d 

OBJS += \
./Application/User/src/gps.o \
./Application/User/src/rpm.o 


# Each subdirectory must supply rules for building sources it contributes
Application/User/src/%.o Application/User/src/%.su Application/User/src/%.cyclo: ../Application/User/src/%.c Application/User/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=16 -DSTM32F750xx -DDEBUG -c -I../../Core/Inc -I../../STM32CubeIDE/Application/User/inc -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/STM32F7508-Discovery -I../../TouchGFX/target -I../../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../../Drivers/STM32F7xx_HAL_Driver/Inc -I../../TouchGFX/App -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../../TouchGFX/target/generated -I../../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../../Drivers/BSP/Components/Common -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../TouchGFX/generated/videos/include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-User-2f-src

clean-Application-2f-User-2f-src:
	-$(RM) ./Application/User/src/gps.cyclo ./Application/User/src/gps.d ./Application/User/src/gps.o ./Application/User/src/gps.su ./Application/User/src/rpm.cyclo ./Application/User/src/rpm.d ./Application/User/src/rpm.o ./Application/User/src/rpm.su

.PHONY: clean-Application-2f-User-2f-src

