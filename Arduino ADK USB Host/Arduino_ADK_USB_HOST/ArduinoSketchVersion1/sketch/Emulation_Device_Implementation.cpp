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

	//! Set the random Seed
	randomSeed(analogRead(0));
}

//! Creates USB report frame
void* EMULATION_DEVICE::_create_usb_report_frame(){

	// Defining a generic pointer to return.
	void* report;
	
	
#ifdef MOUSE_REPORT

	mouse_report_t mouse_report;
	//! Setup the structure values
	mouse_report.buttons = random(255);
	mouse_report.wheel = random(255);
	mouse_report.x = random(255);
	mouse_report.y = random(255);
	report = &mouse_report;

#endif

#ifdef JOYSTICK_REPORT

	joystick_report_t joystick_report;

	/* Assign a random button value */
	for(uint8_t ind = 0; ind < NUM_BUTTONS/8; ind++){
		joystick_report.button[ind] = random(MAX_BUTTON_VAL);
	}
	
    /* Move all of the axes */
    for (uint8_t ind = 0; ind < NUM_AXES; ind++) {
    	joystick_report.axis[ind] = random(MAX_AXIS_VAL);
    }
	
	
	#ifdef DEBUG
	SERIAL_OUTPUT.println("--------");
	
	for(uint8_t ind = 0; ind < NUM_BUTTONS/8; ind++){
		word test_word = joystick_report.button[ind];
		SERIAL_OUTPUT.println(test_word);
	}
	for (uint8_t ind = 0; ind < NUM_AXES; ind++) {
		word test_word_axis = joystick_report.axis[ind];
		SERIAL_OUTPUT.println(test_word_axis);
	}
	SERIAL_OUTPUT.println("--------");
	#endif
	
	report = &joystick_report;
#endif

	_update_packet_id();
	_packet_in_sending_queue = true;
	return report;
}

//! Sends a USB report frame
void EMULATION_DEVICE::_send_usb_report_frame(void *report){

#ifdef MOUSE_REPORT

	//! Send the structure.
	SERIAL_OUTPUT.write((uint8_t*)&report, sizeof(mouse_report_t));
#endif

#ifdef JOYSTICK_REPORT

	//! Send the structure.
	SERIAL_OUTPUT.write((uint8_t*)&report, sizeof(joystick_report_t));
#endif

	_packet_in_sending_queue = false;
}

//! Update packet id
void EMULATION_DEVICE::_update_packet_id(){
	_packet_id ++;
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
		delay(100);
		
		//! Create a valid random USB Frame
		void* report = _create_usb_report_frame();
		
		//! Send the valid report
		_send_usb_report_frame(&report);
	}
}
