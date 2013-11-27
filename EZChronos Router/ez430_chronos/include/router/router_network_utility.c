/*
 * router_network_utility.c
 *
 *  Created on: Nov 5, 2013
 *      Author: Francis Papineau
 */

#include "router_network_utility.h"
#include "function_callbacks.h"
#include "router_main.h"
#include "Utilities.h"
#include "Configs.h"
#include "timer.h"

/**
 * NOTE: The header is managed by the _send_packet function
 */


// sends a heartbeat
void send_hearbeat(){

	BSP_ENTER_CRITICAL_SECTION(intState);
	// Gets the battery value
	packet._heartbeat.battery_voltage = sBatt.voltage;

	// Gets the router mode
	packet._heartbeat.router_mode = get_router_mode();

	BSP_EXIT_CRITICAL_SECTION(intState);

	// Send out the address and size
	_send_packet((void*)&packet._heartbeat, sizeof(packet._heartbeat));
}

// sends an ack signal
void ping_ack(){

	BSP_ENTER_CRITICAL_SECTION(intState);

	// Ack is true
	packet._info.ack = 0x01;

	BSP_EXIT_CRITICAL_SECTION(intState);

	// Send out the address and the size
	_send_packet((void*)&packet._info, sizeof(packet._info));
}

// sends the router status
void send_router_status(){

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

	BSP_EXIT_CRITICAL_SECTION(intState);

	// Send out packet and size
	_send_packet((void*)&packet._status, sizeof(packet._status));
}

// sends the sensor status
void send_sensor_status(){


	BSP_ENTER_CRITICAL_SECTION(intState);

	// Get the appropriate structure pointer.
	if(watch_configs.watch_configs_options.conf_mouse){
		packet._remote_data.data_struct = (void*)&mouse_report;
		packet._remote_data.data_len = sizeof(mouse_report);

	}else if(watch_configs.watch_configs_options.conf_joystick){
		packet._remote_data.data_struct = (void*)&joystick_report;
		packet._remote_data.data_len = sizeof(joystick_report);
	}

	BSP_EXIT_CRITICAL_SECTION(intState);

	// Send the structure.
	_send_packet(packet._remote_data.data_struct,
			sizeof(packet._remote_data.data_struct));
}

// sends the router configs
void send_router_configs(){

	BSP_ENTER_CRITICAL_SECTION(intState);

	// Get radio configs
	packet._radio.values = simpliciti_ed_address;

	BSP_EXIT_CRITICAL_SECTION(intState);

	// Send the packet along with the size;
	_send_packet((void*)&packet._radio, sizeof(packet._radio));
}


// sends the network map
void send_nmap(){

	BSP_ENTER_CRITICAL_SECTION(intState);

	// Set max number of sensors
	packet._nmap.max_sensor_address = MAX_SENSOR_ADDRESS;
	packet._nmap.max_sensor_id = MAX_SENSOR_ADDRESS;

	// Get the sensors that are enabled.
	packet._nmap.en_sensors = enabled_sensors;

	BSP_EXIT_CRITICAL_SECTION(intState);

	// Send out the packet and size.
	_send_packet((void*)&packet._nmap, sizeof(packet._nmap));
}

// sends the sensors enabled
void send_sensor_enabled(){

	BSP_ENTER_CRITICAL_SECTION(intState);

	// Get the sensors in network
	packet._sensor_en.en_sensors = network_sensors;

	// Get enabled sensors
	packet._sensor_en.sensor_config_enable = enabled_sensors;

	BSP_EXIT_CRITICAL_SECTION(intState);

	// The number sensors is set by the check sensors function.
	// packet._sensor_en.number_sensors;

	// Send out the packet and its size.
	_send_packet((void*)&packet._sensor_en, sizeof(packet._sensor_en));
}

// sends the number of sensors active
void send_sensor_number(){

	// The number sensors is set by the check sensors function.
	// packet._sensor_en.number_sensors;


	// Send teh packet and the size
	_send_packet((void*)&packet._num_sensor, sizeof(packet._num_sensor));
}

/**
 * Packet structure:
 * 	[+][Header][Data]
 */
void _send_packet(void* packet_ptr, u8 size){

	BSP_ENTER_CRITICAL_SECTION(intState);

	// Construct the header
	packet._header.node_id = ROUTER;
	packet._header.packet_version = PACKET_VER;

	packet._header.packet_id = sensor_info.packet_id ++;

	packet._header.sensor_id = sensor_info.sensor_node_id;
	packet._header.sensor_run_time = sensor_info.sensor_runtime;
	packet._header.time_stamp = sTimer.timer0_A3_ticks;

	// Size = [header size] + [data size] + 1 for the preamble
	packet._header.message_size = sizeof(packet._header) + size + 1;

	u8 packet_byte_array[packet._header.message_size];

	packet_byte_array[0] = PACKET_PREAMBLE;
	size_t size_of_header = sizeof(packet._header);

	memcpy(packet_byte_array[1], (void*)&packet._header, size_of_header);
	memcpy(packet_byte_array[size_of_header], packet_ptr, size);

	BSP_EXIT_CRITICAL_SECTION(intState);

    // Get radio ready. Wakes up in IDLE state.
    SMPL_Ioctl(IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_AWAKE, 0);

	// Send the packet
	SMPL_SendOpt(base_station_id, (u8*)&packet_byte_array,
			packet._header.message_size, SMPL_TXOPTION_ACKREQ);

    // Put radio back to SLEEP state
    SMPL_Ioctl(IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_SLEEP, 0);
}
