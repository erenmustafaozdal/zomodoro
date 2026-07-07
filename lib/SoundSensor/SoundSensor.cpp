#include "SoundSensor.hpp"

namespace EMO
{

    // Kesme servis rutini (ISR) için global değişken ve fonksiyon
    volatile uint32_t g_sound_pulse_count = 0;
    void IRAM_ATTR soundSensorISR()
    {
        g_sound_pulse_count++;
    }

    SoundSensor::SoundSensor(uint8_t pin, unsigned long sampleTime, uint16_t soundThreshold)
        : pin(pin), sampleTime(sampleTime), soundThreshold(soundThreshold),
          lastWindowTime(0), currentSampleCount(0), lastSampleCount(0), soundDetected(false) {}

    void SoundSensor::Setup()
    {
        pinMode(pin, INPUT);
        // Düşen kenar (FALLING) kesmesini bağla
        attachInterrupt(digitalPinToInterrupt(pin), soundSensorISR, FALLING);
    }

    void SoundSensor::Update(unsigned long currentTime)
    {
        // Örnekleme süresi dolduğunda pencereyi değerlendir
        if (currentTime - lastWindowTime >= sampleTime)
        {
            // Kesme sayacını güvenli (kesmeleri kapatarak) oku ve sıfırla
            noInterrupts();
            uint32_t pulses = g_sound_pulse_count;
            g_sound_pulse_count = 0;
            interrupts();

            lastSampleCount = pulses;
            soundDetected = (pulses > soundThreshold);
            lastWindowTime = currentTime;
        }
    }

    bool SoundSensor::IsSoundDetected()
    {
        return soundDetected;
    }
}
