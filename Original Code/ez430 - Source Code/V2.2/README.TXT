V2.2 (31.12.2012)
See "User Manual for new Functions.pdf" for detailed information.
*************************************************************************************************
-------------------

Menu changes
    - Date Setting menu: Submenu added for Selection of Day of Weeks language
            Currently implemented: English, German, Portuguese, Russian, Spanish and French
    - Tilt mode: Water bubble added
    - SYNC menu: Submenu added to Display SW Version and build date
    - Altimeter mode: Ambient pressure also in PSI available

Other changes
    - Behavior of Time & Date in case of a Reset: 
            Time & Date are set to their default values only if they are invalid

Changed files
    - date.c
    - clock.c
    - acceleration.c
    - acceleration.h
    - display2.c
    - display2.h
    - miscellaneous.c
    - altitude.c


V2.1 (15.04.2012)
See "User Manual for new Functions.pdf" for detailed information.
*************************************************************************************************
-------------------

Menu changes
    LINE2:
    - Date: SECOND display added
            Bottom line shows now: [DAY/MONTH] -> [Day of Week/DAY] -> [YEAR] -> [2.Time] -> [SECOND]
    - Submenu [OSC-R] added to SYNC menu
            [OSC-R] - Reset UCS (Unified Clock System), i.e. after clock failure occured
            Settings for [OSC-R] : [NO] -> [YES] -> [AUTO] -> [MAN]

Other changes
    - Backlight becomes no longer darker after button release 
    - No negative altitude bug fixed
    - Symbol "MAX" appears after clock failure flag set, i.e. after an ESD event
    
Changed files
    - main.c
    - clock.c
    - vti_ps.c
    - miscellaneous.c
    - miscellaneous.h
    - display.h



V2.0 (01.04.2011)
-------------------
See "User Manual for new Functions.pdf" for detailed information.
*************************************************************************************************
User navigation ( [..] = default menu item after reset )

LINE1: 	    [Time] -> Alarm -> Temperature -> Altitude/Ambient pressure -> Acceleration

LINE2: 	    [Date] -> Stopwatch -> Countdown timer -> Agility indicator -> Number storage -> Random number generator -> Battery -> ACC -> PPT -> SYNC -> RFBSL

Removed:
LINE1: 	Heart rate/Speed
LINE2: 	Calories/Distance
*************************************************************************************************

LINE1:
- Time: Daily and weekly time adjustment added
        Improves watch accuracy significantly.
        
- Time: Automatic adjustment for DST (Daylight saving time) added
        It is possible to switch between "no" and "auto" during time adjustment procedure.

- Ambient pressure display added to altitude menu
        Now it is possible to toggle between altitude and ambient pressure view.

LINE2:
- Date: Day of Week display added
        Bottom line shows now: [DAY/MONTH] -> [Day of Week/DAY] -> [YEAR] -> [2.Time]
        
- Date: Second time added
        Adjustable time difference to main time: 0...+23h.

- Stopwatch now also configurable as LAP timer

- Countdown timer added
        It uses the "RECORD" icon as its indicator.
        The countdown timer does not affect the stopwatch. Both could run simultaneously.

- Agility measurement added
        It uses the "Heart" icon for identification of this function.
            
- Lockable number storage for 10 4-digit numbers added
        It uses the "TOTAL" icon as its indicator.

- Random number generator added
        "AVERAGE" icon used for identification of this function

- Submenus added to SYNC menu:
        MYDEF - Set some settings to the authors preferred values
        CLEAR - Clears the number storage and unlock it by setting key memory to "0000"
        RESET - Restarts and resets the watch
            
OTHER:
- Backlight behavior changed
        A short push of the button activates the backlight for about 4 seconds.

- Bluerobin & Test modules excluded from build process 
        It saves about 6kB flash memory - needed for implementation of the features above
        Workaround for missing functions and users of limited IDE versions are implemented in "stubs.c"

Added files
-----------
    agility.c, agility.h
    countdowntimer.c, countdowntimer.h
    display2.c, display2.h
    miscellaneous.c, miscellaneous.h
    random.c, random.h
    stubs.c

Changed files
-------------
    main.c
    display.h
    acceleration.c
    altitude.c
    clock.c
    date.c
    menu.c, menu.h
    rfsimpliciti.c
    stopwatch.c

---------------------------------------------------------------------------------------------------
Some general remarks:
---------------------
All these functions have been developed using IAR's free of charge but code limited "Kickstart" IDE.
Therefore, I had to find some workarounds due to the restrictions: no driver code files are changeable.
There are many dependencies between modules. Be aware of that if you want to change something!

Used IDE & compiler versions: IAR Embedded Workbench 6.0 Kickstart with IAR C/C++ Compiler for MSP430 5.10.4.
This eZ430 Sports Watch firmware is based on TI's Sports Watch project version V1.5 (16.03.2010).


---------------------------------------------------------------------------------------------------
Version history of TI's original Sports Watch project
-----------------------------------------------------
V1.5 (16.03.2010)
Fixed following bugs
- main.c/init_application()                         Changed XT1 drive level to highest to avoid ACLK noise when turning on backlight.
- main.c/wakeup_event(), timer.c/TIMER0_A0_ISR()    Modified key lock procedure.
- vti_ps.c/ps_get_temp()                            Negative °C are now converted correctly to Kelvin
- altitude.c/mx_altitude()                          Enabled fast mode when changing altitude offset
- ports.c/PORT2_ISR()                               Disabled stopwatch stop when watch buttons are locked

Other changes
- main.c/read_calibration_values()                  Added range check for rf_frequoffset variable
                                                    Added bytes for altitude offset correction and s/w version
- altitude.h, altitude.c                            Added initial altitude offset correction 
- SimpliciTI                                        Added SimpliciTI sources to project. Upgraded to Version 1.1.1.
- RFBSL                                             Added wireless update support
- Button names                                      Changed button names from M1/M2/S1/S2/BL to STAR/NUM/UP/DOWN/BACKLIGHT
                                                    
V1.4 (22.11.2009)
First version released to manufacturing.


---------------------------------------------------------------------------------------------------
How to add a new watch Module - esp. use hint (2) if you have a limited IDE
-------------------------------------------------------------------------------
1.  Copy a preexisting module relatively close to what you want your new one to do.
2.  If the module involves a timer and you are not able to edit "timer.h" and/or "timer.c"
    due to the limited IDE - use appropriate functions in stopwatch.c and/or clock.c
    like my injection of cdtimer_tick() in clock_tick() in clock.c to get a call every second
3.  Add the module to the menu by modifying "menu.h" and "menu.c"
4.  For most modules, make sure they are initialized properly by editing "main.c"
5.  Don't forget setting of command line option "--ks_version" in the IAR Kickstart IDE:
    Project -> Options -> Linker -> Extra Options
6.  This project requires the highest optimization step of compiler:
    Please check the box "High" and choose "Size" in Project -> Options -> C/C++Compiler -> Optimizations


---------------------------------------------------------------------------------------------------
How to create an msp430-txt formatted file for programming the Sports Watch via RFBSL
(Workaround for users of limited IDE)
---------------------------------------------
1.  Download and install Elprotronics free software FET-Pro430 Lite 
    http://www.elprotronic.com/download.html
2.  Open the *.d43 file (i.e. "ez430_chronos_868MHz.d43")
3.  Choose "Save Code as" from "File" menu, select "Texas Instruments (*.txt)
4.  My copy of this software created sometimes-erroneous output. You have to disassemble the watch and download the code via IDE in this case.


---------------------------------------------------------------------------------------------------



