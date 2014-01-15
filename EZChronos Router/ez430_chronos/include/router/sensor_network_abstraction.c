/*
 * network_abstraction.c
 *
 *  Created on: Jan 4, 2014
 *      Author: Francis Papineau
 */

#include "configs.h"
#include "sensor_network_abstraction.h"

/**
 * This sends the synching and the necessary messages to the sensor
 * in order to get the network synchronized with all other peices
 * of the network.
 */
void init_wireless_sensor(u8 sensor_number){

	// start by checking the network,
	// get the linkID_t for each sensors
	// 	- request sensor number
	// 	- set the linkID in the struct
	//	- build sensor_data struct

	linkID_t address = sensor_database_t[sensor_number].sensor_link_id;
	check_network();

	// 	- rx, tx ack
	modes.receiver->receive_sensor_response(address);
	if(sensor_state == ACK)
		modes.sensors_arbitrator->ping_ack(address);
	else
		goto error;

	//	- tx, rx configs
	modes.sensors_arbitrator->send_config_req(address);
	modes.receiver->receive_sensor_response(address);
	if(sensor_state != CONFIGS)
		goto error;

	//	- tx, rx status
	modes.sensors_arbitrator->send_status_req(address);
	modes.receiver->receive_sensor_response(address);
	if(sensor_state != STATUS)
		goto error;

	//	- tx, rx sync
	modes.sensors_arbitrator->send_sync(address);
	modes.receiver->receive_sensor_response(address);
	if(sensor_state != SYN)
		goto error;

	//	- tx pause
	modes.sensors_arbitrator->send_pause(address);
	return;

	error:
		packet_error();
		net_error();
		return;
}

/**
 * This function sends the start command to a specific sensor, which
 * in turn starts the data stream from that particular sensor at a rate
 * given by the sync rate.
 */
void start_wireless_sensor(u8 sensor_number){
	modes.sensors_arbitrator->send_start(sensor_database_t[sensor_number].sensor_link_id);
}

// Starts all sensors
void start_all_wireless_sensors(){
	for(register u8 i = 0; i < sizeof(sensor_database_t); i ++){
		start_sensor(i);
	}
}

/**
 * This function sends the stop command to the specific command and thus
 * stops teh communications with that sensor. Although the sensor is still
 * connected to the network the data stream is stopped.
 */
void stop_wireless_sensor(u8 sensor_number){
	modes.sensors_arbitrator->send_stop(sensor_database_t[sensor_number].sensor_link_id);
}

// Stops all sensors
void stop_all_wireless_sensors(){
	for(register u8 i = 0; i < sizeof(sensor_database_t); i ++){
		stop_sensor(i);
	}
}

/**
 * This function resets the specific sensor and thus disconnects the sensor
 * from the network, by resetting the sensor node.
 */
void reset_wireless_sensor(u8 sensor_number){
	modes.sensors_arbitrator->send_abort(sensor_database_t[sensor_number].sensor_link_id);
}

// Resets all sensors
void reset_all_wireless_sensors(){
	for(register u8 i = 0; i < sizeof(sensor_database_t); i ++){
			reset_sensor(i);
	}
}

// Associates the linkId_t to numbers that we can read
void _associate_linkID_t (){

	// gain access to the network table,
	// send sensor number request,
	// assign network number to the sensor database


}

