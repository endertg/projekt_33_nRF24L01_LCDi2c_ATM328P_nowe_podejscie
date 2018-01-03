################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include spi/subdir.mk
-include pcf8574/subdir.mk
-include nrf24l01/subdir.mk
-include netlayer/subdir.mk
-include lcdpcf8574_PL/subdir.mk
-include komunikacja/subdir.mk
-include i2chw/subdir.mk
-include ds18b20/subdir.mk
-include ESP8266/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
projekt_33_nRF24L01_LCDi2c_ATM328P_nowe_podejscie.lss \

FLASH_IMAGE += \
projekt_33_nRF24L01_LCDi2c_ATM328P_nowe_podejscie.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: projekt_33_nRF24L01_LCDi2c_ATM328P_nowe_podejscie.elf secondary-outputs

# Tool invocations
projekt_33_nRF24L01_LCDi2c_ATM328P_nowe_podejscie.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,projekt_33_nRF24L01_LCDi2c_ATM328P_nowe_podejscie.map -mmcu=atmega328p -o "projekt_33_nRF24L01_LCDi2c_ATM328P_nowe_podejscie.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

projekt_33_nRF24L01_LCDi2c_ATM328P_nowe_podejscie.lss: projekt_33_nRF24L01_LCDi2c_ATM328P_nowe_podejscie.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S projekt_33_nRF24L01_LCDi2c_ATM328P_nowe_podejscie.elf  >"projekt_33_nRF24L01_LCDi2c_ATM328P_nowe_podejscie.lss"
	@echo 'Finished building: $@'
	@echo ' '

projekt_33_nRF24L01_LCDi2c_ATM328P_nowe_podejscie.hex: projekt_33_nRF24L01_LCDi2c_ATM328P_nowe_podejscie.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex projekt_33_nRF24L01_LCDi2c_ATM328P_nowe_podejscie.elf  "projekt_33_nRF24L01_LCDi2c_ATM328P_nowe_podejscie.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: projekt_33_nRF24L01_LCDi2c_ATM328P_nowe_podejscie.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p projekt_33_nRF24L01_LCDi2c_ATM328P_nowe_podejscie.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) projekt_33_nRF24L01_LCDi2c_ATM328P_nowe_podejscie.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
