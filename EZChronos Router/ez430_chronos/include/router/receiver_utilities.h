/*
 * receiver_utilities.h
 *
 *  Created on: Nov 27, 2013
 *      Author: Francis Papineau
 */

#include "callback_functions.h"

#ifndef RECEIVER_UTILITIES_H_
#define RECEIVER_UTILITIES_H_
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
