/*
 * receiver_utilities.c
 *
 *  Created on: Nov 27, 2013
 *      Author: Francis Papineau
 */

#include "receiver_utilities.h"
#include "callback_functions.h"
#include "sensor_network_utility.h"
#include "router_network_utility.h"

/**
 * This function receives a packet on the broadcast
 * interface.
 */
void receive_packet(){

	smplStatus_t status;

	// Broadcast id.
	rx_buffer.rx_id = SMPL_LINKID_USER_UUD;

	// Receive that message
	status = rx_callback_function(&rx_buffer);

	// Check the receiving status.
	if(SMPL_SUCCESS != status){

		// Serve a network error.
		net_error();
	}else {
		_check_packet_integrity(&rx_buffer);
	}
}

/**
 * This function receives a specific packet from a specific source.
 */
void receive_specific_packet(linkID_t ID){

	smplStatus_t status;

	// set id.
	rx_buffer.rx_id = id;

	// Receive that message
	status = rx_callback_function(&rx_buffer);

	// Check for receiving status.
	if(SMPL_SUCCESS != status){

		// Serve a network error.
		net_error();
	}else {
		_check_packet_integrity(&rx_buffer);
	}
}

/**
 * This function disassembles the packet, and checks it's
 * integrity.
 *  - [preamble][[msg size]header][data][tail]
 */
receiver_status_t _check_packet_integrity(struct receive_buffer_t* receive_buffer_struct){

	// get the packet
	u8* packet = receive_buffer_struct.data_buffer;

	// check the header
	if((ROUTER_PACKET_PREAMBLE == packet[0]) || (COMMAND_PREAMBLE == packet[0])){

		// check the tail
		if((ROUTER_TAIL == packet[receive_buffer_struct->size_of_buffer - 1]) ||
				(COMMAND_TAIL == packet[receive_buffer_struct->size_of_buffer - 1])){

			// check packet length
			if((packet[1]) == receive_buffer_struct->size_of_buffer){
				return GOOD_INTEGRITY;
			}
		}
	// Bad packet structure
	} else {
		return BAD_INTEGRITY;
	}
}

void _execute_packet(struct receive_buffer_t* receive_buffer_struct){

	// get the packet id to switch on.
	packet_id = receive_buffer_struct->data_buffer[2];

	// Switch on the packet id received.
	switch (packet_id){


	}

}


