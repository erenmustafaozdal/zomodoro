#include "UI.hpp"
#include "Utils.hpp"
#include "Const.hpp"

namespace EMO
{
    UI::UI(uint8_t ldrPin) : the_timer(0), the_beeper(Const::PIN_BEEPER, 1), lightSensor(ldrPin), lastBrightnessUpdate(0), brightnessUpdateInterval(1000)
    {
    }

    // -------------------------------------------------------------------------

    void UI::Show_Ready(const State_IF &a_state)
    {
        the_display.Write(0, "%c=%02u  HAZIR  %c%02u",
                          char(CHAR_ZOMODORO),
                          a_state.Get_Current_Period_Minutes(),
                          char(CHAR_POM),
                          a_state.Get_Pomodoros());

        create_progress(a_state);
        the_display.Write(1, the_progress);
    }

    // -------------------------------------------------------------------------

    void UI::Show_Running(const State_IF &a_state)
    {
        uint8_t pom = a_state.Get_Pomodoros();
        the_display.Write(0, "%c=%02u  %5s  %c%02u",
                          char(CHAR_ZOMODORO),
                          a_state.Get_Current_Period_Minutes(),
                          Utils::ms_to_m_s(a_state.Get_Time_Left_Ms()),
                          char(CHAR_POM),
                          pom);
        create_progress(a_state);

        if (a_state.Is_Pomodoro())
        {
            // yerleşen kalplerden sonra oku ekle
            uint8_t hearts = (pom + 4) / 5;
            if (hearts < Display::MAX_CHARS) // eğer boşluk varsa
                the_progress[hearts] = 126;  // sağa ok işaretini ekle
        }
        the_display.Write(1, the_progress);
    }

    // -------------------------------------------------------------------------

    void UI::Show_Paused(const State_IF &a_state, bool is_sound_detected)
    {
        uint8_t pom = a_state.Get_Pomodoros();
        // alternate those 2 lines
        if (the_timer < 5)
        {
            the_display.Write(0, "%c=%02u  %5s  %c%02u",
                              char(CHAR_ZOMODORO),
                              a_state.Get_Current_Period_Minutes(),
                              Utils::ms_to_m_s(a_state.Get_Time_Left_Ms()),
                              char(CHAR_POM),
                              pom);
        }
        else
        {
            the_display.Write(0, "%c=%02u  %5s  %c%02u",
                              char(CHAR_ZOMODORO),
                              a_state.Get_Current_Period_Minutes(),
                              "",
                              char(CHAR_POM),
                              pom);
        }

        the_timer += 1;
        if (the_timer >= 10)
            the_timer = 0;

        if (is_sound_detected)
        {
            the_display.Write(1, "  Sessiz olun!  ");
        }
        else
        {
            create_progress(a_state);
            the_display.Write(1, the_progress);
        }
    }

    // -------------------------------------------------------------------------

    void UI::Show_Finished(const State_IF &a_state)
    {
        // display pomodoro done while playing beeper
        if (a_state.Is_Pomodoro())
        {
            the_display.Write(0, "    %cOMODORO    ", char(CHAR_ZOMODORO));
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
        // LCD ekranı başlatmadan önce bir gecikme
        delay(100); // 100 ms gecikme

        // LCD ekranın başlatılması ve karakterlerin yüklenmesi
        uint8_t zomodoro[8] = {B01111, B10001, B00010, B00100, B01000, B10001, B11110, B00000};
        uint8_t heart1[8] = {B00000, B00000, B10000, B10000, B10000, B00000, B00000, B00000};
        uint8_t heart2[8] = {B00000, B01000, B11000, B11000, B11000, B01000, B00000, B00000};
        uint8_t heart3[8] = {B00000, B01000, B11100, B11100, B11100, B01100, B00100, B00000};
        uint8_t heart4[8] = {B00000, B01010, B11110, B11110, B11110, B01110, B00100, B00000};
        uint8_t heart5[8] = {B00000, B01010, B11111, B11111, B11111, B01110, B00100, B00000};
        uint8_t pomodoro[8] = {B00001, B01010, B00100, B01110, B11111, B11111, B11111, B01110};

        the_display.Setup_Char(CHAR_ZOMODORO, zomodoro);
        delay(50); // 50 ms gecikme
        the_display.Setup_Char(CHAR_HEART1, heart1);
        delay(50); // 50 ms gecikme
        the_display.Setup_Char(CHAR_HEART2, heart2);
        delay(50); // 50 ms gecikme
        the_display.Setup_Char(CHAR_HEART3, heart3);
        delay(50); // 50 ms gecikme
        the_display.Setup_Char(CHAR_HEART4, heart4);
        delay(50); // 50 ms gecikme
        the_display.Setup_Char(CHAR_HEART5, heart5);
        delay(50); // 50 ms gecikme
        the_display.Setup_Char(CHAR_POM, pomodoro);
        delay(50); // 50 ms gecikme

        the_display.Setup();
        the_beeper.Setup();
    }

    // -------------------------------------------------------------------------

    void UI::create_progress(const State_IF &a_state)
    {
        memset(the_progress, 0, Display::BUF_SIZE);

        uint8_t pomodoro_count = a_state.Get_Pomodoros();
        uint8_t full_hearts = pomodoro_count / 5; // Tam dolu kalp sayısı
        uint8_t remaining = pomodoro_count % 5;   // Kalan pomodoro sayısı
        uint8_t pos = 0;

        // Tam dolu kalpleri ekle
        for (pos = 0; pos < full_hearts && pos < Display::MAX_CHARS; ++pos)
        {
            the_progress[pos] = CHAR_HEART5; // Tam dolu kalp karakteri
        }

        // Kalan pomodoro varsa, uygun yarım dolu kalbi ekle
        if (remaining > 0 && pos < Display::MAX_CHARS)
        {
            switch (remaining)
            {
            case 1:
                the_progress[pos++] = CHAR_HEART1;
                break;
            case 2:
                the_progress[pos++] = CHAR_HEART2;
                break;
            case 3:
                the_progress[pos++] = CHAR_HEART3;
                break;
            case 4:
                the_progress[pos++] = CHAR_HEART4;
                break;
            }
        }

        // Kalan karakterleri boşluklarla doldur
        for (; pos < Display::MAX_CHARS; ++pos)
        {
            the_progress[pos] = ' ';
        }
    }

    void UI::Set_Brightness(uint8_t brightness)
    {
        analogWrite(EMO::Const::PIN_LCD_BRIGHTNESS, brightness);
    }

    void UI::UpdateBrightness(unsigned long currentTime)
    {
        if (currentTime - lastBrightnessUpdate >= brightnessUpdateInterval)
        {
            uint16_t ldr_value = lightSensor.Read();
            uint8_t brightness = map(ldr_value, 300, 800, Const::LCD_MIN_BRIGHTNESS, Const::LCD_MAX_BRIGHTNESS);
            brightness = constrain(brightness, Const::LCD_MIN_BRIGHTNESS, Const::LCD_MAX_BRIGHTNESS);
            Set_Brightness(brightness);
            lastBrightnessUpdate = currentTime;
        }
    }
}
