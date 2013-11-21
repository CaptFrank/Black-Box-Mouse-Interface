
/**
 * Network_Protocol.h
 */

#ifndef _Network_Protocol_h_
#define _Network_Protocol_h_

#include "Configs.h"

/**
 * This file contains the types of packets the router,
 * can send to the ground station. This conforms to the
 * basestation -> router protocol. These packet definitions
 * can be refered to the following.
 *
 * 	- This protocol is specific to only the base station
 * 		and the router.
 */

//! Message IDs.
#define ROUTER_ACK				0x01
#define ROUTER_HEARTBEAT		0x02
#define ROUTER_STATUS			0x03
#define ROUTER_NMAP				0x04
#define ROUTER_CONFIG			0x05

//! Optional
#define ROUTER_DEBUG			0x0B
#define ERROR_MSG				0x0A

//! Internal packet_id values
#define PACKET_ANY				0xFE
#define PACKET_NULL				0xFF

//! Router modes
#define ERROR_MODE				0xFF
#define PWR_ERROR_MODE			0xFE

// *************************************************
// *************** REMOTE DOMAIN *******************
// *************************************************

//! Main packet header structure.
typedef struct packet_header_t {

	u8 message_size;
	u8 packet_id;
	u8 node_id;
	u8 sensor_id;
	u32 time_stamp;
	u32 sensor_run_time;
	u8 packet_version;
};

// *************************************************
//! Router acknowledge message structure
typedef struct router_ack_info_t {
	bool ack;
};

// *************************************************
//! The heartbeat sent to the ground station
//! THIS OCCURS EVERY 2 SECS
typedef struct router_heartbeat_t {

	u8 router_mode;
	u16 battery_voltage;
};

// *************************************************
//! System status information
typedef struct router_status_info_t {

	// general status
	u8 power_state;
	u8 router_mode;

	u8 error_count;
	u8 debug_enable_flag;
	u16 battery_voltage;

	// device info
	u8 router_address;
};

// *************************************************
//! If we are debugging structure
typedef struct router_debug_status_t {

	// wireless debug
	u16 router_acks_sent_counter;
	u16 router_sent_request_counter;
	u16 router_packet_counter;
	u16 router_rx_count;
	u16 router_tx_count;
};
// *************************************************
//! We need to make this for each sensor
//! Network map object
typedef struct router_nmap_info_t {

	u8 max_sensor_id;
	u8 max_sensor_address;
	u8 en_sensors;

};

// *************************************************
typedef struct router_sensor_enable_report_t {

	u8 number_sensors;
	u8 sensor_config_enable;
	u8 en_sensors;
};

// *************************************************
typedef struct error_message_t {

	u8 sensor_id;
	u8 sensor_address;
	u8 error_code;
};

// *************************************************
// DEPRECATED
////! This is the top level structure
//typedef struct sensor_configs_t {
//
//	/*
//	 * regardless of the sensors, the router only sends
//	 * the size of the packets the base station.
//	 */
//	u8 data_pkt_size;
//};

// *************************************************
//! The container for each sensor input.
typedef struct remote_sensor_data_t {

	void* data_struct;
	u8 data_len;
};

// *************************************************
//! This is the remote radio configs.
typedef struct remote_radio_configs_t {
	u8 values[4];
};

// *************************************************
//! This is the ack message for the number of sensors.
typedef struct number_of_sensors_t {
	u8 number_of_sensors;
};

#endif






