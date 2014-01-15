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
#include "utilities.h"
#include "configs.h"

#define SEC_1 		32768

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

// This adds one to the system error.
void system_error(){


	// add one event to the counter.
	sys_errors.system_errors_cnt ++;

	// stop the scheduler
	stop_scheduler();

	// this is a fatal error
	system_integrity_flag.system_intergrity_flag = 1;

	// set if we need to print
	lcd = SYSTEM;

	// check if we need to do something
	_check_errors(&sys_errors);
	return;

}

/**
 * This checks for errors through out the system, and intterupts
 * the display to display the errors is there are any.
 */
void _check_errors(struct system_error_t* events){

	if((events->command_errors_cnt > CMD_MAX_ERROR) ||
			(events->network_errors_cnt > NET_MAX_ERROR) ||
			(events->packet_errors_cnt > PACKET_MAX_ERROR) ||
			(events->sensor_errors_cnt > SENSOR_MAX_ERROR) ||
			(events->system_errors_cnt > SYSTEM_MAX_ERROR)){


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
			(events->sensor_errors_cnt > ERROR_HIGH)||
			(events->system_errors_cnt > ERROR_HIGH)){

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

		// De-assert the flag
		system_integrity_flag.system_intergrity_flag = 0;

		// Print a reboot message
		error_state = REBOOT; lcd = SYSTEM;
		_print_error(lcd, error_state);

		// Wait 1 seconds
		Timer0_A3_Start(SEC_1);

		// Reboot
		reboot();
	}

	// reset the print state
	lcd = NAN;
}

/**
 * This function prints an error event on the
 * hardware LCD.
 */
void _print_error(error_lcd lcd, error_state_t error_state){

	// Create the lcd struct
	struct lcd_struct_t lcd_struct;

	// Clear the display
	clear_display();

	switch (lcd){
		case NET:
			// Network error
			lcd_struct.lcd_string_L1 = "NET ER";
			break;

		case PACKET:
			// Packet error
			lcd_struct.lcd_string_L1 = "PKT ER";
			break;

		case CMD:
			// Command error
			lcd_struct.lcd_string_L1 = "CMD ER";
			break;

		case SENSOR:
			// Sensor error
			lcd_struct.lcd_string_L1 = "SEN ER";
			break;

		case SYSTEM:
			// System error
			lcd_struct.lcd_string_L1 = "SYS ER";
			break;

		default:
			l1_string = NULL;
			break;
	}
	switch (error_state){
		case LOW_ERROR:
			// LOW
			lcd_struct.lcd_string_L2 = "LOW";
			break;

		case HIGH_ERROR:
			// HIGH
			lcd_struct.lcd_string_L2 = "HIGH";
			break;

		case MAX_ERROR:
			// MAX
			lcd_struct.lcd_string_L2 = "MAX";
			break;

		case REBOOT:
			// REBOOT
			lcd_struct.lcd_string_L2 = "REB";
			break;
	}
	if(NULL != l1_string){
		display_chars(LINE1, lcd_struct.lcd_string_L1, SEG_ON);
		display_chars(LINE2, lcd_struct.lcd_string_L2, SEG_ON);
	}
}

/**
 * This function cycles through the error states
 * and displays them on the lcd. This function is called
 * by the menu functions....
 */
void _cycle_errors(error_state){

	_print_error(NET, error_state);

	// Wait 1 seconds
	Timer0_A3_Start(SEC_1);
	_print_error(PACKET, error_state);

	// Wait 1 seconds
	Timer0_A3_Start(SEC_1);
	_print_error(CMD, error_state);

	// Wait 1 seconds
	Timer0_A3_Start(SEC_1);
	_print_error(SENSOR, error_state);

	// Wait 1 seconds
	Timer0_A3_Start(SEC_1);
	_print_error(SYSTEM, error_state);
	// Wait 1 seconds
	Timer0_A3_Start(SEC_1);
}


