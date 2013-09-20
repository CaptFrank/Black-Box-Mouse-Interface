################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hid_tutorial_1/usbdrv/oddebug.c \
../hid_tutorial_1/usbdrv/usbdrv.c 

S_UPPER_SRCS += \
../hid_tutorial_1/usbdrv/usbdrvasm.S 

ASM_SRCS += \
../hid_tutorial_1/usbdrv/usbdrvasm.asm 

OBJS += \
./hid_tutorial_1/usbdrv/oddebug.o \
./hid_tutorial_1/usbdrv/usbdrv.o \
./hid_tutorial_1/usbdrv/usbdrvasm.o 

C_DEPS += \
./hid_tutorial_1/usbdrv/oddebug.d \
./hid_tutorial_1/usbdrv/usbdrv.d 

S_UPPER_DEPS += \
./hid_tutorial_1/usbdrv/usbdrvasm.d 

ASM_DEPS += \
./hid_tutorial_1/usbdrv/usbdrvasm.d 


# Each subdirectory must supply rules for building sources it contributes
hid_tutorial_1/usbdrv/%.o: ../hid_tutorial_1/usbdrv/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/Users/francispapineau/Documents/4th year project/Source Code/Black-Box-Mouse-Interface/Arduino ADK USB Host/arduino/cores/arduino" -I"/Users/francispapineau/Documents/4th year project/Source Code/Black-Box-Mouse-Interface/Arduino ADK USB Host/arduino/variants/mega" -Wall -g2 -gstabs -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

hid_tutorial_1/usbdrv/%.o: ../hid_tutorial_1/usbdrv/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Assembler'
	avr-gcc -x assembler-with-cpp -g2 -gstabs -mmcu=atmega16 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

hid_tutorial_1/usbdrv/%.o: ../hid_tutorial_1/usbdrv/%.asm
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Assembler'
	avr-gcc -x assembler-with-cpp -g2 -gstabs -mmcu=atmega16 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


