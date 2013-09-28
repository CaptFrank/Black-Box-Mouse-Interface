/*
 * Main_Defines.cpp
 *
 *  Created on: Jul 31, 2013
 *      Author: fjpapin
 */


#include "Main_Defines.h"

#define PAUSE_ROUTER				0x07 	// Pause router

	/**
	 * This does a memory check of the whole system, and checks
	 * to see how much free mem there is.
	 */
	word memory_check(){
		word freemem;
		freemem = ((word)&freemem) - ((word)&__bss_end);
		return freemem;
	}




