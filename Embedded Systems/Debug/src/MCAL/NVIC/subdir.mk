################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/MCAL/NVIC/NVIC_prg.c 

C_DEPS += \
./src/MCAL/NVIC/NVIC_prg.d 

OBJS += \
./src/MCAL/NVIC/NVIC_prg.o 


# Each subdirectory must supply rules for building sources it contributes
src/MCAL/NVIC/%.o: ../src/MCAL/NVIC/%.c src/MCAL/NVIC/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F401xC -DUSE_HAL_DRIVER -DHSE_VALUE=25000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-MCAL-2f-NVIC

clean-src-2f-MCAL-2f-NVIC:
	-$(RM) ./src/MCAL/NVIC/NVIC_prg.d ./src/MCAL/NVIC/NVIC_prg.o

.PHONY: clean-src-2f-MCAL-2f-NVIC

