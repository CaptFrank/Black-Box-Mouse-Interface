
/*
 * Emulation_Packet_Assembler.h
 *
 *  Created on: Jul 13, 2013
 *      Author: francispapineau
 */

#include "USB_Structures.h"
#include "Hardware_Defines.h"


/**
 * This class is implemented to be able to assemble a
 * USB Frame to send to the host PC.
 */

 class EMULATION_DEVICE {

	private:
		
// 	#ifdef JOYSTICK_REPORT
// 		joystick_report_t joystick_report;
// 	#endif
// 				
// 	#ifdef MOUSE_REPORT
// 		mouse_report_t mouse_report;
// 	#endif
		
		//! The pointer to the data structure
		byte* _packet_buffer;

		//! The packet id
		word _packet_id;

		//! The packet size
		byte _packet_size;

		//! The mutex for the packet in the queue
		byte _packet_in_sending_queue;

		//! button toggling
		byte _button;

		/**
		 * The assembly function for the packet
		 */
		void _assemble_usb_emulation_frame();

		/**
		 * Create a USB report to send
		 */
		void* _create_usb_report_frame();

		/**
		 * Sends a usb report
		 */
		void _send_usb_report_frame(void* report);

		/**
		 * This updates the packet id
		 */
		void _update_packet_id();
		
	public:

		/**
		 * The default constructor
		 */
		EMULATION_DEVICE();

		/**
		 * The emulation loop
		 */
		void emulate_usb();

		/**
		 * This returns the packet id
		 */
		word get_packet_id();

};
