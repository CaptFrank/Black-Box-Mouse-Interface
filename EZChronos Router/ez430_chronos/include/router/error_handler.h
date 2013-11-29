/*
 * error_handler.h
 *
 *  Created on: Nov 27, 2013
 *      Author: Francis Papineau
 */

#ifndef ERROR_HANDLER_H_
#define ERROR_HANDLER_H_

#define ERROR_MAX			10
#define ERROR_HIGH			8
#define ERROR_LOW			4
#define ERROR_OK			2

// Define the errors in the system
typedef u8 error_t;
error_t errors;

// Define the error states.
typedef enum{

	// Running ok
	OK,

	// Low errors
	LOW_ERROR,

	// Close to threshold
	HIGH_ERROR,

	// At threshold...
	MAX_ERROR

}error_state_t;
error_state_t error_state;

void net_error();

void packet_error();

void command_error();

void sensor_error();

#endif /* ERROR_HANDLER_H_ */
