/*
 * router_network_utility.c
 *
 *  Created on: Nov 5, 2013
 *      Author: Francis Papineau
 */

#include "router_network_utility.h"
#include "callback_functions.h"
#include "router_main.h"
#include "Utilities.h"
#include "error_handler.h"
#include "Configs.h"
#include "timer.h"

/**
 * NOTE: The header is managed by the _send_packet function
 */


// sends a heartbeat
void send_hearbeat(){

	// Set atomic mutex
	BSP_ENTER_CRITICAL_SECTION(intState);
	// Gets the battery value
	packet._heartbeat.battery_voltage = sBatt.voltage;

	// Gets the router mode
	packet._heartbeat.router_mode = get_router_mode();

	// Unset atomic mutex
	BSP_EXIT_CRITICAL_SECTION(intState);

	// Send out the address and size
	_send_packet((void*)&packet._heartbeat, ROUTER_HEART_BEAT,
			sizeof(packet._heartbeat));
}

// sends an ack signal
void ping_ack(){

	// First ping the hw layer
	SMPL_Ping(base_station_id);

	// Set atomic mutex
	BSP_ENTER_CRITICAL_SECTION(intState);

	// Ack is true
	packet._info.ack = 0x01;

	debug_data.router_acks_sent ++;

	// Unset atomic mutex
	BSP_EXIT_CRITICAL_SECTION(intState);

	// Send out the address and the size
	_send_packet((void*)&packet._info, ROUTER_ACK,
			sizeof(packet._info));
}

// sends the router status
void send_router_status(){

	// Set atomic mutex
	BSP_ENTER_CRITICAL_SECTION(intState);

	// set the router status
	// 		- get the modes.
	packet._status.power_state = get_power_status();
	packet._status.router_mode = get_router_mode();

	// gets the number of error
	packet._status.error_count = get_error_status();

	// checks the debug flag to see if it is enabled.
	packet._status.debug_enable_flag = watch_configs.watch_configs_flags;

	// Gets the battery voltage
	packet._status.battery_voltage = sBatt.voltage;

	// Sets the router address.
	packet._status.router_address = ROUTER_ADDRESS;

	// Unset atomic mutex
	BSP_EXIT_CRITICAL_SECTION(intState);

	// Send out packet and size
	_send_packet((void*)&packet._status, ROUTER_STATUS,
			sizeof(packet._status));
}

// sends the sensor data
void send_sensor_data(){

	// Set atomic mutex
	BSP_ENTER_CRITICAL_SECTION(intState);

	// Get the appropriate structure pointer.
	if(watch_configs.watch_configs_options.conf_mouse){
		packet._remote_data.data_struct = (void*)&mouse_report;
		packet._remote_data.data_len = sizeof(mouse_report);

	}else if(watch_configs.watch_configs_options.conf_joystick){
		packet._remote_data.data_struct = (void*)&joystick_report;
		packet._remote_data.data_len = sizeof(joystick_report);
	}

	// Unset atomic mutex
	BSP_EXIT_CRITICAL_SECTION(intState);

	// Send the structure.
	_send_packet(packet._remote_data.data_struct, ROUTER_DATA,
			sizeof(packet._remote_data.data_struct));
}

// sends the router configs
void send_router_configs(){

	// Set atomic mutex
	BSP_ENTER_CRITICAL_SECTION(intState);

	// Get radio configs
	packet._radio.values = simpliciti_ed_address;

	// Unset atomic mutex
	BSP_EXIT_CRITICAL_SECTION(intState);

	// Send the packet along with the size;
	_send_packet((void*)&packet._radio, ROUTER_CONFIG,
			sizeof(packet._radio));
}

// sends the network map
void send_nmap(){

	// Set atomic mutex
	BSP_ENTER_CRITICAL_SECTION(intState);

	// Set max number of sensors
	packet._nmap.max_sensor_address = MAX_SENSOR_ADDRESS;
	packet._nmap.max_sensor_id = MAX_SENSOR_ADDRESS;

	// Get the sensors that are enabled.
	packet._nmap.en_sensors = enabled_sensors;

	// Unset atomic mutex
	BSP_EXIT_CRITICAL_SECTION(intState);

	// Send out the packet and size.
	_send_packet((void*)&packet._nmap, ROUTER_NMAP,
			sizeof(packet._nmap));
}

// sends the sensors enabled
void send_sensor_enabled(){

	// Set atomic mutex
	BSP_ENTER_CRITICAL_SECTION(intState);

	// Get the sensors in network
	packet._sensor_en.en_sensors = network_sensors;

	// Get enabled sensors
	packet._sensor_en.sensor_config_enable = enabled_sensors;

	// Unset atomic mutex
	BSP_EXIT_CRITICAL_SECTION(intState);

	// The number sensors is set by the check sensors function.
	// packet._sensor_en.number_sensors;

	// Send out the packet and its size.
	_send_packet((void*)&packet._sensor_en, SENSOR_ENABLE,
			sizeof(packet._sensor_en));
}

// sends the number of sensors active
void send_sensor_number(){

	// The number sensors is set by the check sensors function.
	// packet._sensor_en.number_sensors;

	// We call it once more to make sure we have the same values \
		as before.
	check_network();

	// Send teh packet and the size
	_send_packet((void*)&packet._num_sensor, SENSOR_NUMBER,
			sizeof(packet._num_sensor));
}

// Sends an error
void send_error_code(u8 error_code, u8 sensor_id){

	// Set atomic mutex
	BSP_ENTER_CRITICAL_SECTION(intState);

	// Set the error code message
	packet._error.error_code = error_code;
	packet._error.sensor_address = base_station_id;
	packet._error.sensor_id = sensor_id;

	// Set atomic mutex
	BSP_EXIT_CRITICAL_SECTION(intState);

	// Send teh packet and the size
	_send_packet((void*)&packet._error, ERROR_MSG,
			sizeof(packet._error));
}

// sends a debug message
void send_debug_msg(){

	// Set atomic mutex
	BSP_ENTER_CRITICAL_SECTION(intState);

	// set the debug message
	packet._debug.router_acks_sent_counter = debug_data.router_acks_sent;
	packet._debug.router_packet_counter = debug_data.router_packet_counter;
	packet._debug.router_rx_count = debug_data.router_rx_count;
	packet._debug.router_sent_request_counter = debug_data.router_sent_requests;
	packet._debug.router_tx_count = debug_data.router_tx_count;

	// Set atomic mutex
	BSP_EXIT_CRITICAL_SECTION(intState);

	// send it off
	_send_packet((void*)&packet._debug, ROUTER_DEBUG,
			sizeof(packet._debug));

}

/**
 * Packet structure:
 * 	[+][Header][Data]
 */
void _send_packet(void* packet_ptr, u8 header, u8 size){

	// Set atomic mutex
	BSP_ENTER_CRITICAL_SECTION(intState);

	// Construct the header
	packet._header.node_id = ROUTER;
	packet._header.packet_version = PACKET_VER;

	packet._header.packet_id = header;

	packet._header.sensor_id = sensor_info.sensor_node_id;
	packet._header.sensor_run_time = sensor_info.sensor_runtime;
	packet._header.time_stamp = sTimer.timer0_A3_ticks;

	// Size = [header size] + [data size] + 1 for the preamble
	packet._header.message_size = sizeof(packet._header) + size + 1;

	u8 packet_byte_array[packet._header.message_size];

	// Add the preamble byte
	packet_byte_array[0] = ROUTER_PACKET_PREAMBLE;
	size_t size_of_header = sizeof(packet._header);

	// copy the current header
	memcpy(packet_byte_array[1], (void*)&packet._header, size_of_header);

	// copy the packet
	memcpy(packet_byte_array[size_of_header], packet_ptr, size);

	// Set the sending buffer.
	router_tx_buffer.data_buffer = packet_byte_array;
	router_tx_buffer.size_of_buffer = packet._header.message_size;
	router_tx_buffer.rx_id = base_station_id;

	debug_data.router_packet_counter ++;

	// Unset atomic mutex
	BSP_EXIT_CRITICAL_SECTION(intState);

	if( SMPL_SUCCESS != tx_callback_function(&router_tx_buffer)){

		// Serve a network error
		net_error();
	}
}
