/*
 * packet_handlers.h
 *
 *  Created on: Nov 5, 2013
 *      Author: Francis Papineau
 */

#ifndef PACKET_HANDLERS_H_
#define PACKET_HANDLERS_H_

#include "sensor_network_utility.h"
#include "router_network_utility.h"
#include "receiver_utilities.h"

/**
 * This file will contain the packet handlers for each packet type,
 * either sending or receiving packet.
 */

struct packet_handlers_t{

	// Defining the different modes
	// - TX MODE
	router_network_utilities_t* base_station_router;
	sensor_network_utilities_t* sensors_arbitrator;

	// - RX MODE
	receiver_router_utilities_t* receiver;

} modes;

/**
 * This function will initialize the packet handler table in memory,
 * for quick access to the function tables.
 */
void init_packet_handlers(void);

/**
 * This function deletes the packet handler past to the function.
 */
void delete_packet_handler(void* packet_handler);

/**
 * This function creates the USB report that needs to be sent to
 * the arduino based on the configs and the sensor data.
 */
void create_usb_report(u8 sensor_id);

/**
 * This function sends the data packet to the base station node.
 */
void send_usb_report();

/**
 * This function looks at the config of the device and creates a
 * usb report (data packet).
 */
void _update_tx_packet(structure_choice_t configs);


#endif /* PACKET_HANDLERS_H_ */
