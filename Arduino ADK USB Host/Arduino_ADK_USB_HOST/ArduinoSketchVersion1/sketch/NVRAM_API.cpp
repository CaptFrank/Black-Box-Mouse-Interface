/*
 * NVRAM_API.cpp
 *
 *  Created on: Jul 25, 2013
 *      Author: fjpapin
 */

#include "NVRAM_API.h"


#define SPACE 	0x00

//! Define the structure
const NVRAM::nv_data_t nvram_default PROGMEM = {

        9600,
        9600,
        9600,
        0x0A,
        0x01,
        SELECT_BUTTON_1,
        INPUT,
        SELECT_BUTTON_2,
        INPUT,
        DBG_LED_1,
        OUTPUT,
        DBG_LED_2,
        OUTPUT,
        DBG_LED_3,
        OUTPUT,
        DBG_LED_4,
        OUTPUT,

        //! Possible commands stored to save ram space.
		0x01,	//
		0x02, SPACE, //
		0x03, //
		0x04, //
		0x05, SPACE, //
		0x06, //
		0x07, SPACE,//
		0x08, //
		0x09, //
		0x0A, SPACE, //
		0x0B, //
		0x0C, //
		0x0D, SPACE, //
		0x0E, //
		0x0F, SPACE, //
		0x10,
		0x11, SPACE,
        0x12,
        0x13

};

//! Load the saved args.
void NVRAM::load(void){
        // check for signature
        if (('f' != EEPROM.read(0)) ||
            ('s' != EEPROM.read(1))) {
                // load defaults
                memcpy_P(&nv, (void*)&nvram_default, sizeof(nv));
        } else {
                // load from NVRAM
                _loadx(2, sizeof(nv), &nv);
        }
}

//! Save the args
void NVRAM::save(void){
        // save to NVRAM
        _savex(2, sizeof(nv), &nv);

        EEPROM.write(0, 'f');
        EEPROM.write(1, 's');
}

//! Load bytes
void NVRAM::_loadx(uint8_t address, uint8_t size, void *value){
        uint8_t         *rp;

        rp = (uint8_t *)value;
        while (size--)
                *rp++ = EEPROM.read(address++);
}

//! Save bytes
void NVRAM::_savex(uint8_t address, uint8_t size, void *value){
        uint8_t         *rp;

        rp = (uint8_t *)value;
        while (size--)
        	EEPROM.write(address++, *rp++);
}

// Saves @ the specific address
void NVRAM::savex(byte address, byte size, void* value){
	_savex(address, size, value);
}



