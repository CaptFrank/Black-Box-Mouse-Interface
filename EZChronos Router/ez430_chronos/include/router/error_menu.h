/*
 * error_menu.h
 *
 *  Created on: Dec 27, 2013
 *      Author: Francis Papineau
 */

#ifndef ERROR_MENU_H_
#define ERROR_MENU_H_

enum {

	UPDATE,
	DISPLAY,
	CLEAR
}error_menu_state;

// This is the
struct error_menu_handler_t{

	u8 network_errors_cnt;
	u8 packet_errors_cnt;
	u8 command_errors_cnt;
	u8 sensor_errors_cnt;

	error_menu_state state;

}error_menu_handler;

/**
 * This function updates the error values on the
 * error menu.
 */
void update_error_menu();

/**
 * This function runs the error menu.
 */
void run_error_menu();

/**
 * This function displays the error values on the
 * error menu.
 */
void display_main_error_menu();

/**
 * This function displays the secondary error menu,
 * presumably the comms errors and packet errors.
 */
void display_secondary_error_menu();

#endif /* ERROR_MENU_H_ */
