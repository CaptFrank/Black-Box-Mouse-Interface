// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

//add your includes for the project Arduino_HID_Joystick here


//add your function definitions for the project Arduino_HID_Joystick here

//File System

#ifndef ARDUINO_HID_JOYSTICK_H_
#define ARDUINO_HID_JOYSTICK_H_

#include <HardwareSerial.h>

#include "EEPROM.h"
#include "NVRAM_API.h"
#include "Main_Defines.h"
#include "Hardware_Defines.h"
#include "Packet_Watchdog.h"
#include "Command_Interpreter.h"


#include "Packet_Handler.h"
#include "Packet_Parser.h"


#include "USB_Device_Implementation.h"
#include "USB_State_Machine.h"


#include "Emulation_Device_Implementation.h"
#include "Network_Protocol.h"


/**
 * This file contains all of the device DEFINE macros, and
 * also includes all of the libraries that are needed to
 * be references. All of the structures and classes are also
 * built by default in this header file.
 **/

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//~~~~~~~~~~~~~~~~~~~~ OBJECT DEFINITIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	//! Define an EEPROM object.
	EEPROMClass eeprom;

	//! Define an WATCHDOG object
	WATCHDOG watchdog;

	//! Define a common USB_STATE_MACHINE object
	USB_STATE_MACHINE usb_state_machine;

	//! Define an NVRAM object
	NVRAM nvram;

	//! Define an PACKET_PARSER object
	PACKET_PARSER packet_parser;

	//! Define a packet decoder function table.
	struct packet_handler_t packet_handlers[] = {

			//{/*PACKET ID*/, /*TARGET FUNCTION*/, /*OBJECT ADDRESS*/},

			//! Any packet will trigger this event.
			{PACKET_ANY,       	WATCHDOG::reset,        		&watchdog},

			//! Packet specific function tables for rx.
			{ROUTER_ACK,	   	PACKET_PARSER::parse, 			&packet_parser},
			{ROUTER_HEARTBEAT, 	PACKET_PARSER::parse, 			&packet_parser},
			{ROUTER_STATUS,    	PACKET_PARSER::parse, 			&packet_parser},
//			{ROUTER_NMAP,	   	PACKET_PARSER::parse, 			&packet_parser},
			{ROUTER_CONFIG,     PACKET_PARSER::parse, 			&packet_parser},
			{SENSOR_ENABLE,    	PACKET_PARSER::parse, 			&packet_parser},
			{SENSOR_CONFIGS,   	PACKET_PARSER::parse, 			&packet_parser},
			{SENSOR_DATA,      	PACKET_PARSER::parse, 			&packet_parser},
			{SENSOR_NUMBER,		PACKET_PARSER::parse,			&packet_parser},

			//! USB local device function calls
//			{USB_DEVICE_CMD,   PACKET_PARSER::parse,			&packet_parser},

			//! Optional
			{ROUTER_DEBUG,     PACKET_PARSER::parse, 			&packet_parser},
			{ERROR_MSG,        PACKET_PARSER::parse, 			&packet_parser}
	};

	//! Define a PACKET_DECODER object
	PACKET_HANDLER packet_decoder((void*)&packet_handlers);

	//! Define a COMMAND_INTERPRETER object
	COMMAND_PARSER command_interpreter(&nvram, &packet_decoder, &usb_state_machine);

	#ifdef DEBUG_LEDs
		//! Define a DEBUG_API object if debug.
		DEBUG_API debug_api;
	#endif

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//~~~~~~~~~~~~~~~~~~~~ VARIABLE DEFINITIONS ~~~~~~~~~~~~~~~~~~~~~~~~
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	//! A generic pointer to the chosen object.
	void* generic_pointer;

	//! The base station address
	byte base_station_address;

	//! The base station state machine mode
	byte base_station_mode;

	//! Define which device was chosen.
	byte emulation_chosen;
	byte usb_device_chosen;

#endif
