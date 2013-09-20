/*
 * USB_Sender_Utils.h
 *
 *  Created on: Aug 30, 2013
 *      Author: francispapineau
 */

#ifndef USB_SENDER_UTILS_H_
#define USB_SENDER_UTILS_H_

#include "USB_Host_Shield_2.0-master/cdcacm.h"

//! Commands needed to operate the AP
uint8_t AP_ON_COMMAND[]    = { 0xFF, 0x07, 0x03 };
uint8_t AP_RESET[] 		   = { 0xFF, 0x01, 0x03 };
uint8_t AP_STOP[]		   = { 0xFF, 0x09, 0x03 };

uint8_t ACC_DATA_REQUEST[] = { 0xFF, 0x08, 0x07, 0x00, 0x00, 0x00, 0x00 };

/**
 * Overriding the method (OnInit) in the CDC Async Operator
 */
class ACMAsyncOper : public CDCAsyncOper {
public:
  virtual uint8_t OnInit(ACM *pacm);
};

/**
 * Sends a frame
 * @param len
 * @param frame
 */
void send_frame(int len, uint8_t* frame);

/**
 * Get a frame
 * @param buf
 * @param len
 */
void get_frame(uint8_t* buf, uint16_t *len);

#endif /* USB_SENDER_UTILS_H_ */
