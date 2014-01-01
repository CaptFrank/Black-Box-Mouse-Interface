/*
 * Utilities.h
 *
 *  Created on: Nov 20, 2013
 *      Author: francis-ccs
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_


/***************************************************
*				STATE MEASUREMENT
***************************************************/

/**
 * Sets the router mode.
 */
void set_router_mode(u8 router_mode);

/**
 * Gets the router mode.
 */
u8 get_router_mode();

/**
 * Resets the router mode
 */
void reset_router_mode();

/***************************************************
*				POWER STATUS
***************************************************/

// These are the available power states.
typedef enum {

	POWER_OVER,
	POWER_GOOD,
	POWER_LOW

}power_state_t;

power_state_t power_state;

/**
 * This function checks if the power state is good
 * or not and returns if th epower rate is not
 * adequate.
 */
void check_power_status();

/**
 * This function returns the power state.
 */
power_state_t get_power_status();

/***************************************************
*				ERROR STATUS
***************************************************/

/**
 * Checks the error status and returns if the threshold
 * is exceeded.
 */
void check_error_status();

/**
 * Returns the error status. (GOOD vs BAD)
 */
u8 get_error_status();

/**
 * This sets the error threshold. (Default = 10)
 */
void set_error_threshold(u8 threshold);

/***************************************************
*				NETWORK STATUS
***************************************************/

/**
 * This checks the network by pinging each sensor.
 *  	- from 1 -> 8
 *  	- gets the total amount of sensors
 */
void check_network();

/**
 * This checks a given address... or sensor.
 */
bool check_sensor(u8 address);

/***************************************************
*				POWER MANAGER
***************************************************/

// Reboot vector definition
static void(*reboot) (void) = 0;

// Sleeps the device
void sleep();

#endif /* UTILITIES_H_ */
