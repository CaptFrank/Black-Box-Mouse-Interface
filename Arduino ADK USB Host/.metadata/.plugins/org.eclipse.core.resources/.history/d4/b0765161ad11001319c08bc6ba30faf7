/*
 * NVRAM_API.h
 *
 *  Created on: Jul 25, 2013
 *      Author: fjpapin
 */

#include "../System_Defines/Includes.h"

/**
 * This class handles the NVRAM accesses and storage
 * structure.
 */
class NVRAM {

	private:

		/**
		 * Loads bytes from NVRAM
		 *
		 * @param address - byte
		 * @param size - byte
		 * @param value - void*
		 */
		void _loadx(byte address, byte size, void* value);

		/**
		 * Saves bytes to NVRAM
		 *
		 * @param address - byte
		 * @param size - byte
		 * @param value - void*
		 */
		void _savex(byte address, byte size, void* value);

	public:

		/**
		 * Load all of the saved variables.
		 */
		void load(void);

		/**
		 * Save all of the loaded variables.
		 */
		void save(void);

		/**
		 * The structure for the nvram varialbes.
		 */
		struct nv_data_t {

			//! Serial settings
			word serial1_speed;
			word serial2_speed;
			word serial3_speed;

			//! RF settings
			byte node_address;
			byte device_mode;

			//! GPIO settings
			//!		buttons:
			byte button_1;
			byte button1_setting;
			byte button_2;
			byte button2_setting;

			//!		LEDs:
			byte led_1;
			byte led1_setting;
			byte led_2;
			byte led2_setting;
			byte led_3;
			byte led3_setting;
			byte led_4;
			byte led4_setting;

			//! Possible Commands;
			byte _ping_router[6];
			byte _ping_sensor[6];
			byte _request_router_run[3];
			byte _request_router_config[7];
			byte _request_sensor_config[7];
			byte _request_sensor_enable[7];
			byte _request_sensor_channel[10];
			byte _request_nmap[4];
			byte _request_router_status[6];
			byte _pause_sensor[7];
			byte _pause_router[7];
			byte _power_on_router[6];
			byte _power_on_sensor[6];
			byte _poweroff_router[6];
			byte _poweroff_sensor[6];
			byte _wakeup_router[6];
			byte _wakeup_sensor[6];
			byte _request_sensor_number[7];
			byte _request_sensor_channels[7];

		};

		//! The exported structure definition.
		struct nv_data_t nv;
};
