#ifndef __POMODORO_HPP__
#define __POMODORO_HPP__

#include <stdint.h>

#include "Button_Logic.hpp"
#include "Timer.hpp"
#include "Period.hpp"
#include "State_IF.hpp"
#include "UI_IF.hpp"
#include "Eeprom_IF.hpp"

namespace EMO
{
    /** Pomodoro mantığı.
     *
     * Sistemin farklı durumlarını yönetmek için bir durum makinesi kullanır.
     * Durumun çıktısı olarak, durumu nasıl sunacağını bilmesi gereken bir UI_IF nesnesi kullanır.
     * Bir durum nesnesi, UI_IF gibi soyut olan State_IF sınıfından türetilen bir sınıfın örneğidir.
     * Bu sınıf, State_IF'te tanımlanan arayüzü uygular.
     *
     * Girdi olarak 2 düğme kullanır.
     */

    class Pomodoro : public State_IF
    {
    public:
        Pomodoro(UI_IF *a_ui, Button_Logic *a_b1, Button_Logic *a_b2,
                 Eeprom_IF *a_eeprom);

        /// Bir kez çağrılır.
        void Setup();

        /// Ana döngüden her 100ms'de bir çağrılır.
        void Run(uint32_t a_time);

        // <Durum arayüzü>
        uint8_t Get_Pomodoros() const { return the_pomodoros; }
        uint8_t Get_Current_Period_Minutes() const
        {
            return the_pom[the_timer_type]->Get_Time_In_Min();
        }
        uint32_t Get_Time_Left_Ms() const
        {
            return the_timer.Get_Time_Left();
        }
        uint32_t Get_Time_Max_Ms() const { return the_timer.Get_Max(); }
        bool Is_Pomodoro() const { return the_timer_type == T_POM25; }
        // </Durum arayüzü>
    private:
        /// Geçerli dönemin kısayolu.
        const Period &p() { return *the_pom[the_timer_type]; }

        void run_ready();
        void run_running(uint32_t a_time);
        void run_finished();
        void run_pause();

        void reset_timer() { the_timer.Reset(p().Get_Time_In_Ms()); }
        void continue_timer() { the_timer.Reset(the_timer.Get_Time_Left()); }

        // Pomodoro dönemlerinin türü
        enum
        {
            T_POM25,
            T_POM5,
            T_POM15,

            T_SIZE
        };

        enum STATE
        {
            READY,
            RUNNING,
            FINISHED,
            PAUSED
        };

        uint8_t the_timer_type; //!< Geçerli zamanlayıcı türü (T_POM25, vb.)
        STATE the_state;
        Timer the_timer;
        uint8_t the_pomodoros; //!< Şu ana kadar yapılan pomodoro sayısı.

        UI_IF *the_ui;
        Button_Logic *the_b1;
        Button_Logic *the_b2;
        Eeprom_IF *the_eeprom;

        Period the_pom25;
        Period the_pom5;
        Period the_pom15;
        Period *the_pom[T_SIZE];
    };
}

#endif
