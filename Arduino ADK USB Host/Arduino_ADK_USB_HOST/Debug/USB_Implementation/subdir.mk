################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../USB_Implementation/USB_Functions.cpp 

OBJS += \
./USB_Implementation/USB_Functions.o 

CPP_DEPS += \
./USB_Implementation/USB_Functions.d 


# Each subdirectory must supply rules for building sources it contributes
USB_Implementation/%.o: ../USB_Implementation/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"C:\Program Files (x86)\Arduino\libraries" -I"C:\Users\fjpapin\workspace\USB_Device" -I"C:\Program Files (x86)\Arduino\hardware\tools\avr\avr\include" -I"C:\Program Files (x86)\Arduino\hardware\arduino\cores\arduino" -I"C:\Program Files (x86)\Arduino\hardware\arduino\variants\mega" -Wall -g2 -gstabs -Os -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -fno-exceptions -v -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


