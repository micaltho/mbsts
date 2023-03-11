################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../platform/bsp/src/adc.cpp \
../platform/bsp/src/canif.cpp \
../platform/bsp/src/dac.cpp \
../platform/bsp/src/digitalinout.cpp \
../platform/bsp/src/errorlog.cpp \
../platform/bsp/src/i2cdevice.cpp \
../platform/bsp/src/interrupt.cpp \
../platform/bsp/src/isl29003.cpp \
../platform/bsp/src/max6576.cpp \
../platform/bsp/src/mc24lc08.cpp \
../platform/bsp/src/mc24lc64.cpp \
../platform/bsp/src/mma7455.cpp \
../platform/bsp/src/pca9531.cpp \
../platform/bsp/src/pca9532.cpp \
../platform/bsp/src/pwm.cpp \
../platform/bsp/src/sr74lvc595.cpp \
../platform/bsp/src/ssd1305.cpp \
../platform/bsp/src/ssd1306.cpp \
../platform/bsp/src/sspdevice.cpp \
../platform/bsp/src/st7565r.cpp 

C_SRCS += \
../platform/bsp/src/font5x7.c \
../platform/bsp/src/fontNum24_24.c \
../platform/bsp/src/lpc17xx_iap.c 

CPP_DEPS += \
./platform/bsp/src/adc.d \
./platform/bsp/src/canif.d \
./platform/bsp/src/dac.d \
./platform/bsp/src/digitalinout.d \
./platform/bsp/src/errorlog.d \
./platform/bsp/src/i2cdevice.d \
./platform/bsp/src/interrupt.d \
./platform/bsp/src/isl29003.d \
./platform/bsp/src/max6576.d \
./platform/bsp/src/mc24lc08.d \
./platform/bsp/src/mc24lc64.d \
./platform/bsp/src/mma7455.d \
./platform/bsp/src/pca9531.d \
./platform/bsp/src/pca9532.d \
./platform/bsp/src/pwm.d \
./platform/bsp/src/sr74lvc595.d \
./platform/bsp/src/ssd1305.d \
./platform/bsp/src/ssd1306.d \
./platform/bsp/src/sspdevice.d \
./platform/bsp/src/st7565r.d 

C_DEPS += \
./platform/bsp/src/font5x7.d \
./platform/bsp/src/fontNum24_24.d \
./platform/bsp/src/lpc17xx_iap.d 

OBJS += \
./platform/bsp/src/adc.o \
./platform/bsp/src/canif.o \
./platform/bsp/src/dac.o \
./platform/bsp/src/digitalinout.o \
./platform/bsp/src/errorlog.o \
./platform/bsp/src/font5x7.o \
./platform/bsp/src/fontNum24_24.o \
./platform/bsp/src/i2cdevice.o \
./platform/bsp/src/interrupt.o \
./platform/bsp/src/isl29003.o \
./platform/bsp/src/lpc17xx_iap.o \
./platform/bsp/src/max6576.o \
./platform/bsp/src/mc24lc08.o \
./platform/bsp/src/mc24lc64.o \
./platform/bsp/src/mma7455.o \
./platform/bsp/src/pca9531.o \
./platform/bsp/src/pca9532.o \
./platform/bsp/src/pwm.o \
./platform/bsp/src/sr74lvc595.o \
./platform/bsp/src/ssd1305.o \
./platform/bsp/src/ssd1306.o \
./platform/bsp/src/sspdevice.o \
./platform/bsp/src/st7565r.o 


# Each subdirectory must supply rules for building sources it contributes
platform/bsp/src/%.o: ../platform/bsp/src/%.cpp platform/bsp/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -std=c++11 -D__USE_LPCOPEN -DDEBUG -D__CODE_RED -DCORE_M3 -DCPP_USE_HEAP -D__LPC17XX__ -I"C:\Users\joklappe\Rhapsody\inc" -I"C:\Users\joklappe\Rhapsody\RXF" -I"C:\Users\joklappe\Rhapsody\GeneratedModel" -I"C:\Users\joklappe\Rhapsody\platform\board\inc" -I"C:\Users\joklappe\Rhapsody\platform\bsp\inc" -I"C:\Users\joklappe\Rhapsody\platform\chip\inc" -I"C:\Users\joklappe\Rhapsody\platform\os\inc" -I"C:\Users\joklappe\Rhapsody\platform\osSupport\inc" -I"C:\Users\joklappe\Rhapsody\platform\framework\inc" -I"C:\Users\joklappe\Rhapsody\platform\os\src\portable\GCC\ARM_CM3" -O0 -fno-common -g3 -Wall -c  -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

platform/bsp/src/%.o: ../platform/bsp/src/%.c platform/bsp/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -DCPP_USE_HEAP -D__LPC17XX__ -I"C:\Users\joklappe\Rhapsody\inc" -I"C:\Users\joklappe\Rhapsody\platform\board\inc" -I"C:\Users\joklappe\Rhapsody\platform\bsp\inc" -I"C:\Users\joklappe\Rhapsody\platform\chip\inc" -I"C:\Users\joklappe\Rhapsody\platform\os\inc" -I"C:\Users\joklappe\Rhapsody\platform\osSupport\inc" -I"C:\Users\joklappe\Rhapsody\platform\framework\inc" -I"C:\Users\joklappe\Rhapsody\platform\os\src\portable\GCC\ARM_CM3" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-platform-2f-bsp-2f-src

clean-platform-2f-bsp-2f-src:
	-$(RM) ./platform/bsp/src/adc.d ./platform/bsp/src/adc.o ./platform/bsp/src/canif.d ./platform/bsp/src/canif.o ./platform/bsp/src/dac.d ./platform/bsp/src/dac.o ./platform/bsp/src/digitalinout.d ./platform/bsp/src/digitalinout.o ./platform/bsp/src/errorlog.d ./platform/bsp/src/errorlog.o ./platform/bsp/src/font5x7.d ./platform/bsp/src/font5x7.o ./platform/bsp/src/fontNum24_24.d ./platform/bsp/src/fontNum24_24.o ./platform/bsp/src/i2cdevice.d ./platform/bsp/src/i2cdevice.o ./platform/bsp/src/interrupt.d ./platform/bsp/src/interrupt.o ./platform/bsp/src/isl29003.d ./platform/bsp/src/isl29003.o ./platform/bsp/src/lpc17xx_iap.d ./platform/bsp/src/lpc17xx_iap.o ./platform/bsp/src/max6576.d ./platform/bsp/src/max6576.o ./platform/bsp/src/mc24lc08.d ./platform/bsp/src/mc24lc08.o ./platform/bsp/src/mc24lc64.d ./platform/bsp/src/mc24lc64.o ./platform/bsp/src/mma7455.d ./platform/bsp/src/mma7455.o ./platform/bsp/src/pca9531.d ./platform/bsp/src/pca9531.o ./platform/bsp/src/pca9532.d ./platform/bsp/src/pca9532.o ./platform/bsp/src/pwm.d ./platform/bsp/src/pwm.o ./platform/bsp/src/sr74lvc595.d ./platform/bsp/src/sr74lvc595.o ./platform/bsp/src/ssd1305.d ./platform/bsp/src/ssd1305.o ./platform/bsp/src/ssd1306.d ./platform/bsp/src/ssd1306.o ./platform/bsp/src/sspdevice.d ./platform/bsp/src/sspdevice.o ./platform/bsp/src/st7565r.d ./platform/bsp/src/st7565r.o

.PHONY: clean-platform-2f-bsp-2f-src

