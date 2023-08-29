################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/NEEVEE\ TECHNOLOGIES/STM32CubeIDE/freeRTOS_Projects/Common/Thirdparty/freeRTOS/croutine.c \
C:/Users/NEEVEE\ TECHNOLOGIES/STM32CubeIDE/freeRTOS_Projects/Common/Thirdparty/freeRTOS/event_groups.c \
C:/Users/NEEVEE\ TECHNOLOGIES/STM32CubeIDE/freeRTOS_Projects/Common/Thirdparty/freeRTOS/list.c \
C:/Users/NEEVEE\ TECHNOLOGIES/STM32CubeIDE/freeRTOS_Projects/Common/Thirdparty/freeRTOS/queue.c \
C:/Users/NEEVEE\ TECHNOLOGIES/STM32CubeIDE/freeRTOS_Projects/Common/Thirdparty/freeRTOS/stream_buffer.c \
C:/Users/NEEVEE\ TECHNOLOGIES/STM32CubeIDE/freeRTOS_Projects/Common/Thirdparty/freeRTOS/tasks.c \
C:/Users/NEEVEE\ TECHNOLOGIES/STM32CubeIDE/freeRTOS_Projects/Common/Thirdparty/freeRTOS/timers.c 

OBJS += \
./Common/Thirdparty/freeRTOS/croutine.o \
./Common/Thirdparty/freeRTOS/event_groups.o \
./Common/Thirdparty/freeRTOS/list.o \
./Common/Thirdparty/freeRTOS/queue.o \
./Common/Thirdparty/freeRTOS/stream_buffer.o \
./Common/Thirdparty/freeRTOS/tasks.o \
./Common/Thirdparty/freeRTOS/timers.o 

C_DEPS += \
./Common/Thirdparty/freeRTOS/croutine.d \
./Common/Thirdparty/freeRTOS/event_groups.d \
./Common/Thirdparty/freeRTOS/list.d \
./Common/Thirdparty/freeRTOS/queue.d \
./Common/Thirdparty/freeRTOS/stream_buffer.d \
./Common/Thirdparty/freeRTOS/tasks.d \
./Common/Thirdparty/freeRTOS/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Common/Thirdparty/freeRTOS/croutine.o: C:/Users/NEEVEE\ TECHNOLOGIES/STM32CubeIDE/freeRTOS_Projects/Common/Thirdparty/freeRTOS/croutine.c Common/Thirdparty/freeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/NEEVEE TECHNOLOGIES/STM32CubeIDE/freeRTOS_Projects/Common/Thirdparty/freeRTOS/include" -I"C:/Users/NEEVEE TECHNOLOGIES/STM32CubeIDE/freeRTOS_Projects/Common/Thirdparty/freeRTOS/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Common/Thirdparty/freeRTOS/event_groups.o: C:/Users/NEEVEE\ TECHNOLOGIES/STM32CubeIDE/freeRTOS_Projects/Common/Thirdparty/freeRTOS/event_groups.c Common/Thirdparty/freeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/NEEVEE TECHNOLOGIES/STM32CubeIDE/freeRTOS_Projects/Common/Thirdparty/freeRTOS/include" -I"C:/Users/NEEVEE TECHNOLOGIES/STM32CubeIDE/freeRTOS_Projects/Common/Thirdparty/freeRTOS/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Common/Thirdparty/freeRTOS/list.o: C:/Users/NEEVEE\ TECHNOLOGIES/STM32CubeIDE/freeRTOS_Projects/Common/Thirdparty/freeRTOS/list.c Common/Thirdparty/freeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/NEEVEE TECHNOLOGIES/STM32CubeIDE/freeRTOS_Projects/Common/Thirdparty/freeRTOS/include" -I"C:/Users/NEEVEE TECHNOLOGIES/STM32CubeIDE/freeRTOS_Projects/Common/Thirdparty/freeRTOS/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Common/Thirdparty/freeRTOS/queue.o: C:/Users/NEEVEE\ TECHNOLOGIES/STM32CubeIDE/freeRTOS_Projects/Common/Thirdparty/freeRTOS/queue.c Common/Thirdparty/freeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/NEEVEE TECHNOLOGIES/STM32CubeIDE/freeRTOS_Projects/Common/Thirdparty/freeRTOS/include" -I"C:/Users/NEEVEE TECHNOLOGIES/STM32CubeIDE/freeRTOS_Projects/Common/Thirdparty/freeRTOS/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Common/Thirdparty/freeRTOS/stream_buffer.o: C:/Users/NEEVEE\ TECHNOLOGIES/STM32CubeIDE/freeRTOS_Projects/Common/Thirdparty/freeRTOS/stream_buffer.c Common/Thirdparty/freeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/NEEVEE TECHNOLOGIES/STM32CubeIDE/freeRTOS_Projects/Common/Thirdparty/freeRTOS/include" -I"C:/Users/NEEVEE TECHNOLOGIES/STM32CubeIDE/freeRTOS_Projects/Common/Thirdparty/freeRTOS/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Common/Thirdparty/freeRTOS/tasks.o: C:/Users/NEEVEE\ TECHNOLOGIES/STM32CubeIDE/freeRTOS_Projects/Common/Thirdparty/freeRTOS/tasks.c Common/Thirdparty/freeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/NEEVEE TECHNOLOGIES/STM32CubeIDE/freeRTOS_Projects/Common/Thirdparty/freeRTOS/include" -I"C:/Users/NEEVEE TECHNOLOGIES/STM32CubeIDE/freeRTOS_Projects/Common/Thirdparty/freeRTOS/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Common/Thirdparty/freeRTOS/timers.o: C:/Users/NEEVEE\ TECHNOLOGIES/STM32CubeIDE/freeRTOS_Projects/Common/Thirdparty/freeRTOS/timers.c Common/Thirdparty/freeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/NEEVEE TECHNOLOGIES/STM32CubeIDE/freeRTOS_Projects/Common/Thirdparty/freeRTOS/include" -I"C:/Users/NEEVEE TECHNOLOGIES/STM32CubeIDE/freeRTOS_Projects/Common/Thirdparty/freeRTOS/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Common-2f-Thirdparty-2f-freeRTOS

clean-Common-2f-Thirdparty-2f-freeRTOS:
	-$(RM) ./Common/Thirdparty/freeRTOS/croutine.cyclo ./Common/Thirdparty/freeRTOS/croutine.d ./Common/Thirdparty/freeRTOS/croutine.o ./Common/Thirdparty/freeRTOS/croutine.su ./Common/Thirdparty/freeRTOS/event_groups.cyclo ./Common/Thirdparty/freeRTOS/event_groups.d ./Common/Thirdparty/freeRTOS/event_groups.o ./Common/Thirdparty/freeRTOS/event_groups.su ./Common/Thirdparty/freeRTOS/list.cyclo ./Common/Thirdparty/freeRTOS/list.d ./Common/Thirdparty/freeRTOS/list.o ./Common/Thirdparty/freeRTOS/list.su ./Common/Thirdparty/freeRTOS/queue.cyclo ./Common/Thirdparty/freeRTOS/queue.d ./Common/Thirdparty/freeRTOS/queue.o ./Common/Thirdparty/freeRTOS/queue.su ./Common/Thirdparty/freeRTOS/stream_buffer.cyclo ./Common/Thirdparty/freeRTOS/stream_buffer.d ./Common/Thirdparty/freeRTOS/stream_buffer.o ./Common/Thirdparty/freeRTOS/stream_buffer.su ./Common/Thirdparty/freeRTOS/tasks.cyclo ./Common/Thirdparty/freeRTOS/tasks.d ./Common/Thirdparty/freeRTOS/tasks.o ./Common/Thirdparty/freeRTOS/tasks.su ./Common/Thirdparty/freeRTOS/timers.cyclo ./Common/Thirdparty/freeRTOS/timers.d ./Common/Thirdparty/freeRTOS/timers.o ./Common/Thirdparty/freeRTOS/timers.su

.PHONY: clean-Common-2f-Thirdparty-2f-freeRTOS

