/*
 * receiver_utilities.c
 *
 *  Created on: Nov 27, 2013
 *      Author: Francis Papineau
 */

#include "Configs.h"
#include "receiver_utilities.h"
#include "callback_functions.h"
#include "sensor_network_utility.h"
#include "router_network_utility.h"

/**
 * This function receives a packet on the broadcast
 * interface.
 */
receiver_status_t receive_command(){

	smplStatus_t status;
	status = NONE;

	// Broadcast id.
	rx_buffer.rx_id = SMPL_LINKID_USER_UUD;

	// Receive that message
	status = rx_callback_function(&rx_buffer);

	// Check for receiving status.
	if(SMPL_SUCCESS != status){

		// Serve a network error.
		net_error();
	}else {
		// Execute the packet if it good
		if(GOOD_INTEGRITY == _check_packet_integrity(&rx_buffer)){
			_execute_command(&rx_buffer);
			return GOOD_INTEGRITY;
		}else{ // return network error
			net_error();
			return BAD_INTEGRITY;
		}
	}
}

/**
 * This function receives a specific packet from a specific source.
 */
receiver_status_t receive_specific_command(linkID_t ID){

	smplStatus_t status;
	status = NONE;

	// set id.
	rx_buffer.rx_id = id;

	// Receive that message
	status = rx_callback_function(&rx_buffer);

	// Check for receiving status.
	if(SMPL_SUCCESS != status){

		// Serve a network error.
		net_error();
	}else {
		// Execute the packet if it good
		if(GOOD_INTEGRITY == _check_packet_integrity(&rx_buffer)){
			_execute_command(&rx_buffer);
			return GOOD_INTEGRITY;
		}else{ // return network error
			net_error();
			return BAD_INTEGRITY;
		}
	}
}

/**
 * This function receives a sensor response after a
 * command has been issued to the router.
 */
receiver_status_t receive_sensor_response(linkID_t id){

	smplStatus_t status;
	status = NONE;

	// set id.
	rx_buffer.rx_id = id;

	// Receive that message
	status = rx_callback_function(&rx_buffer);

	// Check for receiving status.
	if(SMPL_SUCCESS != status){

		// Serve a network error.
		net_error();
	}else {
		// Execute the packet if it good
		if(GOOD_INTEGRITY == _check_packet_integrity(&rx_buffer)){
			_read_sensor_response(&rx_buffer);
			return GOOD_INTEGRITY;
		}else{ // return network error
			net_error();
			return BAD_INTEGRITY;
		}
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

/**
 * This function executes the received command from the base station.
 */
void _execute_command(struct receive_buffer_t* receive_buffer_struct){

	// [Preamble][size][packet_id][...]
	// get the packet id to switch on.
	u8 packet_id = receive_buffer_struct->data_buffer[2];
	linkID_t sensor_addr = receive_buffer_struct->data_buffer[3];

	switch(packet_id){

	// ********************************************
	/**
	 * ROUTER DOMAIN COMMANDS
	 */
	case ROUTER_PING:

		// Command mode activated
		router_state.state_bits.command = ON;

		// Send ACK
		modes.base_station_router->ping_ack();

		// Command mode deactivated
		router_state.state_bits.command = OFF;
		break;

	// ********************************************
	case ROUTER_RUN:

		// Command mode activated
		router_state.state_bits.command = ON;

		// Set state to run
		router_state.state_bits.run = ON;

		// Send ACK
		modes.base_station_router->ping_ack();

		// Command mode deactivated
		router_state.state_bits.command = OFF;
		break;

	// ********************************************
	case ROUTER_CONFIG:

		// Command mode and Query mode Activated
		router_state.state_bits.command = ON;

		// Send query response
		modes.base_station_router->send_router_configs();

		// Command mode and Query mode Activated
		router_state.state_bits.command = OFF;
		break;

	// ********************************************
	case ROUTER_NMAP:

		// Command mode and Query mode Activated
		router_state.state_bits.command = ON;

		// Sends the nmap
		modes.base_station_router->send_nmap();

		// Command mode and Query mode Activated
		router_state.state_bits.command = OFF;
		break;

	// ********************************************
	case ROUTER_STATUS:

		// Command mode and Query mode Activated
		router_state.state_bits.command = ON;

		// Sends the router status
		modes.base_station_router->send_router_status();

		// Command mode and Query mode Activated
		router_state.state_bits.command = OFF;
		break;

	// ********************************************
	case ROUTER_PAUSE:

		// Command mode activated
		router_state.state_bits.command = ON;

		// Set state to pause
		router_state.state_bits.pause = ON;

		// Send ACK
		modes.base_station_router->ping_ack();

		// Command mode deactivated
		router_state.state_bits.command = OFF;
		break;

	// ********************************************
	case ROUTER_PWR_ON:

		// Command mode and Query mode Activated
		router_state.state_bits.command = ON;

		// Sets the state ON
		router_state.state_bits.on = ON;

		// Sends a heart beat
		modes.base_station_router->send_heartbeat();

		// Command mode and Query mode Activated
		router_state.state_bits.command = OFF;
		break;

	// ********************************************
	case ROUTER_PWR_OFF:

		// Command mode and Query mode Activated
		router_state.state_bits.command = ON;

		// Set state to off
		router_state.state_bits.off = ON;

		// Sends a heartbeat
		modes.base_station_router->send_heartbeat();

		// Command mode and Query mode Activated
		router_state.state_bits.command = OFF;
		break;

	// ********************************************
	case ROUTER_WAKE:

		// Command mode activated
		router_state.state_bits.command = ON;

		// Sets the power back on
		router_state.state_bits.on = ON;

		// Send ACK
		modes.base_station_router->ping_ack();

		// Command mode deactivated
		router_state.state_bits.command = OFF;
		break;

	// ********************************************
	case ROUTER_SENSOR_NUMBER:

		// Command mode and Query mode Activated
		router_state.state_bits.command = ON;

		// Sends the number of sensors
		modes.base_station_router->send_sensor_number();

		// Command mode and Query mode Activated
		router_state.state_bits.command = OFF;
		break;

	// ********************************************
	/**
	 * SENSOR DOMAIN COMMANDS
	 */
	case SENSOR_PING:

		// Command mode activated
		router_state.state_bits.command = ON;

		// Sends a ping request to the sensor
		modes.sensors_arbitrator->ping_ack(sensor_addr);
		modes.receiver->

		// Command mode activated
		router_state.state_bits.command = OFF;
		break;

	// ********************************************
	case SENSOR_CONFIG:

		// Command mode activated
		router_state.state_bits.command = ON;

		// Sends a config request to teh sensor
		modes.sensors_arbitrator->send_config_req(sensor_addr);

		// Command mode activated
		router_state.state_bits.command = OFF;
		break;

	// ********************************************
	case ROUTER_SENSOR_CHANNELS:
	case SENSOR_ENABLE:

		// Command mode activated
		router_state.state_bits.command = ON;

		// Sends the enabled sensors
		modes.base_station_router->send_sensor_enabled();

		// Command mode activated
		router_state.state_bits.command = OFF;
		break;

	// ********************************************
	case SENSOR_PAUSE:

		// Command mode activated
		router_state.state_bits.command = ON;

		// Sends a sensor pause command
		modes.sensors_arbitrator->send_pause(sensor_addr);

		// Command mode activated
		router_state.state_bits.command = OFF;
		break;

	// ********************************************
	case SENSOR_PWR_ON:

		// Command mode activated
		router_state.state_bits.command = ON;

		// Powers on the sensor and starts it.
		modes.sensors_arbitrator->send_start(sensor_addr);

		// Command mode activated
		router_state.state_bits.command = OFF;
		break;

	// ********************************************
	case SENSOR_PWR_OFF:

		// Command mode activated
		router_state.state_bits.command = ON;

		// Sends a stop command to a sensor and powers it off
		modes.sensors_arbitrator->send_stop(sensor_addr);

		// Command mode activated
		router_state.state_bits.command = OFF;
		break;

	// ********************************************
	case SENSOR_WAKE:

		// Command mode activated
		router_state.state_bits.command = ON;

		// Wakes up a sensor by sending a heartbeat request.
		modes.sensors_arbitrator->send_heartbeat(sensor_addr);

		// Command mode activated
		router_state.state_bits.command = OFF;
		break;

	default:

		// we have an error.
		// - increase the error count and assert an error
		command_error();
		break;
	}
}

// Get a response for a command
void _read_response(struct receive_buffer_t* receive_buffer_struct){

	// TODO

	// Get the packet ID based on the defines protocol
	u8 packet_id = receive_buffer_struct->data_buffer[2];

	switch(packet_id){

	case SENSOR_ACK:

		// Set the sensor_rx_state to ACK state
		sensor_state = ACK;
		break;

	case SENSOR_CONFIG_REPORT:


		break;

	case SENSOR_STATUS_REPORT:


		break;

	case SENSOR_DATA_REPORT:


		break;

	case SENSOR_SYNC_REPORT:


		break;

	case SENSOR_HEARTBEAT_REPORT:


		break;

	case SENSOR_ERROR_REPORT:


		break;
	}
}


