#ifndef __PERIOD_HPP__
#define __PERIOD_HPP__

#include <stdint.h>

namespace EMO
{
    /** Pomodoro tekniğinin her dönemi için veri depolar.
     * Bu veriler, dakika cinsinden zaman ve bitiş bildirimleri için bip sayısıdır.
     */
    class Period
    {
    public:
        Period(uint8_t a_time = 0, uint8_t a_beeps = 0) : the_time_in_minutes(a_time), the_beeps(a_beeps)
        {
        }

        /// Dakika cinsinden basit sayı döner.
        uint8_t Get_Time_In_Min() const { return the_time_in_minutes; }

        /// Dakika cinsinden zamanı ms cinsinden döner.
        uint32_t Get_Time_In_Ms() const
        {
            return (uint32_t)the_time_in_minutes * 60 * 1000;
        }

        /// Dönem için bip sayısını döner.
        uint8_t Get_Beeps() const { return the_beeps; }

    private:
        uint8_t the_time_in_minutes;
        uint8_t the_beeps; //!< Dönemin sonunda kaç bip verileceğini belirtir
    };
}

#endif
