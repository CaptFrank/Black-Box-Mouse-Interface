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
// Countdown timer functions.
// *************************************************************************************************
// Include section

// system
#include "project.h"
#include <string.h>

// driver
#include "countdowntimer.h"
#include "ports.h"
#include "display.h"
#include "timer.h"
#include "buzzer.h"
#include "user.h"

// logic
#include "menu.h"
#include "display2.h"


// *************************************************************************************************
// Prototypes section
void start_cdtimer(void);
void stop_cdtimer(void);
void reset_cdtimer(void);
void cdtimer_tick(void);
void mx_cdtimer(u8 line);
void sx_cdtimer(u8 line);
void display_cdtimer(u8 line, u8 update);
void set_cdtimer(void);


// *************************************************************************************************
// Defines section


// *************************************************************************************************
// Global Variable section
struct cdtimer scdtimer;


// *************************************************************************************************
// Extern section


// *************************************************************************************************
// @fn          init_cdtimer
// @brief       Presets cdtimer counter and sets cdtimer state to off.
// @param       none
// @return      none
// *************************************************************************************************
void init_cdtimer(void)
{
    // Init cdtimer state 
    scdtimer.state      = CDTIMER_STOP;     
    
    // Set counter to default
    memcpy(scdtimer.time, scdtimer.defaultTime, sizeof(scdtimer.time));

}


// *************************************************************************************************
// @fn          reset_cdtimer
// @brief       Init cdtimer counter and sets mode.
// @param       none
// @return      none
// *************************************************************************************************
void reset_cdtimer(void)
{
    init_cdtimer();
    
    // Set mode to stop timer
	scdtimer.mode = CDTIMER_MODE_ONCE; 
}




// *************************************************************************************************
// @fn          cdtimer_tick
// @brief       Called by 1Hz clock_tick function. 
//              Decreases cdtimer counter and triggers display update.
// @param       none
// @return      none
// *************************************************************************************************
void cdtimer_tick(void)
{
  //Make sure cdtimer is running before we do anything else
  if(scdtimer.state == CDTIMER_RUN)
  {
        // Draw flag minimizes display update activity
        //
        // swt.drawFlag = 1: second L
        // swt.drawFlag = 2: second H/L
        // swt.drawFlag = 3: minutes L, second H/L
        // swt.drawFlag = 4: minutes H/L, second H/L
        // swt.drawFlag = 5: hours L, minutes H/L, second H/L
        // swt.drawFlag = 6: hours H/L, minutes H/L, second H/L

        // Set always second draw flag
        scdtimer.drawFlag = 1;

        // Subtract sequentially
        scdtimer.time[5]--;                            // second  L (0 - 9)
        if (scdtimer.time[5] == 0x2F) 
        {
            scdtimer.drawFlag++;                       // 2
            scdtimer.time[5] = '9';
            scdtimer.time[4]--;                        // second  H (0 - 5)
            if (scdtimer.time[4] == 0x2F) 
            {
                scdtimer.drawFlag ++;                  // 3
                scdtimer.time[4] = '5';
                scdtimer.time[3]--;                    // minutes L (0 - 9)
                if (scdtimer.time[3] == 0x2F) 
                {
                    scdtimer.drawFlag++;               // 4
                    scdtimer.time[3] = '9';
                    scdtimer.time[2]--;                // minutes H (0 - 5)
                                                            
                    if (scdtimer.time[2] == 0x2F) 
                    {
                        scdtimer.drawFlag++;               // 5
                        scdtimer.time[2] = '5';
                        scdtimer.time[1]--;                // hours L (0-9)    

                        if (scdtimer.time[1] == 0x2F) 
                        {
                            scdtimer.drawFlag++;           // 6
                            scdtimer.time[1] = '9';
                            scdtimer.time[0]--;            // hours H (0-1)    

                        } 
                        if(scdtimer.time[0] ==0x2F)
                        {
                             // When we reach 0, reset and beep 
                             stop_cdtimer();
                             init_cdtimer();
                             // Refresh display 
                             display_cdtimer(LINE2, DISPLAY_LINE_UPDATE_FULL);
                             // Option for continue
                             if(scdtimer.mode == CDTIMER_MODE_CONTINUE)
                             { 
                                 // (Re) start cdtimer
                                 start_cdtimer();
                             }
                             start_buzzer(20, CONV_MS_TO_TICKS(50), CONV_MS_TO_TICKS(150));
                        }
                    } 
                }
            }
        }  
        
  }
}



// *************************************************************************************************
// @fn          start_cdtimer
// @brief       Starts cdtimer timer and sets cdtimer state to on.
// @param       none
// @return      none
// *************************************************************************************************
void start_cdtimer(void)
{
    // Set cdtimer run flag
    scdtimer.state = CDTIMER_RUN;   
    
}


// *************************************************************************************************
// @fn          stop_cdtimer
// @brief       Stops cdtimer timer and sets cdtimer state to off.
//              Does not reset cdtimer count.
// @param       none
// @return      none
// *************************************************************************************************
void stop_cdtimer(void)
{
    // Clear cdtimer run flag
    scdtimer.state = CDTIMER_STOP;  
    
    // Call draw routine immediately
    display_cdtimer(LINE2, DISPLAY_LINE_UPDATE_FULL);
}


// *************************************************************************************************
// @fn          mx_cdtimer
// @brief       cdtimer set routine. Mx stops cdtimer and resets count.
// @param       u8 line LINE2
// @return      none
// *************************************************************************************************
void mx_cdtimer(u8 line)
{
    // Stop cdtimer
    stop_cdtimer();

    //Set cdtimer
    set_cdtimer();
            
    // Reset cdtimer count
    init_cdtimer();    
    
    // Display cdtimer time
    display_cdtimer(line, DISPLAY_LINE_UPDATE_FULL);

}


// *************************************************************************************************
// @fn          sx_cdtimer
// @brief       cdtimer direct function. DOWN Button starts/stops cdtimer, but does not reset count.
// @param       u8 line LINE2
// @return      none
// *************************************************************************************************
void sx_cdtimer(u8 line)
{
    // DOWN Button: RUN, STOP
    if(button.flag.down)
    {
        if (scdtimer.state == CDTIMER_STOP)
        {
            // (Re)start cdtimer
            start_cdtimer();
        }
        else 
        {
            // Stop cdtimer 
            stop_cdtimer();
        }
            
    }
}


// *************************************************************************************************
// @fn          display_cdtimer
// @brief       cdtimer user routine. UP/DOWN Button starts/stops cdtimer, but does not reset count.
// @param       u8 line LINE2
//              u8 update   DISPLAY_LINE_UPDATE_PARTIAL, DISPLAY_LINE_UPDATE_FULL
// @return      none
// *************************************************************************************************
void display_cdtimer(u8 line, u8 update)
{
    // Partial line update only
    if (update == DISPLAY_LINE_UPDATE_PARTIAL)
    {   
         // Display HH:MM:SS
         switch(scdtimer.drawFlag) 
         {
             case 6: display_char(LCD_SEG_L2_5, scdtimer.time[0], SEG_ON);
             case 5: display_char(LCD_SEG_L2_4, scdtimer.time[1], SEG_ON);
             case 4: display_char(LCD_SEG_L2_3, scdtimer.time[2], SEG_ON);
             case 3: display_char(LCD_SEG_L2_2, scdtimer.time[3], SEG_ON);
             case 2: display_char(LCD_SEG_L2_1, scdtimer.time[4], SEG_ON);
             case 1: display_char(LCD_SEG_L2_0, scdtimer.time[5], SEG_ON);
         }       
     }
    // Redraw whole line, but only if cdtimer is currently displayed
    else if((update == DISPLAY_LINE_UPDATE_FULL) && (ptrMenu_L2 == &menu_L2_cdtimer))
    {
		// Show blinking heart icon
		display_symbol(LCD_ICON_RECORD, SEG_ON_BLINK_ON);
		
        // Display HH:MM:SS
        display_chars(LCD_SEG_L2_5_0, scdtimer.time, SEG_ON);
        display_symbol(LCD_SEG_L2_COL1, SEG_ON);
        display_symbol(LCD_SEG_L2_COL0, SEG_ON);
    }
    else if (update == DISPLAY_LINE_CLEAR)
    {
        // Clean up symbols when leaving function
		if (scdtimer.state == CDTIMER_STOP) 
		{
			display_symbol(LCD_ICON_RECORD, SEG_OFF_BLINK_OFF);
		}
		else
		{
			display_symbol(LCD_ICON_RECORD, SEG_ON_BLINK_OFF);
		}
    }
}

// *************************************************************************************************
// @fn          set_cdtimer
// @brief       Set's the cdtimer.
// @param       none
// @return      none
// *************************************************************************************************
void set_cdtimer(void)
{
    u8 select;
    s32 hours;
    s32 minutes;
    s32 seconds;
    s32 ModeTmp;
    u8 * str;
        
    //Get hours, minutes, and seconds into interger form
    hours   = (scdtimer.defaultTime[0]-48)*10  + (scdtimer.defaultTime[1]-48);
    minutes = (scdtimer.defaultTime[2]-48)*10  + (scdtimer.defaultTime[3]-48);
    seconds = (scdtimer.defaultTime[4]-48)*10  + (scdtimer.defaultTime[5]-48);
    ModeTmp = scdtimer.mode;
        
        
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
            // Store local variables in global cdtimer default
            scdtimer.defaultTime[0]=*itoa(hours, 2, 0);
            scdtimer.defaultTime[1]=*itoa(hours, 1, 0);
            scdtimer.defaultTime[2]=*itoa(minutes, 2, 0);
            scdtimer.defaultTime[3]=*itoa(minutes, 1, 0);
            scdtimer.defaultTime[4]=*itoa(seconds, 2, 0);
            scdtimer.defaultTime[5]=*itoa(seconds, 1, 0);
            scdtimer.mode = ModeTmp;
            //Set display update flag
            display.flag.line2_full_update = 1;
            break;
        }

        switch (select)
        {
            case 0: // Display HH:MM:SS (LINE2) 
                    str = itoa(hours, 2, 0);
                    display_chars(LCD_SEG_L2_5_4, str, SEG_ON);
                    display_symbol(LCD_SEG_L2_COL0, SEG_ON);
                    
                    str = itoa(minutes, 2, 0);
                    display_chars(LCD_SEG_L2_3_2, str, SEG_ON);
                        
                    str = itoa(seconds, 2, 0);
                    display_chars(LCD_SEG_L2_1_0, str, SEG_ON);

                    // Set hours
                    set_value(&hours, 2, 0, 0, 19, SETVALUE_ROLLOVER_VALUE + SETVALUE_DISPLAY_VALUE + SETVALUE_NEXT_VALUE, LCD_SEG_L2_5_4, display_value1);
                    select = 1;
                    break;

            case 1: // Set minutes
                    set_value(&minutes, 2, 0, 0, 59, SETVALUE_ROLLOVER_VALUE + SETVALUE_DISPLAY_VALUE + SETVALUE_NEXT_VALUE, LCD_SEG_L2_3_2, display_value1);
                    select = 2;
                    break;
                                    
            case 2: // Set seconds
                    set_value(&seconds, 2, 0, 0, 59, SETVALUE_ROLLOVER_VALUE + SETVALUE_DISPLAY_VALUE + SETVALUE_NEXT_VALUE, LCD_SEG_L2_1_0, display_value1);
                    select = 3;
                    break;
            
            case 3: // Set mode
                    clear_line(LINE2);
                    set_value(&ModeTmp, 0, 0, 0, 1, SETVALUE_DISPLAY_VALUE + SETVALUE_ROLLOVER_VALUE + SETVALUE_NEXT_VALUE, LCD_SEG_L2_3_0, display_CONT_ONCE);
                    select = 0;
        }
    }
    
    // Clear button flag
    button.all_flags = 0;
    
}

