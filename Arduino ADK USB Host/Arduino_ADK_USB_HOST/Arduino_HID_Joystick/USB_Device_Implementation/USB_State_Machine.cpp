/*
 * Parser_State_Machine.cpp
 *
 *  Created on: Jul 24, 2013
 *      Author: fjpapin
 */

#include "USB_State_Machine.h"

//! Setup the state machine
USB_STATE_MACHINE::USB_STATE_MACHINE(){

	reset_device = (void) 0;
	current_state = LOCAL_DEVICE_SETUP;
	next_state = current_state ++;
}

//! Move backwards
void USB_STATE_MACHINE::move_state_backwards(){

	next_state = current_state;
	current_state --;
}

//! Move forawards
void USB_STATE_MACHINE::move_state_forward(){

	current_state = next_state;
	next_state ++;
	if(next_state == 7){
		next_state = LOCAL_RESET;
	}
}

//! Move to local error
void USB_STATE_MACHINE::move_state_to_local_error(byte previous_state){

	current_state = LOCAL_ERROR_MODE(previous_state);
	next_state = LOCAL_RESET;
}

//! Move to local reset
void USB_STATE_MACHINE::move_state_to_local_reset(){

	current_state = LOCAL_RESET;
	next_state = NULL;
}

//! Move to network error
void USB_STATE_MACHINE::move_state_to_network_error(byte previous_state){

	current_state = NETWORK_ERROR_MODE(previous_state);
	next_state = NETWORK_RESET;
	#ifdef DEBUG_LEDs
		debug_api.set_leds(FATAL_ERROR);
	#endif
	error((void*)__LINE__, (void*)__func__);
}

//! Move to network reset
void USB_STATE_MACHINE::move_state_to_network_reset(){

	current_state = NETWORK_RESET;
	next_state = NULL;
	#ifdef DEBUG_LEDs
		debug_api.set_leds(FATAL_ERROR);
	#endif
	error((void*)__LINE__, (void*)__func__);
}

//! Gets the current state
byte USB_STATE_MACHINE::get_current_state(){

	return current_state;
}
