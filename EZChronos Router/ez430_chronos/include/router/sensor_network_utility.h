/*
 * network_utility.c
 *
 *  Created on: Nov 5, 2013
 *      Author: Francis Papineau
 */

#ifndef NETWORK_UTILITY_H_
#define NETWORK_UTILITY_H_

#include "network_protocol.h"
#include "Configs.h"

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

union {

	packet_header_t _header;


} packets;

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

#endif /* NETWORK_UTILITY_C_ */
