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

#define MAX_SENSORS				2
#define ON						1
#define OFF						0

#define ROUTER_ADDRESS 			0
#define MAX_SENSOR_ADDRESS 		8
#define BYTE_LENGTH				8

/*************************************************/
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
} watch_configs;

/*************************************************/

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
} enabled_sensors;

/*************************************************/

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
} network_sensors;

/*************************************************/

union {

	// the states in bit form
	struct {

		u8 on	 	: 1;
		u8 init		: 1;
		u8 run		: 1;
		u8 stop		: 1;
		u8 pause	: 1;
		u8 command	: 1;
		u8 error	: 1;
		u8 off		: 1;

	} state_bits;

	// The state as a byte
	u8 router_state_byte

} router_state;


/*************************************************/

typedef struct mouse_report_t{

	u8 buttons;   /*! Houses all the bits to toggle for each button. (8bits)*/
	u8 x;		/*! X axis analog values (8bits) */
	u8 y;		/*! Y axis analog values (8bits) */
	u8 wheel;	/*! Wheel analog values. (8bits) */

	// We need this to separate our data between the packets.
	u8 spacer;

}mouse_report;

/**
 * Creating a structure of variable data.
 * This is used to be able to vary the data from the
 * input parameters such as buttons (Setting them HIGH/LOW).
 */

typedef struct joystick_report_t{

 	u16 axis[NUM_AXES]; // 1 axis with 16 bits.
	u8 button[(NUM_BUTTONS)/8]; // 8 buttons per byte

	// We need this to separate our data between the packets.
	u8 spacer;

}joystick_report;

/*************************************************/

// The base station ID
linkID_t base_station_id;

// The sensor IDs
linkID_t sensors[MAX_SENSORS];

// Atomic mutex
bspIState_t intState;

struct sensor_info{

	u8 sensor_node_id;
	u32 sensor_runtime;
	u16 packet_id;

}sensor_info;

#endif /* CONFIGS_H_ */
