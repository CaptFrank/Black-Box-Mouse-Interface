/*
 * USB_Defines.h
 *
 *  Created on: Jul 12, 2013
 *      Author: fjpapin
 */

#ifndef USB_STRUCTURES_h_
#define USB_STRUCTURES_h_

#include "Hardware_Defines.h"

//static byte idle_rate = 500 / 4; // see HID1_11.pdf sect 7.2.4

/// If the mouse is chosen.
#ifdef MOUSE_REPORT

/**
 * Creating a structure of variable data.
 * This is used to be able to vary the data from the
 * input parameters such as buttons (Setting them HIGH/LOW).
 */

typedef struct mouse_report_t{

	byte buttons;   /*! Houses all the bits to toggle for each button. (8bits)*/
	int8_t x;		/*! X axis analog values (8bits) */
	int8_t y;		/*! Y axis analog values (8bits) */
	int8_t wheel;	/*! Wheel analog values. (8bits) */
	uint8_t spacer;
	
}mouse_report_t;

/// Defining a mouse_report_t structure.
//extern mouse_report_t mouse_report;

#endif

/// If the joystick is chosen
#ifdef JOYSTICK_REPORT

/**
 * Creating a structure of variable data.
 * This is used to be able to vary the data from the
 * input parameters such as buttons (Setting them HIGH/LOW).
 */

typedef struct joystick_report_t{

 	int16_t axis[NUM_AXES];
	uint8_t button[(NUM_BUTTONS)/8]; // 8 buttons per byte
	uint8_t spacer;
	
}joystick_report_t;


/// Defining a joystick_report_t structure.
//extern joystick_report_t joystick_report;

#endif

#endif /* USB_DEFINES_H_ */
