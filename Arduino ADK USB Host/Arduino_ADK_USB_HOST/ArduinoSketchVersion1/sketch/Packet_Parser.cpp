/*
 * Sensor_PACKET_PARSER.c
 *
 *  Created on: Jul 13, 2013
 *      Author: francispapineau
 */
#include "Packet_Parser.h"

//! Default constructor
PACKET_PARSER::PACKET_PARSER(){}

void PACKET_PARSER::set_handler(PACKET_HANDLER* packet_handler){
	this->_packet_handler = packet_handler;
}

//! Parse the structures.
void PACKET_PARSER::parse(void *arg, byte packet_id, byte packet_ver,
		void *buf) {
	
	//! Process String
	((PACKET_PARSER*) arg)->_parse(packet_id, packet_ver, buf);
}

//! Check if a specific packet was read.
bool PACKET_PARSER::_check_read_packet(byte packet_type){
	if((!this->_packet_handler->_guard_bool) || !(this->_packet_handler->_packet_id == packet_type)){
#ifdef DEBUG_LEDs
		debug_api.set_leds(REBOOT_ERROR);
#endif
		error();
	}
	return true;
}

//! Check the memory space
void PACKET_PARSER::_check_memory_space(size_t mem_space) {

	//! Check memory integrity
	if (memory_check() <= mem_space)
#ifdef DEBUG_LEDs
		debug_api.set_leds(MEMORY_ERROR);
#endif
	error();
}

//! Check packet integrity
bool PACKET_PARSER::_check_packet_integrity(char* packet) {

	//! Checks length, Header, Tail
	if (packet[2] > EMPTY)
		if (packet[0] == '+')
			if (packet[sizeof(packet) - 1] == '*')
				return true;

	return false;
}

//! Checks the ack signal
void PACKET_PARSER::_check_ack() {
	if (this->_ack.ack) {
		return;
	} else {
#ifdef DEBUG_LEDs
		debug_api.set_leds(REBOOT_ERROR);
#endif
		error();
	}
}

//! Checks the heartbeat signal
void PACKET_PARSER::_check_heartbeat() {

	//! Checks the heartbeat of the remote device.
	if (_heartbeat.battery_voltage < MIN_BATT_LEVEL) {
#ifdef DEBUG_LEDs
		debug_api.set_leds(INFO_ERROR);
#endif
#ifdef DEBUG
		char* debug_info;
		sprintf(debug_info, "[SENSOR %d]: Battery level low", _header.sensor_id);
		DEBUG_SERIAL.println(debug_info);
#endif
	}

	if (_heartbeat.router_mode == ERROR_MODE) {
#ifdef DEBUG_LEDs
		debug_api.set_leds(INFO_ERROR);
#endif
#ifdef DEBUG
		char* debug_info;
		sprintf(debug_info, "[ROUTER]: MODE ERROR");
		DEBUG_SERIAL.println(debug_info);
#endif
	}
}

//! Checks the router status.
void PACKET_PARSER::_check_router_status() {

	if (_status.error_count >= MAX_ROUTER_ERRORS) {
#ifdef DEBUG_LEDs
		debug_api.set_leds(INFO_ERROR);
#endif
#ifdef DEBUG
		char* debug_info;
		sprintf(debug_info, "[ROUTER]: ERRORS > MAX ERRORS");
		DEBUG_SERIAL.println(debug_info);
#endif
	}
	if (_status.router_mode == ERROR_MODE) {
		_heartbeat.router_mode = _status.router_mode;
#ifdef DEBUG_LEDs
		debug_api.set_leds(INFO_ERROR);
#endif
#ifdef DEBUG
		char* debug_info;
		sprintf(debug_info, "[ROUTER]: MODE == ERROR");
		DEBUG_SERIAL.println(debug_info);
#endif
	}
	if (_status.power_state == PWR_ERROR_MODE) {
#ifdef DEBUG_LEDs
		debug_api.set_leds(INFO_ERROR);
#endif
#ifdef DEBUG
		char* debug_info;
		sprintf(debug_info, "[ROUTER]: MODE == PWR ERROR");
		DEBUG_SERIAL.println(debug_info);
#endif
	}
	//! Redundancy to save memeory space.
	if (_status.battery_voltage < MIN_BATT_LEVEL) {
		_heartbeat.battery_voltage = _status.battery_voltage;
		_check_heartbeat();
	}
}

//! Checks Packet header
void PACKET_PARSER::_check_packet_header() {

	if (_header.message_size < 1) {
#ifdef DEBUG_LEDs
		debug_api.set_leds(INFO_ERROR);
#endif
#ifdef DEBUG
		char* debug_info;
		sprintf(debug_info, "[SENSOR %d]: Packet size < 1", _header.sensor_id);
		DEBUG_SERIAL.println(debug_info);
#endif
	}

	if (_header.packet_version != 0x01) {
#ifdef DEBUG_LEDs
		debug_api.set_leds(DEBUG_ERROR);
#endif
#ifdef DEBUG
		char* debug_info;
		sprintf(debug_info, "[ROUTER]: Packet ver. not supported", _header.packet_version);
		DEBUG_SERIAL.println(debug_info);
#endif
	}

}

//! Gets the nmap structure
void PACKET_PARSER::_get_nmap(void* buf) {

	//! cast the void buffer to nmap struct.
	router_nmap_info_t* buf_ptr;
	buf_ptr = (router_nmap_info_t*) buf;
	
	//! Get the sensor info from the packet sent.
	_alloc_mem((void*)&_nmap, sizeof(router_nmap_info_t),
		(void*) buf_ptr);
}

//! Gets the sensor configs
void PACKET_PARSER::_get_sensor_configs(void* buf) {

	//! Cast buf to class needed;
	sensor_configs_t* buf_ptr;
	buf_ptr = (sensor_configs_t*)buf;

	//! Get the sensor info from the packet sent.
	_alloc_mem((void*)&_configs, sizeof(sensor_configs_t),
			(void*) buf_ptr);
}

//! Gets the sensor data
void PACKET_PARSER::_get_sensor_data(void* buf) {

	//! Cast buf to class needed;
	remote_sensor_data_t* buf_ptr;
	buf_ptr = (remote_sensor_data_t*)buf;

	//! Checks for memory space
	_check_memory_space(sizeof(_data));

	//! Allocate the structures
	//! This allocates the received buffer to a remote sensor data 
	//! structure.
	_alloc_mem((void*) &_data, sizeof(_data), (void*) buf_ptr);
}

//! Allocate buffer
void PACKET_PARSER::_alloc_mem(void* dest_pointer, size_t size, void* buf) {
	memcpy(dest_pointer, buf, size);
}

//! Parse the packet
void PACKET_PARSER::_parse(byte packet_id, byte packet_ver, void *buf) {

	char* buffer = (char*) buf;
       char* debug_info;

	//! Check if there is space left
	_check_memory_space();

	//! Check if the string is ok to process.
	this->_check_packet_integrity((char*) buf);

	//! Assigns the new construct
	memcpy(&_header, buffer, sizeof(packet_header_t));
	_check_packet_header();

	buffer += sizeof(packet_header_t);

	switch (packet_id) {

	case ROUTER_ACK:
		_alloc_mem(&_ack, sizeof(_ack), buffer);
		_check_ack();
		return;

	case ROUTER_HEARTBEAT:
		_alloc_mem(&_heartbeat, sizeof(_heartbeat), buffer);
		_check_heartbeat();
		return;

	case ROUTER_STATUS:
		_alloc_mem(&_status, sizeof(_status), buffer);
		_check_router_status();
		return;

	case ROUTER_NMAP:
		_check_memory_space(sizeof(router_nmap_info_t));
		_get_nmap((void*) buf);
		return;

	case ROUTER_CONFIG:
		_alloc_mem(&_radio_configs, sizeof(_radio_configs), buffer);
		return;

	case SENSOR_ENABLE:
		_alloc_mem(&_en_sensors, sizeof(_en_sensors), buffer);
		return;

	case SENSOR_CONFIGS:
		_check_memory_space(sizeof(sensor_configs_t));
		_get_sensor_configs((void*) buffer);
		return;

	case SENSOR_DATA:
		_check_memory_space(sizeof(remote_sensor_data_t));
		_get_sensor_data((void*) buffer);
		return;

	case ROUTER_DEBUG:
		_alloc_mem(&_debug, sizeof(_debug), buffer);

#ifdef DEBUG
		sprintf(debug_info, "acks: %d \npckts: %d\nrx_count: %d\nsnt_rqs: %d\ntx_count: %d",
				_debug.router_acks_sent_counter, _debug.router_packet_counter,
				_debug.router_rx_count, _debug.router_sent_request_counter,
				_debug.router_tx_count);
		DEBUG_SERIAL.println(debug_info);
#endif
		return;

	case ERROR_MSG:
		_alloc_mem(&_error, sizeof(_error), buffer);

#ifdef DEBUG
		sprintf(debug_info, "[%d] %d -> %d", _error.error_code,
				_error.sensor_address, _error.sensor_id);
		DEBUG_SERIAL.println(debug_info);
#endif
		return;

	case SENSOR_NUMBER:
		_alloc_mem(&_num_sensors, sizeof(_num_sensors), buffer);
		return;

	default: //! Nothing done here
		return;
	}
}
