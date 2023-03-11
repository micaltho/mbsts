################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../platform/chip/src/adc_17xx_40xx.c \
../platform/chip/src/can_17xx_40xx.c \
../platform/chip/src/chip_17xx_40xx.c \
../platform/chip/src/clock_17xx_40xx.c \
../platform/chip/src/cmp_17xx_40xx.c \
../platform/chip/src/crc_17xx_40xx.c \
../platform/chip/src/dac_17xx_40xx.c \
../platform/chip/src/eeprom_17xx_40xx.c \
../platform/chip/src/emc_17xx_40xx.c \
../platform/chip/src/enet_17xx_40xx.c \
../platform/chip/src/gpdma_17xx_40xx.c \
../platform/chip/src/gpio_17xx_40xx.c \
../platform/chip/src/gpioint_17xx_40xx.c \
../platform/chip/src/i2c_17xx_40xx.c \
../platform/chip/src/i2s_17xx_40xx.c \
../platform/chip/src/iap.c \
../platform/chip/src/iocon_17xx_40xx.c \
../platform/chip/src/lcd_17xx_40xx.c \
../platform/chip/src/pmu_17xx_40xx.c \
../platform/chip/src/ring_buffer.c \
../platform/chip/src/ritimer_17xx_40xx.c \
../platform/chip/src/rtc_17xx_40xx.c \
../platform/chip/src/sdc_17xx_40xx.c \
../platform/chip/src/sdmmc_17xx_40xx.c \
../platform/chip/src/spi_17xx_40xx.c \
../platform/chip/src/ssp_17xx_40xx.c \
../platform/chip/src/stopwatch_17xx_40xx.c \
../platform/chip/src/sysctl_17xx_40xx.c \
../platform/chip/src/sysinit_17xx_40xx.c \
../platform/chip/src/timer_17xx_40xx.c \
../platform/chip/src/uart_17xx_40xx.c \
../platform/chip/src/wwdt_17xx_40xx.c 

C_DEPS += \
./platform/chip/src/adc_17xx_40xx.d \
./platform/chip/src/can_17xx_40xx.d \
./platform/chip/src/chip_17xx_40xx.d \
./platform/chip/src/clock_17xx_40xx.d \
./platform/chip/src/cmp_17xx_40xx.d \
./platform/chip/src/crc_17xx_40xx.d \
./platform/chip/src/dac_17xx_40xx.d \
./platform/chip/src/eeprom_17xx_40xx.d \
./platform/chip/src/emc_17xx_40xx.d \
./platform/chip/src/enet_17xx_40xx.d \
./platform/chip/src/gpdma_17xx_40xx.d \
./platform/chip/src/gpio_17xx_40xx.d \
./platform/chip/src/gpioint_17xx_40xx.d \
./platform/chip/src/i2c_17xx_40xx.d \
./platform/chip/src/i2s_17xx_40xx.d \
./platform/chip/src/iap.d \
./platform/chip/src/iocon_17xx_40xx.d \
./platform/chip/src/lcd_17xx_40xx.d \
./platform/chip/src/pmu_17xx_40xx.d \
./platform/chip/src/ring_buffer.d \
./platform/chip/src/ritimer_17xx_40xx.d \
./platform/chip/src/rtc_17xx_40xx.d \
./platform/chip/src/sdc_17xx_40xx.d \
./platform/chip/src/sdmmc_17xx_40xx.d \
./platform/chip/src/spi_17xx_40xx.d \
./platform/chip/src/ssp_17xx_40xx.d \
./platform/chip/src/stopwatch_17xx_40xx.d \
./platform/chip/src/sysctl_17xx_40xx.d \
./platform/chip/src/sysinit_17xx_40xx.d \
./platform/chip/src/timer_17xx_40xx.d \
./platform/chip/src/uart_17xx_40xx.d \
./platform/chip/src/wwdt_17xx_40xx.d 

OBJS += \
./platform/chip/src/adc_17xx_40xx.o \
./platform/chip/src/can_17xx_40xx.o \
./platform/chip/src/chip_17xx_40xx.o \
./platform/chip/src/clock_17xx_40xx.o \
./platform/chip/src/cmp_17xx_40xx.o \
./platform/chip/src/crc_17xx_40xx.o \
./platform/chip/src/dac_17xx_40xx.o \
./platform/chip/src/eeprom_17xx_40xx.o \
./platform/chip/src/emc_17xx_40xx.o \
./platform/chip/src/enet_17xx_40xx.o \
./platform/chip/src/gpdma_17xx_40xx.o \
./platform/chip/src/gpio_17xx_40xx.o \
./platform/chip/src/gpioint_17xx_40xx.o \
./platform/chip/src/i2c_17xx_40xx.o \
./platform/chip/src/i2s_17xx_40xx.o \
./platform/chip/src/iap.o \
./platform/chip/src/iocon_17xx_40xx.o \
./platform/chip/src/lcd_17xx_40xx.o \
./platform/chip/src/pmu_17xx_40xx.o \
./platform/chip/src/ring_buffer.o \
./platform/chip/src/ritimer_17xx_40xx.o \
./platform/chip/src/rtc_17xx_40xx.o \
./platform/chip/src/sdc_17xx_40xx.o \
./platform/chip/src/sdmmc_17xx_40xx.o \
./platform/chip/src/spi_17xx_40xx.o \
./platform/chip/src/ssp_17xx_40xx.o \
./platform/chip/src/stopwatch_17xx_40xx.o \
./platform/chip/src/sysctl_17xx_40xx.o \
./platform/chip/src/sysinit_17xx_40xx.o \
./platform/chip/src/timer_17xx_40xx.o \
./platform/chip/src/uart_17xx_40xx.o \
./platform/chip/src/wwdt_17xx_40xx.o 


# Each subdirectory must supply rules for building sources it contributes
platform/chip/src/%.o: ../platform/chip/src/%.c platform/chip/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -DCPP_USE_HEAP -D__LPC17XX__ -I"C:\Users\joklappe\Rhapsody\inc" -I"C:\Users\joklappe\Rhapsody\platform\board\inc" -I"C:\Users\joklappe\Rhapsody\platform\bsp\inc" -I"C:\Users\joklappe\Rhapsody\platform\chip\inc" -I"C:\Users\joklappe\Rhapsody\platform\os\inc" -I"C:\Users\joklappe\Rhapsody\platform\osSupport\inc" -I"C:\Users\joklappe\Rhapsody\platform\framework\inc" -I"C:\Users\joklappe\Rhapsody\platform\os\src\portable\GCC\ARM_CM3" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-platform-2f-chip-2f-src

clean-platform-2f-chip-2f-src:
	-$(RM) ./platform/chip/src/adc_17xx_40xx.d ./platform/chip/src/adc_17xx_40xx.o ./platform/chip/src/can_17xx_40xx.d ./platform/chip/src/can_17xx_40xx.o ./platform/chip/src/chip_17xx_40xx.d ./platform/chip/src/chip_17xx_40xx.o ./platform/chip/src/clock_17xx_40xx.d ./platform/chip/src/clock_17xx_40xx.o ./platform/chip/src/cmp_17xx_40xx.d ./platform/chip/src/cmp_17xx_40xx.o ./platform/chip/src/crc_17xx_40xx.d ./platform/chip/src/crc_17xx_40xx.o ./platform/chip/src/dac_17xx_40xx.d ./platform/chip/src/dac_17xx_40xx.o ./platform/chip/src/eeprom_17xx_40xx.d ./platform/chip/src/eeprom_17xx_40xx.o ./platform/chip/src/emc_17xx_40xx.d ./platform/chip/src/emc_17xx_40xx.o ./platform/chip/src/enet_17xx_40xx.d ./platform/chip/src/enet_17xx_40xx.o ./platform/chip/src/gpdma_17xx_40xx.d ./platform/chip/src/gpdma_17xx_40xx.o ./platform/chip/src/gpio_17xx_40xx.d ./platform/chip/src/gpio_17xx_40xx.o ./platform/chip/src/gpioint_17xx_40xx.d ./platform/chip/src/gpioint_17xx_40xx.o ./platform/chip/src/i2c_17xx_40xx.d ./platform/chip/src/i2c_17xx_40xx.o ./platform/chip/src/i2s_17xx_40xx.d ./platform/chip/src/i2s_17xx_40xx.o ./platform/chip/src/iap.d ./platform/chip/src/iap.o ./platform/chip/src/iocon_17xx_40xx.d ./platform/chip/src/iocon_17xx_40xx.o ./platform/chip/src/lcd_17xx_40xx.d ./platform/chip/src/lcd_17xx_40xx.o ./platform/chip/src/pmu_17xx_40xx.d ./platform/chip/src/pmu_17xx_40xx.o ./platform/chip/src/ring_buffer.d ./platform/chip/src/ring_buffer.o ./platform/chip/src/ritimer_17xx_40xx.d ./platform/chip/src/ritimer_17xx_40xx.o ./platform/chip/src/rtc_17xx_40xx.d ./platform/chip/src/rtc_17xx_40xx.o ./platform/chip/src/sdc_17xx_40xx.d ./platform/chip/src/sdc_17xx_40xx.o ./platform/chip/src/sdmmc_17xx_40xx.d ./platform/chip/src/sdmmc_17xx_40xx.o ./platform/chip/src/spi_17xx_40xx.d ./platform/chip/src/spi_17xx_40xx.o ./platform/chip/src/ssp_17xx_40xx.d ./platform/chip/src/ssp_17xx_40xx.o ./platform/chip/src/stopwatch_17xx_40xx.d ./platform/chip/src/stopwatch_17xx_40xx.o ./platform/chip/src/sysctl_17xx_40xx.d ./platform/chip/src/sysctl_17xx_40xx.o ./platform/chip/src/sysinit_17xx_40xx.d ./platform/chip/src/sysinit_17xx_40xx.o ./platform/chip/src/timer_17xx_40xx.d ./platform/chip/src/timer_17xx_40xx.o ./platform/chip/src/uart_17xx_40xx.d ./platform/chip/src/uart_17xx_40xx.o ./platform/chip/src/wwdt_17xx_40xx.d ./platform/chip/src/wwdt_17xx_40xx.o

.PHONY: clean-platform-2f-chip-2f-src

