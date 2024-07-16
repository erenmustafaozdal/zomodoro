#ifndef __COUNTER_HPP__
#define __COUNTER_HPP__

#include <stdint.h>

namespace EMO
{
    /** Geçen süreyi sayar.
     *
     * Update(time) çağrıldığında, bu sınıfın bir nesnesi süre değerini günceller,
     * böylece ne kadar süredir sayıldığını söyleyebilir.
     */
    class Counter
    {
    public:
        Counter() { Reset(); }
        virtual ~Counter() {} // Timer bu sınıftan türediği için sanal yapıcı

        void Update(uint32_t a_time)
        {
            if (the_start_time == 0) // ilk çalıştırma
            {
                the_start_time = a_time;
            }

            // başlarken 0 olacak (yukarıya bakın)
            the_duration = a_time - the_start_time;
        }

        void Reset()
        {
            the_start_time = 0;
            the_duration = 0;
        }

        uint32_t Duration() const { return the_duration; }

    private:
        uint32_t the_start_time;
        uint32_t the_duration;
    };
}

#endif
