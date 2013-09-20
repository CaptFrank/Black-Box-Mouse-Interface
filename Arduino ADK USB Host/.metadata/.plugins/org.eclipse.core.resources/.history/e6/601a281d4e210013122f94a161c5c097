################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include USB_Implementation/subdir.mk
-include USB_HID_API/subdir.mk
-include USB_Device_Implementation/subdir.mk
-include System_Defines/subdir.mk
-include Sensor_Parser_Implementation/USB_Sender/USB_Host_Shield_2.0-master/examples/HID/le3dp/subdir.mk
-include Sensor_Parser_Implementation/USB_Sender/USB_Host_Shield_2.0-master/examples/HID/USBHIDJoystick/subdir.mk
-include Sensor_Parser_Implementation/USB_Sender/USB_Host_Shield_2.0-master/subdir.mk
-include Sensor_Parser_Implementation/USB_Sender/subdir.mk
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
Arduino_ADK_USB_HOST.lss \

FLASH_IMAGE += \
Arduino_ADK_USB_HOST.hex \

EEPROM_IMAGE += \
Arduino_ADK_USB_HOST.eep \

SIZEDUMMY += \
sizedummy \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: Arduino_ADK_USB_HOST.elf secondary-outputs

# Tool invocations
Arduino_ADK_USB_HOST.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C++ Linker'
	avr-g++ -Wl,-Map,Arduino_ADK_USB_HOST.map,--cref -L"/Users/francispapineau/Documents/4th year project/Source Code/Black-Box-Mouse-Interface/Arduino ADK USB Host" -mmcu=atmega16 -o "Arduino_ADK_USB_HOST.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Arduino_ADK_USB_HOST.lss: Arduino_ADK_USB_HOST.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Arduino_ADK_USB_HOST.elf  >"Arduino_ADK_USB_HOST.lss"
	@echo 'Finished building: $@'
	@echo ' '

Arduino_ADK_USB_HOST.hex: Arduino_ADK_USB_HOST.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex Arduino_ADK_USB_HOST.elf  "Arduino_ADK_USB_HOST.hex"
	@echo 'Finished building: $@'
	@echo ' '

Arduino_ADK_USB_HOST.eep: Arduino_ADK_USB_HOST.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Arduino_ADK_USB_HOST.elf  "Arduino_ADK_USB_HOST.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Arduino_ADK_USB_HOST.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega16 Arduino_ADK_USB_HOST.elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: Arduino_ADK_USB_HOST.elf
	@echo 'Invoking: AVRDude'
	/usr/local/CrossPack-AVR-20120217/bin/avrdude -pm16 -carduino -b9600 -Uflash:w:Arduino_ADK_USB_HOST.hex:a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EEPROM_IMAGE)$(ELFS)$(FLASH_IMAGE)$(LSS)$(S_DEPS)$(CXX_DEPS)$(S_UPPER_DEPS)$(C++_DEPS)$(ASM_DEPS)$(CC_DEPS)$(AVRDUDEDUMMY)$(CPP_DEPS)$(C_UPPER_DEPS)$(SIZEDUMMY) Arduino_ADK_USB_HOST.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY) $(AVRDUDEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
