#ifndef __POMODORO_HPP__
#define __POMODORO_HPP__

#include <stdint.h>

#include "Button_Logic.hpp"
#include "Timer.hpp"
#include "Period.hpp"
#include "State_IF.hpp"
#include "UI_IF.hpp"
#include "Eeprom_IF.hpp"
#include "SoundSensor.hpp"

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
        Pomodoro(
            UI_IF *a_ui,
            Button_Logic *a_b1,
            Button_Logic *a_b2,
            Eeprom_IF *a_eeprom,
            SoundSensor *a_soundSensor);

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
        bool Is_Pomodoro() const { return the_timer_type == T_POM20; }
        // </Durum arayüzü>
    private:
        /// Geçerli dönemin kısayolu.
        const Period &p() { return *the_pom[the_timer_type]; }

        void run_ready(uint32_t a_time);
        void run_running(uint32_t a_time);
        void run_finished();
        void run_pause();
        void run_calibrating(uint32_t a_time);

        void reset_timer() { the_timer.Reset(p().Get_Time_In_Ms()); }
        void continue_timer() { the_timer.Reset(the_timer.Get_Time_Left()); }

        // Pomodoro dönemlerinin türü
        enum
        {
            T_POM20,
            T_POM10,
            T_POM30,

            T_SIZE
        };

        enum STATE
        {
            READY,
            RUNNING,
            FINISHED,
            PAUSED,
            SOUND_DETECTED,
            CALIBRATING
        };

        void handle_sound_detection(uint32_t a_time);

        uint8_t the_timer_type; //!< Geçerli zamanlayıcı türü (T_POM20, vb.)
        STATE the_state;
        Timer the_timer;
        uint8_t the_pomodoros; //!< Şu ana kadar yapılan pomodoro sayısı.

        UI_IF *the_ui;
        Button_Logic *the_b1;
        Button_Logic *the_b2;
        Eeprom_IF *the_eeprom;
        SoundSensor *the_soundSensor;

        uint32_t the_pause_time;
        uint32_t the_duration;
        uint32_t the_sound_pause_time;
        uint32_t the_calib_start_time;
        uint16_t the_max_detected_noise;
        uint32_t the_last_button_activity_time;
        uint8_t the_sound_trigger_count;

        Period the_pom_work;
        Period the_pom_break_short;
        Period the_pom_break_long;
        Period *the_pom[T_SIZE];
    };
}

#endif
