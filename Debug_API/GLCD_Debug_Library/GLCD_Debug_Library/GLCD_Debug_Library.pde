/// 
/// @mainpage	GLCD_Debug_Library 
/// @details	<#details#>
/// @n 
/// @n 
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


///
/// @file	GLCD_Debug_Library.pde 
/// @brief	Main sketch
/// @details	<#details#>
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
/// @n
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
#else // error
#error Platform not defined
#endif

// Include application, user and local libraries
#include "LocalLibrary.h"

// Define variables and constants
///
/// @brief	Name of the LED
/// @details	Each board has a LED but connected to a different pin
///
uint8_t LED1;


///
/// @brief	Setup
/// @details	Define the pin the LED is connected to
///
// Add setup code 
void setup() {
  // LED1 pin number
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega2560__) // Arduino specific 
  LED1 = 13; 
#elif defined(__PIC32MX__) // chipKIT specific
  LED1 = 13;
#elif defined(__AVR_ATmega644P__) // Wiring specific
  LED1 = 15; 
#elif defined(__MSP430G2452__) || defined(__MSP430G2553__) || defined(__MSP430G2231__) // LaunchPad specific
  LED1 = 2; 
#elif defined(MCU_STM32F103RB) || defined(MCU_STM32F103ZE) || defined(MCU_STM32F103CB) || defined(MCU_STM32F103RE) // Maple specific
  LED1 = BOARD_LED_PIN; 
#endif

  pinMode(LED1, OUTPUT);     
}

///
/// @brief	Loop
/// @details	Call blink
///
// Add loop code 
void loop() {
  blink(LED1, 3, 333);
  delay(1000);    
}
