#ifndef __UI_HPP__
#define __UI_HPP__

#include "UI_IF.hpp"
#include "Display.hpp"
#include "Beeper.hpp"
#include "State_IF.hpp"
#include "LDR.hpp"

namespace EMO
{
    /// LCD ekran ve beeper kullanan kullanıcı arayüzü sınıfı.
    class UI : public UI_IF
    {
    public:
        UI(uint8_t ldrPin);

        virtual void Show_Ready(const State_IF &);
        virtual void Show_Running(const State_IF &);
        virtual void Show_Paused(const State_IF &a_state, bool is_sound_detected = false) override;
        virtual void Show_Finished(const State_IF &) override;
        virtual void Show_Calibrating(const State_IF &, uint32_t elapsed_ms) override;

        virtual void Set_Beeper(uint8_t);
        virtual bool Showing() const;

        virtual void Setup();

        // LDR'den gelen bilgiyle parlaklık ayarlar
        void Set_Brightness(uint8_t brightness);
        // Parlaklık güncelleme fonksiyonu
        void UpdateBrightness(unsigned long currentTime);

    private:
        // OLED Çizim Yardımcıları
        void drawHeader(const State_IF &a_state);
        void drawBattery(int16_t x, int16_t y);
        void drawSmallHeart(int16_t x, int16_t y, uint8_t fill_level);
        void drawClippedHeart(int16_t x, int16_t y, uint8_t fill_pct);
        bool is_heart_filled_pixel(int16_t col, int16_t row);
        void drawTomato(int16_t x, int16_t y);
        void drawPause(int16_t x, int16_t y);
        void drawShush(int16_t x, int16_t y);

        uint8_t the_timer;

        Beeper the_beeper;
        Display the_display;

        LDR lightSensor; // LDR modülü
        unsigned long lastBrightnessUpdate;
        const unsigned long brightnessUpdateInterval;
    };
}

#endif
