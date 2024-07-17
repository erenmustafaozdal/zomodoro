#include "Pomodoro.hpp"
#include "Utils.hpp"
#include "Const.hpp"

namespace EMO
{
    Pomodoro::Pomodoro(UI_IF *a_ui, Button_Logic *a_b1, Button_Logic *a_b2,
                       Eeprom_IF *a_eeprom) : the_timer_type(T_POM20), the_state(READY),
                                              the_timer(0), the_pomodoros(0),

                                              the_ui(a_ui),
                                              the_b1(a_b1),
                                              the_b2(a_b2),
                                              the_eeprom(a_eeprom),

                                              the_pom25(Const::POM_WORK_MIN, Const::POM_WORK_BEEPS),
                                              the_pom5(Const::POM_BREAK_SHORT_MIN, Const::POM_BREAK_SHORT_BEEPS),
                                              the_pom15(Const::POM_BREAK_LONG_MIN, Const::POM_BREAK_LONG_BEEPS)
    {
        the_pom[T_POM20] = &the_pom25;
        the_pom[T_POM10] = &the_pom5;
        the_pom[T_POM30] = &the_pom15;

        // Pomodoroları EEPROM'dan oku
        the_pomodoros = the_eeprom->Read(Const::POM_SAVE_ADDRESS);

        reset_timer();
    }

    // -------------------------------------------------------------------------

    void Pomodoro::Setup()
    {
        the_ui->Setup();
    }

    // -------------------------------------------------------------------------

    void Pomodoro::Run(uint32_t a_time)
    {
        if (the_state == READY)
            run_ready();
        else if (the_state == RUNNING)
            run_running(a_time);
        else if (the_state == FINISHED)
            run_finished();
        else if (the_state == PAUSED)
            run_pause();
    }

    // -------------------------------------------------------------------------

    void Pomodoro::run_ready()
    {
        the_ui->Show_Ready(*this);

        // B1 basıldıysa, zamanlayıcıdaki süreler arasında döngü yap
        if (the_b1->Released())
        {
            the_timer_type = (the_timer_type + 1) % T_SIZE;
            reset_timer();
            Utils::debug("sonraki zamanlayıcı indeksi = %u", the_timer_type);
        }

        if (the_b2->On())
        {
            // B2'ye 3 saniyeden uzun süre basıldıysa pomodoroları sıfırla
            if (the_b2->Duration() > 3000)
            {
                the_pomodoros = 0;

                // Pomodoroları EEPROM'a kaydet
                the_eeprom->Write(Const::POM_SAVE_ADDRESS, the_pomodoros);

                the_timer_type = T_POM20;
                reset_timer();
                Utils::debug("pomodorolar sıfırlandı");
            }
        }
        // b2 kapalı
        else if (the_b2->Released())
        {
            if (the_b2->Last_Duration() < 250)
            {
                the_ui->Set_Beeper(p().Get_Beeps());
                reset_timer();
                Utils::debug("çalışma durumuna geçiliyor");

                the_state = RUNNING;
            }
        }
    }

    // -------------------------------------------------------------------------

    void Pomodoro::run_running(uint32_t a_time)
    {
        // sayaç güncelleniyor
        the_timer.Update(a_time);

        the_ui->Show_Running(*this);

        if (the_timer.Elapsed())
        {
            the_state = FINISHED;
        }
        else if (the_b2->Released())
        {
            the_state = PAUSED;
        }
    }

    // -------------------------------------------------------------------------

    void Pomodoro::run_finished()
    {
        the_ui->Show_Finished(*this);

        // bip sesi bitene kadar çal
        if (the_ui->Showing() == false)
        {
            if (the_timer_type == T_POM20)
            {
                the_pomodoros += 1;
                // Pomodoroları EEPROM'a kaydet
                the_eeprom->Write(Const::POM_SAVE_ADDRESS, the_pomodoros);

                the_timer_type = T_POM10;
                if (the_pomodoros % 4 == 0)
                {
                    the_timer_type = T_POM30;
                }
            }
            else
            {
                the_timer_type = T_POM20;
            }
            reset_timer();
            the_state = READY;
        }
    }

    // -------------------------------------------------------------------------

    void Pomodoro::run_pause()
    {
        the_ui->Show_Paused(*this);

        // B2'ye basıldıysa çalışma durumuna geç
        if (the_b2->On())
        {
            // B2'ye 3 saniyeden uzun süre basıldıysa pomodoro iptal edilir
            if (the_b2->Duration() > 3000)
            {
                reset_timer();
                the_state = READY;
                the_b2->Reset();
            }
        }
        // b2 kapalı
        else if (the_b2->Released())
        {
            if (the_b2->Last_Duration() < 250)
            {
                continue_timer();
                the_state = RUNNING;
            }
        }
    }
}
