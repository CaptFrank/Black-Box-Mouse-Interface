/*
 * Main_Defines.h
 *
 *  Created on: Jul 10, 2013
 *      Author: francispapineau
 */

#include "System_Defines/Includes.h"
#include "Sensor_Parser_Implementation/Network_Protocol.h"


/**
 * This file contains all of the device DEFINE macros, and
 * also includes all of the libraries that are needed to
 * be references. All of the structures and classes are also
 * built by default in this header file.
 **/

extern "C" {
//! external reference to the end of the BSS for use in checking memory consumption
	extern word __bss_end;
}

 //! ONLY ONE OF THE FOLLOWING SHOULD BE CHOSEN!
 #define MOUSE_REPORT						//! Only send the Mouse USB report
 //#define JOYSTICK_REPORT					//! Only send the joystick USB report
 //#define MOUSE_JOYSTICK_REPORT			//! Send both joystick and mouse USb reports

//! This determines the sensor data maps
#define WATCH_ONLY
//#define WATCH_SENSOR_EMG
//#define WATCH_SENSOR_OTHER

//! Environment wide defines.
#define MAX_ROUTER_ERRORS	10
#define MIN_BATT_LEVEL		100
#define GOOD				1
#define FIVE_SECONDS		5000
#define EMPTY				0

#define MAX_WARNINGS 		10
#define MAX_INFO			INFINITY
#define MAX_DEBUG			INFINITY
#define MAX_MEMORY			10

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//~~~~~~~~~~~~~~~~~~~~ OBJECT DEFINITIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	//! Define an EEPROM object.
	EEPROM eeprom;

	//! Define an NVRAM object
	NVRAM nvram;

	//! Define an WATCHDOG object
	WATCHDOG watchdog;

	//! Define an PACKET_PARSER object
	PACKET_PARSER packet_parser;

	//! Define a COMMAND_INTERPRETER object
	COMMAND_INTERPRETER command_interpreter(&nvram);

	//! Define a common USB_STATE_MACHINE object
	USB_STATE_MACHINE usb_state_machine;

	//! Define a packet decoder function table.
	struct packet_handler packet_handlers[13] = {

			//{/*PACKET ID*/, /*TARGET FUNCTION*/, /*OBJECT ADDRESS*/},

			//! Any packet will trigger this event.
			{PACKET_ANY,       	WATCHDOG::reset,        		&watchdog},

			//! Packet specific function tables for rx.
			{ROUTER_ACK,	   	PACKET_PARSER::parse, 			&packet_parser},
			{ROUTER_HEARTBEAT, 	PACKET_PARSER::parse, 			&packet_parser},
			{ROUTER_STATUS,    	PACKET_PARSER::parse, 			&packet_parser},
			{ROUTER_NMAP,	   	PACKET_PARSER::parse, 			&packet_parser},
			{ROUTER_CONFIG,     PACKET_PARSER::parse, 			&packet_parser},
			{SENSOR_ENABLE,    	PACKET_PARSER::parse, 			&packet_parser},
			{SENSOR_CONFIGS,   	PACKET_PARSER::parse, 			&packet_parser},
			{SENSOR_DATA,      	PACKET_PARSER::parse, 			&packet_parser},
			{SENSOR_NUMBER,		PACKET_PARSER::parse,			&packet_parser},

			//! USB local device function calls
			{USB_DEVICE_CMD,   PACKET_PARSER::parse,			&packet_parser},

			//! Optional
			{ROUTER_DEBUG,     PACKET_PARSER::parse, 			&packet_parser},
			{ERROR_MSG,        PACKET_PARSER::parse, 			&packet_parser}
	};

	//! Define a PACKET_DECODER object
	PACKET_DECODER packet_decoder(packet_handlers);

	#ifdef DEBUG_LEDs
		//! Define a DEBUG_API object if debug.
		DEBUG_API debug_api;
		error_type_counts_t error_type_counts;
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

	//! Cached structs to keep
	router_nmap_info_t* nmap;
	sensor_configs_t* configs;
	remote_sensor_data_t* data;

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//~~~~~~~~~~~~~~~~~~~~ FUNCTION DEFINITIONS ~~~~~~~~~~~~~~~~~~~~~~~~
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	//! Reset the device.
	void(*reset_device) (void) = 0; //declare reset function @ address 0

	/**
	 * This does a memory check of the whole system, and checks
	 * to see how much free mem there is.
	 */
	word memory_check();

	/**
	 * This function is accessible throughout the code repo
	 * it allows the functions to return and terminate the process
	 * as an error.
	 */
	void error(void* line, void* function);
