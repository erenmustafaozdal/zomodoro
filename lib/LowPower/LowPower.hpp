#ifndef LOW_POWER_HPP
#define LOW_POWER_HPP

#include <LowPower.h>

namespace EMO
{
    class LowPowerManager
    {
    public:
        LowPowerManager(unsigned long timeoutMiliseconds);

        void CheckLowPower();
        void ExitLowPower();

    private:
        unsigned long timeoutMillis;
        unsigned long lastActivityTime;
    };

    // Kesme fonksiyonu bildirimi
    void wakeUp();
}

#endif
