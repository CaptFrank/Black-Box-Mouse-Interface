/*
 * user_sensor_configs.h
 *
 *  Created on: Jan 1, 2014
 *      Author: Francis Papineau
 */

#ifndef USER_SENSOR_CONFIGS_H_
#define USER_SENSOR_CONFIGS_H_

#include "project.h"
#include "acceleration.h"
#include "altitude.h"
#include "configs.h"

// External definitions
extern accel sAccel;
extern alt sAlt;

// Hardware acceleration definitions
#define ACCELEROMETER_1 			(u8)sAccel.xyz[0]; // x
#define ACCELEROMETER_2				(u8)sAccel.xyz[1];	// y
#define ACCELEROMETER_3				(u8)sAccel.xyz[2]; // z

// Hardware altitude definitons
#define ALTITUDE					(u16)sAlt.altitude;
#define PRESSURE 					(s16)sAlt.pressure;

// Hardware system button definitons
#define SYSTEM_BUTTON_STAR			(u8)BUTTON_STAR_IS_PRESSED
#define SYSTEM_BUTTON_NUM			(u8)BUTTON_NUM_IS_PRESSED
#define SYSTEM_BUTTON_UP			(u8)BUTTON_UP_IS_PRESSED
#define SYSTEM_BUTTON_DOWN			(u8)BUTTON_DOWN_IS_PRESSED
#define SYSTEM_BUTTON_BACKLIGHT		(u8)BUTTON_BACKLIGHT_IS_PRESSED
#define NONE						0

static sensor_type sensor_types[MAX_SENSORS] =  {
												WIRED,
												WIRED,
												WIRED
												};
#define NUMBER_OF_WIRELESS_SENSORS	0

/**
 * This file is the user config file for the sensor map
 *
 * - TYPES OF INPUTS
 * 	- SYSTEM_BUTTONS
 * 		- SYSTEM_BUTTON_STAR
 * 		- SYSTEM_BUTTON_NUM
 * 		- SYSTEM_BUTTON_UP
 * 		- SYSTEM_BUTTON_DOWN
 * 		- SYSTEM_BUTTON_BACKLIGHT
 *
 * 	- ACCELEROMETER
 * 		- ACCELEROMETER_1 (x)
 * 		- ACCELEROMETER_2 (y)
 * 		- ACCELEROMETER_3 (z)
 * 	- ALTIMETER
 * 		- ALTITUDE
 * 		- PRESSURE
 * 	- SENSOR_NUMBER
 * 		- REMOTE_1
 * 		- REMOTE_2
 * 		- ...
 */

// SELECT MOUSE OR JOYSTICK
#define MOUSE_CHOICE
//#define JOYSTICK

#define NETWORK_ENABLE
#ifdef NETWORK_ENABLE
	const u8 base_station_address = { 0, BASE_STATION_ADDRESS };
#endif

#define BASE_STATION_ADDRESS		0x00, 0x00, 0x00, 0x00

#ifdef MOUSE_CHOICE

	#define BUTTON_1				SYSTEM_BUTTON_STAR
	#define BUTTON_2				SYSTEM_BUTTON_NUM
	#define BUTTON_3				SYSTEM_BUTTON_UP
	#define BUTTON_4				SYSTEM_BUTTON_DOWN
	#define BUTTON_5				SYSTEM_BUTTON_BACKLIGHT

	#define AXIS_1					ACCELEROMETER_1
	#define AXIS_2					ACCELEROMETER_2
	#define WHEEL					ALTITUDE

#endif

#ifdef JOYSTICK_CHOICE

#define BUTTON_1				SYSTEM_BUTTON_STAR
#define BUTTON_2				SYSTEM_BUTTON_NUM
#define BUTTON_3				SYSTEM_BUTTON_UP
#define BUTTON_4				SYSTEM_BUTTON_DOWN
#define BUTTON_5				SYSTEM_BUTTON_BACKLIGHT

#define AXIS_1					ACCELEROMETER_1
#define AXIS_2					ACCELEROMETER_2
#define AXIS_3					ACCELEROMETER_3

#endif

#endif /* USER_SENSOR_CONFIGS_H_ */
