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

        // LCD genellikle aşağıda gösterildiği gibi etiketlenen 16 pin aracılığıyla arayüzlenir
        //                                      // Arduino Bağlantıları
        //                                      // LCD                              ARDUINO
        //                                      //  1. GND - Ground                 GND
        //                                      //  2. VDD - 3 - 5V                 5V
        const uint8_t PIN_LCD_CONTRAST = 10; // //  3. VO  - Contrast
        const uint8_t PIN_RS = 11;           // //  4. RS  - Register Select
        //                                      //  5. RW  - Read/Write             GND
        const uint8_t PIN_ENABLE = 8; //        //  6. E   - Enable
        //                                      //  7. DB0 - Data Bit 0             N/A
        //                                      //  8. DB1 - Data Bit 1             N/A
        //                                      //  9. DB2 - Data Bit 2             N/A
        //                                      // 10. DB3 - Data Bit 3             N/A
        const uint8_t PIN_D4 = 4;             //// 11. DB4 - Data Bit 4
        const uint8_t PIN_D5 = 5;             //// 12. DB5 - Data Bit 5
        const uint8_t PIN_D6 = 6;             //// 13. DB6 - Data Bit 6
        const uint8_t PIN_D7 = 7;             //// 14. DB7 - Data Bit 7
        const uint8_t PIN_LCD_BRIGHTNESS = 9; //// 15. BL1 - Backlight +
        //                                      // 16. BL2 - Backlight -            GND

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
