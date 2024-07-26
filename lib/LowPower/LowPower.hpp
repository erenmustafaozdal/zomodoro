#ifndef LOW_POWER_HPP
#define LOW_POWER_HPP

#include <LowPower.h>
#include <PinChangeInterrupt.h>
#include "PIRSensor.hpp"

namespace EMO
{
    class LowPowerManager
    {
    public:
        LowPowerManager(unsigned long timeoutMiliseconds, PIRSensor *a_pirSensor);

        void CheckLowPower();
        void ExitLowPower();

    private:
        unsigned long timeoutMillis;
        unsigned long lastActivityTime;
        PIRSensor *the_pirSensor;
    };

    // Kesme fonksiyonu bildirimi
    void wakeUp();
}

#endif
