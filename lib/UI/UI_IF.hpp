#ifndef __UI_IF_HPP__
#define __UI_IF_HPP__

#include <stdint.h>

namespace EMO
{
    class State_IF;

    /// UI için arayüz sınıfı - pomodoro sınıfı bir şeyler göstermek için bunu kullanır.
    class UI_IF
    {
    public:
        virtual ~UI_IF() {}

        /// Durumları görselleştirir.
        virtual void Show_Ready(const State_IF &) = 0;
        virtual void Show_Running(const State_IF &) = 0;
        virtual void Show_Paused(const State_IF &, bool is_sound_detected = false) = 0;
        virtual void Show_Finished(const State_IF &) = 0;

        /// UI nesnesinin beeper'ını ayarlar.
        virtual void Set_Beeper(uint8_t) = 0;

        /// LDR sensörüne göre LCD parlaklık ayarlar
        virtual void Set_Brightness(uint8_t a_brightness) = 0;
        virtual void UpdateBrightness(unsigned long currentTime) = 0;

        /// Durumun gösterilip gösterilmediğini döner (biraz zaman alabilir).
        virtual bool Showing() const = 0;

        /// Başlangıçta bir kez çağrılır.
        virtual void Setup() = 0;
    };
}

#endif
