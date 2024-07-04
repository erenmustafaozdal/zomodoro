#ifndef __BUTTON_LOGIC_HPP__
#define __BUTTON_LOGIC_HPP__

#include <stdint.h>

namespace EMO
{
    /** Buton işlevselliği - mantıksal katman.
     *
     * Girişin etkinleştirilmesi ve devre dışı bırakılması etrafında mantık oluşturur.
     *
     * Güncel zamanla Update(time) ile çağrılmalıdır. Bu, basmaları, bırakmaları, durumu ve
     * mevcut ve önceki durumların sürelerini algılamada kullanışlıdır.
     * Belirli yöntemlerdeki yorumlara bakınız.
     *
     * Zaman ms veya başka bir birim olarak verilebilir. Bütün Duration hesaplaması
     * bu birimleri de kullanır.
     */
    class Button_Logic
    {
    public:
        Button_Logic() { Reset(); }
        virtual ~Button_Logic() {}

        // Bir kez çağrılır.
        virtual void Setup() {}

        // Mantık her zaman durumu false olarak ayarlar
        // - Button içinde geçersiz kılınmıştır.
        virtual void Update(uint32_t a_time) { Update(a_time, false); }

        // Mevcut zamanı ve verilen yeni durumu kullanarak iç durumu ayarlar.
        void Update(uint32_t a_time, bool a_pin_active);

        // Yükselen kenarda true döner - Update'in bir sonraki çağrısında temizlenir.
        bool Pressed() const { return the_pressed == 1; }

        // Düşen kenarda true döner - Update'in bir sonraki çağrısında temizlenir.
        bool Released() const { return the_released == 1; }

        // Pinin gerçek durumu.
        bool On() const { return the_state; }

        // Durumu başlangıç haline sıfırlar.
        void Reset()
        {
            the_state = 0;
            the_pressed = 0;
            the_released = 0;
            the_start_time = 0;
            the_duration = 0;
            the_last_duration = 0;
        }

        // Mevcut durumun süresi.
        uint32_t Duration() const { return the_duration; }

        // Önceki durumun süresi.
        uint32_t Last_Duration() const { return the_last_duration; }

    private:
        uint8_t the_state : 1;
        uint8_t the_pressed : 1;
        uint8_t the_released : 1;

        uint32_t the_start_time;
        uint32_t the_duration;      //!< Mevcut durumun süresi.
        uint32_t the_last_duration; //!< Önceki durumun süresi.
    };
}

#endif