/*
 * router_network_utility.c
 *
 *  Created on: Nov 5, 2013
 *      Author: Francis Papineau
 */

typedef struct {

	void (*ping_ack)();
	void (*ping_nack)();
	void (*send_status)();
	void (*send_configs)();
	void (*send_nmap)();
	void (*send_sensor_enabled)();


} router_network_utilities_t;


