#include "UI.hpp"
#include "Utils.hpp"
#include "Const.hpp"

namespace EMO
{
    UI::UI() : the_timer(0), the_beeper(Const::PIN_BEEPER, 1)
    {
    }

    // -------------------------------------------------------------------------

    void UI::Show_Ready(const State_IF &a_state)
    {
        the_display.Write(0, "Z=%02u HAZIR   %c%02u",
                          a_state.Get_Current_Period_Minutes(),
                          char(CHAR_POM),
                          a_state.Get_Pomodoros());
        return;

        create_progress(a_state);
        the_display.Write(1, the_progress);
    }

    // -------------------------------------------------------------------------

    void UI::Show_Running(const State_IF &a_state)
    {
        uint8_t pom = a_state.Get_Pomodoros();
        the_display.Write(0, "Z=%02u %5s   %c%02u",
                          a_state.Get_Current_Period_Minutes(),
                          Utils::ms_to_m_s(a_state.Get_Time_Left_Ms()),
                          char(CHAR_POM),
                          pom);
        create_progress(a_state);

        if (a_state.Is_Pomodoro())
        {
            if (pom < Display::MAX_CHARS) // we have space
                the_progress[pom] = 126;  // this is the arrow char
        }
        the_display.Write(1, the_progress);
    }

    // -------------------------------------------------------------------------

    void UI::Show_Paused(const State_IF &a_state)
    {
        uint8_t pom = a_state.Get_Pomodoros();
        // alternate those 2 lines
        if (the_timer < 5)
        {
            the_display.Write(0, "Z=%02u %5s   %c%02u",
                              a_state.Get_Current_Period_Minutes(),
                              Utils::ms_to_m_s(a_state.Get_Time_Left_Ms()),
                              char(CHAR_POM),
                              pom);
        }
        else
        {
            the_display.Write(0, "Z=%02u %5s   %c%02u",
                              a_state.Get_Current_Period_Minutes(),
                              "",
                              char(CHAR_POM),
                              pom);
        }

        the_timer += 1;
        if (the_timer >= 10)
            the_timer = 0;

        create_progress(a_state);
        the_display.Write(1, the_progress);
    }

    // -------------------------------------------------------------------------

    void UI::Show_Finished(const State_IF &a_state)
    {
        // display pomodoro done while playing beeper
        if (a_state.Is_Pomodoro())
        {
            the_display.Write(0, "!   ZOMODORO   !");
            the_display.Write(1, "  Aferin sana!  ");
        }
        else
        {
            the_display.Write(0, "   Mola bitti   ");
            the_display.Write(1, "    Odaklan!    ");
        }

        the_beeper.Update();
    }

    // -------------------------------------------------------------------------

    void UI::Set_Beeper(uint8_t a_val)
    {
        the_beeper.Reset(a_val);
    }

    // -------------------------------------------------------------------------

    bool UI::Showing() const
    {
        // Bip sesi kesildiğinde işimiz biter.
        return the_beeper.Done() == false;
    }

    // -------------------------------------------------------------------------

    void UI::Setup()
    {
        uint8_t pomodoro[8] =
            {
                B00000,
                B01010,
                B11111,
                B11111,
                B11111,
                B01110,
                B00100,
                B00000};

        the_display.Setup_Char(CHAR_POM, pomodoro);

        the_display.Setup();
        the_beeper.Setup();
    }

    // -------------------------------------------------------------------------

    void UI::create_progress(const State_IF &a_state)
    {
        memset(the_progress, 0, Display::BUF_SIZE);
        uint8_t pos = 0;
        for (pos = 0; pos < a_state.Get_Pomodoros() &&
                      pos < Display::MAX_CHARS;
             ++pos)
        {
            the_progress[pos] = CHAR_POM;
        }
    }
}
