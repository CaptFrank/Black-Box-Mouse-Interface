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

#define MAX_SENSORS				0

#define ON						1
#define OFF						0

#define ROUTER_ADDRESS 			0
#define MAX_SENSOR_ADDRESS 		8
#define BYTE_LENGTH				8

#define PACKET_TIMEOUT			1000 // one second

/*************************************************
 * 			ROUTER STATES
 *************************************************/
#define ON_RESET				1
#define INIT					2
#define RUN						4
#define STOP					8
#define PAUSE					16
#define COMMAND					32
#define ERROR					64
#define OFF						128

u8 reset;

/**
 * This is the system integrity flag. It is used in
 * determining if the system has been compromised or not.
 * In other words it is set high when there is a fatal error
 * and the system has been compromised. To reset this flag,
 * you much reboot the device.
 */
struct {
	u8 system_intergrity_flag : 1;
}system_integrity_flag;

/**
 * This is the configs array, that contains each sensors
 * configurations, channels, channel types.
 */
struct {

	struct sensor_packet_header_t 	header;
	struct sensor_status_report_t 	status;
	struct sensor_configs_t			configs;
	struct sensor_error_t		 	error;
	struct sensor_data_struct_t 	data;
	struct sensor_sync_report_t		sync;

}sensor_configurations[8];

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
		u8 network_enable	: 1;

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

		u8 on	 	: 1; //1
		u8 init		: 1; //2
		u8 run		: 1; //4
		u8 stop		: 1; //8
		u8 pause	: 1; //16
		u8 command	: 1; //32
		u8 error	: 1; //64
		u8 off		: 1; //128

	} state_bits;

	// The state as a byte
	u8 router_state_byte;

} router_state;

/*************************************************/

struct debug_data_t{

	u16 router_acks_sent;
	u16 router_packet_counter;
	u16 router_rx_count;
	u16 router_sent_requests;
	u16 router_tx_count;
} debug_data;

/*************************************************/

struct mouse_report_t{

	u8 buttons; /*! Houses all the bits to toggle for each button. (8bits)*/
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

struct joystick_report_t{

 	u8 x; // 1 axis with 16 bits.
 	u8 y;
	u8 buttons; // 8 buttons per byte

	// We need this to separate our data between the packets.
	u8 spacer;

}joystick_report;

void* structure_choice;

// The choice of the device.
typedef enum {

	MOUSE,
	JOYSTICK,
	NONE
}structure_choice_t;
structure_choice_t choice;

/*************************************************/

// The base station ID
linkID_t base_station_id;

// Simpliciti id
// TODO
u8 simpliciti_ap_address[4];

// The sensor IDs
//	- Struct for data
struct sensor_t {
	u8 sync_time;
	u8 sensor_number;
	linkID_t sensor_link_id;
};

// Array for structures
struct sensor_t sensor_database_t[MAX_SENSORS];

// Atomic mutex
bspIState_t intState;


struct sensor_info{

	u8 sensor_node_id;
	u32 sensor_runtime;
	u16 packet_id;

}sensor_info;

#endif /* CONFIGS_H_ */
