/*
 * Emulation_Packet_Aseembler.cpp
 *
 *  Created on: Jul 13, 2013
 *      Author: francispapineau
 */

#include "Emulation_Device_Implementation.h"

static byte idle_rate = 500 / 4; // see HID1_11.pdf sect 7.2.4

//! Default Constructor
EMULATION_DEVICE::EMULATION_DEVICE(){
	//! Sending mutex
	_sending_mutex = false;

	//! Initializing the enviroment variables
	_packet_buffer = EMPTY;
	_packet_id = EMPTY;
	_packet_in_sending_queue = true;
	_button = 0;
	_packet_size = 0;
	_button = 0;

}

//! Creates USB report frame
void EMULATION_DEVICE::_create_usb_report_frame(){

#ifdef MOUSE_REPORT

	//! Setup the structure values
	mouse_report.buttons = random(255);
	mouse_report.wheel = random(255);
	mouse_report.x = random(255);
	mouse_report.y = random(255);

	//! Reassign the structure to send.
	_packet_buffer = &mouse_report;
#endif

#ifdef JOYSTICK_REPORT

    setButton(&joystick_report, _button);
    clearButton(&joystick_report, _button);

    /* Move all of the axes */
    for (uint8_t ind=0; ind<8; ind++) {
    	joystick_report.axis[ind] += 10 * (ind+1);
    }

	//! Reassign the structure to send.
	_packet_buffer = &joystick_report;

    _button++;
    if (_button >= 40) {
       _button = 0;
    }
#endif

	_update_packet_id();
	_packet_in_sending_queue = true;
}

//! Sends a USB report frame
void EMULATION_DEVICE::_send_usb_report_frame(){

#ifdef MOUSE_REPORT

	//! Send the structure.
	SERIAL_OUTPUT.write((uint8_t*)mouse_report, sizeof(mouse_report_t));
#endif

#ifdef JOYSTICK_REPORT

	//! Send the structure.
	SERIAL_OUTPUT.write((uint8_t*)joystick_report, sizeof(joystick_report_t));
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

// turn a button on
void setButton(joystick_report_t *joy, uint8_t button){
    uint8_t index = button/8;
    uint8_t bit = button - 8*index;

    joy->button[index] |= 1 << bit;
}

// turn a button off
void clearButton(joystick_report_t *joy, uint8_t button){
    uint8_t index = button/8;
    uint8_t bit = button - 8*index;

    joy->button[index] &= ~(1 << bit);
}

//! Emulates a USB interface
void EMULATION_DEVICE::emulate_usb(){

	//! Do this forever.
	while(1){

		//! Check to see if a report needs to be sent, using
		//! the idle rate.
		if ((TCNT1 > ((4 * (F_CPU / 1024000)) * idle_rate)
				|| TCNT1 > 0x7FFF) && idle_rate != 0) {

			//! Needs to send
			_sending_mutex = true;
		}else{

			//! Create a valid random USB Frame
			_create_usb_report_frame();
		}

		//! If we need to send.
		if(_sending_mutex){

			//! Send the report.
			//! and reset the timer.
			_send_usb_report_frame();
			TCNT1 = 0;
		}

		//! No need to send anymore.
		_sending_mutex = false;
	}
}
