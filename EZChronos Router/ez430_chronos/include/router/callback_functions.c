/*
 * callback_functions.c
 *
 *  Created on: Nov 27, 2013
 *      Author: Francis Papineau
 */

#include "callback_functions.h"

/**
 * the receive callback function
 */
smplStatus_t rx_callback_function(struct receive_buffer_t* receive_buffer_struct){

	smplStatus_t status;

	// Get radio ready. Wakes up in IDLE state.
	SMPL_Ioctl(IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_AWAKE, 0);

	// Send the packet
	status = SMPL_Receive(receive_buffer_struct->rx_id,
			(u8*) receive_buffer_struct->data_buffer,
			(u8*) receive_buffer_struct->size_of_buffer);

	// Put radio back to SLEEP state
	SMPL_Ioctl(IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_SLEEP, 0);

	return status;
}

/**
 * the transmit callback function
 */
smplStatus_t tx_callback_function(struct transmit_buffer_t* transmit_buffer_struct){

	smplStatus_t status;

    // Get radio ready. Wakes up in IDLE state.
    SMPL_Ioctl(IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_AWAKE, 0);

	// Send the packet
	status = SMPL_SendOpt(transmit_buffer_struct->tx_id,
			(u8*)transmit_buffer_struct->data_buffer,
			transmit_buffer_struct->size_of_buffer,
			SMPL_TXOPTION_ACKREQ);

    // Put radio back to SLEEP state
    SMPL_Ioctl(IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_SLEEP, 0);

    return status;
}



