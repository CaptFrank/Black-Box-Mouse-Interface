/*
 * packet_handlers.c
 *
 *  Created on: Nov 5, 2013
 *      Author: Francis Papineau
 */

#include "packet_handlers.h"

/**
 * This function creates 2 structures of function tables.
 * one of the router<->base_station command sender and one of the
 * router<->sensor command sender.
 */

void init_packet_handlers(void){

	/**
	 * Get the structures and assign the pointers
	 * to the modes.
	 */
	modes.base_station_router = &router_utilities;
	modes.sensors_arbitrator = &sensor_utilities;
	modes.receiver = &receiver_utilities;
}

/**
 * This function deletes the pointer the the packet
 * handler.
 */
void delete_packet_handler(void* packet_handler){

	// we just set the pointer to null.
	packet_handler = NULL;
}

/**
 * This function creates the USB report that needs to be sent to
 * the arduino baed on the configs and the sensor data.
 */
void create_usb_report(){



}

/**
 * This function gets the usb report created to send to
 * the base station.
 */
void* get_usb_report(){



}
