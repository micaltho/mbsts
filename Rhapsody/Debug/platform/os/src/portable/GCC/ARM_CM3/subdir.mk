################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../platform/os/src/portable/GCC/ARM_CM3/port.c \
../platform/os/src/portable/GCC/ARM_CM3/runTimeStats.c 

C_DEPS += \
./platform/os/src/portable/GCC/ARM_CM3/port.d \
./platform/os/src/portable/GCC/ARM_CM3/runTimeStats.d 

OBJS += \
./platform/os/src/portable/GCC/ARM_CM3/port.o \
./platform/os/src/portable/GCC/ARM_CM3/runTimeStats.o 


# Each subdirectory must supply rules for building sources it contributes
platform/os/src/portable/GCC/ARM_CM3/%.o: ../platform/os/src/portable/GCC/ARM_CM3/%.c platform/os/src/portable/GCC/ARM_CM3/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -DCPP_USE_HEAP -D__LPC17XX__ -I"C:\Users\joklappe\Rhapsody\inc" -I"C:\Users\joklappe\Rhapsody\platform\board\inc" -I"C:\Users\joklappe\Rhapsody\platform\bsp\inc" -I"C:\Users\joklappe\Rhapsody\platform\chip\inc" -I"C:\Users\joklappe\Rhapsody\platform\os\inc" -I"C:\Users\joklappe\Rhapsody\platform\osSupport\inc" -I"C:\Users\joklappe\Rhapsody\platform\framework\inc" -I"C:\Users\joklappe\Rhapsody\platform\os\src\portable\GCC\ARM_CM3" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-platform-2f-os-2f-src-2f-portable-2f-GCC-2f-ARM_CM3

clean-platform-2f-os-2f-src-2f-portable-2f-GCC-2f-ARM_CM3:
	-$(RM) ./platform/os/src/portable/GCC/ARM_CM3/port.d ./platform/os/src/portable/GCC/ARM_CM3/port.o ./platform/os/src/portable/GCC/ARM_CM3/runTimeStats.d ./platform/os/src/portable/GCC/ARM_CM3/runTimeStats.o

.PHONY: clean-platform-2f-os-2f-src-2f-portable-2f-GCC-2f-ARM_CM3

