/* 
	Editor: http://www.visualmicro.com
	        arduino debugger, visual micro +, free forum and wiki
	
	Hardware: Arduino Mega 2560 or Mega ADK, Platform=avr, Package=arduino
*/

#define __AVR_ATmega2560__
#define _VMDEBUG 1
#define ARDUINO 101
#define ARDUINO_MAIN
#define F_CPU 16000000L
#define __AVR__
#define __cplusplus
extern "C" void __cxa_pure_virtual() {;}

//
//
void configure_device(NVRAM* nvram_object);

#include "C:\Program Files (x86)\Arduino\hardware\arduino\variants\mega\pins_arduino.h" 
#include "C:\Program Files (x86)\Arduino\hardware\arduino\cores\arduino\arduino.h"
#include "Z:\Black-Box-Mouse-Interface\Arduino ADK USB Host\Arduino_ADK_USB_HOST\ArduinoSketchVersion1\sketch\sketch.ino"
#include "Z:\Black-Box-Mouse-Interface\Arduino ADK USB Host\Arduino_ADK_USB_HOST\ArduinoSketchVersion1\sketch\Arduino_HID_Joystick.h"
#include "Z:\Black-Box-Mouse-Interface\Arduino ADK USB Host\Arduino_ADK_USB_HOST\ArduinoSketchVersion1\sketch\Command_Interpreter.cpp"
#include "Z:\Black-Box-Mouse-Interface\Arduino ADK USB Host\Arduino_ADK_USB_HOST\ArduinoSketchVersion1\sketch\Command_Interpreter.h"
#include "Z:\Black-Box-Mouse-Interface\Arduino ADK USB Host\Arduino_ADK_USB_HOST\ArduinoSketchVersion1\sketch\Debug_LED_Function.cpp"
#include "Z:\Black-Box-Mouse-Interface\Arduino ADK USB Host\Arduino_ADK_USB_HOST\ArduinoSketchVersion1\sketch\Debug_LED_Function.h"
#include "Z:\Black-Box-Mouse-Interface\Arduino ADK USB Host\Arduino_ADK_USB_HOST\ArduinoSketchVersion1\sketch\EEPROM.cpp"
#include "Z:\Black-Box-Mouse-Interface\Arduino ADK USB Host\Arduino_ADK_USB_HOST\ArduinoSketchVersion1\sketch\EEPROM.h"
#include "Z:\Black-Box-Mouse-Interface\Arduino ADK USB Host\Arduino_ADK_USB_HOST\ArduinoSketchVersion1\sketch\Emulation_Device_Implementation.cpp"
#include "Z:\Black-Box-Mouse-Interface\Arduino ADK USB Host\Arduino_ADK_USB_HOST\ArduinoSketchVersion1\sketch\Emulation_Device_Implementation.h"
#include "Z:\Black-Box-Mouse-Interface\Arduino ADK USB Host\Arduino_ADK_USB_HOST\ArduinoSketchVersion1\sketch\Hardware_Defines.h"
#include "Z:\Black-Box-Mouse-Interface\Arduino ADK USB Host\Arduino_ADK_USB_HOST\ArduinoSketchVersion1\sketch\Main_Defines.cpp"
#include "Z:\Black-Box-Mouse-Interface\Arduino ADK USB Host\Arduino_ADK_USB_HOST\ArduinoSketchVersion1\sketch\Main_Defines.h"
#include "Z:\Black-Box-Mouse-Interface\Arduino ADK USB Host\Arduino_ADK_USB_HOST\ArduinoSketchVersion1\sketch\NVRAM_API.cpp"
#include "Z:\Black-Box-Mouse-Interface\Arduino ADK USB Host\Arduino_ADK_USB_HOST\ArduinoSketchVersion1\sketch\NVRAM_API.h"
#include "Z:\Black-Box-Mouse-Interface\Arduino ADK USB Host\Arduino_ADK_USB_HOST\ArduinoSketchVersion1\sketch\Network_Protocol.h"
#include "Z:\Black-Box-Mouse-Interface\Arduino ADK USB Host\Arduino_ADK_USB_HOST\ArduinoSketchVersion1\sketch\Packet_Handler.cpp"
#include "Z:\Black-Box-Mouse-Interface\Arduino ADK USB Host\Arduino_ADK_USB_HOST\ArduinoSketchVersion1\sketch\Packet_Handler.h"
#include "Z:\Black-Box-Mouse-Interface\Arduino ADK USB Host\Arduino_ADK_USB_HOST\ArduinoSketchVersion1\sketch\Packet_Parser.cpp"
#include "Z:\Black-Box-Mouse-Interface\Arduino ADK USB Host\Arduino_ADK_USB_HOST\ArduinoSketchVersion1\sketch\Packet_Parser.h"
#include "Z:\Black-Box-Mouse-Interface\Arduino ADK USB Host\Arduino_ADK_USB_HOST\ArduinoSketchVersion1\sketch\Packet_Watchdog.cpp"
#include "Z:\Black-Box-Mouse-Interface\Arduino ADK USB Host\Arduino_ADK_USB_HOST\ArduinoSketchVersion1\sketch\Packet_Watchdog.h"
#include "Z:\Black-Box-Mouse-Interface\Arduino ADK USB Host\Arduino_ADK_USB_HOST\ArduinoSketchVersion1\sketch\USB_Device_Implementation.cpp"
#include "Z:\Black-Box-Mouse-Interface\Arduino ADK USB Host\Arduino_ADK_USB_HOST\ArduinoSketchVersion1\sketch\USB_Device_Implementation.h"
#include "Z:\Black-Box-Mouse-Interface\Arduino ADK USB Host\Arduino_ADK_USB_HOST\ArduinoSketchVersion1\sketch\USB_State_Machine.cpp"
#include "Z:\Black-Box-Mouse-Interface\Arduino ADK USB Host\Arduino_ADK_USB_HOST\ArduinoSketchVersion1\sketch\USB_State_Machine.h"
#include "Z:\Black-Box-Mouse-Interface\Arduino ADK USB Host\Arduino_ADK_USB_HOST\ArduinoSketchVersion1\sketch\USB_Structures.h"
