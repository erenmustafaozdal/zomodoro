#ifndef __DISPLAY_HPP__
#define __DISPLAY_HPP__

#include <Adafruit_SSD1306.h>

namespace EMO
{
    /** SSD1306 OLED Ekran Sarmalayıcı Sınıfı.
     */
    class Display
    {
    public:
        Display();

        void Setup();

        Adafruit_SSD1306& GetLcd() { return the_lcd; }

    private:
        Adafruit_SSD1306 the_lcd;
    };
}

#endif
