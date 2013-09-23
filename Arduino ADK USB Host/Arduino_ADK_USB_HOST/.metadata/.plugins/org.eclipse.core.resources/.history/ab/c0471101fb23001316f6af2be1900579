################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include USB_Device_Implementation/subdir.mk
-include System_Defines/subdir.mk
-include Sensor_Parser_Implementation/subdir.mk
-include Emulation_Device_Implementation/subdir.mk
-include Debug_API/subdir.mk
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
Arduino_HID_Joystick.lss \

FLASH_IMAGE += \
Arduino_HID_Joystick.hex \

EEPROM_IMAGE += \
Arduino_HID_Joystick.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Arduino_HID_Joystick.elf secondary-outputs

# Tool invocations
Arduino_HID_Joystick.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C++ Linker'
	avr-gcc -Os -Wl,--gc-sections  -L"/Volumes/DataHDD/Documents/4th Year Project/Black-Box-Mouse-Interface/Arduino ADK USB Host/Arduino_ADK_USB_HOST/Arduino_Mega_2560_or_Mega_ADK/Release" -mmcu=atmega2560  -o"Arduino_HID_Joystick.elf" $(OBJS) $(USER_OBJS) $(LIBS) -lm
	@echo 'Finished building target: $@'
	@echo ' '

Arduino_HID_Joystick.lss: Arduino_HID_Joystick.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Arduino_HID_Joystick.elf  >"Arduino_HID_Joystick.lss"
	@echo 'Finished building: $@'
	@echo ' '

Arduino_HID_Joystick.hex: Arduino_HID_Joystick.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex Arduino_HID_Joystick.elf  "Arduino_HID_Joystick.hex"
	@echo 'Finished building: $@'
	@echo ' '

Arduino_HID_Joystick.eep: Arduino_HID_Joystick.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Arduino_HID_Joystick.elf  "Arduino_HID_Joystick.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Arduino_HID_Joystick.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega2560 Arduino_HID_Joystick.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EEPROM_IMAGE)$(ELFS)$(FLASH_IMAGE)$(LSS)$(S_DEPS)$(CXX_DEPS)$(S_UPPER_DEPS)$(C++_DEPS)$(ASM_DEPS)$(CC_DEPS)$(CPP_DEPS)$(C_UPPER_DEPS)$(SIZEDUMMY) Arduino_HID_Joystick.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
