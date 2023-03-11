################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../platform/os/src/croutine.c \
../platform/os/src/event_groups.c \
../platform/os/src/list.c \
../platform/os/src/queue.c \
../platform/os/src/stream_buffer.c \
../platform/os/src/tasks.c \
../platform/os/src/timers.c 

C_DEPS += \
./platform/os/src/croutine.d \
./platform/os/src/event_groups.d \
./platform/os/src/list.d \
./platform/os/src/queue.d \
./platform/os/src/stream_buffer.d \
./platform/os/src/tasks.d \
./platform/os/src/timers.d 

OBJS += \
./platform/os/src/croutine.o \
./platform/os/src/event_groups.o \
./platform/os/src/list.o \
./platform/os/src/queue.o \
./platform/os/src/stream_buffer.o \
./platform/os/src/tasks.o \
./platform/os/src/timers.o 


# Each subdirectory must supply rules for building sources it contributes
platform/os/src/%.o: ../platform/os/src/%.c platform/os/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -DCPP_USE_HEAP -D__LPC17XX__ -I"C:\Users\joklappe\Rhapsody\inc" -I"C:\Users\joklappe\Rhapsody\platform\board\inc" -I"C:\Users\joklappe\Rhapsody\platform\bsp\inc" -I"C:\Users\joklappe\Rhapsody\platform\chip\inc" -I"C:\Users\joklappe\Rhapsody\platform\os\inc" -I"C:\Users\joklappe\Rhapsody\platform\osSupport\inc" -I"C:\Users\joklappe\Rhapsody\platform\framework\inc" -I"C:\Users\joklappe\Rhapsody\platform\os\src\portable\GCC\ARM_CM3" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-platform-2f-os-2f-src

clean-platform-2f-os-2f-src:
	-$(RM) ./platform/os/src/croutine.d ./platform/os/src/croutine.o ./platform/os/src/event_groups.d ./platform/os/src/event_groups.o ./platform/os/src/list.d ./platform/os/src/list.o ./platform/os/src/queue.d ./platform/os/src/queue.o ./platform/os/src/stream_buffer.d ./platform/os/src/stream_buffer.o ./platform/os/src/tasks.d ./platform/os/src/tasks.o ./platform/os/src/timers.d ./platform/os/src/timers.o

.PHONY: clean-platform-2f-os-2f-src

