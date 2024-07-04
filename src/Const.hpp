#ifndef __CONST_HPP__
#define __CONST_HPP__

#include <stdint.h>

namespace EMO
{
    namespace Const
    {
        const uint8_t PIN_BEEPER = 2;         // beeper
        const uint8_t PIN_B1 = 3;             // button 1
        const uint8_t PIN_B2 = 4;             // button 2
        const uint8_t PIN_LCD_CONTRAST = 5;   // button contrast
        const uint8_t PIN_LCD_BRIGHTNESS = 6; // button brighness up

        // display
        const uint8_t PIN_RS = 7;
        const uint8_t PIN_ENABLE = 8;
        const uint8_t PIN_D4 = 9;
        const uint8_t PIN_D5 = 10;
        const uint8_t PIN_D6 = 11;
        const uint8_t PIN_D7 = 12;

        // pomodoro constants
        const uint8_t POM_WORK_MIN = 25;
        const uint8_t POM_BREAK_SHORT_MIN = 5;
        const uint8_t POM_BREAK_LONG_MIN = 15;

        const uint8_t POM_WORK_BEEPS = 5;
        const uint8_t POM_BREAK_SHORT_BEEPS = 1;
        const uint8_t POM_BREAK_LONG_BEEPS = 3;

        // eeprom address for saving pomodoros
        const int POM_SAVE_ADDRESS = 0;
    }
}

#endif