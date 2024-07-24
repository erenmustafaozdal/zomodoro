#include "SoundSensor.hpp"

namespace EMO
{

    SoundSensor::SoundSensor(uint8_t pin, unsigned long sampleTime, uint16_t soundThreshold)
        : pin(pin), sampleTime(sampleTime), soundThreshold(soundThreshold) {}

    void SoundSensor::Setup()
    {
        pinMode(pin, INPUT);
    }

    bool SoundSensor::IsSoundDetected()
    {
        unsigned long startTime = millis();
        uint16_t sampleBufferValue = 0;

        while (millis() - startTime < sampleTime)
        {
            if (digitalRead(pin) == LOW)
            {
                sampleBufferValue++;
            }
        }

        Serial.print("sampleBufferValue: ");
        Serial.println(sampleBufferValue);
        return sampleBufferValue > soundThreshold;
    }
}
