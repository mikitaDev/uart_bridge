################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/usr/clk/ckl.c 

OBJS += \
./Drivers/usr/clk/ckl.o 

C_DEPS += \
./Drivers/usr/clk/ckl.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/usr/clk/%.o Drivers/usr/clk/%.su Drivers/usr/clk/%.cyclo: ../Drivers/usr/clk/%.c Drivers/usr/clk/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I/uart_bridge/Drivers/usr -I/uart_bridge/Drivers/usr/gpio -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-usr-2f-clk

clean-Drivers-2f-usr-2f-clk:
	-$(RM) ./Drivers/usr/clk/ckl.cyclo ./Drivers/usr/clk/ckl.d ./Drivers/usr/clk/ckl.o ./Drivers/usr/clk/ckl.su

.PHONY: clean-Drivers-2f-usr-2f-clk

