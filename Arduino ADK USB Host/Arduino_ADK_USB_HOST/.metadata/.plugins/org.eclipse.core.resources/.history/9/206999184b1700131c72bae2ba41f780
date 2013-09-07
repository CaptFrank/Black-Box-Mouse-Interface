/*
 * USB_Reports.h
 *
 *  Created on: Jul 11, 2013
 *      Author: fjpapin
 */

#ifndef USB_REPORTS_H_
#define USB_REPORTS_H_

#include "../System_Defines/Main_Defines.h"

//! Mouse USB report chosen
#ifdef MOUSE_REPORT

#undef USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH
#define USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH 	54

prog_uint8_t usbHidReportDescriptor[USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH] = {

	    0x05, 0x01,                    //! USAGE_PAGE (Generic Desktop)
	    0x09, 0x02,                    //! USAGE (Mouse)
	    0xa1, 0x01,                    //! COLLECTION (Application)
	    0x09, 0x01,                    //!   USAGE (Pointer)
	    0xa1, 0x00,                    //!   COLLECTION (Physical)
	    0x85, 0x01,                    //!     REPORT_ID (1)
	    0x05, 0x09,                    //!     USAGE_PAGE (Button)
	    0x19, 0x01,                    //!     USAGE_MINIMUM (Button 1)
	    0x29, 0x03,                    //!     USAGE_MAXIMUM (Button 3)
	    0x15, 0x00,                    //!     LOGICAL_MINIMUM (0)
	    0x25, 0x01,                    //!     LOGICAL_MAXIMUM (1)
	    0x95, 0x03,                    //!     REPORT_COUNT (3)
	    0x75, 0x01,                    //!     REPORT_SIZE (1)
	    0x81, 0x02,                    //!     INPUT (Data,Var,Abs)
	    0x95, 0x01,                    //!     REPORT_COUNT (1)
	    0x75, 0x05,                    //!     REPORT_SIZE (5)
	    0x81, 0x03,                    //!     INPUT (Cnst,Var,Abs)
	    0x05, 0x01,                    //!     USAGE_PAGE (Generic Desktop)
	    0x09, 0x30,                    //!     USAGE (X)
	    0x09, 0x31,                    //!     USAGE (Y)
	    0x09, 0x38,                    //!     USAGE (Wheel)
	    0x15, 0x81,                    //!     LOGICAL_MINIMUM (-127)
	    0x25, 0x7f,                    //!     LOGICAL_MAXIMUM (127)
	    0x75, 0x08,                    //!     REPORT_SIZE (8)
	    0x95, 0x03,                    //!     REPORT_COUNT (3)
	    0x81, 0x06,                    //!     INPUT (Data,Var,Rel)
	    0xc0,                          //!   END_COLLECTION
	    0xc0,                          //! END_COLLECTION
};


#endif

//! Joystick USB report chosen
#ifdef JOYSTICK_REPORT

#undef USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH
#define USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH 	46

prog_uint8_t usbHidReportDescriptor[USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH] = {

	    0x05, 0x01,                    //! USAGE_PAGE (Generic Desktop)
	    0x09, 0x04,                    //! USAGE (Joystick)
	    0xa1, 0x01,                    //! COLLECTION (Application)
	    0xa1, 0x00,                    //!   COLLECTION (Physical)
	    0x85, 0x02,                    //!     REPORT_ID (2)
	    0x05, 0x09,                    //!     USAGE_PAGE (Button)
	    0x19, 0x01,                    //!     USAGE_MINIMUM (Button 1)
	    0x29, 0x10,                    //!     USAGE_MAXIMUM (Button 16)
	    0x15, 0x00,                    //!     LOGICAL_MINIMUM (0)
	    0x25, 0x01,                    //!     LOGICAL_MAXIMUM (1)
	    0x95, 0x10,                    //!     REPORT_COUNT (16)
	    0x75, 0x01,                    //!     REPORT_SIZE (1)
	    0x81, 0x02,                    //!     INPUT (Data,Var,Abs)
	    0x05, 0x01,                    //!     USAGE_PAGE (Generic Desktop)
	    0x09, 0x30,                    //!     USAGE (X)
	    0x09, 0x31,                    //!     USAGE (Y)
	    0x09, 0x32,                    //!     USAGE (Z)
	    0x15, 0x81,                    //!     LOGICAL_MINIMUM (-127)
	    0x25, 0x7f,                    //!     LOGICAL_MAXIMUM (127)
	    0x75, 0x08,                    //!     REPORT_SIZE (8)
	    0x95, 0x04,                    //!     REPORT_COUNT (3)
	    0x81, 0x02,                    //!     INPUT (Data,Var,Abs)
	    0xc0,                          //!   END_COLLECTION
	    0xc0,                          //! END_COLLECTION
};


#endif

//! Mouse and Joystick USB report chosen
#ifdef MOUSE_JOYSTICK_REPORT

#undef USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH
#define USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH 	100

prog_uint8_t usbHidReportDescriptor[USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH] = {

		0x05, 0x01,                    //! USAGE_PAGE (Generic Desktop)
		0x09, 0x02,                    //! USAGE (Mouse)
		0xa1, 0x01,                    //! COLLECTION (Application)
		0x09, 0x01,                    //!   USAGE (Pointer)
		0xa1, 0x00,                    //!   COLLECTION (Physical)
		0x85, 0x01,                    //!     REPORT_ID (1)
		0x05, 0x09,                    //!     USAGE_PAGE (Button)
		0x19, 0x01,                    //!     USAGE_MINIMUM (Button 1)
		0x29, 0x03,                    //!     USAGE_MAXIMUM (Button 3)
		0x15, 0x00,                    //!     LOGICAL_MINIMUM (0)
		0x25, 0x01,                    //!     LOGICAL_MAXIMUM (1)
		0x95, 0x03,                    //!     REPORT_COUNT (3)
		0x75, 0x01,                    //!     REPORT_SIZE (1)
		0x81, 0x02,                    //!     INPUT (Data,Var,Abs)
		0x95, 0x01,                    //!     REPORT_COUNT (1)
		0x75, 0x05,                    //!     REPORT_SIZE (5)
		0x81, 0x03,                    //!     INPUT (Cnst,Var,Abs)
		0x05, 0x01,                    //!     USAGE_PAGE (Generic Desktop)
		0x09, 0x30,                    //!     USAGE (X)
		0x09, 0x31,                    //!     USAGE (Y)
		0x09, 0x38,                    //!     USAGE (Wheel)
		0x15, 0x81,                    //!     LOGICAL_MINIMUM (-127)
		0x25, 0x7f,                    //!     LOGICAL_MAXIMUM (127)
		0x75, 0x08,                    //!     REPORT_SIZE (8)
		0x95, 0x03,                    //!     REPORT_COUNT (3)
		0x81, 0x06,                    //!     INPUT (Data,Var,Rel)
		0xc0,                          //!   END_COLLECTION
		0xc0,                          //! END_COLLECTION

//! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	    0x05, 0x01,                    //! USAGE_PAGE (Generic Desktop)
	    0x09, 0x04,                    //! USAGE (Joystick)
	    0xa1, 0x01,                    //! COLLECTION (Application)
	    0xa1, 0x00,                    //!   COLLECTION (Physical)
	    0x85, 0x02,                    //!     REPORT_ID (2)
	    0x05, 0x09,                    //!     USAGE_PAGE (Button)
	    0x19, 0x01,                    //!     USAGE_MINIMUM (Button 1)
	    0x29, 0x10,                    //!     USAGE_MAXIMUM (Button 16)
	    0x15, 0x00,                    //!     LOGICAL_MINIMUM (0)
	    0x25, 0x01,                    //!     LOGICAL_MAXIMUM (1)
	    0x95, 0x10,                    //!     REPORT_COUNT (16)
	    0x75, 0x01,                    //!     REPORT_SIZE (1)
	    0x81, 0x02,                    //!     INPUT (Data,Var,Abs)
	    0x05, 0x01,                    //!     USAGE_PAGE (Generic Desktop)
	    0x09, 0x30,                    //!     USAGE (X)
	    0x09, 0x31,                    //!     USAGE (Y)
	    0x09, 0x32,                    //!     USAGE (Z)
	    0x15, 0x81,                    //!     LOGICAL_MINIMUM (-127)
	    0x25, 0x7f,                    //!     LOGICAL_MAXIMUM (127)
	    0x75, 0x08,                    //!     REPORT_SIZE (8)
	    0x95, 0x04,                    //!     REPORT_COUNT (3)
	    0x81, 0x02,                    //!     INPUT (Data,Var,Abs)
	    0xc0,                          //!   END_COLLECTION
	    0xc0,                          //! END_COLLECTION

    };

#endif

#endif //! USB_REPORTS_H_
