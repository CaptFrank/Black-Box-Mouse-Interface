/*
 * USB_Sender_Utils.cpp
 *
 *  Created on: Aug 30, 2013
 *      Author: francispapineau
 */

#include "USB_Sender_Utils.h"
#include "max3421e.h"

/**
 * An override of the OnInit method inside the ACMAsyncOper
 * Class.
 * @param pacm
 * @return byte
 */
uint8_t ACMAsyncOper::OnInit(ACM *pacm){
	uint8_t rcode = 0;

	// Set DTR=1 and RTS=1:
	rcode = pacm->SetControlLineState(3);

	if (rcode) {
		error((void*) __LINE__, (void*) __func__);
	}

	lc.bCharFormat = 0;
	lc.bParityType = 0;
	lc.bDataBits = 8;

	rcode = pacm->SetLineCoding(&lc);

	if (rcode){
		error((void*) __LINE__, (void*) __func__);
	}
	return 0;
}

/**
 * This sends a frame to the usb host port.
 * @param len
 * @param frame
 */
void send_frame(int len, uint8_t* frame){

	uint8_t rcode;

	rcode = acm.SndData(len, frame);
	if (rcode) {
		error((void*) __LINE__, (void*) __func__);
	}
	return;
}

/**
 * This gets a frame from the usb host port.
 * @param buf
 * @param len
 */
void get_frame(uint8_t* buf, uint16_t *len){

	uint8_t rcode;
	rcode = acm.RcvData(len, buf);

	if (rcode && rcode != hrNAK) {
		error((void*) __LINE__, (void*) __func__);
	}
}

