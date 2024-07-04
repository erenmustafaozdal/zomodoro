#include "Button_Logic.hpp"
#include "Utils.hpp"

namespace EMO
{
    void Button_Logic::Update(uint32_t a_time, bool a_pin_active)
    {
        uint8_t state = a_pin_active; // pinin mevcut durumu

        if (the_start_time == 0) // ilk çalışma
        {
            the_start_time = a_time;
            the_state = state;
        }

        if (the_state == state) // en yaygın koşul önce
        {
            the_duration = a_time - the_start_time;
            the_pressed = 0;  // aynı olduğundan temizle
            the_released = 0; // aynı olduğundan temizle
        }
        else // durum değişti
        {
            // son süre olarak şimdi ile son ayarlanmış başlama zamanı
            // arasındaki farkı alırız (bir sonraki satırda değişmeden önce).
            the_last_duration = a_time - the_start_time;
            the_start_time = a_time;
            the_duration = 0;

            if (state) // yeni durum ON
            {
                the_pressed = 1;
                the_released = 0;
                Utils::debug("BASILDI");
            }
            else // yeni durum OFF
            {
                the_pressed = 0;
                the_released = 1;
                Utils::debug("BIRAKILDI");
            }
            the_state = state;
        }
    }
}
