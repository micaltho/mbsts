################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../platform/osSupport/src/Mutex.cpp \
../platform/osSupport/src/PeriodicTaskBase.cpp \
../platform/osSupport/src/PostOffice.cpp \
../platform/osSupport/src/Semaphore.cpp \
../platform/osSupport/src/TaskBase.cpp \
../platform/osSupport/src/TimerBase.cpp 

C_SRCS += \
../platform/osSupport/src/cmsis_os.c 

CPP_DEPS += \
./platform/osSupport/src/Mutex.d \
./platform/osSupport/src/PeriodicTaskBase.d \
./platform/osSupport/src/PostOffice.d \
./platform/osSupport/src/Semaphore.d \
./platform/osSupport/src/TaskBase.d \
./platform/osSupport/src/TimerBase.d 

C_DEPS += \
./platform/osSupport/src/cmsis_os.d 

OBJS += \
./platform/osSupport/src/Mutex.o \
./platform/osSupport/src/PeriodicTaskBase.o \
./platform/osSupport/src/PostOffice.o \
./platform/osSupport/src/Semaphore.o \
./platform/osSupport/src/TaskBase.o \
./platform/osSupport/src/TimerBase.o \
./platform/osSupport/src/cmsis_os.o 


# Each subdirectory must supply rules for building sources it contributes
platform/osSupport/src/%.o: ../platform/osSupport/src/%.cpp platform/osSupport/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -std=c++11 -D__USE_LPCOPEN -DDEBUG -D__CODE_RED -DCORE_M3 -DCPP_USE_HEAP -D__LPC17XX__ -I"C:\Users\joklappe\Rhapsody\inc" -I"C:\Users\joklappe\Rhapsody\RXF" -I"C:\Users\joklappe\Rhapsody\GeneratedModel" -I"C:\Users\joklappe\Rhapsody\platform\board\inc" -I"C:\Users\joklappe\Rhapsody\platform\bsp\inc" -I"C:\Users\joklappe\Rhapsody\platform\chip\inc" -I"C:\Users\joklappe\Rhapsody\platform\os\inc" -I"C:\Users\joklappe\Rhapsody\platform\osSupport\inc" -I"C:\Users\joklappe\Rhapsody\platform\framework\inc" -I"C:\Users\joklappe\Rhapsody\platform\os\src\portable\GCC\ARM_CM3" -O0 -fno-common -g3 -Wall -c  -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

platform/osSupport/src/%.o: ../platform/osSupport/src/%.c platform/osSupport/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -DCPP_USE_HEAP -D__LPC17XX__ -I"C:\Users\joklappe\Rhapsody\inc" -I"C:\Users\joklappe\Rhapsody\platform\board\inc" -I"C:\Users\joklappe\Rhapsody\platform\bsp\inc" -I"C:\Users\joklappe\Rhapsody\platform\chip\inc" -I"C:\Users\joklappe\Rhapsody\platform\os\inc" -I"C:\Users\joklappe\Rhapsody\platform\osSupport\inc" -I"C:\Users\joklappe\Rhapsody\platform\framework\inc" -I"C:\Users\joklappe\Rhapsody\platform\os\src\portable\GCC\ARM_CM3" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-platform-2f-osSupport-2f-src

clean-platform-2f-osSupport-2f-src:
	-$(RM) ./platform/osSupport/src/Mutex.d ./platform/osSupport/src/Mutex.o ./platform/osSupport/src/PeriodicTaskBase.d ./platform/osSupport/src/PeriodicTaskBase.o ./platform/osSupport/src/PostOffice.d ./platform/osSupport/src/PostOffice.o ./platform/osSupport/src/Semaphore.d ./platform/osSupport/src/Semaphore.o ./platform/osSupport/src/TaskBase.d ./platform/osSupport/src/TaskBase.o ./platform/osSupport/src/TimerBase.d ./platform/osSupport/src/TimerBase.o ./platform/osSupport/src/cmsis_os.d ./platform/osSupport/src/cmsis_os.o

.PHONY: clean-platform-2f-osSupport-2f-src

