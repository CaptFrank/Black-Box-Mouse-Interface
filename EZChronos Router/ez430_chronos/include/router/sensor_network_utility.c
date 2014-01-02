/*
 * network_utility.c
 *
 *  Created on: Nov 5, 2013
 *      Author: Francis Papineau
 */

#include "sensor_network_utility.h"
#include "callback_functions.h"
#include "error_handler.h"
#include "nwk_types.h"
#include "utilities.h"



/**
 * These are the needed application level
 * executions for each command.
 *
 * NOTE: the general structure on how the messages
 * will be passed with regards to the sensor and the
 * router is as follows.
 *
 * 	- [@][header][Message Value][Tail]
 * 	- '-''@''0x01''0x0A'
 */

// Pings a sensor
void ping_ack(linkID_t id){

	// First ping @ the hw layer
	SMPL_Ping(id);

	// Setup the ping command
	u8 cmd [] = {PING};

	// Send it off
	_send_command(id, cmd, sizeof(cmd));

	// Receive the response
	receiver_utilities.receive_sensor_response(id);
}

// Sends a config request
void send_config_req(linkID_t id){

	// Set the config request
	u8 cmd [] = {CONFIG_REQ};

	debug_data.router_sent_requests ++;

	// Send it off
	_send_command(id, cmd, sizeof(cmd));

	// Receive the response
	receiver_utilities.receive_sensor_response(id);
}

// Sends a status request
void send_status_req(linkID_t id){

	// Setup the status request command
	u8 cmd [] = {STATUS_REQ};

	debug_data.router_sent_requests ++;

	// Send it off
	_send_command(id, cmd, sizeof(cmd));

	// Receive the response
	receiver_utilities.receive_sensor_response(id);
}

// Sends a sync message
void send_sync(linkID_t id){

	// Setup the Sync Command
	u8 cmd [] = {SYNC, id, HEARTBEAT_FREQ + id};

	// Send it off
	_send_command(id, cmd, sizeof(cmd));

	// Receive the response
	receiver_utilities.receive_sensor_response(id);
}

// Sends a start command
void send_start(linkID_t id){

	// Format the start command
	u8 cmd [] = {START};

	// Send it off
	_send_command(id, cmd, sizeof(cmd));

	// Receive the response
	receiver_utilities.receive_sensor_response(id);
}

// Sends a stop message
void send_stop(linkID_t id){

	// Format the stop command
	u8 cmd [] = {STOP};

	// Send it off
	_send_command(id, cmd, sizeof(cmd));

	// Receive the response
	receiver_utilities.receive_sensor_response(id);
}

// Sends an abort message
void send_abort(linkID_t id){

	// Format the abort command
	u8 cmd [] = {ABORT};

	// Send it off
	_send_command(id, cmd, sizeof(cmd));

	// Receive the response
	receiver_utilities.receive_sensor_response(id);
}

// Sends an abort message
void send_pause(linkID_t id){

	// Format the abort command
	u8 cmd [] = {PAUSE};

	// Send it off
	_send_command(id, cmd, sizeof(cmd));

	// Receive the response
	receiver_utilities.receive_sensor_response(id);
}

// Sends an error message
void send_error(u8 error_code,  linkID_t id){

	// Format the error message
	u8 cmd [] = {ERROR, error_code};

	// Send it off
	_send_command(id, cmd, sizeof(cmd));

	// Setup timeout
	setup_timeout_timer(PACKET_TIMEOUT);

	// Receive the response
	receiver_utilities.receive_sensor_response(id);
}

// The internal sending function
void _send_command(linkID_t id, u8* cmd, size_t size){

	// Set atomic mutex
	BSP_ENTER_CRITICAL_SECTION(intState);

	// Format the packet
	u8 packet[size + PACKET_FORMAT];
	packet[0] = PACKET_PREAMBLE;
	memcpy(packet[2], cmd, size);
	packet[sizeof(packet)] = COMMAND_TAIL;
	packet[1] = size + PACKET_FORMAT;

	// set the transmit buffer
	sensor_transmit_buf.data_buffer = packet;
	sensor_transmit_buf.size_of_buffer = sizeof(packet);
	sensor_transmit_buf.tx_id = id;

	debug_data.router_packet_counter ++;

	// Set atomic mutex
	BSP_ENTER_CRITICAL_SECTION(intState);

	// sends the message
	if(SMPL_SUCCESS != tx_callback_function(&sensor_transmit_buf)){

		// Serve a network error.
		net_error();
	}

	// Receive a response - stay in loop until message received
	while((BAD_INTEGRITY != receive_sensor_response(id)) || (GOOD_INTEGRITY != receive_sensor_response(id))){}
}
