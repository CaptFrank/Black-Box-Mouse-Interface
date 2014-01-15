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
 * creation and getting of the usb report data from the
 * remote sensors.
 *
 * 		we use the Configs.h
 * 		-	enabled_sensors
 * 		- 	network_sensors
 *
 * 		To determine the next course of action.
 */

// This state is called numerous times in order to
// receive the packets from the sensor nodes.
#define SENSOR_POLL			6

// Defines the start of the scheduler init.
#define INIT_SCHEDULER		0

// State machine enum
enum scheduler_state_t{

	INIT_SCHED,
	RUN_SCHED,
	UPDATE_SCHED,
	STOP_SCHED,
	RESET_SCHED

} scheduler_state;

scheduler_state_t scheduler_state[5];

struct scheduler_t {

	// Serial id for tracking
	u8 uid;

	// Atomic bool guard
	u8 stop_guard;

	// The state
	u8 state;

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
 * This kills the scheduler process. This is triggered
 * by a fatal error or a key combo on the error menu.
 */
void stop_scheduler();

/**
 * This resets the scheduler handle and sets it to NULL.
 */
void reset_scheduler();


#endif /* SCHEDULER_H_ */
