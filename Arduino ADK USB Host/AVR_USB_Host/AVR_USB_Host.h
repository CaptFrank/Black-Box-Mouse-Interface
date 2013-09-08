// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef AVR_USB_Host_H_
#define AVR_USB_Host_H_
#include "Arduino.h"
//add your includes for the project AVR_USB_Host here

//File System
#include <Arduino.h>
#include <EEPROM/EEPROM.h>
#include <HardwareSerial.h>
#include <avr/pgmspace.h>
#include <avr/io.h>

#include "System_Defines/Hardware_Defines.h"
#include "Debug_API/Debug_LED_Function.h"
#include "USB_Implementation/USB_Reports.h"
#include "USB_Implementation/USB_Functions.h"
#include "System_Defines/Main_Defines.h"
#include "../USB_Device_Implementation/USB_Device_Implementation.h"

//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
extern word __bss_end;

#ifdef __cplusplus
} // extern "C"
#endif

//add your function definitions for the project AVR_USB_Host here




//Do not add code below this line
#endif /* AVR_USB_Host_H_ */