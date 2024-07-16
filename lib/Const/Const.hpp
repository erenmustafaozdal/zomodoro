#ifndef __CONST_HPP__
#define __CONST_HPP__

#include <stdint.h>

namespace EMO
{
    namespace Const
    {
        const uint8_t PIN_BEEPER = 12;
        const uint8_t PIN_B1 = 2;
        const uint8_t PIN_B2 = 3;
        const uint8_t PIN_LCD_CONTRAST = 9;
        const uint8_t PIN_LCD_BRIGHTNESS = 8;

        // display
        const uint8_t PIN_RS = 11;
        const uint8_t PIN_ENABLE = 10;
        const uint8_t PIN_D4 = 4;
        const uint8_t PIN_D5 = 5;
        const uint8_t PIN_D6 = 6;
        const uint8_t PIN_D7 = 7;

        // pomodoro constants
        const uint8_t POM_WORK_MIN = 20;
        const uint8_t POM_BREAK_SHORT_MIN = 10;
        const uint8_t POM_BREAK_LONG_MIN = 30;

        const uint8_t POM_WORK_BEEPS = 5;
        const uint8_t POM_BREAK_SHORT_BEEPS = 1;
        const uint8_t POM_BREAK_LONG_BEEPS = 3;

        // eeprom address for saving pomodoros
        const int POM_SAVE_ADDRESS = 0;
    }
}

#endif