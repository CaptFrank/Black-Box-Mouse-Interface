/*
 * callback_functions.h
 *
 *  Created on: Nov 27, 2013
 *      Author: Francis Papineau
 */

#ifndef CALLBACK_FUNCTIONS_H_
#define CALLBACK_FUNCTIONS_H_

#include "nwk_types.h"

#define MAX_BUFFER	255

/**
 * These are the 2 different callback functions that are accessed
 * when we want to send or receive data from or to a node.
 */

struct receive_buffer_t {

	// A serial uid to track the struct
	u8 uid;

	// A receiver command
	// 		- Sensor - [0x01]
	// 		- Base Station - [0x02]
	u8 mode;

	// Link id received from
	linkID_t rx_id;

	// Data buffer
	u8 data_buffer[MAX_BUFFER];

	// the size of the buffer
	u8 size_of_buffer;

	// rx timeout
	u8 timeout;

}rx_buf;

struct transmit_buffer_t {

	// A serial uid to track the struct
	u8 uid;

	// Link id to send to
	linkID_t tx_id;

	// Data buffer
	u8 data_buffer[MAX_BUFFER];

	// the size of the buffer;
	u8 size_of_buffer;

}tx_buf;

/**
 * the receive callback function
 */
void rx_callback_function(struct receive_buffer_t* receive_buffer_struct);
void rx_until_trigger_callback_function(struct receive_buffer_t* receive_buffer_struct);

/**
 * the transmit callback function
 */
void tx_callback_function(struct transmit_buffer_t* transmit_buffer_struct);


#endif /* CALLBACK_FUNCTIONS_H_ */
