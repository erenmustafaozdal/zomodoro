#ifndef __BUTTON_HPP__
#define __BUTTON_HPP__

#include <Arduino.h>
#include "Button_Logic.hpp"

namespace EMO
{
    /** Dijital pini buton işlevselliğiyle sarmalar.
     *
     * Mantıksal bir buton sınıfına donanım katmanı (pin ayarlama, değerini okuma) ekler.
     */
    class Button : public Button_Logic
    {
    public:
        Button(uint8_t a_pin) : the_pin(a_pin) {}

        // Pin modunu ayarlamak için bir kez çağrılır.
        virtual void Setup() { pinMode(the_pin, INPUT_PULLUP); }

        // Mevcut zamanı ve pinin durumunu alarak iç durumu ayarlar.
        virtual void Update(uint32_t a_time)
        {
            // PULLUP olduğu için aktif (basılı) durum LOW okunduğunda olur
            Button_Logic::Update(a_time, digitalRead(the_pin) == LOW);
        }

    private:
        uint8_t the_pin; //!< Kullanılan dijital giriş pini.
    };
}

#endif