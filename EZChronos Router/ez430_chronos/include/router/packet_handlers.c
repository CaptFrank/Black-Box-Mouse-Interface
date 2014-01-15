/*
 * packet_handlers.c
 *
 *  Created on: Nov 5, 2013
 *      Author: Francis Papineau
 */

#include "packet_handlers.h"
#include "callback_functions.h"
#include "error_handler.h"
#include "configs.h"
#include "user_sensor_configs.h"

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

	// Initiate the rx and tx uids and other tracking
	// parameters.
	tx_buf.uid = 0x122;
	rx_buf.uid = 0x123;
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
 * the arduino based on the configs and the sensor data. This is
 * only pertaining to the data stream of the device.
 */
void create_usb_report(u8 sensor_id){

/**
 * This function creates the usb report from the data
 * received from the remote sensors and the local sensors which are
 * enabled.
 */

	// Get the packet buffer and wrap it with our packet header
	// that the base station can understand.
	if(sensor_state == DATA){

		// We update the packet that is going to be sent.
		_update_tx_packet(choice);

	}else {
		// If there is an error in the packet stream
		sys_errors.packet_errors_cnt ++;
	}
}

/**
 * This function sends the data packet to the base station node.
 */
void send_usb_report(){

	// Sends the usb report to the base station
	send_sensor_data();
}

/**
 * This function looks at the config of the device and creates a
 * usb report (data packet).
 */
void _update_tx_packet(structure_choice_t configs){

	// concat the packets.
	// Mouse selected
	if(configs == MOUSE){
		// Assign values
		// Buttons
		mouse_report.buttons |= BUTTON_1;
		mouse_report.buttons |= BUTTON_2 << 1;
		mouse_report.buttons |= BUTTON_3 << 2;
		mouse_report.buttons |= BUTTON_4 << 3;
		mouse_report.buttons |= BUTTON_5 << 4;

		// Axis
		mouse_report.x = AXIS_1;
		mouse_report.y = AXIS_2;

		// Wheel
		mouse_report.wheel = WHEEL;
	}

	else if(configs == JOYSTICK){
		// Assign values
		// Buttons
		joystick_report.buttons |= BUTTON_1;
		joystick_report.buttons |= BUTTON_2 << 1;
		joystick_report.buttons |= BUTTON_3 << 2;
		joystick_report.buttons |= BUTTON_4 << 3;
		joystick_report.buttons |= BUTTON_5 << 4;

		// Axis
		joystick_report.x = AXIS_1;
		joystick_report.y = AXIS_2;
		joystick_report.z = AXIS_3;
	}
	else {
		// Error and system is compromized
		system_integrity_flag = 1;
		sys_error();
	}
}
