################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../platform/framework/src/TermColor.cpp \
../platform/framework/src/crc32.cpp \
../platform/framework/src/crc32slow.cpp \
../platform/framework/src/systeminfo.cpp 

C_SRCS += \
../platform/framework/src/sbrk.c 

CPP_DEPS += \
./platform/framework/src/TermColor.d \
./platform/framework/src/crc32.d \
./platform/framework/src/crc32slow.d \
./platform/framework/src/systeminfo.d 

C_DEPS += \
./platform/framework/src/sbrk.d 

OBJS += \
./platform/framework/src/TermColor.o \
./platform/framework/src/crc32.o \
./platform/framework/src/crc32slow.o \
./platform/framework/src/sbrk.o \
./platform/framework/src/systeminfo.o 


# Each subdirectory must supply rules for building sources it contributes
platform/framework/src/%.o: ../platform/framework/src/%.cpp platform/framework/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -std=c++11 -D__USE_LPCOPEN -DDEBUG -D__CODE_RED -DCORE_M3 -DCPP_USE_HEAP -D__LPC17XX__ -I"C:\Users\joklappe\Rhapsody\inc" -I"C:\Users\joklappe\Rhapsody\RXF" -I"C:\Users\joklappe\Rhapsody\GeneratedModel" -I"C:\Users\joklappe\Rhapsody\platform\board\inc" -I"C:\Users\joklappe\Rhapsody\platform\bsp\inc" -I"C:\Users\joklappe\Rhapsody\platform\chip\inc" -I"C:\Users\joklappe\Rhapsody\platform\os\inc" -I"C:\Users\joklappe\Rhapsody\platform\osSupport\inc" -I"C:\Users\joklappe\Rhapsody\platform\framework\inc" -I"C:\Users\joklappe\Rhapsody\platform\os\src\portable\GCC\ARM_CM3" -O0 -fno-common -g3 -Wall -c  -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

platform/framework/src/%.o: ../platform/framework/src/%.c platform/framework/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -DCPP_USE_HEAP -D__LPC17XX__ -I"C:\Users\joklappe\Rhapsody\inc" -I"C:\Users\joklappe\Rhapsody\platform\board\inc" -I"C:\Users\joklappe\Rhapsody\platform\bsp\inc" -I"C:\Users\joklappe\Rhapsody\platform\chip\inc" -I"C:\Users\joklappe\Rhapsody\platform\os\inc" -I"C:\Users\joklappe\Rhapsody\platform\osSupport\inc" -I"C:\Users\joklappe\Rhapsody\platform\framework\inc" -I"C:\Users\joklappe\Rhapsody\platform\os\src\portable\GCC\ARM_CM3" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-platform-2f-framework-2f-src

clean-platform-2f-framework-2f-src:
	-$(RM) ./platform/framework/src/TermColor.d ./platform/framework/src/TermColor.o ./platform/framework/src/crc32.d ./platform/framework/src/crc32.o ./platform/framework/src/crc32slow.d ./platform/framework/src/crc32slow.o ./platform/framework/src/sbrk.d ./platform/framework/src/sbrk.o ./platform/framework/src/systeminfo.d ./platform/framework/src/systeminfo.o

.PHONY: clean-platform-2f-framework-2f-src

