################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm

# All of the sources participating in the build are defined here
-include sources.mk
-include driver/subdir.mk
-include subdir.mk
-include objects.mk

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: ez430_chronos_datalogger_433MHz.out

# Tool invocations
ez430_chronos_datalogger_433MHz.out: 
	@echo 'Building target: $@'
	@echo 'Invoking: MSP430 Linker'
	80 80 "ez430_chronos_datalogger_433MHz.out" "ez430_chronos_datalogger_433MHz.map" "/msp430/include" "/lib" "/include" "/msp430/include"  "ez430_chronos_datalogger_433MHz.out"
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS) ez430_chronos_datalogger_433MHz.out
	-@echo ' '

post-build:
	-@echo 'Create flash image: TI-TXT'
	-".exe" --ti_txt "ez430_chronos_datalogger_433MHz.out" -o "ez430_chronos_datalogger_433MHz.txt" -order MS -romwidth 16
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
