/*
 * scheduler.h
 *
 *  Created on: Dec 4, 2013
 *      Author: francis-ccs
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include "configs.h"
#include "user_sensor_configs.h"

/**
 * This file contains the round robin scheduler for the
 * creation and getting of the usb report sent to the
 * ground station.
 *
 * 		we use the Configs.h
 * 		-	enabled_sensors
 * 		- 	network_sensors
 *
 * 		To determine the next course of action.
 */

#define ROUTER_ACK			1
#define ROUTER_CONFIG		2
#define ROUTER_STATUS		3
#define ROUTER_SYNC			4
#define ROUTER_START		5

// This state is called numerous times in order to
// receive the packets from the sensor nodes.
#define SENSOR_POLL			6

struct scheduler_t {

	// Serial id for tracking
	u8 uid;

	// The sensor inputs
	u8 sensor_inputs [8];
}scheduler;

/**
 * This initializes the scheduler.
 * 	- Starts at the 0 state;
 */
void init_scheduler();

/**
 * This function starts the process forking for
 * every stage of the rx and tx of the network.
 */
void start_scheduler();

/**
 * This pauses the scheduler for interrupt servicing
 * and error passing as well as the interruption of the
 * message passing between the sensor node and the base station.
 */
void pause_scheduler();

/**
 * This kills the scheduler process. This is triggered
 * by a fatal error or a key combo on the error menu.
 */
void stop_scheduler();

/**
 * This resets the scheduler handle and sets it to NULL.
 */
void reset_scheduler();


#endif /* SCHEDULER_H_ */
