#include <stdarg.h>
#include <Arduino.h>
#include "Display.hpp"
#include "Const.hpp"

namespace EMO
{
    Display::Display() : the_lcd(Const::PIN_RS, Const::PIN_ENABLE,
                                 Const::PIN_D4, Const::PIN_D5, Const::PIN_D6, Const::PIN_D7)
    {
        for (uint8_t i = 0; i < MAX_LINES; ++i)
            memset(the_old_line[i], 0, BUF_SIZE);
    }

    // -------------------------------------------------------------------------

    void Display::Setup()
    {
        the_lcd.begin(MAX_CHARS, MAX_LINES);             // 16x2 formatında başlat
        pinMode(EMO::Const::PIN_LCD_BRIGHTNESS, OUTPUT); // PWM pini kullanır
        pinMode(EMO::Const::PIN_LCD_CONTRAST, OUTPUT);   // PWM pini kullanır

        // 80/255 duty cycle PWM verir
        analogWrite(EMO::Const::PIN_LCD_BRIGHTNESS, 128);

        // Bu pin ile GND arasında 22uF kapasitör bulunur
        analogWrite(EMO::Const::PIN_LCD_CONTRAST, 144);
    }

    // -------------------------------------------------------------------------

    void Display::Setup_Char(uint8_t a_char, uint8_t *a_matrix)
    {
        the_lcd.createChar(a_char, a_matrix);
    }

    // -------------------------------------------------------------------------

    void Display::Write(uint8_t a_x, uint8_t a_y, const char *a_format, ...)
    {
        va_list vl;
        va_start(vl, a_format);
        write(a_x, a_y, a_format, vl);
        va_end(vl);
    }

    // -------------------------------------------------------------------------

    void Display::Write(uint8_t a_y, const char *a_format, ...)
    {
        va_list vl;
        va_start(vl, a_format);
        write(0, a_y, a_format, vl);
        va_end(vl);
    }

    // -------------------------------------------------------------------------

    void Display::write(uint8_t a_x, uint8_t a_y, const char *a_format, va_list &a_vl)
    {
        if (a_y >= MAX_LINES)
            return;

        int written = vsnprintf(the_buf, BUF_SIZE, a_format, a_vl);

        if (written >= 0) // Karakter yazmasak bile - hala satırı temizleriz
        {
            // Kalan kısmı boşluklarla doldur
            for (int i = written; i < MAX_CHARS; ++i)
                the_buf[i] = ' ';
            the_buf[MAX_CHARS] = 0;
        }
        else
        {
            memset(the_buf, 0, BUF_SIZE);
        }

        if (strcmp(the_buf, the_old_line[a_y]) != 0)
        {
            the_lcd.setCursor(0, a_y);
            the_lcd.print(the_buf);
            memcpy(the_old_line[a_y], the_buf, BUF_SIZE);
        }
    }
}
