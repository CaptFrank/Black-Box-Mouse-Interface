/*
 * router_network_utility.c
 *
 *  Created on: Nov 5, 2013
 *      Author: Francis Papineau
 */

#include "network_protocol.h"

#define ROUTER				0
#define PACKET_VER			A

#define PACKET_PREAMBLE		'+'

// Atomic mutex
bspIState_t intState;

// Function pointer table.
typedef struct {

	// Sends a router heartbeat packet
	void (*send_heartbeat)();

	// Sends an ack signal
	void (*ping_ack)();

	// Send the router status packet
	void (*send_router_status)();

	// Send the specific sensor status
	void (*send_sensor_status)(u8 sensor_id);

	// Send the router configs.
	void (*send_router_configs)();

	// Send the specified sensor configs.
	void (*send_sensor_configs)(u8 sensor_id);

	// Sends the network map...
	// Sends the max sensor address and the max
	// Sensor count
	void (*send_nmap)();

	// Sends the enabled sensors
	void (*send_sensor_enabled)();

	// Sends the number of sensors.
	void (*send_sensor_number)();

} router_network_utilities_t;

/* This is the packet structure union, which
 * holds divers structures needed to create the
 * divers network packets.
 */
union {

	struct packet_header_t 					_header;
	struct router_ack_info_t				_info;
	struct router_heartbeat_t				_heartbeat;
	struct router_status_info_t				_status;
	struct router_debug_status_t			_debug;
	struct router_nmap_info_t				_nmap;
	struct router_sensor_enable_report_t	_sensor_en;
	struct error_message_t					_error;
	struct remote_sensor_data_t				_remote_data;
	struct remote_radio_configs_t			_radio;
	struct number_of_sensors_t				_num_sensor;


}packet;


// sends a heartbeat
void send_hearbeat();

// sends an ack signal
void ping_ack();

// sends the router status
void send_router_status();

// sends the sensor status
void send_sensor_status();

// sends the router configs
void send_router_configs();

// sends the network map
void send_nmap();

// sends the sensors enabled
void send_sensor_enabled();

// sends the number of sensors active
void send_sensor_number();

// Internal sending function
void _send_packet(void* packet_ptr, u8 size);

