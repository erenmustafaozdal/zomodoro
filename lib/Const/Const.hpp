#ifndef __CONST_HPP__
#define __CONST_HPP__

#include <stdint.h>
#include <Arduino.h>

namespace EMO
{
    namespace Const
    {
        static const uint8_t PIN_BEEPER = 12;
        static const uint8_t PIN_B1 = 2;
        static const uint8_t PIN_B2 = 3;
        static const uint8_t PIN_LDR = A0;            // LDR pini tanımı
        static const uint8_t PIN_SOUND_SENSOR = A1;   // Ses sensörü pini tanımı
        static const uint8_t SOUND_SAMPLE_TIME = 10;  // Ses kontrolü yapılacak zaman
        static const uint16_t SOUND_THRESHOLD = 1333; // Ses eşiği

        // LCD genellikle aşağıda gösterildiği gibi etiketlenen 16 pin aracılığıyla arayüzlenir
        //                                          /// Arduino Bağlantıları
        //                                          /// LCD                              ARDUINO
        //                                          ///  1. GND - Ground                 GND
        //                                          ///  2. VDD - 3 - 5V                 5V
        static const uint8_t PIN_LCD_CONTRAST = 10; ///  3. VO  - Contrast
        static const uint8_t PIN_RS = 11;           ///  4. RS  - Register Select
        //                                          ///  5. RW  - Read/Write             GND
        static const uint8_t PIN_ENABLE = 8; //     ///  6. E   - Enable
        //                                          ///  7. DB0 - Data Bit 0             N/A
        //                                          ///  8. DB1 - Data Bit 1             N/A
        //                                          ///  9. DB2 - Data Bit 2             N/A
        //                                          /// 10. DB3 - Data Bit 3             N/A
        static const uint8_t PIN_D4 = 4;             // 11. DB4 - Data Bit 4
        static const uint8_t PIN_D5 = 5;             // 12. DB5 - Data Bit 5
        static const uint8_t PIN_D6 = 6;             // 13. DB6 - Data Bit 6
        static const uint8_t PIN_D7 = 7;             // 14. DB7 - Data Bit 7
        static const uint8_t PIN_LCD_BRIGHTNESS = 9; // 15. BL1 - Backlight +
        //                                           // 16. BL2 - Backlight -            GND

        // Ekran parlaklık ayarları
        static const uint8_t LCD_MIN_BRIGHTNESS = 11;
        static const uint8_t LCD_MAX_BRIGHTNESS = 33;

        // pomodoro sabitleri
        static const uint8_t POM_WORK_MIN = 20;
        static const uint8_t POM_BREAK_SHORT_MIN = 10;
        static const uint8_t POM_BREAK_LONG_MIN = 30;

        static const uint8_t POM_WORK_BEEPS = 11;
        static const uint8_t POM_BREAK_SHORT_BEEPS = 5;
        static const uint8_t POM_BREAK_LONG_BEEPS = 7;

        // Pomodoroları kaydetmek için eeprom adresi
        static const int POM_SAVE_ADDRESS = 0;
    }
}

#endif
