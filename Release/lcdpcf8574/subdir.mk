################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lcdpcf8574/lcdpcf8574.c 

OBJS += \
./lcdpcf8574/lcdpcf8574.o 

C_DEPS += \
./lcdpcf8574/lcdpcf8574.d 


# Each subdirectory must supply rules for building sources it contributes
lcdpcf8574/%.o: ../lcdpcf8574/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


