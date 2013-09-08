################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Sensor_Parser_Implementation/USB_Sender/USB_Sender_Utils.cpp 

OBJS += \
./Sensor_Parser_Implementation/USB_Sender/USB_Sender_Utils.o 

CPP_DEPS += \
./Sensor_Parser_Implementation/USB_Sender/USB_Sender_Utils.d 


# Each subdirectory must supply rules for building sources it contributes
Sensor_Parser_Implementation/USB_Sender/%.o: ../Sensor_Parser_Implementation/USB_Sender/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/Volumes/DataHDD/Documents/4th Year Project/Black-Box-Mouse-Interface/Arduino ADK USB Host/Arduino_ADK_USB_HOST" -I"/Volumes/DataHDD/Documents/4th Year Project/Black-Box-Mouse-Interface/Arduino ADK USB Host/Arduino_ADK_USB_HOST" -I"/Volumes/DataHDD/Documents/4th Year Project/Black-Box-Mouse-Interface/Arduino ADK USB Host/AVR_USB_Host" -D__IN_ECLIPSE__=1 -DUSB_VID= -DUSB_PID= -DARDUINO=100 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '


