/*
 * error_menu.h
 *
 *  Created on: Dec 27, 2013
 *      Author: Francis Papineau
 */

#ifndef ERROR_MENU_H_
#define ERROR_MENU_H_

#include "Configs.h"

#define ERROR_MENU_ON		0x01
#define ERROR_MENU_OFF		0x02

// This is the
struct error_menu_handler_t {

	// Error counts.
	u8 network_errors_cnt;
	u8 packet_errors_cnt;
	u8 command_errors_cnt;
	u8 sensor_errors_cnt;

	// Error States
	u8 error_menu_state;

	// Display message
	u8 msg[35];

}error_menu_handler;

/**
 * This function updates the error values on the
 * error menu.
 */
void update_error_menu();

/**
 * This function displays the error values on the
 * error menu.
 */
void display_main_error_menu(u8 line, u8 update);

/**
 * Reset the error menu
 */
void reset_error_menu(void);

/**
 * Check if the error menu is on.
 */
u8 is_error_menu_active(void);

#endif /* ERROR_MENU_H_ */
