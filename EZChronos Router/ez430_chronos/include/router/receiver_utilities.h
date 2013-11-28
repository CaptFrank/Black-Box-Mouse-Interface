/*
 * receiver_utilities.h
 *
 *  Created on: Nov 27, 2013
 *      Author: Francis Papineau
 */


#ifndef RECEIVER_UTILITIES_H_
#define RECEIVER_UTILITIES_H_

#include "callback_functions.h"
#include "packet_handlers.h"

// Possible router commands that can be sent

#define ROUTER_PING					0x01
#define SENSOR_PING					0x02
#define ROUTER_RUN					0x03
#define ROUTER_CONFIG				0x04
#define SENSOR_CONFIG				0x05
#define SENSOR_ENABLE				0x06
#define SENSOR_CHANNEL				0x07
#define ROUTER_NMAP					0x08
#define ROUTER_STATUS				0x09
#define SENSOR_PAUSE				0x0A
#define ROUTER_PAUSE				0x0B
#define ROUTER_PWR_ON				0x0C
#define SENSOR_PWR_ON				0x0D
#define ROUTER_PWR_OFF				0x0E
#define SENSOR_PWR_OFF				0x0F
#define ROUTER_WAKE					0x10
#define SENSOR_WAKE					0x11
#define ROUTER_SENSOR_NUMBER		0x12
#define ROUTER_SENSOR_CHANNELS		0x13


/**
 * This is packet state structure,
 * which is important when checking the
 * packet integrity at an application level.
 */
typedef enum {

	// Good packet structure
	GOOD_INTEGRITY,

	// Bad packet structure.
	BAD_INTEGRITY

}receiver_status_t;

// Function pointer table.
typedef struct {

	void (*receiver_packet)();
	void (*receiver_specific_packet)();

} receiver_router_utilities_t;

// define the type
receiver_router_utilities_t receiver_utilities;

// define the receive buffer
struct receive_buffer_t rx_buffer;

/**
 * This function receives a broadcast message
 */
void receive_packet();

/**
 * This function receives a packet from a specific source.
 */
void receive_specific_packet(linkID_t ID);

/**
 * This is the internal packet integrity checker.
 * Returns true if the packet is good,
 * Returns false if the packet is bad.
 */
bool _check_packet_integrity(struct receive_buffer_t* receive_buffer_struct);

/**
 * This function executes the packet if needed.
 */
void _execute_packet(struct receive_buffer_t* receive_buffer_struct);

#endif /* RECEIVER_UTILITIES_H_ */
