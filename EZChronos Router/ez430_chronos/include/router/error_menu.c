/*
 * error_menu.c
 *
 *  Created on: Dec 27, 2013
 *      Author: Francis Papineau
 */
#include "error_menu.h"

#define DISPLAY_LINE_UPDATE_FULL		0x01	// update full
#define DISPLAY_LINE_UPDATE_PARTIAL 	0x02	// update partial

/**
 * This function updates the error values on the
 * error menu.
 */
void update_error_menu(){

	// Update the error count
	error_menu_handler.state = UPDATE;

	error_menu_handler.command_errors_cnt =
			sys_errors.command_errors_cnt;

	error_menu_handler.network_errors_cnt =
			sys_errors.network_errors_cnt;

	error_menu_handler.packet_errors_cnt =
			sys_errors.packet_errors_cnt;

	error_menu_handler.sensor_errors_cnt =
			sys_errors.sensor_errors_cnt;
}

/**
 * This function runs the error menu.
 */
void run_error_menu(){

	// Update the error numbers
	update_error_menu();

	// Display the error numbers
	display_data_error();


}

/**
 * This function displays the error values on the
 * error menu.
 */
void display_main_error_menu(u8 line, u8 update){

	u8* str;
	error_menu_state state;

	// Get the new values and assign them.
	run_error_menu();

}

/**
 * This is the utility function to display the error
 * count data.
 */
void display_data_error(){


}

