#ifndef __UI_HPP__
#define __UI_HPP__

#include "UI_IF.hpp"
#include "Display.hpp"
#include "Beeper.hpp"
#include "State_IF.hpp"

namespace EMO
{
    /// LCD ekran ve beeper kullanan kullanıcı arayüzü sınıfı.
    class UI : public UI_IF
    {
    public:
        UI();

        virtual void Show_Ready(const State_IF &);
        virtual void Show_Running(const State_IF &);
        virtual void Show_Paused(const State_IF &);
        virtual void Show_Finished(const State_IF &);

        virtual void Set_Beeper(uint8_t);
        virtual bool Showing() const;

        virtual void Setup();

    private:
        /// Alt satır (ilerleme) için dizeyi doldurur.
        void create_progress(const State_IF &);

        enum
        {
            CHAR_HEART1 = 1,  //!< 1. kalp karakteri.
            CHAR_HEART2 = 2,  //!< 2. kalp karakteri.
            CHAR_HEART3 = 3,  //!< 3. kalp karakteri.
            CHAR_HEART4 = 4,  //!< 4. kalp karakteri.
            CHAR_HEART5 = 5,  //!< 5. kalp karakteri.
            CHAR_POM = 6,     //!< Pomodoro karakteri.
            CHAR_SQUARE = 255 //!< Dolu kare karakteri.
        };

        uint8_t the_timer;

        Beeper the_beeper;
        Display the_display;
        char the_progress[Display::BUF_SIZE];
    };
}

#endif
