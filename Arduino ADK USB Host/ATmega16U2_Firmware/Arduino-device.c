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

/*-
 * Copyright (c) 2011 Darran Hunt (darran [at] hunt dot net dot nz)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
 * THE CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/** \file
 *
 *  Main source file for the Arduino-mouse project. This file contains the main tasks of
 *  the project and is responsible for the initial application hardware configuration.
 */

#include "Arduino-device.h"

#define MOUSE_DATA					1
#define JOYSTICK_DATA				2
#define MOUSE_JOYSTICK_DATA			3

#ifdef MOUSE_REPORT
	/** Buffer to hold the previously generated Mouse HID report, for comparison purposes inside the HID class driver. */
	uint8_t PrevMouseHIDReportBuffer[sizeof(USB_MouseReport_Data_t)];

	/** LUFA HID Class driver interface configuration and state information. This structure is
	 *  passed to all HID Class driver functions, so that multiple instances of the same class
	 *  within a device can be differentiated from one another.
	 */
	USB_ClassInfo_HID_Device_t Mouse_HID_Interface = {
		.Config = {
		.InterfaceNumber              = 0,
		.ReportINEndpoint			  = 
			{
				.Address			  = (ENDPOINT_DIR_IN | MOUSE_EPNUM),
				.Size				  = MOUSE_EPSIZE,
				.Banks				  = 0,
			},
		.PrevReportINBuffer           = PrevMouseHIDReportBuffer,
		.PrevReportINBufferSize       = sizeof(PrevMouseHIDReportBuffer),
		},
	};

	/** Main program entry point. This routine contains the overall program flow, including initial
	 *  setup of all components and the main program loop.
	 */

	USB_MouseReport_Data_t DeviceReport;
#endif

#ifdef JOYSTICK_REPORT
	/** Buffer to hold the previously generated Joystick HID report, for comparison purposes inside the HID class driver. */
	uint8_t PrevJoystickHIDReportBuffer[sizeof(USB_JoystickReport_Data_t)];

	/** LUFA HID Class driver interface configuration and state information. This structure is
	 *  passed to all HID Class driver functions, so that multiple instances of the same class
	 *  within a device can be differentiated from one another.
	 */
	USB_ClassInfo_HID_Device_t Joystick_HID_Interface = {
		.Config = {
		.InterfaceNumber              = 0,
		.ReportINEndpoint			  = 
			{
				.Address			  = JOYSTICK_EPADDR,
				.Size				  = JOYSTICK_EPSIZE,
				.Banks				  = 1,
			},
		.PrevReportINBuffer           = PrevJoystickHIDReportBuffer,
		.PrevReportINBufferSize       = sizeof(PrevJoystickHIDReportBuffer),
		},
	};

	/** Main program entry point. This routine contains the overall program flow, including initial
	 *  setup of all components and the main program loop.
	 */

	USB_JoystickReport_Data_t DeviceReport;
#endif

#ifdef MOUSE_JOYSTICK_REPORT
// TODO
#endif


/** Circular buffer to hold data from the serial port before it is sent to the host. */
RingBuff_t USARTtoUSB_Buffer;

/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
	int struct_type = 0;
	
	// Define the right report to send
	#ifdef MOUSE_REPORT
		USB_MouseReport_Data_t newReport;
		struct_type = MOUSE_DATA;
	#endif
	#ifdef JOYSTICK_REPORT
		USB_JoystickReport_Data_t newReport;	
		struct_type = JOYSTICK_DATA;
	#endif
	#ifdef MOUSE_JOYSTICK_REPORT
		// TODO
		struct_type = MOUSE_JOYSTICK_DATA;
	#endif
	
	int ind;

	SetupHardware();

	RingBuffer_InitBuffer(&USARTtoUSB_Buffer);

	sei();

	for (;;) {
	    RingBuff_Count_t BufferCount = RingBuffer_GetCount(&USARTtoUSB_Buffer);

	    if (BufferCount >= 4) {
		for (ind=0; ind<3; ind++) {
		    ((uint8_t *)&newReport)[ind] = RingBuffer_Remove(&USARTtoUSB_Buffer);
		}

		RingBuffer_Remove(&USARTtoUSB_Buffer);	// unused wheel for now

		map_mem((void*)&DeviceReport, (void*)&newReport, struct_type);
	    }

		#ifdef MOUSE_REPORT
			HID_Device_USBTask(&Mouse_HID_Interface);
		#endif
		#ifdef JOYSTICK_REPORT
			HID_Device_USBTask(&Joystick_HID_Interface);
		#endif
		#ifdef MOUSE_JOYSTICK_REPORT
			// TODO	
		#endif
	    USB_USBTask();
	}
}

/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware(void)
{
	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Hardware Initialization */
	Serial_Init(9600, false);
	USB_Init();

	/* Start the flush timer so that overflows occur rapidly to push received bytes to the USB interface */
	TCCR0B = (1 << CS02);
	
	UCSR1B = ((1 << RXCIE1) | (1 << TXEN1) | (1 << RXEN1));
}

/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_Connect(void)
{
	//LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Disconnect(void)
{
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	#ifdef MOUSE_REPORT
		HID_Device_ConfigureEndpoints(&Mouse_HID_Interface);
	#endif
	#ifdef JOYSTICK_REPORT
		HID_Device_ConfigureEndpoints(&Joystick_HID_Interface);
	#endif
	#ifdef MOUSE_JOYSTICK_REPORT
		HID_Device_ConfigureEndpoints(&Mouse_Joystick_HID_Interface);
	#endif

	USB_Device_EnableSOFEvents();
}

/** Event handler for the library USB Unhandled Control Request event. */
void EVENT_USB_Device_UnhandledControlRequest(void)
{
	#ifdef MOUSE_REPORT
		HID_Device_ProcessControlRequest(&Mouse_HID_Interface);	
	#endif
	#ifdef JOYSTICK_REPORT
		HID_Device_ProcessControlRequest(&Joystick_HID_Interface);
	#endif
	#ifdef MOUSE_JOYSTICK_REPORT
		HID_Device_ProcessControlRequest(&Mouse_Joystick_HID_Interface);
	#endif
}

/** Event handler for the USB device Start Of Frame event. */
void EVENT_USB_Device_StartOfFrame(void)
{
	#ifdef MOUSE_REPORT
		HID_Device_MillisecondElapsed(&Mouse_HID_Interface);
	#endif
	#ifdef JOYSTICK_REPORT
		HID_Device_MillisecondElapsed(&Joystick_HID_Interface);	
	#endif
	#ifdef MOUSE_JOYSTICK_REPORT
		HID_Device_MillisecondElapsed(&Mouse_Joystick_HID_Interface);
	#endif
}

/** HID class driver callback function for the creation of HID reports to the host.
 *
 *  \param[in]     HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in,out] ReportID    Report ID requested by the host if non-zero, otherwise callback should set to the generated report ID
 *  \param[in]     ReportType  Type of the report to create, either REPORT_ITEM_TYPE_In or REPORT_ITEM_TYPE_Feature
 *  \param[out]    ReportData  Pointer to a buffer where the created report should be stored
 *  \param[out]    ReportSize  Number of bytes written in the report (or zero if no report is to be sent
 *
 *  \return Boolean true to force the sending of the report, false to let the library determine if it needs to be sent
 */
bool CALLBACK_HID_Device_CreateHIDReport(
    USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
    uint8_t* const ReportID,
    const uint8_t ReportType,
    void* ReportData,
    uint16_t* const ReportSize)
{
	USB_MouseReport_Data_t* reportp = (USB_MouseReport_Data_t*)ReportData;

	*reportp = DeviceReport;

	*ReportSize = sizeof(USB_MouseReport_Data_t);
	return false;
}

/** HID class driver callback function for the processing of HID reports from the host.
 *
 *  \param[in] HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in] ReportID    Report ID of the received report from the host
 *  \param[in] ReportType  The type of report that the host has sent, either REPORT_ITEM_TYPE_Out or REPORT_ITEM_TYPE_Feature
 *  \param[in] ReportData  Pointer to a buffer where the created report has been stored
 *  \param[in] ReportSize  Size in bytes of the received HID report
 */
void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                          const uint8_t ReportID,
                                          const uint8_t ReportType,
                                          const void* ReportData,
                                          const uint16_t ReportSize)
{
    /* Not used but must be present */
}

void map_mem(void* device_reporold_t, void* new_device_report, int data_type){
	
	switch (data_type){
		case MOUSE_DATA:
			device_reporold_t = (USB_MouseReport_Data_t*)device_reporold_t;
			new_device_report = (USB_MouseReport_Data_t*)new_device_report;
			
			device_reporold_t->Button = new_device_report->Button;
			device_reporold_t->X = new_device_report->X;
			device_reporold_t->Y = new_device_report->Y;
		return;
		case JOYSTICK_DATA:
		
			return;
		case MOUSE_JOYSTICK_DATA:
			//TODO
			return;
		default:
			return;
	}
}
/** ISR to manage the reception of data from the serial port, placing received bytes into a circular buffer
 *  for later transmission to the host.
 */
ISR(USART1_RX_vect, ISR_BLOCK)
{
	uint8_t ReceivedByte = UDR1;

	if (USB_DeviceState == DEVICE_STATE_Configured)
	  RingBuffer_Insert(&USARTtoUSB_Buffer, ReceivedByte);
}
