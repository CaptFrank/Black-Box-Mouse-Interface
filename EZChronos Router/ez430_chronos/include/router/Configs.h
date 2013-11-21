/*
 * Configs.h
 *
 *  Created on: Nov 20, 2013
 *      Author: francis-ccs
 */

#ifndef CONFIGS_H_
#define CONFIGS_H_

/**
 * This file contains the configs for the watch, in terms
 * of mouse or joystick selection.
 */


#define ROUTER_ADDRESS 			0
#define MAX_SENSOR_ADDRESS 		8

#define BYTE_LENGTH				8


// The general configs of the watch.
union {

	// the bit structure.
	struct {

		// Configure as either mouse or joystick
		u8 conf_mouse 		: 1;
		u8 conf_joystick 	: 1;

		// Configure the max amount of axis
		// Max = 0b11 = 3 axis;
		u8 max_axis			: 2;

		// Configure the max number of button
		// bytes, 8buttons per byte.
		// Max = 0b11 = 3*8 = 24 buttons.
		u8 max_button_bytes	: 2;

		// This enables the debug test of the mouse
		u8 conf_debug		: 1;

		// Future...
		u8 extra			: 1;

	}watch_configs_options;

	// Assign each config to a single byte.
	u8 watch_configs_flags;
}watch_configs;

union {

	// the bit structure.
	struct {

		u8 sensor_1 : 1;
		u8 sensor_2 : 1;
		u8 sensor_3 : 1;
		u8 sensor_4 : 1;
		u8 sensor_5 : 1;
		u8 sensor_6 : 1;
		u8 sensor_7 : 1;
		u8 sensor_8 : 1;

	}sensors;

	// Each flag is now defined as a byte
	u8 sensor_enable_flags;
}enabled_sensors;

union {

	// the bit structure.
	struct {

		u8 sensor_1 : 1;
		u8 sensor_2 : 1;
		u8 sensor_3 : 1;
		u8 sensor_4 : 1;
		u8 sensor_5 : 1;
		u8 sensor_6 : 1;
		u8 sensor_7 : 1;
		u8 sensor_8 : 1;

	}sensors;

	// Each flag is now defined as a byte
	u8 sensor_flags;
}network_sensors;



typedef struct mouse_report_t{

	byte buttons;   /*! Houses all the bits to toggle for each button. (8bits)*/
	int8_t x;		/*! X axis analog values (8bits) */
	int8_t y;		/*! Y axis analog values (8bits) */
	int8_t wheel;	/*! Wheel analog values. (8bits) */

	// We need this to separate our data between the packets.
	uint8_t spacer;

}mouse_report;;



/**
 * Creating a structure of variable data.
 * This is used to be able to vary the data from the
 * input parameters such as buttons (Setting them HIGH/LOW).
 */

typedef struct joystick_report_t{

 	int16_t axis[NUM_AXES]; // 1 axis with 16 bits.
	uint8_t button[(NUM_BUTTONS)/8]; // 8 buttons per byte

	// We need this to separate our data between the packets.
	uint8_t spacer;

}joystick_report;

#endif /* CONFIGS_H_ */
