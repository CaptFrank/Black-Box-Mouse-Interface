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
	avr-gcc -I"/Volumes/DataHDD/Documents/4th Year Project/Black-Box-Mouse-Interface/Arduino ADK USB Host/Arduino_ADK_USB_HOST" -I"/Volumes/DataHDD/Documents/4th Year Project/Black-Box-Mouse-Interface/Arduino ADK USB Host/Arduino_ADK_USB_HOST" -I"/Volumes/DataHDD/Documents/4th Year Project/Black-Box-Mouse-Interface/Arduino ADK USB Host/AVR_USB_Host" -I"/Volumes/DataHDD/Documents/4th Year Project/Black-Box-Mouse-Interface/Arduino ADK USB Host/libraries/EEPROM" -D__IN_ECLIPSE__=1 -DARDUINO=100 -DUSB_PID= -DUSB_VID= -Wall -Os -g -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

USB_HID_API/%.o: ../USB_HID_API/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Assembler'
	avr-gcc -x assembler-with-cpp -mmcu=atmega2560 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

USB_HID_API/%.o: ../USB_HID_API/%.asm
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Assembler'
	avr-gcc -x assembler-with-cpp -mmcu=atmega2560 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


