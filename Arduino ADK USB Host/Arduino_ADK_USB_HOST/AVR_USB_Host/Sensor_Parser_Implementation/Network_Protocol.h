/*
 * Network_Protocol.h
 *
 *  Created on: Jul 24, 2013
 *      Author: fjpapin
 */


//! Internal State Machine.

// ENABLES THE COMS DEBUG MESSAGES OVER SERIAL2;
#define ROUTER_COMS_DEBUG

//! Message IDs.
#define ROUTER_ACK				0x01
#define ROUTER_HEARTBEAT		0x02
#define ROUTER_STATUS			0x03
#define ROUTER_NMAP				0x04
#define ROUTER_CONFIG			0x05
#define SENSOR_ENABLE			0x06
#define SENSOR_CONFIGS			0x07
#define SENSOR_DATA				0x08
#define SENSOR_NUMBER			0x09
#define SENSOR_CHANNELS			0x0A

//! Command Descriptors
#define USB_DEVICE_CMD			0x31

//! Optional
#define ROUTER_DEBUG			0x07
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
struct packet_header_t {

	byte message_size;
	byte packet_id;
	byte node_id;
	byte sensor_id;
	uint32_t time_stamp;
	uint32_t sensor_run_time;
	byte packet_version;
};

// *************************************************
//! Router acknowledge message structure
struct router_ack_info_t {

	bool ack;
};

// *************************************************
//! The heartbeat sent to the ground station
//! THIS OCCURS EVERY 2 SECS
struct router_heartbeat_t {

	byte router_mode;
	byte battery_voltage;
};

// *************************************************
//! System status information
struct router_status_info_t {

	// general status
	byte power_state;
	byte router_mode;

	byte error_count;
	byte debug_enable_flag;
	byte battery_voltage;

	// device info
	byte router_address;
	String router_id;
};

#ifdef ROUTER_COMS_DEBUG
// *************************************************
//! If we are debugging structure
struct router_debug_status_t {

	// wireless debug
	word router_acks_sent_counter;
	word router_sent_request_counter;
	word router_packet_counter;
	word router_rx_count;
	word router_tx_count;
};
#endif
// *************************************************
//! We need to make this for each sensor
//! Network map object
struct router_nmap_info_t {

	byte sensor_id;
	byte sensor_address;

};

// *************************************************
struct router_sensor_enable_report_t {

	byte number_sensors;
	byte sensor_config_enable;
};

// *************************************************
struct error_message_t {

	byte sensor_id;
	byte sensor_address;
	byte error_code;
};

// *************************************************
//! This is the top level structure
class sensor_configs_t {

	//! For each sensor
		byte sensor_id;
		byte sensor_data_type; //! 0 = int, 2 = float, 3 = double
		byte data_size;
		byte number_of_channels;
};

// *************************************************
//! The container for each sensor input.
class remote_sensor_data_t {

	byte sensor_id;
	class channels_t {
		//! This is the structure containing each data point
		//! from each channel.
		byte channel_id;
		word channel_data;
	}channels[1];
};

// *************************************************
//! This is the remote radio configs.
struct remote_radio_configs_t {
	word values[8];
};

// *************************************************
//! This is the ack message for the number of sensors.
struct number_of_sensors_t {
	byte number_of_sensors;
};

// *************************************************
//! This is the ack message for the number of channels for a sensor.
struct number_of_channels_t {
	byte sensor_id;
	byte number_of_channels;
};


// *************************************************
// ************* LOCAL DOMAIN **********************
// *************************************************

//! This executes a command on the local system.
struct local_command_t {
	byte command_id;
	byte target_address;

};



