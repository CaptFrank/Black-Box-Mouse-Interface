/*
 * error_menu.c
 *
 *  Created on: Dec 27, 2013
 *      Author: Francis Papineau
 */
#include "user.h"
#include "string.h"

// system
#include "project.h"

// driver
#include "display.h"

#include "error_menu.h"
#include "stdio.h"

/**
 * This function updates the error values on the
 * error menu.
 */
void update_error_menu(){

    // Move the text
    u8 firstElem = error_menu_handler.msg[0];
    u8 len = sizeof(error_menu_handler.msg) / sizeof(u8);

    // Advance the test characters in the array
    for(u8 i = 0; i < len - 1; i++) error_menu_handler.msg[i] =
    		error_menu_handler.msg[i+1];

    // Get the new first element
    error_menu_handler.msg[len - 1] = firstElem;

    // Set display update flag
    display.flag.update_error_menu = 1;
}

/**
 * This is the utility function to display the error
 * count data.
 */
void display_main_error_menu(u8 line, u8 update){

	// If we need a full update
    if (update == DISPLAY_LINE_UPDATE_FULL)
    {
    	// Display the message in the first segment
        display_chars(LCD_SEG_L1_3_0, error_menu_handler.msg, SEG_ON);

        // Start the heart beat symbol in blink mode.
        display_symbol(LCD_ICON_HEART, SEG_ON_BLINK_ON);

        // Set mode
        error_menu_handler.mode = ERROR_MENU_ON;
    }
    else if (update == DISPLAY_LINE_UPDATE_PARTIAL)
    { // If the display only need a partial update

    	// Update the message only
        display_chars(LCD_SEG_L1_3_0, error_menu_handler.msg, SEG_ON);
    }
    else if (update == DISPLAY_LINE_CLEAR)
    {
        display_symbol(LCD_ICON_HEART, SEG_OFF);

        reset_error_menu();
    }
}

/**
 * Reset the error menu
 */
void reset_error_menu(void){

	// Reset the mode of the menu
	error_menu_handler.error_menu_state = ERROR_MENU_OFF;

	// Update the error count
	error_menu_handler.command_errors_cnt =
			sys_errors.command_errors_cnt;

	error_menu_handler.network_errors_cnt =
			sys_errors.network_errors_cnt;

	error_menu_handler.packet_errors_cnt =
			sys_errors.packet_errors_cnt;

	error_menu_handler.sensor_errors_cnt =
			sys_errors.sensor_errors_cnt;

	// Create a string with the error values
	sprintf(error_menu_handler.msg, "CMD:%d NET:%d PKT:%d SENS:%d",
			error_menu_handler.command_errors_cnt,
			error_menu_handler.network_errors_cnt,
			error_menu_handler.packet_errors_cnt,
			error_menu_handler.sensor_errors_cnt);
}

/**
 * Check if the error menu is on.
 */
u8 is_error_menu_active(void){

	// Return true if the mode of the error menu is ON
	return error_menu_handler.mode == ERROR_MENU_ON;
}

