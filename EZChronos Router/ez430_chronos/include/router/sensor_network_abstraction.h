/*
 * network_abstraction.h
 *
 *  Created on: Jan 4, 2014
 *      Author: Francis Papineau
 */

#ifndef NETWORK_ABSTRACTION_H_
#define NETWORK_ABSTRACTION_H_

/**
 * In this file, there resides the network abstraction layer for the
 * entire network arbitration scheme. In other words, the sending and
 * receiving of data from the router to the sensors and vice versa.
 */

/**
 * This sends the synching and the necessary messages to the sensor
 * in order to get the network synchronized with all other peices
 * of the network.
 */
void init_sensor(u8 sensor_number);

/**
 * This function sends the start command to a specific sensor, which
 * in turn starts the data stream from that particular sensor at a rate
 * given by the sync rate.
 */
void start_sensor(u8 sensor_number);
void start_all_sensors();

/**
 * This function sends the stop command to the specific command and thus
 * stops teh communications with that sensor. Although the sensor is still
 * connected to the network the data stream is stopped.
 */
void stop_sensor(u8 sensor_number);
void stop_all_sensors();

/**
 * This function resets the specific sensor and thus disconnects the sensor
 * from the network, by resetting the sensor node.
 */
void reset_sensor(u8 sensor_number);
void reset_all_sensors();

/**
 * This function sets the linkID_t associations.
 */
void _associate_linkID_t();

#endif /* NETWORK_ABSTRACTION_H_ */
