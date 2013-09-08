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
-include System_Defines/EEPROM/subdir.mk
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
AVR_USB_Host.lss \

FLASH_IMAGE += \
AVR_USB_Host.hex \

EEPROM_IMAGE += \
AVR_USB_Host.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: AVR_USB_Host.elf secondary-outputs

# Tool invocations
AVR_USB_Host.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C++ Linker'
	avr-gcc -Os -Wl,--gc-sections  -L"/Volumes/DataHDD/Documents/4th Year Project/Black-Box-Mouse-Interface/Arduino ADK USB Host/Arduino_ADK_USB_HOST/Release" -mmcu=atmega2560  -o"AVR_USB_Host.elf" $(OBJS) $(USER_OBJS) $(LIBS) -lm
	@echo 'Finished building target: $@'
	@echo ' '

AVR_USB_Host.lss: AVR_USB_Host.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S AVR_USB_Host.elf  >"AVR_USB_Host.lss"
	@echo 'Finished building: $@'
	@echo ' '

AVR_USB_Host.hex: AVR_USB_Host.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex AVR_USB_Host.elf  "AVR_USB_Host.hex"
	@echo 'Finished building: $@'
	@echo ' '

AVR_USB_Host.eep: AVR_USB_Host.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex AVR_USB_Host.elf  "AVR_USB_Host.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: AVR_USB_Host.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega2560 AVR_USB_Host.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EEPROM_IMAGE)$(ELFS)$(FLASH_IMAGE)$(LSS)$(S_DEPS)$(CXX_DEPS)$(S_UPPER_DEPS)$(C++_DEPS)$(ASM_DEPS)$(CC_DEPS)$(CPP_DEPS)$(C_UPPER_DEPS)$(SIZEDUMMY) AVR_USB_Host.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
