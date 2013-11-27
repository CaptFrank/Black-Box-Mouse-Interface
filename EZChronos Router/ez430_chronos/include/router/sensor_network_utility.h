/*
 * network_utility.c
 *
 *  Created on: Nov 5, 2013
 *      Author: Francis Papineau
 */

#ifndef NETWORK_UTILITY_H_
#define NETWORK_UTILITY_H_

#include "network_protocol.h"
#include "nwk_types.h"
#include "Configs.h"

/**
 * These are the possible commands the router
 * can send.
 */
#define PING				0x01
#define CONFIG_REQ			0x02
#define STATUS_REQ			0x03

/**
 * The sync command is structured as follows:
 * 	- 0x04, time to sync, heartbeat freq
 */
#define SYNC				0x04
#define START				0x05
#define STOP				0x06
#define ABORT				0x07
#define ERROR				0x08

#define HEARTBEAT_FREQ		0x01
#define PACKET_FORMAT		0x03
#define COMMAND_PREAMBLE	'@'
#define COMMAND_TAIL		0x0A

/**
 * This is the function table for the sensor
 * callbacks.
 */
typedef struct {

	void (*send_heartbeat)(linkID_t id);

	void (*ping_ack)(linkID_t id);

	void (*send_config_req)(linkID_t id);
	void (*send_status_req)(linkID_t id);
	void (*send_sync)(linkID_t id);
	void (*send_start)(linkID_t id);
	void (*send_stop)(linkID_t id);
	void (*send_abort)(linkID_t id);
	void (*send_error)(u8 error_code, linkID_t id);

}sensor_network_utilities_t;

// define the type
sensor_network_utilities_t sensor_utilities;

/**
 * This is the transmit buffer.
 */
struct transmit_buffer_t sensor_transmit_buf;

/**
 * Sends a ping acknowledgment.
 */
void ping_ack(linkID_t id);

/**
 * Sends a request to receive configuration info, from the sensor
 * node.
 */
void send_config_req(linkID_t id);

/**
 * Sends a request to receive a status packet from the sensor node.
 */
void send_status_req(linkID_t id);

/**
 * This sends a sync packet to the sensor node. This is sent to
 * enable a synchronization between the host and the client.
 */
void send_sync(linkID_t id);

/**
 * This sends a start command to the sensor.
 */
void send_start(linkID_t id);

/**
 * This stops the sensor node.
 */
void send_stop(linkID_t id);

/**
 * This sends an abort signal to the sensor node. This is done,
 * if we have an error at the host side.
 */
void send_abort(linkID_t id);

/**
 * This sends an error code to the remote sensor node. This also sends
 * an abort packet to stop the sensor engine.
 */
void send_error(u8 error_code, linkID_t id);

/**
 * the internal used function to send a message
 */
void _send_command(linkID_t id, u8* cmd, size_t size);

#endif /* NETWORK_UTILITY_C_ */
