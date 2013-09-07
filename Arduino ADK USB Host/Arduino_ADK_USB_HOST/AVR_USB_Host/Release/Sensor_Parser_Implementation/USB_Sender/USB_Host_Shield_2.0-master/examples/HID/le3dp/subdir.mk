################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Sensor_Parser_Implementation/USB_Sender/USB_Host_Shield_2.0-master/examples/HID/le3dp/le3dp_rptparser.cpp 

OBJS += \
./Sensor_Parser_Implementation/USB_Sender/USB_Host_Shield_2.0-master/examples/HID/le3dp/le3dp_rptparser.o 

CPP_DEPS += \
./Sensor_Parser_Implementation/USB_Sender/USB_Host_Shield_2.0-master/examples/HID/le3dp/le3dp_rptparser.d 


# Each subdirectory must supply rules for building sources it contributes
Sensor_Parser_Implementation/USB_Sender/USB_Host_Shield_2.0-master/examples/HID/le3dp/%.o: ../Sensor_Parser_Implementation/USB_Sender/USB_Host_Shield_2.0-master/examples/HID/le3dp/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/Applications/Development/Arduino.app/Contents/Resources/Java/hardware/arduino/cores/arduino" -I"/Applications/Development/Arduino.app/Contents/Resources/Java/hardware/arduino/variants/mega" -I"/Volumes/DataHDD/Documents/4th Year Project/Black-Box-Mouse-Interface/Arduino ADK USB Host/Arduino_ADK_USB_HOST/AVR_USB_Host" -D__IN_ECLIPSE__=1 -DUSB_VID= -DUSB_PID= -DARDUINO=100 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '


