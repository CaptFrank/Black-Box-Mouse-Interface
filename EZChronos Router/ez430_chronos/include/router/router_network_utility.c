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

/**
 * NOTE: The header is managed by the _send_packet function
 */


// sends a heartbeat
void send_hearbeat(){

	// Gets the battery value
	packet._heartbeat.battery_voltage = sBatt.voltage;

	// Gets the router mode
	packet._heartbeat.router_mode = get_router_mode();

	// Send out the address and size
	_send_packet((void*)&packet._heartbeat, sizeof(packet._heartbeat));
}

// sends an ack signal
void ping_ack(){

	// Ack is true
	packet._info.ack = 0x01;

	// Send out the address and the size
	_send_packet((void*)&packet._info, sizeof(packet._info));
}

// sends the router status
void send_router_status(){

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

	// Send out packet and size
	_send_packet((void*)&packet._status, sizeof(packet._status));
}

// sends the sensor status
void send_sensor_status(){

	// Get the appropriate structure pointer.
	if(watch_configs.watch_configs_options.conf_mouse){
		packet._remote_data.data_struct = (void*)&mouse_report;
		packet._remote_data.data_len = sizeof(mouse_report);

	}else if(watch_configs.watch_configs_options.conf_joystick){
		packet._remote_data.data_struct = (void*)&joystick_report;
		packet._remote_data.data_len = sizeof(joystick_report);

	}

	// Send the structure.
	_send_packet(packet._remote_data.data_struct, packet._remote_data.data_struct);
}

// sends the router configs
void send_router_configs(){

	// Get radio configs
	packet._radio.values = simpliciti_ed_address;

	// Send the packet along with the size;
	_send_packet((void*)&packet._radio, sizeof(packet._radio));
}


// sends the network map
void send_nmap(){

	// Set max number of sensors
	packet._nmap.max_sensor_address = MAX_SENSOR_ADDRESS;
	packet._nmap.max_sensor_id = MAX_SENSOR_ADDRESS;

	// Get the sensors that are enabled.
	packet._nmap.en_sensors = enabled_sensors;

	// Send out the packet and size.
	_send_packet((void*)&packet._nmap, sizeof(packet._nmap));
}

// sends the sensors enabled
void send_sensor_enabled(){

	// Get the sensors in network
	packet._sensor_en.en_sensors = network_sensors;

	// Get enabled sensors
	packet._sensor_en.sensor_config_enable = enabled_sensors;

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

_send_packet(void* packet_ptr, u8 size){

	//TODO

}
