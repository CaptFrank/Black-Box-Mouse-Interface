/*
 * error_handler.h
 *
 *  Created on: Nov 27, 2013
 *      Author: Francis Papineau
 */

#ifndef ERROR_HANDLER_H_
#define ERROR_HANDLER_H_

#define PACKET_ERROR_MAX	10
#define CMD_ERROR_MAX		10
#define NET_ERROR_MAX		20
#define SENSOR_ERROR_MAX	20
#define SYSTEM_MAX_ERROR	10

#define ERROR_HIGH			8
#define ERROR_LOW			4
#define ERROR_OK			2

// Define the errors in the system
typedef u8 error_t;
error_t errors;

// Define the errors to print
typedef enum {

	NAN,
	NET,
	PACKET,
	CMD,
	SENSOR,
	SYSTEM

} error_lcd;
error_lcd lcd;

// Defines the error type strcture
struct system_error_t {

	u8 network_errors_cnt;
	u8 packet_errors_cnt;
	u8 command_errors_cnt;
	u8 sensor_errors_cnt;
	u8 system_errors_cnt;
}sys_errors;

// Define the error states.
typedef enum{

	// Running ok
	OK,

	// Low errors
	LOW_ERROR,

	// Close to threshold
	HIGH_ERROR,

	// At threshold...
	MAX_ERROR,

	// This is only used when the system integrity flag is set
	// or when we need to reboot the system
	REBOOT

}error_state_t;
error_state_t error_state;

/**
 * This adds one event to the network error
 * structure.
 */
void net_error();

/**
 * This adds one event to the packet error
 * structure.
 */
void packet_error();

/**
 * This adds one event to the command error
 * strucuture.
 */
void command_error();

/**
 * This adds one event to the sensor error
 * structure
 */
void sensor_error();


/**
 * This adds one event to the system error
 * structure
 */
void system_error();

/**
 * This checks for errors through out the system.
 */
void _check_errors(struct system_error_t* events);

/**
 * This function prints an error event on the
 * hardware LCD.
 */
void _print_error(error_lcd* lcd, error_state_t* error_state);

/**
 * This function cycles through the error states
 * and displays them on the lcd. This function is called
 * by the menu functions....
 */
void _cycle_errors(struct lcd_struct_t* lcd,
		struct system_error_t* events);

#endif /* ERROR_HANDLER_H_ */
