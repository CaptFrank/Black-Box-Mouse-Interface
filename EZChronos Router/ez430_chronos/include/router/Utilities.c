/*
 * Utilities.c
 *
 *  Created on: Nov 20, 2013
 *      Author: francis-ccs
 */

#include "battery.h"
#include "Configs.h"
#include "error_handler.h"
#include "callback_functions.h"

/**
 * These are the utility functions used in the main code.
 * They are implemented in order to add functionality
 * to the watch.
 */

/******************************************************
 * 				ROUTER STATE MANAGEMENT
 ******************************************************/

void set_router_mode(u8 router_mode){

	// Set the router mode to the passed mode
	router_state.router_state_byte = router_mode;
}

/**
 * Gets the router mode.
 */
u8 get_router_mode(){

	// Gets the router mode
	return router_state.router_state_byte;
}

/**
 * Resets the router mode
 */
void reset_router_mode(){

	// Reset the state of the router
	set_router_mode(ON_RESET);
}

/***************************************************
*				POWER STATUS
***************************************************/

/**
 * This function checks if the power state is good
 * or not and returns if the power rate is not
 * adequate.
 */
void check_power_status(){

	// If the power is over the threshold.
	if(sBatt.voltage > BATTERY_HIGH_THRESHOLD){
		power_state = POWER_OVER;

	// If the power is lower than the threshold
	}else if(sBatt.voltage < BATTERY_LOW_THRESHOLD){
		power_state = POWER_LOW;

	// If the power is good
	}else {
		power_state = POWER_GOOD;
	}
}

/**
 * This function returns the power state.
 */
power_state_t get_power_status(){

	// get the power state.
	return power_state;
}

/***************************************************
*				ERROR STATUS
***************************************************/

/**
 * Checks the error status and returns if the threshold
 * is exceeded.
 */
void check_error_status(){

	// Max errors reached...
	// 	- Reboot device.
	if(errors > ERROR_MAX){

		// Assign the new error state
		error_state = MAX_ERROR;

		// Assign the error state to the flags
		router_state.state_bits.error = ON;

		// Assign the stop bit
		router_state.state_bits.stop = ON;

		// Restart the router.
		router_state.state_bits.off = ON;

	}else if(errors > ERROR_HIGH){

		// Assign the new error state
		error_state = HIGH_ERROR;

		// Assign the new flags.
		router_state.state_bits.error = ON;

	}else if(errors > ERROR_LOW){

		// Assign the new error state
		error_state = LOW_ERROR;

	}else {

		// Assign the OK state.
		error_state = OK;
	}

}

/**
 * Returns the error status. (GOOD vs BAD)
 */
u8 get_error_status(){

	// return the error_state;
	return error_state;
}

/***************************************************
*				NETWORK STATUS
***************************************************/

/**
 * This checks the network by pinging each sensor.
 *  	- from 1 -> 8
 *  	- gets the total amount of sensors
 */
void check_network(){

	for(register u8 i = 0; i > MAX_SENSORS; i ++){

		// if our check sensor ping worked
		if(check_sensor(sensors[i])){

			// add them to the list
			(*network_sensors.sensors)[0] |= 1 << i ;

			// add them to enabled list
			(*enabled_sensors.sensors)[0] |= 1 << i;
		}
	}
}

/**
 * This checks a given address... or sensor.
 */
bool check_sensor(linkID_t address){

	// first ping the sensor on transport level
	if(SMPL_SUCCESS == SMPL_Ping(address)){

		// Ping using application layer
		modes.sensors_arbitrator.ping_ack(address);

		// receive the ack return.
		modes.receiver.receive_sensor_response(address);

		// Check if we got an ACK back.
		if(sensor_state == ACK){
			return true;
		}

		// Command issues
		command_error();
		return false;

	// Something went wrong
	}else{

		modes.sensors_arbitrator->send_abort(address);
		modes.sensors_arbitrator->send_error(address);
		// Sensor is in an unknown state.
		sensor_error();
		return false;
	}
}

