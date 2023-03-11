################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../platform/board/src/board.c \
../platform/board/src/board_sysinit.c \
../platform/board/src/lpc_phy_smsc87x0.c 

C_DEPS += \
./platform/board/src/board.d \
./platform/board/src/board_sysinit.d \
./platform/board/src/lpc_phy_smsc87x0.d 

OBJS += \
./platform/board/src/board.o \
./platform/board/src/board_sysinit.o \
./platform/board/src/lpc_phy_smsc87x0.o 


# Each subdirectory must supply rules for building sources it contributes
platform/board/src/%.o: ../platform/board/src/%.c platform/board/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -DCPP_USE_HEAP -D__LPC17XX__ -I"C:\Users\joklappe\Rhapsody\inc" -I"C:\Users\joklappe\Rhapsody\platform\board\inc" -I"C:\Users\joklappe\Rhapsody\platform\bsp\inc" -I"C:\Users\joklappe\Rhapsody\platform\chip\inc" -I"C:\Users\joklappe\Rhapsody\platform\os\inc" -I"C:\Users\joklappe\Rhapsody\platform\osSupport\inc" -I"C:\Users\joklappe\Rhapsody\platform\framework\inc" -I"C:\Users\joklappe\Rhapsody\platform\os\src\portable\GCC\ARM_CM3" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-platform-2f-board-2f-src

clean-platform-2f-board-2f-src:
	-$(RM) ./platform/board/src/board.d ./platform/board/src/board.o ./platform/board/src/board_sysinit.d ./platform/board/src/board_sysinit.o ./platform/board/src/lpc_phy_smsc87x0.d ./platform/board/src/lpc_phy_smsc87x0.o

.PHONY: clean-platform-2f-board-2f-src

