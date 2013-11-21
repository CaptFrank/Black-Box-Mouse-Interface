/*
 * function_callbacks.c
 *
 *  Created on: Nov 5, 2013
 *      Author: Francis Papineau
 */

#ifndef FUNCTION_CALLBACKS_C_
#define FUNCTION_CALLBACKS_C_

/**
 * This file contains the function callbacks to send and receive
 * transmissions from and to devices.
 */

u16* connect_network(void* ID);

/**
 * This function is a receiver callback, which receives
 * a packet from a specific link ID.
 */
u8* rx_function_callback_sensor(void* ID);

/**
 * This function sends data to the sensor node specified.
 */
void tx_function_callback_sensor(void* ID, void* packet, u8 size);

/**
 * This function is a receiver callback, which receives
 * a packet from a specific link ID.
 */
u8* rx_function_callback_router(void* ID);

/**
 * This function sends data to the sensor node specified.
 * Concatenates the header and the message and the tail.
 */
void tx_function_callback_router(void* ID, void* packet, u8 size);


#endif /* FUNCTION_CALLBACKS_C_ */
