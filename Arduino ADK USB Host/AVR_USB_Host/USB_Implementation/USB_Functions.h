/*
 * USB_Defines.h
 *
 *  Created on: Jul 12, 2013
 *      Author: fjpapin
 */

#ifndef USB_DEFINES_H_
#define USB_DEFINES_H_

#include "../USB_HID_API/usbconfig.h"
#include "../USB_HID_API/usbdrv.h"
#include "../System_Defines/Hardware_Defines.h"


static uint8_t idle_rate = 500 / 4; // see HID1_11.pdf sect 7.2.4
static uint8_t protocol_version = 0; // see HID1_11.pdf sect 7.2.6

/// If the mouse is chosen.
#ifdef MOUSE_REPORT

/**
 * Creating a structure of variable data.
 * This is used to be able to vary the data from the
 * input parameters such as buttons (Setting them HIGH/LOW).
 */
struct mouse_report_t {

	uint8_t report_id; /*! the REPORT_ID of the message (8bits)*/
	uint8_t buttons;   /*! Houses all the bits to toggle for each button. (8bits)*/
	int8_t x;		/*! X axis analog values (8bits) */
	int8_t y;		/*! Y axis analog values (8bits) */
	int8_t wheel;	/*! Wheel analog values. (8bits) */
};

/// Defining a mouse_report_t structure.
static mouse_report_t mouse_report;

/**
 * Sends a USB report of the mouse structure only.
 * @param report - mouse_report_t
 */
void send_mouse_report(mouse_report_t* report);
#endif

/// If the joystick is chosen
#ifdef JOYSTICK_REPORT

/**
 * Creating a structure of variable data.
 * This is used to be able to vary the data from the
 * input parameters such as buttons (Setting them HIGH/LOW).
 */
struct joystick_report_t {

	byte report_id; /*! the REPORT_ID of the message (8bits)*/
	int16_t x;		/*! X axis analog values (16bits) */
	int16_t y;		/*! Y axis analog values (16bits) */
	byte buttons;	/*! Houses all the bits to toggle for each button. (8bits)*/

};

/// Defining a joystick_report_t structure
static joystick_report_t joystick_report;

/**
 * Sends a USB report of the joystick structure only.
 * @param report - joystick_report_t
 */
void send_joystick_report(joystick_report_t* report);

#endif

/**
 * Creating a structure of variable data.
 * This is used to be able to vary the data from the
 * input parameters such as buttons (Setting them HIGH/LOW).
 */
#ifdef MOUSE_JOYSTICK_REPORT
struct joystick_mouse_report_t {

	/**
	 * Combining the above structs together
	 * to form an uber structure.
	 */
	mouse_report_t mouse;
	joystick_report_t joystick;

} ;

/// Defining a joystick_mouse_report_t structure
static joystick_mouse_report_t joystick_mouse_report;

/**
 * Sends a USB report of the joystick and mouse structure only.
 * @param report - joystick_mouse_report
 */
void send_mouse_joystick_report(joystick_mouse_report_t* report);
#endif

#endif /* USB_DEFINES_H_ */
