/*
 * Emulation_Packet_Aseembler.cpp
 *
 *  Created on: Jul 13, 2013
 *      Author: francispapineau
 */

#include "Emulation_Device_Implementation.h"

//! Default Constructor
EMULATION_DEVICE::EMULATION_DEVICE(){
	//! Initializing the enviroment variables
	_packet_buffer = EMPTY;
	_packet_id = EMPTY;
	_packet_in_sending_queue = true;
	_packet_size = 0;

	_clear_report();

	//! Set the random Seed
	randomSeed(analogRead(0));
}

//! Creates USB report frame
void EMULATION_DEVICE::_create_usb_report_frame(){

#ifdef MOUSE_REPORT

	//! Setup the structure values
	mouse_report.buttons = random(255);
	mouse_report.wheel = random(255);
	mouse_report.x = random(255);
	mouse_report.y = random(255);

#endif

#ifdef JOYSTICK_REPORT

	/* Assign a random button value */
	for(uint8_t ind = 0; ind < NUM_BUTTONS/8; ind++){
		byte button_test = this->joystick_report.button[ind] = (uint8_t)random(MAX_BUTTON_VAL);
	}
	
    /* Move all of the axes */
    for (uint16_t ind = 0; ind < NUM_AXES; ind++) {
    	word axis_test = this->joystick_report.axis[ind] = (uint16_t)random(MAX_AXIS_VAL);
		SERIAL_OUTPUT.println(this->joystick_report.axis[ind]);
    }
	
	#ifdef DEBUG
	SERIAL_OUTPUT.println("--------");
	
	for(uint8_t ind = 0; ind < NUM_BUTTONS/8; ind++){
		word test_word = this->joystick_report.button[ind];
		SERIAL_OUTPUT.println(test_word);
	}
	for (uint16_t ind = 0; ind < NUM_AXES; ind++) {
		word test_word_axis = this->joystick_report.axis[ind];
		SERIAL_OUTPUT.println(test_word_axis);
	}
	SERIAL_OUTPUT.println("--------");
	
	#endif
#endif

	_update_packet_id();
	_packet_in_sending_queue = true;
}

//! Sends a USB report frame
void EMULATION_DEVICE::_send_usb_report_frame(void *report){

#ifdef MOUSE_REPORT

	//! Send the structure.
	SERIAL_OUTPUT.write((uint8_t*)report, sizeof(mouse_report_t));
#endif

#ifdef JOYSTICK_REPORT

	//! Send the structure.
	SERIAL_OUTPUT.write((uint8_t*)report, sizeof(joystick_report_t));
#endif

	_packet_in_sending_queue = false;
}

//! Update packet id
void EMULATION_DEVICE::_update_packet_id(){
	_packet_id ++;
}

//! Clears the report
void EMULATION_DEVICE::_clear_report(){
	#ifdef JOYSTICK_REPORT
	/* Assign a random button value */
	for(uint8_t ind = 0; ind < NUM_BUTTONS/8; ind++){
		this->joystick_report.button[ind] = 0;
	}
			
	/* Move all of the axes */
	for (uint8_t ind = 0; ind < NUM_AXES; ind++) {
		this->joystick_report.axis[ind] = 0;
	}
	#endif
	
	#ifdef MOUSE_REPORT
		mouse_report.buttons = 0;
		mouse_report.wheel = 0;
		mouse_report.x = 0;
		mouse_report.y = 0;
	#endif
}

//! Gets a packet id
word EMULATION_DEVICE::get_packet_id(){
	return (word)_packet_id;
}

//! Emulates a USB interface
void EMULATION_DEVICE::emulate_usb(){

	#ifdef DEBUG
		SERIAL_OUTPUT.println("RUNNING EMULATION");
	#endif
	
	//! Do this forever.
	while(1){

		//! Delay the sending of the frame.
		delay(500);
		
		//! Create a valid random USB Frame
		_create_usb_report_frame();
		
		//! Send the valid report
		_send_usb_report_frame(&joystick_report);
		
		//! Clears teh structure
		_clear_report();
	}
}
