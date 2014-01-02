/**
 * router_main.h
 *
 *  Created on: Nov 5, 2013
 *      Author: Francis Papineau
 */

#ifndef ROUTER_MAIN_H_
#define ROUTER_MAIN_H_

/**
 * This file will contain only the main functionality of the router
 * and will have the main state machine implementation. All of the work
 * functions will be implemented otherwise in other files.
 */

/**
 * This function will setup the main router structures, such as the
 * packet containers and the data containers to contain:
 * 		- Temperature
 * 		- Altitude
 * 		- Accelerometer
 * 		- Pressure
 */
void init_stuctures(void);

/**
 * This function initializes the function callbacks that are used
 * for either sending or receiving data.
 * 		- RxCallback_Function
 * 		- TxCallback_Function
 */
void init_function_callbacks(void);

/**
 * This function initializes the packet handlers, that are needed
 * to handle either type of packet; Sensor or Base Station packets.
 * Both of which will have a set o packet decoders and handlers to
 * decode and analyze the divers packets.
 * 		- Decoders
 * 		- Handlers
 */
void init_handlers(void);

/**
 * This function is used to initialize the router global variable
 * context to run, and sets the flags as well as the mutex.
 */
void init_router_context(void);

/**
 * This function will run the state machine for the router...
 */
void run_router(void);

/**
 * This function will stop the router functionnality.
 */
void stop_router(void);

/**
 * This function will exit the router application with an
 * error.
 */
void stop_router_error(u8 error_code);

/**
 * This associates the linkID to the comprehensible sensor number.
 */
void _check_link_ID_association(void);

#endif /* ROUTER_MAIN_H_ */
