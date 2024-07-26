#include "LowPower.hpp"
#include "Const.hpp"
#include <Arduino.h>

namespace EMO
{
    LowPowerManager::LowPowerManager(unsigned long timeoutMiliseconds)
        : timeoutMillis(timeoutMiliseconds),
          lastActivityTime(millis())
    {
        // Buton pinlerine kesme atama
        attachInterrupt(digitalPinToInterrupt(EMO::Const::PIN_B1), wakeUp, RISING);
        attachInterrupt(digitalPinToInterrupt(EMO::Const::PIN_B2), wakeUp, RISING);
    }

    void LowPowerManager::CheckLowPower()
    {
        // Serial.print("millis() - lastActivityTime: ");
        // Serial.println(millis() - lastActivityTime);
        if (millis() - lastActivityTime > timeoutMillis)
        {
            // LowPower moduna geçiş
            Serial.println("LowPower moduna geçiliyor...");
            LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
            lastActivityTime = millis();
        }
    }

    void LowPowerManager::ExitLowPower()
    {
        lastActivityTime = millis();
    }

    // Kesme fonksiyonu
    void wakeUp()
    {
        // Hiçbir şey yapma, sadece işlemciyi uyandır
    }
}
