/*
 * network_protocol_router_sensor.h
 *
 *  Created on: Nov 29, 2013
 *      Author: francis-ccs
 */

#ifndef NETWORK_PROTOCOL_ROUTER_SENSOR_H_
#define NETWORK_PROTOCOL_ROUTER_SENSOR_H_

#include "Configs.h"

/**
 * These are the possible commands the router
 * can send.
 */
#define PING						0x01
#define CONFIG_REQ					0x02
#define STATUS_REQ					0x03

/**
 * The sync command is structured as follows:
 * 	- 0x04, time to sync, heartbeat freq
 */
#define SYNC						0x04
#define START						0x05
#define STOP						0x06
#define ABORT						0x07
#define ERROR						0x08
#define PAUSE						0x09

#define HEARTBEAT_FREQ				0x01
#define PACKET_FORMAT				0x03
#define COMMAND_PREAMBLE			'@'
#define COMMAND_TAIL				0x0A

// Possible reports received
#define SENSOR_ACK					0x14
#define SENSOR_CONFIG_REPORT		0x15
#define SENSOR_STATUS_REPORT		0x16
#define SENSOR_DATA_REPORT			0x17
#define SENSOR_SYNC_REPORT			0x18
#define SENSOR_HEARTBEAT_REPORT		0x19
#define SENSOR_ERROR_REPORT			0x20

// *************************************************
// *************** REMOTE DOMAIN *******************
// *************************************************

typedef struct sensor_packet_header_t {

	u8 message_size;
	u8 packet_id;
	u8 sensor_id;
	u32 sensor_run_time;
	u8 packet_version;
};

// *************************************************
//! Sensor acknowledge message structure
//!	- 0/1 true of false
typedef struct sensor_ack_info_t {

	bool ack;
};

//! Sensor configs report
//! - [sensor type][# of channels][channel types]
//! 	- [A, D][0 - 8][0,0,1,1,1,0,0,0]
typedef struct sensor_configs_t {

	u8 sensor_type;
	u8 num_channels;
	u8 channel_types;
};

//! Sensor status report
//! - [STATE]
//! - 1 - OK
//! - 2 - FAIL
//! - 3 - ERROR
//! - 4 - BOOT
//! - 5 - REBOOT
//!	- 6 - RESET
//! - 7 - N/A
//! - 8 - N/A
typedef struct sensor_status_report_t {

	u8 state;
};

//! Sensor data report
//! - [channel data][channel data][...]
//! - 8*8 bits - max value 0 -> 255
typedef struct sensor_data_struct_t {

	u8 data_array[8];
};

//! Sensor sync report
typedef struct sensor_sync_report_t {

	u16 sync_time;

	u8 interrupt_number;
	u8 priority;

};

//! Sensor heartbeat report
typedef struct sensor_heartbeat_t {

	u8 router_mode;
	u16 battery_voltage;
};


//! Sensor error report
//! - Error codes
//! - 1 - Boot error
//! - 2 - Memory error
//! - 3 - Runtime error
//! - 4 - Sync error
//! - 5 - Packet format error
//!	- 6 - Interrupt error
//! - 7 - Reset error
//! - 8 - Sut-down error
typedef struct sensor_error_t {

	u8 error_code;
};

#endif /* NETWORK_PROTOCOL_ROUTER_SENSOR_H_ */
