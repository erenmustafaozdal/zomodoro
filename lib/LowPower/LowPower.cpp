#include "LowPower.hpp"
#include "Const.hpp"
#include <Arduino.h>

namespace EMO
{
    LowPowerManager::LowPowerManager(
        unsigned long timeoutMiliseconds,
        PIRSensor *a_pirSensor) : timeoutMillis(timeoutMiliseconds),
                                  lastActivityTime(millis()),
                                  the_pirSensor(a_pirSensor)
    {
        // Hareket sensörünün ayarlarını tamamla
        the_pirSensor->Setup();

        // Buton pinlerine kesme atama
        attachPCINT(digitalPinToPCINT(EMO::Const::PIN_PIR_SENSOR), wakeUp, CHANGE);
        attachPCINT(digitalPinToPCINT(EMO::Const::PIN_B1), wakeUp, RISING);
        attachPCINT(digitalPinToPCINT(EMO::Const::PIN_B2), wakeUp, RISING);
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
