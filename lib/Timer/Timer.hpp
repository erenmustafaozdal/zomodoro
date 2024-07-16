#ifndef __TIMER_HPP__
#define __TIMER_HPP__

#include "Counter.hpp"

namespace EMO
{
    /** Kapsanan Sayaç sınıfı.
     *
     * Bu sınıf, maksimum değer ve zamanlayıcının bitip bitmediğini ve ne kadar zaman kaldığını kontrol etmek için yöntemler ekleyerek Counter sınıfını genişletir.
     */
    class Timer : public Counter
    {
    public:
        Timer(uint32_t a_max) : the_max(a_max) {}

        /// Zamanlayıcı verilen maksimum sürede çalıştıysa doğru döner.
        bool Elapsed() const { return Duration() >= the_max; }

        /// Zamanlayıcıyı yeni maksimum değere sıfırlar.
        void Reset(uint32_t a_max)
        {
            Counter::Reset();
            the_max = a_max;
        }

        /// Maksimum değeri döner.
        uint32_t Get_Max() const { return the_max; }

        /// Kalan zamanı veya zamanlayıcı bittiyse 0 döner.
        uint32_t Get_Time_Left() const
        {
            if (Duration() < the_max)
                return the_max - Duration();
            else
                return 0;
        }

    private:
        uint32_t the_max;
    };
}

#endif
