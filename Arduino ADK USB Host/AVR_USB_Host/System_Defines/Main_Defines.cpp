/*
 * Main_Defines.cpp
 *
 *  Created on: Jul 31, 2013
 *      Author: fjpapin
 */

#include "Main_Defines.h"
#include "Debug_API/Debug_LED_Function.h"


	//! Reset the device.
	void(*reset_device) (void) = 0; //declare reset function @ address 0

	/**
	 * This does a memory check of the whole system, and checks
	 * to see how much free mem there is.
	 */
	word memory_check(){
		word freemem;
		freemem = ((word)&freemem) - ((word)&__bss_end);
		return freemem;
	}

	/**
	 * This function is accessible throughout the code repo
	 * it allows the functions to return and terminate the process
	 * as an error.
	 */
	void error(void* line, void* function){

	//! Print if defined
	#ifdef DEBUG_SERIAL
		printf("[ERROR]: %d, %s", (int)line,  (char*)function);
	#endif
	#ifdef DEBUG_LEDs
		debug_api.print_error(FATAL, FATAL_ERROR);
		debug_api.set_leds(FATAL_ERROR);
	#endif
		//! Disconnect the device.
		usbDeviceDisconnect();
		command_interpreter.send_cmd(USB_DEVICE_CMD, (void*)PAUSE_ROUTER);
		send_frame(sizeof(AP_STOP), AP_STOP);
		send_frame(sizeof(AP_RESET), AP_RESET);
		usb_state_machine.move_state_to_local_error(usb_state_machine.current_state);

	#ifdef SELECT_BUTTON_2
		//! Infinite loop hangs the system
		for(;;);
	#endif
		reset_device();
	}

