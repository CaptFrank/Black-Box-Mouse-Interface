/*
 * USB_Device_Implementation.cpp
 *
 *  Created on: Jul 17, 2013
 *      Author: francispapineau
 */

#include "USB_Device_Implementation.h"
#include "../System_Defines/Command_Interpreter.h"

static byte idle_rate = 500 / 4; // see HID1_11.pdf sect 7.2.4

#define ROUTER			0
#define BUTTONS			0
#define WHEEL			1
#define X_AXIS			2
#define Y_AXIS			3

//! Default Constructor
USB_DEVICE::USB_DEVICE(){
	//! Sending mutex
	_sending_mutex = false;

	//! Initializing the enviroment variables
	_packet_buffer = EMPTY;
	_packet_id = EMPTY;
	_packet_in_sending_queue = true;
	_packet_size = 0;
}

void USB_DEVICE::run_usb(){

	//! Sets up the rf network
	_init_rf_network();

	/**
	 * Once the state machine gets here, it polls for data from the router
	 * and parses it into the structures.
	 */

	for(;;){

		//! Check to see if a report needs to be sent, using
		//! the idle rate.
		if ((TCNT1 > ((4 * (F_CPU / 1024000)) * idle_rate)
				|| TCNT1 > 0x7FFF) && idle_rate != 0) {

			//! Needs to send
			_sending_mutex = true;
		}else{

			//! Create a valid random USB Frame
			_create_usb_report_frame();
		}

		//! If we need to send.
		if(_sending_mutex){

			//! Send the report.
			//! and reset the timer.
			_send_usb_report_frame();
			TCNT1 = 0;
		}

		//! No need to send anymore.
		_sending_mutex = false;
	}
}

//! Create a valid packet to send in USB format
void USB_DEVICE::_create_usb_report_frame(){
#ifdef MOUSE_REPORT
	#ifdef WATCH_ONLY
		buttons_mouse = packet_parser._data[ROUTER].channels[BUTTONS].channel_data;
		wheel_mouse = packet_parser._data[ROUTER].channels[WHEEL].channel_data;
		x_axis_mouse = packet_parser._data[ROUTER].channels[X_AXIS].channel_data;
		y_axis_mouse = packet_parser._data[ROUTER].channels[Y_AXIS].channel_data;
	#endif
	//! Reassign the structure to send.
	_packet_buffer = (uint8_t* )&mouse_report;
#endif

#ifdef JOYSTICK_REPORT

	for(register byte i = 0; i < NUM_AXES; i ++){
		joystick_report.axis[i] = packet_parser._data.axis[i];
	}
	for(register byte i = 0; i < NUM_BUTTONS/8; i ++){
		joystick_report.button[i] = packet_parser._data.button[i];
	}

	//! Reassign the structure to send.
	_packet_buffer = (uint8_t* )&joystick_report;
#endif
}

//! Sends a USB report frame
void USB_DEVICE::_send_usb_report_frame(){

#ifdef MOUSE_REPORT

	//! Send the structure.
	RF_SERIAL.write(_packet_buffer, sizeof(mouse_report));
#endif

#ifdef JOYSTICK_REPORT

	//! Send the structure.
	RF_SERIAL.write(_packet_buffer, sizeof(joystick_report));
#endif

	_packet_in_sending_queue = false;
}

//! Setup rf link
void USB_DEVICE::_init_rf_network(){
	/**
	 * Start the state machine and push the state to start.
	 *
	 * FROM: 	LOCAL_DEVICE_SETUP
	 * TO: 		NETWORK_SETUP
	 */
	usb_state_machine.move_state_forward();

	/**
	 * Powers on the router.
	 */
	command_interpreter.send_cmd(USB_DEVICE_CMD, (void*)POWERON_ROUTER);

	/**
	 * Move the state machine to the ID wakeup router section of the
	 * state machine.
	 *
	 * FROM: 	NETWORK_SETUP
	 * TO: 		NETWORK_ID_REQUEST
	 */
	usb_state_machine.move_state_forward();

	/** This function sends_a wakeup call to the router and makes the
	 * router go into command polling mode. This allows the router to
	 * only react to the commands sent by the ground station and not the
	 * sensors.
	 *
	 * -> This function needs an ack before a watchdog timer expires
	 *    to continue with the setup process.
	 *
	 *	-> power_on_router();
	 * 	 1. send_wakeup_router();
	 * 	 	-> receive_router_ack();
 	 */
	command_interpreter.send_cmd(USB_DEVICE_CMD, (void*)WAKEUP_ROUTER);

	/**
	 * Makes sure that the device is ok and running
	 */
	command_interpreter.send_cmd(USB_DEVICE_CMD, (void*)PING_ROUTER);

	/**
	 * Move the state machine to the network status request state.
	 *
	 * FROM:	NETWORK_ID_REQUEST
	 * TO: 		NETWORK_STATUS_REQUEST
	 */
	usb_state_machine.move_state_forward();

	/**
	 * This function requests a router status structure. It sends a
	 * request command and polls until a structure is returned or when a
	 * watchdog timer exhaust is caught.
	 *
	 * -> This function needs an ack before a watchdog timer expires
	 *    to continue with the setup process.
	 *
  	 * 	  2. request_router_status();
  	 * 	  	-> receive_router_status();
	 */
	command_interpreter.send_cmd(USB_DEVICE_CMD, (void*)REQUEST_ROUTER_STATUS);

	/**
	 * Gets the router configs. [Radio Bytes Config]
	 * Gets the radio configuration registers in the transceiver.
	 */
	command_interpreter.send_cmd(USB_DEVICE_CMD, (void*)REQUEST_ROUTER_CONFIG);

	/**
	 * Save them to eeprom address 200dec.
	 */
	nvram.savex((byte)200, (byte)8, (void*)&packet_parser._radio_configs);

	/**
	 * Move the state machine to the network map request.
	 *
	 * FROM:	NETWORK_STATUS_REQUEST
	 * TO: 		NETWORK_MAP_REQUEST
	 */
	usb_state_machine.move_state_forward();

	/**
	 * This function is very crucial to the network implementation, as
	 * it maps out the receiver and sender nodes. This function sends a
	 * generic "nmap" command, which activates a network_read() command on
	 * the router. Then in turn, the router returns a network structure,
	 * which contains enddevice information and other crucial network info.
	 *
	 * -> This function needs a message before a watchdog timer expires
	 *    to continue with the setup process.
	 *
	 *		3. request_net_map();
	 *			-> receive_nmap();
	 */
	command_interpreter.send_cmd(USB_DEVICE_CMD, (void*)REQUEST_NMAP);

	/**
	 * Move the state machine to the network sensor configs.
	 *
	 * FROM:	NETWORK_MAP_REQUEST
	 * TO: 		NETWORK_SENSOR_CONFIGS
	 */
	usb_state_machine.move_state_forward();

//TODO
// DO I REALLY NEED THIS?????
// DYNAMIC OR STATIC BY USER BASE

//	/**
//	 * Now that the network topology is mapped out, the follwoing command
//	 * is issued to all endpoint devices (sensors) to acquire their
//	 * respective specifics, such as channel IDs, speed and data types.
//	 *
//	 * -> This function needs a message before a watchdog timer expires
//	 *    to continue with the setup process.
//	 *
//	 * 		4. request_sensor_channel_info();
//	 * 			-> receive_channel_info();
//	 */
//	command_interpreter.send_cmd(USB_DEVICE_CMD, (void*)REQUEST_SENSOR_CONFIG);

	/**
	 * This function polls for an enabled sensor report generated by the
	 * user on the router, by selecting which sensor is enabled.
	 *
	 * 		5. get_user_enable_sensors();
	 * 			-> set_flags(byte sensor flags);
	 */
	command_interpreter.send_cmd(USB_DEVICE_CMD, (void*)REQUEST_SENSOR_ENABLE);

#ifdef DEBUG
	char* text;
	DEBUG_SERIAL.print("[NOTICE]: The following sensors are active:\n");
	for(register byte i = 0; i < sizeof(byte); i ++){
		byte bitmask = 0b11111110;
		bitmask = ~bitmask;
		byte sensor = packet_parser._en_sensors & bitmask;
		if(sensor > 0)
			sprintf(text, "\t - Sensor [%d] : ACTIVE\n", (i+1));
			DEBUG_SERIAL.print(text);
	}
#endif
	/**
	 * Move the state machine to the network sensor configs.
	 *
	 * FROM:	NETWORK_SENSOR_CONFIGS
	 * TO: 		LOCAL_CONFIGURATION
	 */
	usb_state_machine.move_state_forward();

	/**
	 * Then to finalize the ground station network initialization,
	 * we need to allocate buffers for each sensor and then create a
	 * call priority table, which in other words is a call scheduler.
	 * This finalizes the network setup on the ground station side.
	 *
	 * -> This function needs a message before a watchdog timer expires
	 *	to continue with the setup process.
	 *		6. configure_ground_station();
     * 			-> allocate_buffers(nampe_t* nmap, channel_info_t* channel_info);
     *			-> create_call_priority_table();
     *
     * *** NOTE: This is handled internally... No control signals are needed.
     * 			 Only checking memory space is valid.
	 */
	if(memory_check() <= MAX_MEMORY){
#ifdef DEBUG_LEDs
		debug_api.set_leds(MEMORY_ERROR);
#endif
		error((void*) __LINE__, (void*) __func__);
	}

	/**
	 * Move the state machine to the network sensor configs.
	 *
	 * FROM:	LOCAL_CONFIGURATION
	 * TO: 		NETWORK_REQUEST_ROUTER_STATE_RUN
	 */
	usb_state_machine.move_state_forward();


	/**
	 * After this step is complete, we go into the loop that does all the
	 * usb work and processing.
	 */
}

//! Sets up the parameters for the usb report to be sent
void USB_DEVICE::_setup_usb_report_params(){

#ifdef MOUSE_REPORT
	//! Setup the structure values

	buttons_mouse = &packet_parser._data[ROUTER].channels[BUTTONS].channel_data;
	wheel_mouse = &packet_parser._data[ROUTER].channels[WHEEL].channel_data;
	x_axis_mouse = &packet_parser._data[ROUTER].channels[X_AXIS].channel_data;
	y_axis_mouse = &packet_parser._data[ROUTER].channels[Y_AXIS].channel_data;

	//! Reassign the structure to send.
	_packet_buffer = &mouse_report;
#endif

#ifdef JOYSTICK_REPORT
	//! Reassign the structure to send.
	_packet_buffer = (uint8_t* )&joystick_report;
#endif

}
