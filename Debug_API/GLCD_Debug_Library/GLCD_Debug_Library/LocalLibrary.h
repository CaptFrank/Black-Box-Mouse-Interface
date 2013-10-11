///
/// @file	LocalLibrary.h 
/// @brief	Library header
/// @details	<#details#>
/// @n	
/// @n @b	Project GLCD_Debug_Library
/// @n @a	Developed with [embedXcode](http://embedXcode.weebly.com)
/// 
/// @author	Francis Papineau
/// @author	Francis Papineau
/// @date	2013-10-10 9:11 PM
/// @version	<#version#>
/// 
/// @copyright	© Francis Papineau, 2013
/// @copyright	CC = BY NC SA
///
/// @see	ReadMe.txt for references
///


// Core library - MCU-based
#if defined (__AVR_ATmega328P__) || defined (__AVR_ATmega2560__) // Arduino specific
  #if defined(ARDUINO) && (ARDUINO >= 100)
  #include "Arduino.h" // for Arduino 1.0
  #else
  #include "WProgram.h" // for Arduino 23
  #endif
#elif defined(__32MX320F128H__) || defined(__32MX795F512L__) // chipKIT specific 
#include "WProgram.h"
#elif defined(__AVR_ATmega644P__) // Wiring specific
#include "Wiring.h"
#elif defined(__MSP430G2452__) || defined(__MSP430G2553__) || defined(__MSP430G2231__) // LaunchPad specific
#include "Energia.h"
#elif defined(MCU_STM32F103RB) || defined(MCU_STM32F103ZE) || defined(MCU_STM32F103CB) || defined(MCU_STM32F103RE) // Maple specific
#include "WProgram.h"	
#endif

#ifndef GLCD_Debug_Library_LocalLibrary_h
#define GLCD_Debug_Library_LocalLibrary_h

///
/// @brief	Blink a LED
/// @details	LED attached to pin is light on then light off
/// @n		Total cycle duration = ms
/// @param	pin pin to which the LED is attached
/// @param	times number of times
/// @param	ms cycle duration in ms
///
void blink(uint8_t pin, uint8_t times, uint16_t ms);

#endif
