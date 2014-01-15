/*
 * scheduler.c
 *
 *  Created on: Dec 4, 2013
 *      Author: francis-ccs
 */

#include "project.h"
#include "configs.h"
#include "scheduler.h"
#include "router_main.h"
#include "timer.h"
#include "user_sensor_configs.h"

// Init the sensor scheduler
void init_scheduler(){

	// Set the tracker
	scheduler.uid = 0x24;

	// Set the state machine
	scheduler.state = INIT_SCHEDULER;

	for(register u8 i = 0; i < sizeof(sensor_database_t); i++){
		init_sensor(sensor_database_t[i].sensor_number);
	}
	// Start the scheduler
	start_scheduler();
}

// Starts the sensor data thread
void start_scheduler(){

	// move state
	scheduler.state ++;

	// Start the sensors
	for(register u8 i = 0; i < sizeof(sensor_database_t); i++){
		start_sensor(sensor_database_t[i].sensor_number);
	}

	// while not stopped
	while (!scheduler.stop_guard){
		/**
		 * This is where we would schedule the sensor addressing
		 * from the sensor address map.
		 *
		 * 	- We send the commands to each sensor in sequence.
		 * 	- The sensor addressing is done in sequence.
		 */

		// poll data for the sensor
		modes.receiver->receive_sensor_response(sensor_database_t[i].sensor_link_id);

		// Move to the new sensor
		i = (i + 1) % MAX_SENSORS;

		// Wait one / 5 sec
		Timer0_A4_Delay(SEC_1 / 5);

		// poll for commands from the base station if there is one
		modes.receiver->receive_command();

		// Run the router routines
		run_router();
	}

}

// Stop the scheduler
void stop_scheduler(){

	// Set the stop guard
	scheduler.stop_guard = 1;
}

// Reset the scheduler
void reset_scheduler(){

	// Reset the scheduler
	init_scheduler();
}
