/*
 * Packet_Watchdog.cpp
 *
 *  Created on: Jul 24, 2013
 *      Author: fjpapin
 */

#include "Packet_Watchdog.h"

//! Reset the timer, accessible publicly.
void WATCHDOG::reset(void *arg, uint8_t packet_id, uint8_t pakcet_ver, void *packet_data) {
        ((WATCHDOG *)arg)->_reset();
}

/**
 * The check watchdog method.
 */
void WATCHDOG::check_watchdog(void){
        if (0 == _last_time_stamp) {
                //! we have never seen a packet

                //! Swap the bug character to "where is the link"
                //! Doing this every iteration is a bit wasteful, but we only do this while
                //! there is nothing else to do.
        } else {
                if (0 == _last_time_stamp) {
                        //! we are not currently in an alarm condition

                        //! if we have just timed out, next time around the alarm will sound
                        if ((millis() - _last_time_stamp) > PACKET_TIMEOUT) {
                        		_last_time_stamp = 1;
                                _alarm_inverted = true;

                                //! XXX we should save the last GPS data here in NVRAM
                                //! for lost-model recovery purposes.
                        }

                } else {
                        //! we are currently in an alarm condition

                        //! is it time to sound the alarm beep again?
                        if ((millis() - _last_alarm) > PACKET_ALARM_RATE) {
                        		_last_alarm = millis();

                                //! toggle the bug glyph between "where is the link" and "hey you!"
                                _alarm_inverted = !_alarm_inverted;
                        }
                }
        }
}

//! Reset the watchog timer.
void WATCHDOG::_reset(void){
        //! Kill the alarm if it's going and swap the bug character back
        if (0 != _last_alarm) {
                _last_alarm = 0;
        }

        //! Remember when we saw this packet
        _last_time_stamp = millis();
}
