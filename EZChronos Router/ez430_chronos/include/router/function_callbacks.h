/*
 * function_callbacks.c
 *
 *  Created on: Nov 5, 2013
 *      Author: Francis Papineau
 */

#ifndef FUNCTION_CALLBACKS_C_
#define FUNCTION_CALLBACKS_C_

typedef struct rx_packet{
	linkID_t id;
	u8 rx_packet[255];
	u8 rx_packet_len;
}rx_buffer;


/**
 * This function is a receiver callback, which receives
 * a packet from a specific link ID.
 */
void rx_function_callback_sensor(linkID_t ID);

/**
 * This function sends data to the sensor node specified.
 */
void tx_function_callback_sensor(linkID_t ID, void* packet, u8 size);

/**
 * This function is a receiver callback, which receives
 * a packet from a specific link ID.
 */
void rx_function_callback_router(linkID_t ID);

/**
 * This function sends data to the sensor node specified.
 * Concatenates the header and the message and the tail.
 */
void tx_function_callback_router(linkID_t ID, void* packet, u8 size);


#endif /* FUNCTION_CALLBACKS_C_ */
