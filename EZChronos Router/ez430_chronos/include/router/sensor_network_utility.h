/*
 * network_utility.c
 *
 *  Created on: Nov 5, 2013
 *      Author: Francis Papineau
 */

#include "network_protocol.h"

#ifndef NETWORK_UTILITY_H_
#define NETWORK_UTILITY_H_

typedef struct {

	void (*send_heartbeat)();

	void (*ping_ack)();
	void (*ping_nack)();
	void (*send_config_req)();
	void (*send_status_req)();
	void (*send_sync)();
	void (*send_start)();
	void (*send_stop)();
	void (*send_abort)();
	void (*send_error)(u8 error_code);

}sensor_network_utilities_t;

union {

	packet_header_t _header;


} packets;

/**
 * Sends a ping acknowledgment.
 */
void ping_ack();

/**
 * Sends a ping non acknowledgment.
 * 	 - this is used in error cases, when remote commands cannot be
 * 	 	executed.
 */
void ping_nack();

/**
 * Sends a request to receive configuration info, from the sensor
 * node.
 */
void send_config_req();

/**
 * Sends a request to receive a status packet from the sensor node.
 */
void send_status_req();

/**
 * This sends a sync packet to the sensor node. This is sent to
 * enable a synchronization between the host and the client.
 */
void send_sync();

/**
 * This sends a start command to the sensor.
 */
void send_start();

/**
 * This stops the sensor node.
 */
void send_stop();

/**
 * This sends an abort signal to the sensor node. This is done,
 * if we have an error at the host side.
 */
void send_abort();

/**
 * This sends an error code to the remote sensor node. This also sends
 * an abort packet to stop the sensor engine.
 */
void send_error(u8 error_code);

#endif /* NETWORK_UTILITY_C_ */
