################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
LUFA_Arduino_ADK.lss \

FLASH_IMAGE += \
LUFA_Arduino_ADK.hex \

EEPROM_IMAGE += \
LUFA_Arduino_ADK.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: LUFA_Arduino_ADK.elf secondary-outputs

# Tool invocations
LUFA_Arduino_ADK.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C++ Linker'
	avr-gcc -Os -Wl,--gc-sections  -L"/Volumes/DataHDD/Documents/4th Year Project/Black-Box-Mouse-Interface/Arduino ADK USB Host/Arduino_ADK_USB_HOST/Arduino_Mega_2560_or_Mega_ADK/Release" -mmcu=atmega2560  -o"LUFA_Arduino_ADK.elf" $(OBJS) $(USER_OBJS) $(LIBS) -lm
	@echo 'Finished building target: $@'
	@echo ' '

LUFA_Arduino_ADK.lss: LUFA_Arduino_ADK.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S LUFA_Arduino_ADK.elf  >"LUFA_Arduino_ADK.lss"
	@echo 'Finished building: $@'
	@echo ' '

LUFA_Arduino_ADK.hex: LUFA_Arduino_ADK.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex LUFA_Arduino_ADK.elf  "LUFA_Arduino_ADK.hex"
	@echo 'Finished building: $@'
	@echo ' '

LUFA_Arduino_ADK.eep: LUFA_Arduino_ADK.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex LUFA_Arduino_ADK.elf  "LUFA_Arduino_ADK.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: LUFA_Arduino_ADK.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega2560 LUFA_Arduino_ADK.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EEPROM_IMAGE)$(ELFS)$(FLASH_IMAGE)$(LSS)$(S_DEPS)$(CXX_DEPS)$(S_UPPER_DEPS)$(C++_DEPS)$(ASM_DEPS)$(CC_DEPS)$(CPP_DEPS)$(C_UPPER_DEPS)$(SIZEDUMMY) LUFA_Arduino_ADK.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
