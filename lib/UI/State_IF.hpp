#ifndef __STATE_IF_HPP__
#define __STATE_IF_HPP__

namespace EMO
{
    /** Sistemin durumu - soyut sınıf.
     *
     * Durumu bir UI örneğine geçirmek için kullanılır.
     * UI'ın bir şeyler gösterebilmesi için yeterli bilgi içermelidir.
     */
    class State_IF
    {
    public:
        virtual ~State_IF() {}

        virtual uint8_t Get_Pomodoros() const = 0;
        virtual uint8_t Get_Current_Period_Minutes() const = 0;
        virtual uint32_t Get_Time_Left_Ms() const = 0;
        virtual uint32_t Get_Time_Max_Ms() const = 0;
        virtual bool Is_Pomodoro() const = 0;
    };
}

#endif
