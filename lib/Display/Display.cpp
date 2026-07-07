#include <stdarg.h>
#include <Arduino.h>
#include <Wire.h>
#include "Display.hpp"
#include "Const.hpp"

namespace EMO
{
    Display::Display() : the_lcd(128, 64, &Wire, -1)
    {
        for (uint8_t i = 0; i < MAX_LINES; ++i)
            memset(the_old_line[i], 0, BUF_SIZE);
    }

    // -------------------------------------------------------------------------

    void Display::Setup()
    {
        Wire.begin();

        // Deneyap OLED varsayılan adresi 0x7A (7-bit adresi 0x3D) veya ADR kısa devreyle 0x78 (0x3C)'dir.
        if(!the_lcd.begin(SSD1306_SWITCHCAPVCC, 0x3D)) {
            if(!the_lcd.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
                Serial.println(F("SSD1306 OLED ekran başlatılamadı!"));
                return;
            }
        }
        
        the_lcd.clearDisplay();
        the_lcd.setTextSize(1); // Okunabilir olması için yazı tipi boyutu
        the_lcd.setTextColor(SSD1306_WHITE);
        the_lcd.setCursor(0, 0);
        the_lcd.println("Zomodoro");
        the_lcd.display();
    }

    // -------------------------------------------------------------------------

    void Display::Setup_Char(uint8_t a_char, uint8_t *a_matrix)
    {
        // OLED için custom karakter yüklemeye gerek yok, stub yapıldı
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

        if (written >= 0)
        {
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
            memcpy(the_old_line[a_y], the_buf, BUF_SIZE);
            
            the_lcd.clearDisplay();
            // 1. Satır
            the_lcd.setCursor(0, 8);
            the_lcd.print(the_old_line[0]);
            // 2. Satır
            the_lcd.setCursor(0, 32);
            the_lcd.print(the_old_line[1]);
            the_lcd.display();
            
            Serial.println(the_buf);
        }
    }
}
