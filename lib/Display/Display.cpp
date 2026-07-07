#include <Arduino.h>
#include <Wire.h>
#include "Display.hpp"

namespace EMO
{
    Display::Display() : the_lcd(128, 64, &Wire, -1)
    {
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
}
