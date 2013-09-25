/*
 * NVRAM_API.h
 *
 *  Created on: Jul 25, 2013
 *      Author: fjpapin
 */

#ifndef _NVRAM_h_
#define _NVRAM_h_

#include "Hardware_Defines.h"

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
		void _loadx(uint8_t address, uint8_t size, void* value);

		/**
		 * Saves bytes to NVRAM
		 *
		 * @param address - byte
		 * @param size - byte
		 * @param value - void*
		 */
		void _savex(uint8_t address, uint8_t size, void* value);

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
		 * Saves bytes to NVRAM
		 *
		 * @param address - byte
		 * @param size - byte
		 * @param value - void*
		 */
		void savex(uint8_t address, uint8_t size, void* value);

		/**
		 * The structure for the nvram varialbes.
		 */
		struct nv_data_t {

			//! Serial settings
			word serial1_speed;
			word serial2_speed;
			word serial3_speed;

			//! RF settings
			uint8_t node_address;
			uint8_t device_mode;

			//! GPIO settings
			//!		buttons:
			uint8_t button_1;
			uint8_t button1_setting;
			uint8_t button_2;
			uint8_t button2_setting;

			//!		LEDs:
			uint8_t led_1;
			uint8_t led1_setting;
			uint8_t led_2;
			uint8_t led2_setting;
			uint8_t led_3;
			uint8_t led3_setting;
			uint8_t led_4;
			uint8_t led4_setting;

			//! Possible Commands;
			uint8_t _ping_router[6];
			uint8_t _ping_sensor[6];
			uint8_t _request_router_run[3];
			uint8_t _request_router_config[7];
			uint8_t _request_sensor_config[7];
			uint8_t _request_sensor_enable[7];
			uint8_t _request_sensor_channel[10];
//			uint8_t _request_nmap[4];
			uint8_t _request_router_status[6];
			uint8_t _pause_sensor[7];
			uint8_t _pause_router[7];
			uint8_t _power_on_router[6];
			uint8_t _power_on_sensor[6];
			uint8_t _poweroff_router[6];
			uint8_t _poweroff_sensor[6];
			uint8_t _wakeup_router[6];
			uint8_t _wakeup_sensor[6];
			uint8_t _request_sensor_number[7];
			uint8_t _request_sensor_channels[7];

		};

		//! The exported structure definition.
		struct nv_data_t nv;
};

#endif
