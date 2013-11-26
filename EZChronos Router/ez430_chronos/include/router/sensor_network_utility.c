/*
 * network_utility.c
 *
 *  Created on: Nov 5, 2013
 *      Author: Francis Papineau
 */

#include "sensor_network_utility.h"
#include "nwk_types.h"



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

	// Setup the ping command
	u8 cmd [] = {PING};

	// Send it off
	_send_command(id, cmd, sizeof(cmd));

}

// Sends a config request
void send_config_req(linkID_t id){

	// Set the config request
	u8 cmd [] = {CONFIG_REQ};

	// Send it off
	_send_command(id, cmd, sizeof(cmd));
}

// Sends a status request
void send_status_req(linkID_t id){

	// Setup the status request command
	u8 cmd [] = {STATUS_REQ};

	// Send it off
	_send_command(id, cmd, sizeof(cmd));
}

// Sends a sync message
void send_sync(linkID_t id){

	// Setup the Sync Command
	u8 cmd [] = {SYNC, id, HEARTBEAT_FREQ};

	// Send it off
	_send_command(id, cmd, sizeof(cmd));
}

// Sends a start command
void send_start(linkID_t id){

	// Format the start command
	u8 cmd [] = {START};

	// Send it off
	_send_command(id, cmd, sizeof(cmd));
}

// Sends a stop message
void send_stop(linkID_t id){

	// Format the stop command
	u8 cmd [] = {STOP};

	// Send it off
	_send_command(id, cmd, sizeof(cmd));
}

// Sends an abort message
void send_abort(linkID_t id){

	// Format the abort command
	u8 cmd [] = {ABORT};

	// Send it off
	_send_command(id, cmd, sizeof(cmd));
}

// Sends an error message
void send_error(u8 error_code,  linkID_t id){

	// Format the error message
	u8 cmd [] = {ERROR, error_code};

	// Send it off
	_send_command(id, cmd, sizeof(cmd));
}

// The internal sending fucntion
void _send_command(linkID_t id, u8* cmd, size_t size){

	// Format the packet

	u8 packet[size + PACKET_FORMAT];

	packet[0] = PACKET_PREAMBLE;

	memcpy(packet[1], cmd, size);

	packet[sizeof(packet)] = COMMAND_TAIL;


	// Send the packet off to the appropriate ndoe.
	SMPL_SendOpt(id, (u8*) &packet, size, SMPL_TXOPTION_ACKREQ);
}
