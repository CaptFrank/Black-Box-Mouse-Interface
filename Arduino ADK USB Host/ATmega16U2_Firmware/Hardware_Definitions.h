/*
 * Hardware_Definitions.h
 *
 * Created: 9/18/2013 10:53:52 AM
 *  Author: Administrator
 */ 


#ifndef HARDWARE_DEFINITIONS_H_
#define HARDWARE_DEFINITIONS_H_

/************************************************************************/
/*
This is the hardware definitions for the device platform. This is the
file where we would define what kind of device we are using. This can
be either a Joystick, a Mouse, or a Combination of the two.

*** Note:
	This file can only define one interface. ONLY ONE device at a time
	can be defined.
*/
/************************************************************************/

/*
 * This definition enables the mouse interface. The data will map to a 
 * mouse device driver.
 */
#define MOUSE_REPORT

/*
 * This definition enables the joystick interface. The data will map to a
 * joystick device driver.
 */
//#define JOYSTICK_REPORT

/* 
 * This definition enables both the mouse and joystick interface. 
 * The data will be mapped to both a mouse device driver, and 
 * a joystick device driver.
 */
///#define MOUSE_JOYSTICK_REPORT


#endif /* HARDWARE_DEFINITIONS_H_ */
