################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../RXF/RXF_Active.cpp \
../RXF/RXF_ErrorHandler.cpp \
../RXF/RXF_Event.cpp \
../RXF/RXF_EventQueue.cpp \
../RXF/RXF_MAIN.cpp \
../RXF/RXF_MainTask.cpp \
../RXF/RXF_MemoryPoolBase.cpp \
../RXF/RXF_Mutex.cpp \
../RXF/RXF_Reactive.cpp \
../RXF/RXF_Task.cpp \
../RXF/RXF_Tick.cpp \
../RXF/RXF_TimeoutEvent.cpp \
../RXF/RXF_Timer.cpp 

CPP_DEPS += \
./RXF/RXF_Active.d \
./RXF/RXF_ErrorHandler.d \
./RXF/RXF_Event.d \
./RXF/RXF_EventQueue.d \
./RXF/RXF_MAIN.d \
./RXF/RXF_MainTask.d \
./RXF/RXF_MemoryPoolBase.d \
./RXF/RXF_Mutex.d \
./RXF/RXF_Reactive.d \
./RXF/RXF_Task.d \
./RXF/RXF_Tick.d \
./RXF/RXF_TimeoutEvent.d \
./RXF/RXF_Timer.d 

OBJS += \
./RXF/RXF_Active.o \
./RXF/RXF_ErrorHandler.o \
./RXF/RXF_Event.o \
./RXF/RXF_EventQueue.o \
./RXF/RXF_MAIN.o \
./RXF/RXF_MainTask.o \
./RXF/RXF_MemoryPoolBase.o \
./RXF/RXF_Mutex.o \
./RXF/RXF_Reactive.o \
./RXF/RXF_Task.o \
./RXF/RXF_Tick.o \
./RXF/RXF_TimeoutEvent.o \
./RXF/RXF_Timer.o 


# Each subdirectory must supply rules for building sources it contributes
RXF/%.o: ../RXF/%.cpp RXF/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -std=c++11 -D__USE_LPCOPEN -DDEBUG -D__CODE_RED -DCORE_M3 -DCPP_USE_HEAP -D__LPC17XX__ -I"C:\Users\joklappe\Rhapsody\inc" -I"C:\Users\joklappe\Rhapsody\RXF" -I"C:\Users\joklappe\Rhapsody\GeneratedModel" -I"C:\Users\joklappe\Rhapsody\platform\board\inc" -I"C:\Users\joklappe\Rhapsody\platform\bsp\inc" -I"C:\Users\joklappe\Rhapsody\platform\chip\inc" -I"C:\Users\joklappe\Rhapsody\platform\os\inc" -I"C:\Users\joklappe\Rhapsody\platform\osSupport\inc" -I"C:\Users\joklappe\Rhapsody\platform\framework\inc" -I"C:\Users\joklappe\Rhapsody\platform\os\src\portable\GCC\ARM_CM3" -O0 -fno-common -g3 -Wall -c  -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-RXF

clean-RXF:
	-$(RM) ./RXF/RXF_Active.d ./RXF/RXF_Active.o ./RXF/RXF_ErrorHandler.d ./RXF/RXF_ErrorHandler.o ./RXF/RXF_Event.d ./RXF/RXF_Event.o ./RXF/RXF_EventQueue.d ./RXF/RXF_EventQueue.o ./RXF/RXF_MAIN.d ./RXF/RXF_MAIN.o ./RXF/RXF_MainTask.d ./RXF/RXF_MainTask.o ./RXF/RXF_MemoryPoolBase.d ./RXF/RXF_MemoryPoolBase.o ./RXF/RXF_Mutex.d ./RXF/RXF_Mutex.o ./RXF/RXF_Reactive.d ./RXF/RXF_Reactive.o ./RXF/RXF_Task.d ./RXF/RXF_Task.o ./RXF/RXF_Tick.d ./RXF/RXF_Tick.o ./RXF/RXF_TimeoutEvent.d ./RXF/RXF_TimeoutEvent.o ./RXF/RXF_Timer.d ./RXF/RXF_Timer.o

.PHONY: clean-RXF

