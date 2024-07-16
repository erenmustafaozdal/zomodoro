#ifndef __BEEPER_HPP__
#define __BEEPER_HPP__

#include <Arduino.h>

namespace EMO
{
    /** Bir dijital çıkışı birkaç kez açıp kapatmayı yöneten sınıf.
     *
     * Örneğin bir TMB12A05 gibi bir buzzer veya bir LED ile açıp kapatma işlemleri için kullanılabilir.
     *
     * Update() her çağrıldığında, durumu açık ve kapalı arasında değiştirir.
     */

    class Beeper
    {
    public:
        Beeper(uint8_t a_pin, uint16_t a_max_beeps) : the_pin(a_pin), the_cycle(0), the_max_beeps(a_max_beeps)
        {
        }

        void Setup() { pinMode(the_pin, OUTPUT); }

        bool Done() const { return the_cycle >= (the_max_beeps << 1); }

        void Update()
        {
            if (!Done())
            {
                digitalWrite(the_pin, (the_cycle & 1) ? LOW : HIGH);
                the_cycle += 1;
            }
        }

        void Reset(uint16_t a_max_beeps = 0)
        {
            the_cycle = 0;
            if (a_max_beeps > 0)
            {
                the_max_beeps = a_max_beeps;
            }
            digitalWrite(the_pin, LOW);
        }

    private:
        uint8_t the_pin;        //!< Kullanılan dijital giriş.
        uint16_t the_cycle;     //!< Update() çağrılarının sayısını tutar.
        uint16_t the_max_beeps; //!< Maksimum 'beep' sayısını tutar.
    };
}

#endif
