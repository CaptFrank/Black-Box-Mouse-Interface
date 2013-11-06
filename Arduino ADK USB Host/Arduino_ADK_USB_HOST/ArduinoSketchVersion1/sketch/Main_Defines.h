/*
 * Main_Defines.h
 *
 *  Created on: Jul 10, 2013
 *      Author: francispapineau
 */

//#include "./Includes.h"

#ifndef MAIN_DEFINES_h_
#define MAIN_DEFINES_h_

//USB Implementation
#include "Network_Protocol.h"
#include <Arduino.h>

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//~~~~~~~~~~~~~~~~~~~~ FUNCTION DEFINITIONS ~~~~~~~~~~~~~~~~~~~~~~~~
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	//! Reset the device.
	static void(*reset_device) (void) = 0; //declare reset function @ address 0

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
	static inline void error(void* line, void* function){

	//! Print if defined
	#ifdef DEBUG_SERIAL
		printf("[ERROR]: %d, %s", (int)line,  (char*)function);
	#endif
	#ifdef DEBUG_LEDs
		debug_api.print_error(FATAL, FATAL_ERROR);
		debug_api.set_leds(FATAL_ERROR);
	#endif

	#ifndef DEBUG
		command_interpreter.send_cmd(USB_DEVICE_CMD, (void*)PAUSE_ROUTER);
		usb_state_machine.move_state_to_local_error(usb_state_machine.current_state);
	#endif

	#ifdef SELECT_BUTTON_2
		//! Infinite loop hangs the system
		for(;;);
	#endif
		reset_device();
	}

#endif
