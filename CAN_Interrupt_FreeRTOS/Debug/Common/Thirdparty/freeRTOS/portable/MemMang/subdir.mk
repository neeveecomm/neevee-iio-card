################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/NEEVEE\ TECHNOLOGIES/STM32CubeIDE/freeRTOS_Projects/Common/Thirdparty/freeRTOS/portable/MemMang/heap_4.c 

OBJS += \
./Common/Thirdparty/freeRTOS/portable/MemMang/heap_4.o 

C_DEPS += \
./Common/Thirdparty/freeRTOS/portable/MemMang/heap_4.d 


# Each subdirectory must supply rules for building sources it contributes
Common/Thirdparty/freeRTOS/portable/MemMang/heap_4.o: C:/Users/NEEVEE\ TECHNOLOGIES/STM32CubeIDE/freeRTOS_Projects/Common/Thirdparty/freeRTOS/portable/MemMang/heap_4.c Common/Thirdparty/freeRTOS/portable/MemMang/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/NEEVEE TECHNOLOGIES/STM32CubeIDE/freeRTOS_Projects/Common/Thirdparty/freeRTOS/include" -I"C:/Users/NEEVEE TECHNOLOGIES/STM32CubeIDE/freeRTOS_Projects/Common/Thirdparty/freeRTOS/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Common-2f-Thirdparty-2f-freeRTOS-2f-portable-2f-MemMang

clean-Common-2f-Thirdparty-2f-freeRTOS-2f-portable-2f-MemMang:
	-$(RM) ./Common/Thirdparty/freeRTOS/portable/MemMang/heap_4.cyclo ./Common/Thirdparty/freeRTOS/portable/MemMang/heap_4.d ./Common/Thirdparty/freeRTOS/portable/MemMang/heap_4.o ./Common/Thirdparty/freeRTOS/portable/MemMang/heap_4.su

.PHONY: clean-Common-2f-Thirdparty-2f-freeRTOS-2f-portable-2f-MemMang

