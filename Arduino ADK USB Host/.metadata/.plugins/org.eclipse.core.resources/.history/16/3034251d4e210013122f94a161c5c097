################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../USB_HID_API/oddebug.c \
../USB_HID_API/usbdrv.c 

S_UPPER_SRCS += \
../USB_HID_API/usbdrvasm.S 

ASM_SRCS += \
../USB_HID_API/usbdrvasm.asm 

OBJS += \
./USB_HID_API/oddebug.o \
./USB_HID_API/usbdrv.o \
./USB_HID_API/usbdrvasm.o 

C_DEPS += \
./USB_HID_API/oddebug.d \
./USB_HID_API/usbdrv.d 

S_UPPER_DEPS += \
./USB_HID_API/usbdrvasm.d 

ASM_DEPS += \
./USB_HID_API/usbdrvasm.d 


# Each subdirectory must supply rules for building sources it contributes
USB_HID_API/%.o: ../USB_HID_API/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/Users/francispapineau/Documents/4th year project/Source Code/Black-Box-Mouse-Interface/Arduino ADK USB Host/arduino/cores/arduino" -I"/Users/francispapineau/Documents/4th year project/Source Code/Black-Box-Mouse-Interface/Arduino ADK USB Host/libraries" -I"/Users/francispapineau/Documents/4th year project/Source Code/Black-Box-Mouse-Interface/Arduino ADK USB Host/arduino/variants/mega" -Wall -g2 -gstabs -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

USB_HID_API/%.o: ../USB_HID_API/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Assembler'
	avr-gcc -x assembler-with-cpp -g2 -gstabs -mmcu=atmega16 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

USB_HID_API/%.o: ../USB_HID_API/%.asm
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Assembler'
	avr-gcc -x assembler-with-cpp -g2 -gstabs -mmcu=atmega16 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


