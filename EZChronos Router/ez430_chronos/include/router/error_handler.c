/*
 * error_handler.c
 *
 *  Created on: Nov 27, 2013
 *      Author: Francis Papineau
 */

#include "error_handler.h"
#include "router_main.h"
#include "lcd_structure.h"
#include "display.h"
#include "Configs.h"

/**
 * This adds one event to the network error
 * structure.
 */
void net_error(){

	// add one event to the counter.
	sys_errors.network_errors_cnt ++;

	// set if we need to print
	lcd = NET;

	// check if we need to do something
	_check_errors(&sys_errors);
	return;
}

/**
 * This adds one event to the packet error
 * structure.
 */
void packet_error(){

	// add one event to the counter.
	sys_errors.packet_errors_cnt ++;

	// set if we need to print
	lcd = PACKET;

	// check if we need to do something
	_check_errors(&sys_errors);
	return;
}

/**
 * This adds one event to the command error
 * strucuture.
 */
void command_error(){

	// add one event to the counter.
	sys_errors.command_errors_cnt ++;

	// set if we need to print
	lcd = CMD;

	// check if we need to do something
	_check_errors(&sys_errors);
	return;
}

/**
 * This adds one event to the sensor error
 * structure
 */
void sensor_error(){

	// add one event to the counter.
	sys_errors.sensor_errors_cnt ++;

	// set if we need to print
	lcd = SENSOR;

	// check if we need to do something
	_check_errors(&sys_errors);
	return;
}

/**
 * This checks for errors through out the system, and intterupts
 * the display to display the errors is there are any.
 */
void _check_errors(struct lcd_struct_t* lcd,
		struct system_error_t* events){

	if((events->command_errors_cnt > CMD_MAX_ERROR) ||
			(events->network_errors_cnt > NET_MAX_ERROR) ||
			(events->packet_errors_cnt > PACKET_MAX_ERROR) ||
			(events->sensor_errors_cnt > SENSOR_MAX_ERROR)){


		// Display warning.
		clear_display();
		display_chars(LINE1, (u8*)"ERROR !!", SEG_ON);

		// start blinking.
		start_blink();

		// hang until reset
		while(!reset){__no_operation();}

		// stop blinking
		stop_blink();
		stop_router_error();

	} else if((events->command_errors_cnt > ERROR_HIGH) ||
			(events->network_errors_cnt > ERROR_HIGH) ||
			(events->packet_errors_cnt > ERROR_HIGH) ||
			(events->sensor_errors_cnt > ERROR_HIGH)){

		// display high error threshold
		clear_display();
		display_chars(LINE1, (u8*)"HIGH ERR", SEG_ON);

		// Wait some time
		u8 i = 255;
		while(i--){};

		// clear display
		clear_display();

		// restore the lcd state
		display_chars(LINE1, lcd->lcd_string_L1, SEG_ON);
		display_chars(LINE2, lcd->lcd_string_L2, SEG_ON);
	}

	// reset the print state
	lcd = NAN;
}

/**
 * This function prints an error event on the
 * hardware LCD.
 */
void _print_error(error_lcd* lcd, error_state_t* error_state){

// TODO

}

/**
 * This function cycles through the error states
 * and displays them on the lcd. This function is called
 * by the menu functions....
 */
void _cycle_errors(struct system_error_t* events){

// TODO

}


