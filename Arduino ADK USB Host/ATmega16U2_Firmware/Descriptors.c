/*
             LUFA Library
     Copyright (C) Dean Camera, 2010.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2010  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this 
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in 
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting 
  documentation, and that the name of the author not be used in 
  advertising or publicity pertaining to distribution of the 
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *
 *  USB Device Descriptors, for library use when in USB device mode. Descriptors are special 
 *  computer-readable structures which the host requests upon device enumeration, to determine
 *  the device's capabilities and functions.  
 */

#include "Descriptors.h"

/** HID class report descriptor. This is a special descriptor constructed with values from the
 *  USBIF HID class specification to describe the reports and capabilities of the HID device. This
 *  descriptor is parsed by the host and its contents used to determine what data (and in what encoding)
 *  the device will send, and what it may be sent back from the host. Refer to the HID specification for
 *  more details on HID report descriptors.
 */


#ifdef MOUSE_REPORT
	const USB_Descriptor_HIDReport_Datatype_t PROGMEM MouseReport[] =
	{
		0x05, 0x01,          /* Usage Page (Generic Desktop)             */
		0x09, 0x02,          /* Usage (Mouse)                            */
		0xA1, 0x01,          /* Collection (Application)                 */
		0x09, 0x01,          /*   Usage (Pointer)                        */
		0xA1, 0x00,          /*   Collection (Application)               */
		0x95, 0x03,          /*     Report Count (3)                     */
		0x75, 0x01,          /*     Report Size (1)                      */
		0x05, 0x09,          /*     Usage Page (Button)                  */
		0x19, 0x01,          /*     Usage Minimum (Button 1)             */
		0x29, 0x03,          /*     Usage Maximum (Button 3)             */
		0x15, 0x00,          /*     Logical Minimum (0)                  */
		0x25, 0x01,          /*     Logical Maximum (1)                  */
		0x81, 0x02,          /*     Input (Data, Variable, Absolute)     */
		0x95, 0x01,          /*     Report Count (1)                     */
		0x75, 0x05,          /*     Report Size (5)                      */
		0x81, 0x01,          /*     Input (Constant)                     */
		0x75, 0x08,          /*     Report Size (8)                      */
		0x95, 0x02,          /*     Report Count (2)                     */
		0x05, 0x01,          /*     Usage Page (Generic Desktop Control) */
		0x09, 0x30,          /*     Usage X                              */
		0x09, 0x31,          /*     Usage Y                              */
		0x15, 0x81,          /*     Logical Minimum (-127)               */
		0x25, 0x7F,          /*     Logical Maximum (127)                */
		0x81, 0x06,          /*     Input (Data, Variable, Relative)     */
		0xC0,                /*   End Collection                         */
		0xC0                 /* End Collection                           */
	};
#endif

//! Joystick USB report chosen
#ifdef JOYSTICK_REPORT
	const USB_Descriptor_HIDReport_Datatype_t PROGMEM JoystickReport[] = {

		/* Use the HID class driver's standard Joystick report.
		 *   Min X/Y/Z Axis values: -255
		 *   Max X/Y/Z Axis values:  255
		 *   Min physical X/Y/Z Axis values (used to determine resolution): -1
		 *   Max physical X/Y/Z Axis values (used to determine resolution):  1
		 *   Buttons: 10
		 */
		HID_DESCRIPTOR_JOYSTICK(-255, 255, -1, 1, 10)
	};
#endif

//! Mouse and Joystick USB report chosen
#ifdef MOUSE_JOYSTICK_REPORT
	const USB_Descriptor_HIDReport_Datatype_t PROGMEM JoystickMouseReport[] = {
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

		/* Use the HID class driver's standard Joystick report.
		 *   Min X/Y/Z Axis values: -255
		 *   Max X/Y/Z Axis values:  255
		 *   Min physical X/Y/Z Axis values (used to determine resolution): -1
		 *   Max physical X/Y/Z Axis values (used to determine resolution):  1
		 *   Buttons: 10
		 */
		HID_DESCRIPTOR_JOYSTICK(-255, 255, -1, 1, 8)
	};
#endif

/** Device descriptor structure. This descriptor, located in FLASH memory, describes the overall
 *  device characteristics, including the supported USB version, control endpoint size and the
 *  number of device configurations. The descriptor is read out by the USB host when the enumeration
 *  process begins.
 */
const USB_Descriptor_Device_t PROGMEM DeviceDescriptor =
{
	.Header                 = {.Size = sizeof(USB_Descriptor_Device_t), .Type = DTYPE_Device},
		
	.USBSpecification       = VERSION_BCD(01.10),
	.Class                  = 0x00,
	.SubClass               = 0x00,
	.Protocol               = 0x00,
				
	.Endpoint0Size          = FIXED_CONTROL_ENDPOINT_SIZE,
		
	.VendorID               = 0x03EB,
	.ProductID              = 0x2041,
	.ReleaseNumber          = 0x0000,
		
	.ManufacturerStrIndex   = 0x01,
	.ProductStrIndex        = 0x02,
	.SerialNumStrIndex      = NO_DESCRIPTOR,
		
	.NumberOfConfigurations = FIXED_NUM_CONFIGURATIONS
};

/** Configuration descriptor structure. This descriptor, located in FLASH memory, describes the usage
 *  of the device in one of its supported configurations, including information about any device interfaces
 *  and endpoints. The descriptor is read out by the USB host during the enumeration process when selecting
 *  a configuration so that the host may correctly communicate with the USB device.
 */
const USB_Descriptor_Configuration_t PROGMEM ConfigurationDescriptor =
{
	.Config = 
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Configuration_Header_t), .Type = DTYPE_Configuration},

			.TotalConfigurationSize = sizeof(USB_Descriptor_Configuration_t),
			.TotalInterfaces        = 1,
				
			.ConfigurationNumber    = 1,
			.ConfigurationStrIndex  = NO_DESCRIPTOR,
				
			.ConfigAttributes       = (USB_CONFIG_ATTR_RESERVED | USB_CONFIG_ATTR_SELFPOWERED),
			
			.MaxPowerConsumption    = USB_CONFIG_POWER_MA(200)
		},
		
	.HID_Interface = 
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

			.InterfaceNumber        = 0x00,
			.AlternateSetting       = 0x00,
			
			.TotalEndpoints         = 1,
				
			.Class                  = 0x03,
			.SubClass               = 0x01,

#ifdef MOUSE_REPORT
			.Protocol               = HID_CSCP_MouseBootProtocol, //changed from HID_BOOT_MOUSE_PROTOCOL,
#endif

#ifdef JOYSTICK_REPORT
			.Protocol				= HID_CSCP_HIDClass,
#endif

#ifdef MOUSE_JOYSTICK_REPORT
			.Protocol				= HID_CSCP_MouseBootProtocol
#endif
			.InterfaceStrIndex      = NO_DESCRIPTOR
		},

	.HID_DeviceHID = 
		{
			.Header                 = {.Size = sizeof(USB_HID_Descriptor_HID_t), .Type = HID_DTYPE_HID}, //changed added HID

			.HIDSpec                = VERSION_BCD(01.11),
			.CountryCode            = 0x00,
			.TotalReportDescriptors = 1,
			.HIDReportType          = HID_DTYPE_Report, //changed add HID
			.HIDReportLength        = sizeof(MouseReport)
		},

	.HID_ReportINEndpoint = 
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

			#ifdef MOUSE_REPORT
			.EndpointAddress        = (ENDPOINT_DIR_IN | MOUSE_EPNUM), //changed from ENDPOINT_DIRECTION_DIR_IN
			#endif

			#ifdef JOYSTICK_REPORT
			.EndpointAddress        = JOYSTICK_EPADDR,
			#endif

			#ifdef MOUSE_JOYSTICK_REPORT
			.EndpointAddress        = (ENDPOINT_DIR_IN | MOUSE_JOYSTICK_EPNUM),
			#endif

			.Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
			
			#ifdef MOUSE_REPORT
			.EndpointSize           = MOUSE_EPSIZE,
			#endif

			#ifdef JOYSTICK_REPORT
			.EndpointSize           = JOYSTICK_EPSIZE,
			#endif

			#ifdef MOUSE_JOYSTICK_REPORT
			.EndpointSize           = MOUSE_JOYSTICK_EPSIZE,
			#endif
			.PollingIntervalMS      = 0x0A
		}
};

/** Language descriptor structure. This descriptor, located in FLASH memory, is returned when the host requests
 *  the string descriptor with index 0 (the first index). It is actually an array of 16-bit integers, which indicate
 *  via the language ID table available at USB.org what languages the device supports for its string descriptors.
 */
const USB_Descriptor_String_t PROGMEM LanguageString =
{
	.Header                 = {.Size = USB_STRING_LEN(1), .Type = DTYPE_String},
		
	.UnicodeString          = {LANGUAGE_ID_ENG}
};

/** Manufacturer descriptor string. This is a Unicode string containing the manufacturer's details in human readable
 *  form, and is read out upon request by the host when the appropriate string ID is requested, listed in the Device
 *  Descriptor.
 */
const USB_Descriptor_String_t PROGMEM ManufacturerString =
{
	.Header                 = {.Size = USB_STRING_LEN(7), .Type = DTYPE_String},
		
	.UnicodeString          = L"Carleton University"
};

/** Product descriptor string. This is a Unicode string containing the product's details in human readable form,
 *  and is read out upon request by the host when the appropriate string ID is requested, listed in the Device
 *  Descriptor.
 */
const USB_Descriptor_String_t PROGMEM ProductString =
{
	.Header                 = {.Size = USB_STRING_LEN(9), .Type = DTYPE_String},
	
	#ifdef MOUSE_REPORT
	.UnicodeString          = L"Medical Mouse 0.1"
	#endif

	#ifdef JOYSTICK_REPORT
	.UnicodeString          = L"Medical Joystick 0.1"
	#endif

	#ifdef MOUSE_JOYSTICK_REPORT
	.UnicodeString          = L"Medical Mouse & Joystick 0.1"
	#endif
};

/** This function is called by the library when in device mode, and must be overridden (see library "USB Descriptors"
 *  documentation) by the application code so that the address and size of a requested descriptor can be given
 *  to the USB library. When the device receives a Get Descriptor request on the control endpoint, this function
 *  is called so that the descriptor details can be passed back and the appropriate descriptor sent back to the
 *  USB host.
 */
uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
                                    const uint8_t wIndex,
                                    const void** const DescriptorAddress)
{
	const uint8_t  DescriptorType   = (wValue >> 8);
	const uint8_t  DescriptorNumber = (wValue & 0xFF);

	void*    Address = NULL;
	uint16_t Size    = NO_DESCRIPTOR;

	switch (DescriptorType)
	{
		case DTYPE_Device:
			Address = (void*)&DeviceDescriptor;
			Size    = sizeof(USB_Descriptor_Device_t);
			break;
		case DTYPE_Configuration:
			Address = (void*)&ConfigurationDescriptor;
			Size    = sizeof(USB_Descriptor_Configuration_t);
			break;
		case DTYPE_String:
			switch (DescriptorNumber)
			{
				case 0x00:
					Address = (void*)&LanguageString;
					Size    = pgm_read_byte(&LanguageString.Header.Size);
					break;
				case 0x01:
					Address = (void*)&ManufacturerString;
					Size    = pgm_read_byte(&ManufacturerString.Header.Size);
					break;
				case 0x02:
					Address = (void*)&ProductString;
					Size    = pgm_read_byte(&ProductString.Header.Size);
					break;
			}
			
			break;
		case HID_DTYPE_HID: //added HID
			Address = (void*)&ConfigurationDescriptor.HID_DeviceHID;
			Size    = sizeof(USB_HID_Descriptor_HID_t); // added HID
			break;
		case HID_DTYPE_Report: //added HID 
		
			#ifdef MOUSE_REPORT
			Address = (void*)&MouseReport;
			Size    = sizeof(MouseReport);
			#endif

			#ifdef JOYSTICK_REPORT
			Address = (void*)&JoystickReport;
			Size    = sizeof(JoystickReport);
			#endif

			#ifdef MOUSE_JOYSTICK_REPORT
			Address = (void*)&JoystickMouseReport;
			Size    = sizeof(JoystickMouseReport);
			#endif
			break;
	}
	
	*DescriptorAddress = Address;		
	return Size;
}

