// *************************************************************************************************
//
//  Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/ 
//   
//   
//    Redistribution and use in source and binary forms, with or without 
//    modification, are permitted provided that the following conditions 
//    are met:
//  
//      Redistributions of source code must retain the above copyright 
//      notice, this list of conditions and the following disclaimer.
//   
//      Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the 
//      documentation and/or other materials provided with the   
//      distribution.
//   
//      Neither the name of Texas Instruments Incorporated nor the names of
//      its contributors may be used to endorse or promote products derived
//      from this software without specific prior written permission.
//  
//    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
//    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
//    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//    A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
//    OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
//    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
//    LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//    THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
//    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
//    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// *************************************************************************************************
// Random generator functions.
// *************************************************************************************************
// Include section

// system
#include "project.h"
#include <string.h>
#include <stdlib.h>

// driver
#include "ports.h"
#include "display.h"
#include "timer.h"
#include "buzzer.h"
#include "user.h"

// logic
#include "menu.h"
#include "random.h"
#include "clock.h"
#include "date.h"
#include "altitude.h"
#include "display2.h"


// *************************************************************************************************
// Prototypes section
void start_random(void);
void stop_random(void);
void reset_random(void);
void random_tick(void);
void mx_random(u8 line);
void sx_random(u8 line);
void display_random(u8 line, u8 update);
void set_random(void);


// *************************************************************************************************
// Defines section
#define RANDOM_MAX  9999


// *************************************************************************************************
// Global Variable section
struct random srandom;

// *************************************************************************************************
// Extern section


// *************************************************************************************************
// @fn          random_tick
// @brief       Called by 1Hz clock_tick function. 
// @param       none
// @return      none
// *************************************************************************************************
void random_tick(void)
{
  //Make sure it is something running before we do anything else
  if(srandom.state == RANDOM_RUN)
  {
      // Generate random number
      if(srandom.Style == STYLE_ALTERNATE) 
      { 
          srandom.Digit[0] = srandom.Digit[1];
          srandom.Digit[1] = srandom.Digit[2];
          srandom.Digit[2] = srandom.Digit[3];
          srandom.Digit[3] = srandom.Digit[4];
          srandom.Digit[4] = (rand() % 10) + 0x30;
      }
      else 
      {
          srandom.RandomNumber = (rand() % (srandom.RandomMax-srandom.RandomMin+1)) + srandom.RandomMin;
      }
      
      // Check mode
      if(srandom.mode == MODE_ONCE) 
      { 
          srandom.state = RANDOM_STOP; 
          display_symbol(LCD_SYMB_AVERAGE, SEG_ON);
      }
  }
}




// *************************************************************************************************
// @fn          reset_random
// @brief       Initialize random generator.
// @param       none
// @return      none
// *************************************************************************************************
void reset_random(void)
{
    u8 i;
    // Init random state 'Off'
    srandom.state = RANDOM_STOP;     
    srandom.mode = MODE_CONTINUE;
    // Style
    srandom.Style = STYLE_DEFAULT;

    // Initialize random generator
    srand((int)(sAlt.temperature) * (int)(sAlt.pressure));
    srandom.RandomMin = 0;
    srandom.RandomMax = RANDOM_MAX;
    srandom.RandomNumber = (rand() % (srandom.RandomMax-srandom.RandomMin+1)) + srandom.RandomMin;
    for(i = 0; i < 5; i++) { srandom.Digit[i] = 0; }
}




// *************************************************************************************************
// @fn          start_random
// @brief       Starts random.
// @param       none
// @return      none
// *************************************************************************************************
void start_random(void)
{

   // Set random run flag
    srandom.state = RANDOM_RUN;   
    
}


// *************************************************************************************************
// @fn          stop_random
// @brief       Stops random.
// @param       none
// @return      none
// *************************************************************************************************
void stop_random(void)
{
    // Clear cdtimer run flag
    srandom.state = RANDOM_STOP;  
    
}


// *************************************************************************************************
// @fn          mx_random
// @brief       Set routine for random.
// @param       u8 line LINE2
// @return      none
// *************************************************************************************************
void mx_random(u8 line)
{
    // Stop random
    stop_random();

    //Set random
    set_random();
            
    // start random
    start_random();    
    
    // Display cdtimer time
    display_random(line, DISPLAY_LINE_UPDATE_FULL);

}


// *************************************************************************************************
// @fn          sx_random
// @brief       Direct function for random. DOWN Button starts/stops random.
// @param       u8 line LINE2
// @return      none
// *************************************************************************************************
void sx_random(u8 line)
{
    // DOWN Button: RUN, STOP
    if(button.flag.down)
    {
        if (srandom.state == RANDOM_STOP)
        {
            // (Re)start random
            start_random();
            if(srandom.mode == MODE_ONCE)
            {
                display_symbol(LCD_SYMB_AVERAGE, SEG_OFF);
            }
        }
        else 
        {
            // Stop random 
            stop_random();
        }
            
    }
}


// *************************************************************************************************
// @fn          display_special
// @brief       Display routine for special text
// @param       u8 segments		LCD segments where value is displayed - not used
//				u32 value	    see below
//				u8 digits		Number of digits to convert - not used
//				u8 blanks		Number of leadings blanks in itoa result string - not used
// @return      none
// *************************************************************************************************
void display_special(u8 segments, u32 value, u8 digits, u8 blanks)
{
	if(value == 0) { display_chars(LCD_SEG_L2_3_0, (u8 *)"ALL-", SEG_ON_BLINK_ON); }
	if(value == 1) { display_chars(LCD_SEG_L2_3_0, (u8 *)"ONE-", SEG_ON_BLINK_ON); }
}



// *************************************************************************************************
// @fn          display_random
// @brief       User routine for random. UP/DOWN Button starts/stops random generator, but does not reset.
// @param       u8 line LINE2
//              u8 update   DISPLAY_LINE_UPDATE_PARTIAL, DISPLAY_LINE_UPDATE_FULL
// @return      none
// *************************************************************************************************
void display_random(u8 line, u8 update)
{
    u8 * str;
    
    if (update == DISPLAY_LINE_UPDATE_PARTIAL)
	{
		// Show AVERAGE icon
		display_symbol(LCD_SYMB_AVERAGE, SEG_ON);
	}
    
    // Partial line update only
    if ((update == DISPLAY_LINE_UPDATE_PARTIAL) || (update == DISPLAY_LINE_UPDATE_FULL))
    {   
        if(srandom.Style == STYLE_ALTERNATE) { str = (u8 *)srandom.Digit; }
        else { str = itoa(srandom.RandomNumber, 5, 4); }
        display_chars(LCD_SEG_L2_4_0, str, SEG_ON);
    }    
    else if (update == DISPLAY_LINE_CLEAR)
         {
             // Stop random generator when leaving function
             srandom.state = RANDOM_STOP;
             // Clean up display
             display_symbol(LCD_SYMB_AVERAGE, SEG_OFF_BLINK_OFF); 
         }
}

// *************************************************************************************************
// @fn          set_random
// @brief       Set's the random generator maximum number.
// @param       none
// @return      none
// *************************************************************************************************
void set_random(void)
{
    u8 select;
    s32 RandomMaxTmp;
    s32 RandomMinTmp;
    s32 RandomModeTmp;
    s32 RandomStyleTmp;
         
    // Copy to temp 
    RandomMaxTmp = srandom.RandomMax;
    RandomMinTmp = srandom.RandomMin;
    RandomModeTmp = srandom.mode;
    RandomStyleTmp = srandom.Style;
        
    // Display current value
    clear_display_all();
    // Show blinking AVERAGE icon
	display_symbol(LCD_SYMB_AVERAGE, SEG_ON_BLINK_ON);

    
    // Init value index
    select = 0; 
        
    // Loop values until all are set or user breaks set
    while(1) 
    {
        // Idle timeout: exit without saving 
        if (sys.flag.idle_timeout) break;
        
        // NUM Button (short): save, then exit 
        if (button.flag.num) 
        {
            // Store local variables in global 
            srandom.RandomMax = RandomMaxTmp;
            srandom.RandomMin = RandomMinTmp;
            srandom.mode = RandomModeTmp;
            srandom.Style = RandomStyleTmp;
            //Set display update flag
            display_symbol(LCD_SYMB_AVERAGE, SEG_ON_BLINK_OFF);
            display.flag.full_update = 1;
            break;
        }

        switch (select)
        {
            case 0: // Set random max number
                    display_chars(LCD_SEG_L1_3_0, (u8 *)"HI  ", SEG_ON);
                    set_value(&RandomMaxTmp, 4, 3, RandomMinTmp+1, RANDOM_MAX, SETVALUE_DISPLAY_VALUE + SETVALUE_FAST_MODE + SETVALUE_NEXT_VALUE, LCD_SEG_L2_3_0, display_value1);
                    select = 1;
                    break;
            case 1: // Set random min number
                    display_chars(LCD_SEG_L1_3_0, (u8 *)"LO  ", SEG_ON);
                    set_value(&RandomMinTmp, 4, 3, 0, RandomMaxTmp-1, SETVALUE_DISPLAY_VALUE + SETVALUE_FAST_MODE + SETVALUE_NEXT_VALUE, LCD_SEG_L2_3_0, display_value1);
                    select = 2;
                    break;
            case 2: // Set random generator mode
                    display_chars(LCD_SEG_L1_3_0, (u8 *)"MODE", SEG_ON);
                    set_value(&RandomModeTmp, 0, 0, 0, 1, SETVALUE_DISPLAY_VALUE + SETVALUE_ROLLOVER_VALUE + SETVALUE_NEXT_VALUE, LCD_SEG_L2_3_0, display_CONT_ONCE);
                    select = 3;
            case 3: // Set random view style
                    display_chars(LCD_SEG_L1_3_0, (u8 *)"STYL", SEG_ON);
                    set_value(&RandomStyleTmp, 0, 0, 0, 1, SETVALUE_DISPLAY_VALUE + SETVALUE_ROLLOVER_VALUE + SETVALUE_NEXT_VALUE, LCD_SEG_L2_3_0, display_special);
                    select = 0;
                    break;
        }
    }
    // Clear button flag
    button.all_flags = 0;
    
}

