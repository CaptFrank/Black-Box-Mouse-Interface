/*
 * Includes.h
 *
 *  Created on: Aug 30, 2013
 *      Author: francispapineau
 */

#ifndef INCLUDES_H_
#define INCLUDES_H_

//File System
#include <Arduino.h>
#include <EEPROM/EEPROM.h>
#include <HardwareSerial.h>
#include <avr/pgmspace.h>

//System Defines
#include "./Command_Interpreter.h"
#include "./Hardware_Defines.h"
#include "./NVRAM_API.h"
#include "./Packet_Watchdog.h"

//USB Implementation
#include "../USB_Implementation/USB_Reports.h"
#include "../USB_Implementation/USB_Functions.h"

//USB HID API
#include "../USB_HID_API/usbconfig.h"
#include "../USB_HID_API/usbdrv.h"

//USB Device Implementation
#include "../USB_Device_Implementation/USB_Device_Implementation.h"
#include "../USB_Device_Implementation/USB_State_Machine.h"

//Sensor Parser Implementation
#include "../Sensor_Parser_Implementation/Network_Protocol.h"
#include "../Sensor_Parser_Implementation/Packet_Handler.h"
#include "../Sensor_Parser_Implementation/Packet_Parser.h"
#include "../Sensor_Parser_Implementation/USB_Sender/USB_Sender_Utils.h"
#include "../Sensor_Parser_Implementation/USB_Sender/USB_Host_Shield_2.0-master/cdcacm.h"

//Emulation Device Implementation
#include "../Emulation_Device_Implementation/Emulation_Device_Implementation.h"

//Debug API
#include "../Debug_API/Debug_LED_Function.h"


#endif /* INCLUDES_H_ */
