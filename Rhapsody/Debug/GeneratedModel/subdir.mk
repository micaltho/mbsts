################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../GeneratedModel/AccelerationData.cpp \
../GeneratedModel/AccelerationMeasuring.cpp \
../GeneratedModel/Application.cpp \
../GeneratedModel/ConfigStorage.cpp \
../GeneratedModel/Controller.cpp \
../GeneratedModel/Display.cpp \
../GeneratedModel/DisplayTask.cpp \
../GeneratedModel/EepromData.cpp \
../GeneratedModel/JoystickDownButton.cpp \
../GeneratedModel/JoystickDownHandler.cpp \
../GeneratedModel/JoystickDownIRQ.cpp \
../GeneratedModel/JoystickLeftButton.cpp \
../GeneratedModel/JoystickLeftHandler.cpp \
../GeneratedModel/JoystickLeftIRQ.cpp \
../GeneratedModel/JoystickMiddelIRQ.cpp \
../GeneratedModel/JoystickMiddleButton.cpp \
../GeneratedModel/JoystickMiddleHandler.cpp \
../GeneratedModel/JoystickRightButton.cpp \
../GeneratedModel/JoystickRightHandler.cpp \
../GeneratedModel/JoystickRightIRQ.cpp \
../GeneratedModel/JoystickUpButton.cpp \
../GeneratedModel/JoystickUpHandler.cpp \
../GeneratedModel/JoystickUpIRQ.cpp \
../GeneratedModel/LPC1769.cpp \
../GeneratedModel/LPCAccelerationSensor.cpp \
../GeneratedModel/LPCBuilder.cpp \
../GeneratedModel/LPCEeprom.cpp \
../GeneratedModel/LPCInit.cpp \
../GeneratedModel/LPCJoystickDownButton.cpp \
../GeneratedModel/LPCJoystickLeftButton.cpp \
../GeneratedModel/LPCJoystickMiddleButton.cpp \
../GeneratedModel/LPCJoystickRightButton.cpp \
../GeneratedModel/LPCJoystickUpButton.cpp \
../GeneratedModel/LPCOledDisplay.cpp \
../GeneratedModel/MainLPC1769.cpp \
../GeneratedModel/RXF_Event_Pools.cpp \
../GeneratedModel/TimeCounter.cpp 

CPP_DEPS += \
./GeneratedModel/AccelerationData.d \
./GeneratedModel/AccelerationMeasuring.d \
./GeneratedModel/Application.d \
./GeneratedModel/ConfigStorage.d \
./GeneratedModel/Controller.d \
./GeneratedModel/Display.d \
./GeneratedModel/DisplayTask.d \
./GeneratedModel/EepromData.d \
./GeneratedModel/JoystickDownButton.d \
./GeneratedModel/JoystickDownHandler.d \
./GeneratedModel/JoystickDownIRQ.d \
./GeneratedModel/JoystickLeftButton.d \
./GeneratedModel/JoystickLeftHandler.d \
./GeneratedModel/JoystickLeftIRQ.d \
./GeneratedModel/JoystickMiddelIRQ.d \
./GeneratedModel/JoystickMiddleButton.d \
./GeneratedModel/JoystickMiddleHandler.d \
./GeneratedModel/JoystickRightButton.d \
./GeneratedModel/JoystickRightHandler.d \
./GeneratedModel/JoystickRightIRQ.d \
./GeneratedModel/JoystickUpButton.d \
./GeneratedModel/JoystickUpHandler.d \
./GeneratedModel/JoystickUpIRQ.d \
./GeneratedModel/LPC1769.d \
./GeneratedModel/LPCAccelerationSensor.d \
./GeneratedModel/LPCBuilder.d \
./GeneratedModel/LPCEeprom.d \
./GeneratedModel/LPCInit.d \
./GeneratedModel/LPCJoystickDownButton.d \
./GeneratedModel/LPCJoystickLeftButton.d \
./GeneratedModel/LPCJoystickMiddleButton.d \
./GeneratedModel/LPCJoystickRightButton.d \
./GeneratedModel/LPCJoystickUpButton.d \
./GeneratedModel/LPCOledDisplay.d \
./GeneratedModel/MainLPC1769.d \
./GeneratedModel/RXF_Event_Pools.d \
./GeneratedModel/TimeCounter.d 

OBJS += \
./GeneratedModel/AccelerationData.o \
./GeneratedModel/AccelerationMeasuring.o \
./GeneratedModel/Application.o \
./GeneratedModel/ConfigStorage.o \
./GeneratedModel/Controller.o \
./GeneratedModel/Display.o \
./GeneratedModel/DisplayTask.o \
./GeneratedModel/EepromData.o \
./GeneratedModel/JoystickDownButton.o \
./GeneratedModel/JoystickDownHandler.o \
./GeneratedModel/JoystickDownIRQ.o \
./GeneratedModel/JoystickLeftButton.o \
./GeneratedModel/JoystickLeftHandler.o \
./GeneratedModel/JoystickLeftIRQ.o \
./GeneratedModel/JoystickMiddelIRQ.o \
./GeneratedModel/JoystickMiddleButton.o \
./GeneratedModel/JoystickMiddleHandler.o \
./GeneratedModel/JoystickRightButton.o \
./GeneratedModel/JoystickRightHandler.o \
./GeneratedModel/JoystickRightIRQ.o \
./GeneratedModel/JoystickUpButton.o \
./GeneratedModel/JoystickUpHandler.o \
./GeneratedModel/JoystickUpIRQ.o \
./GeneratedModel/LPC1769.o \
./GeneratedModel/LPCAccelerationSensor.o \
./GeneratedModel/LPCBuilder.o \
./GeneratedModel/LPCEeprom.o \
./GeneratedModel/LPCInit.o \
./GeneratedModel/LPCJoystickDownButton.o \
./GeneratedModel/LPCJoystickLeftButton.o \
./GeneratedModel/LPCJoystickMiddleButton.o \
./GeneratedModel/LPCJoystickRightButton.o \
./GeneratedModel/LPCJoystickUpButton.o \
./GeneratedModel/LPCOledDisplay.o \
./GeneratedModel/MainLPC1769.o \
./GeneratedModel/RXF_Event_Pools.o \
./GeneratedModel/TimeCounter.o 


# Each subdirectory must supply rules for building sources it contributes
GeneratedModel/%.o: ../GeneratedModel/%.cpp GeneratedModel/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -std=c++11 -D__USE_LPCOPEN -DDEBUG -D__CODE_RED -DCORE_M3 -DCPP_USE_HEAP -D__LPC17XX__ -I"C:\Users\joklappe\Rhapsody\inc" -I"C:\Users\joklappe\Rhapsody\RXF" -I"C:\Users\joklappe\Rhapsody\GeneratedModel" -I"C:\Users\joklappe\Rhapsody\platform\board\inc" -I"C:\Users\joklappe\Rhapsody\platform\bsp\inc" -I"C:\Users\joklappe\Rhapsody\platform\chip\inc" -I"C:\Users\joklappe\Rhapsody\platform\os\inc" -I"C:\Users\joklappe\Rhapsody\platform\osSupport\inc" -I"C:\Users\joklappe\Rhapsody\platform\framework\inc" -I"C:\Users\joklappe\Rhapsody\platform\os\src\portable\GCC\ARM_CM3" -O0 -fno-common -g3 -Wall -c  -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-GeneratedModel

clean-GeneratedModel:
	-$(RM) ./GeneratedModel/AccelerationData.d ./GeneratedModel/AccelerationData.o ./GeneratedModel/AccelerationMeasuring.d ./GeneratedModel/AccelerationMeasuring.o ./GeneratedModel/Application.d ./GeneratedModel/Application.o ./GeneratedModel/ConfigStorage.d ./GeneratedModel/ConfigStorage.o ./GeneratedModel/Controller.d ./GeneratedModel/Controller.o ./GeneratedModel/Display.d ./GeneratedModel/Display.o ./GeneratedModel/DisplayTask.d ./GeneratedModel/DisplayTask.o ./GeneratedModel/EepromData.d ./GeneratedModel/EepromData.o ./GeneratedModel/JoystickDownButton.d ./GeneratedModel/JoystickDownButton.o ./GeneratedModel/JoystickDownHandler.d ./GeneratedModel/JoystickDownHandler.o ./GeneratedModel/JoystickDownIRQ.d ./GeneratedModel/JoystickDownIRQ.o ./GeneratedModel/JoystickLeftButton.d ./GeneratedModel/JoystickLeftButton.o ./GeneratedModel/JoystickLeftHandler.d ./GeneratedModel/JoystickLeftHandler.o ./GeneratedModel/JoystickLeftIRQ.d ./GeneratedModel/JoystickLeftIRQ.o ./GeneratedModel/JoystickMiddelIRQ.d ./GeneratedModel/JoystickMiddelIRQ.o ./GeneratedModel/JoystickMiddleButton.d ./GeneratedModel/JoystickMiddleButton.o ./GeneratedModel/JoystickMiddleHandler.d ./GeneratedModel/JoystickMiddleHandler.o ./GeneratedModel/JoystickRightButton.d ./GeneratedModel/JoystickRightButton.o ./GeneratedModel/JoystickRightHandler.d ./GeneratedModel/JoystickRightHandler.o ./GeneratedModel/JoystickRightIRQ.d ./GeneratedModel/JoystickRightIRQ.o ./GeneratedModel/JoystickUpButton.d ./GeneratedModel/JoystickUpButton.o ./GeneratedModel/JoystickUpHandler.d ./GeneratedModel/JoystickUpHandler.o ./GeneratedModel/JoystickUpIRQ.d ./GeneratedModel/JoystickUpIRQ.o ./GeneratedModel/LPC1769.d ./GeneratedModel/LPC1769.o ./GeneratedModel/LPCAccelerationSensor.d ./GeneratedModel/LPCAccelerationSensor.o ./GeneratedModel/LPCBuilder.d ./GeneratedModel/LPCBuilder.o ./GeneratedModel/LPCEeprom.d ./GeneratedModel/LPCEeprom.o ./GeneratedModel/LPCInit.d ./GeneratedModel/LPCInit.o ./GeneratedModel/LPCJoystickDownButton.d ./GeneratedModel/LPCJoystickDownButton.o ./GeneratedModel/LPCJoystickLeftButton.d ./GeneratedModel/LPCJoystickLeftButton.o ./GeneratedModel/LPCJoystickMiddleButton.d ./GeneratedModel/LPCJoystickMiddleButton.o ./GeneratedModel/LPCJoystickRightButton.d ./GeneratedModel/LPCJoystickRightButton.o ./GeneratedModel/LPCJoystickUpButton.d ./GeneratedModel/LPCJoystickUpButton.o ./GeneratedModel/LPCOledDisplay.d ./GeneratedModel/LPCOledDisplay.o ./GeneratedModel/MainLPC1769.d ./GeneratedModel/MainLPC1769.o ./GeneratedModel/RXF_Event_Pools.d ./GeneratedModel/RXF_Event_Pools.o ./GeneratedModel/TimeCounter.d ./GeneratedModel/TimeCounter.o

.PHONY: clean-GeneratedModel

