/*
 * callback_functions.c
 *
 *  Created on: Nov 27, 2013
 *      Author: Francis Papineau
 */

#include "Configs.h"
#include "callback_functions.h"

/**
 * the receive callback function
 */
smplStatus_t rx_callback_function(struct receive_buffer_t* receive_buffer_struct){

	smplStatus_t status;

	// Set the receiving flag
	simplicity_flag |= SIMPLICITI_TRIGGER_RECEIVED_DATA;

	// Get radio ready. Wakes up in IDLE state.
	SMPL_Ioctl(IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_AWAKE, 0);

	// Receive the data
	status = SMPL_Receive(receive_buffer_struct->rx_id,
			(u8*) receive_buffer_struct->data_buffer,
			(u8*) receive_buffer_struct->size_of_buffer);

	// Reset the receiving flag
	clearflag(simplicity_flag, SIMPLICITI_TRIGGER_RECEIVED_DATA);

	// Put radio back to SLEEP state
	SMPL_Ioctl(IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_SLEEP, 0);

	debug_data.router_rx_count ++;

	return status;
}

/**
 * the transmit callback function
 */
smplStatus_t tx_callback_function(struct transmit_buffer_t* transmit_buffer_struct){

	smplStatus_t status;

	// Set the transmitting flag
	simplicity_flag |= SIMPLICITI_TRIGGER_SEND_DATA;

    // Get radio ready. Wakes up in IDLE state.
    SMPL_Ioctl(IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_AWAKE, 0);

	// Send the packet
	status = SMPL_SendOpt(transmit_buffer_struct->tx_id,
			(u8*)transmit_buffer_struct->data_buffer,
			transmit_buffer_struct->size_of_buffer,
			SMPL_TXOPTION_ACKREQ);

	// Reset the transmitting flag
	clearflag(simplicity_flag, SIMPLICITI_TRIGGER_SEND_DATA);

    // Put radio back to SLEEP state
    SMPL_Ioctl(IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_SLEEP, 0);

	debug_data.router_tx_count ++;

    return status;
}

/**
 * Continous receiving until trigger
 */
smplStatus_t rx_until_trigger_callback_function(struct receive_buffer_t* receive_buffer_struct){

	smplStatus_t status;

	// Wait 5 seconds
	Timer0_A3_Start(SEC_1);

	// Do a check until 5sec has elapsed.
	while(!TA0R){
		status = rx_callback_function(receive_buffer_struct);
	}
	return status;
}


