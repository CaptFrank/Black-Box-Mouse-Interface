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
	_button = 0;
	_packet_size = 0;
	_button = 0;

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

	for(uint8_t ind = 0; ind <= NUM_BUTTONS/8; ind++){
		joystick_report.button[ind] <<= 1;
		joystick_report.button[ind] |= (uint8_t)1;
	}

    /* Move all of the axes */
    for (uint8_t ind = 0; ind < NUM_AXES; ind++) {
    	joystick_report.axis[ind] = random(255);
    }

	#ifdef DEBUG
	DEBUG_SERIAL.println("--------");
	for(uint8_t ind = 0; ind <= NUM_BUTTONS/8; ind++){
		SERIAL_OUTPUT.println(joystick_report.button[ind]);
	}
	for (uint8_t ind = 0; ind < NUM_AXES; ind++) {
		SERIAL_OUTPUT.println(joystick_report.axis[ind]);
	}
	DEBUG_SERIAL.println("--------");
	#endif

    _button++;
    if (_button >= NUM_BUTTONS) {
       _button = 0;
	   
		for(uint8_t ind = 0; ind < NUM_BUTTONS/8; ind++){
			joystick_report.button[ind] = 0;
		}
    }
#endif

	_update_packet_id();
	_packet_in_sending_queue = true;
}

//! Sends a USB report frame
void EMULATION_DEVICE::_send_usb_report_frame(){

#ifdef MOUSE_REPORT

	//! Send the structure.
	SERIAL_OUTPUT.write((uint8_t*)&mouse_report, sizeof(mouse_report_t));
#endif

#ifdef JOYSTICK_REPORT

	//! Send the structure.
	SERIAL_OUTPUT.write((uint8_t*)&joystick_report, sizeof(joystick_report_t));
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
		delay(500);
		
		//! Create a valid random USB Frame
		_create_usb_report_frame();
		
		//! Send the valid report
		_send_usb_report_frame();
	}
}
