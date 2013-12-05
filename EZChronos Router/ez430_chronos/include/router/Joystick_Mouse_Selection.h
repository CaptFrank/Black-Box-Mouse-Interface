/*
 * Joystick_Mouse_Selection.h
 *
 *  Created on: Nov 20, 2013
 *      Author: francis-ccs
 */

#ifndef JOYSTICK_MOUSE_SELECTION_H_
#define JOYSTICK_MOUSE_SELECTION_H_

#include "Configs.h"
#include "display.h"
#include "error_handler.h"
#include "timer.h"

#define SEC_5	163840

/**
 * This file contains the prototypes for the selection routine
 * that takes place in the boot up sequence, in order to select
 * if we are using a mouse template or a joystick template.
 */

inline structure_choice_t get_selection(){

	// the selected choice.
	u8 selected = 0x00;
	structure_choice_t choice = NONE;

	// Display the choice screen
	clear_display();
	display_chars(LINE1, (u8*)"SELECT:", SEG_ON);
	display_chars(LINE2, (u8*)"M OR J", SEG_ON);

	// Start blinking
	start_blink();

	// Wait 5 seconds
	Timer0_A3_Start(SEC_5);

	// Do a check until 5sec has elapsed.
	while(!TA0R){
		if((!selected)){
			choice = _check_selection(selected);
		}
	}

	/**
	 * Assign appropriate structures.
	 */
	_assign_data_struct(choice);
	return;
}

inline structure_choice_t _check_selection(u8 selected, structure_choice_t choice){

	// Check to see if the buttons were pressed
	if(BUTTON_NUM_IS_PRESSED){

		// mouse was chosen
		choice = MOUSE;
		selected = 0x01;
	}else if(BUTTON_DOWN_IS_PRESSED){

		// joystick was chosen
		choice = JOYSTICK;
		selected = 0x01;
	}else{

		// nothing was chosen
		choice = NONE;
		selected = 0x00;
	}

	// return our choice
	return choice;
}

inline void _assign_data_struct(structure_choice_t choice){

	// if the mouse was chosen
	if(choice == MOUSE){

		// assign the mouse report
		structure_choice = (void*)mouse_report;

	// if the joystick was chosen
	}else if(choice == JOYSTICK){

		// assign the joystick report
		structure_choice = (void*)joystick_report;

	}else {
		// something went wrong
		system_error();
	}
}

#endif /* JOYSTICK_MOUSE_SELECTION_H_ */
