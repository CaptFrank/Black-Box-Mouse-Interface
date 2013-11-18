/*
 * packet_handlers.h
 *
 *  Created on: Nov 5, 2013
 *      Author: Francis Papineau
 */

#ifndef PACKET_HANDLERS_H_
#define PACKET_HANDLERS_H_

/**
 * This file will contain the packet handlers for each packet type,
 * either sending or receiving packet.
 */

/**
 * This function will initialize the packet handler table in memory,
 * for quick access to the function tables.
 */
void init_packet_handlers(void);

/**
 * This function sets a packet handler to a new packet that is passed
 * through the function.
 */
void set_run_packet_handlers(void* packet);

/**
 * This function deletes the packet handler past to the function.
 */
void delete_packet_handler(void* packet_handler);


#endif /* PACKET_HANDLERS_H_ */