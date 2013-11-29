/*
 * network_protocol_router_sensor.h
 *
 *  Created on: Nov 29, 2013
 *      Author: francis-ccs
 */

#ifndef NETWORK_PROTOCOL_ROUTER_SENSOR_H_
#define NETWORK_PROTOCOL_ROUTER_SENSOR_H_

#include "Configs.h"

/**
 * These are the possible commands the router
 * can send.
 */
#define PING						0x01
#define CONFIG_REQ					0x02
#define STATUS_REQ					0x03

/**
 * The sync command is structured as follows:
 * 	- 0x04, time to sync, heartbeat freq
 */
#define SYNC						0x04
#define START						0x05
#define STOP						0x06
#define ABORT						0x07
#define ERROR						0x08
#define PAUSE						0x09

#define HEARTBEAT_FREQ				0x01
#define PACKET_FORMAT				0x03
#define COMMAND_PREAMBLE			'@'
#define COMMAND_TAIL				0x0A

// Possible reports received
#define SENSOR_ACK					0x14
#define SENSOR_CONFIG_REPORT		0x15
#define SENSOR_STATUS_REPORT		0x16
#define SENSOR_DATA_REPORT			0x17
#define SENSOR_SYNC_REPORT			0x18
#define SENSOR_HEARTBEAT_REPORT		0x19
#define SENSOR_ERROR_REPORT			0x20

// *************************************************
// *************** REMOTE DOMAIN *******************
// *************************************************

// TODO



#endif /* NETWORK_PROTOCOL_ROUTER_SENSOR_H_ */
