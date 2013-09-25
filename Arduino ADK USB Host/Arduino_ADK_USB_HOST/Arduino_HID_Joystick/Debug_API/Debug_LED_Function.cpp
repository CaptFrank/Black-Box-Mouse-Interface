/*
 * Debug_LED_Function.cpp
 *
 *  Created on: Jul 13, 2013
 *      Author: francispapineau
 */

#ifdef DEBUG_LEDS
#include "Debug_LED_Function.h"
#include "../System_Defines/Hardware_Defines.h"
#include "../Debug_API/Debug_LED_Function.h"

//! Initialize the object
void DEBUG_API::DEBUG_API(){
	errors.warnings_errors = EMPTY;
	errors.memory_errors = EMPTY;
	errors.info_errors = EMPTY;
	errors.debug_errors = EMPTY;
	set_leds(CLEAR_ERRORS);
}

//! Reboot the device with a cause
void DEBUG_API::reboot_cause_error(byte cause){

	String string = "[%s]: Rebooting Device. ERR: %d, LED: %h";
	print_error(DEBUG_STRINGS[cause],
			DEBUG_CODES[cause],
			DEBUG_LED_CODES[cause],
			&string);
	reset_device();
}

//! This prints an error
void DEBUG_API::print_error(String error_type, byte error_code, byte error_led_code, String* string){


#ifdef DEBUG

	if(debug_set){
		char temp_string[sizeof(string) + 11];
			sprintf(temp_string, string->c_str(),
					error_type, error_code, error_led_code);

			DEBUG_PRINTLN(temp_string);
	}
#endif
			set_leds(error_code);
}


//! The public access to the print error method
void DEBUG_API::print_error(byte error_index, String* string){

#ifdef DEBUG
	if(debug_set){
		char temp_string[sizeof(string) + 11];
			sprintf(temp_string, string->c_str(),
					DEBUG_STRINGS[error_index],
					DEBUG_CODES[error_index],
					DEBUG_LED_CODES[error_index]);

			DEBUG_PRINTLN(temp_string);
	}
#endif
	set_leds(DEBUG_CODES[error_index]);

	switch(error_index){

		case WARNING:
			if ((errors.warnings_errors ++) > MAX_WARNINGS)
				reboot_cause_error(WARNING);
			break;
		case INFO:
			if((errors.info_errors ++) > MAX_INFO)
				reboot_cause_error(INFO);
			break;
		case DEBUG_LED:
			if((errors.debug_errors ++) > MAX_DEBUG)
				reboot_cause_error(DEBUG_LED);
			break;
		case MEMORY:
			if((errors.memory_errors ++) > MAX_MEMORY)
				reboot_cause_error(MEMORY);
			break;
		default:
			break;
	}
}

//! Enables the api
void DEBUG_API::enable_debug(){
	debug_set = true;
}

//! This disables the api
void DEBUG_API::disable_debug(){
	debug_set = false;
}

//! Get the number of errors
byte DEBUG_API::get_number_of(String error_index){

	switch(error_index){

		case WARNING:
			return errors.warnings_errors;
		case INFO:
			return errors.info_errors;
		case DEBUG_LED:
			return errors.debug_errors;
		case MEMORY:
			return errors.memory_errors;
		default:
			return EMPTY;
	}
}

//! This sets LEDS.
void DEBUG_API::set_leds(byte error_code){

	byte led_output = DEBUG_LED_CODES[error_code];

	digitalWrite(DBG_LED_1, (error_code & 0b0001));
	digitalWrite(DBG_LED_2, (((error_code & 0b0010) >> 1)));
	digitalWrite(DBG_LED_3,((error_code & 0b0100) >> 2));
	digitalWrite(DBG_LED_4,((error_code & 0b1000) >> 3));

}

//! This tests the leds
void DEBUG_API::test_leds(){

	//! turn them on...
	for(register byte i = 0; i < NUMBER_OF_LEDS; i++){
		digitalWrite(DBG_LED_1 + i, 0x01);
	}
	delay(500); //! delay

	//! Turn them off
	for(register byte i = NUMBER_OF_LEDS; i > NUMBER_OF_LEDS; i--){
		digitalWrite(DBG_LED_1 + i, 0x00);
	}
}
#endif


