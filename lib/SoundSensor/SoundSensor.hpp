#ifndef SOUND_SENSOR_HPP
#define SOUND_SENSOR_HPP

#include <Arduino.h>

namespace EMO
{
    class SoundSensor
    {
    public:
        SoundSensor(uint8_t pin, unsigned long sampleTime, uint16_t soundThreshold);
        void Setup();
        void Update(unsigned long currentTime);
        bool IsSoundDetected();

        void SetThreshold(uint16_t threshold) { soundThreshold = threshold; }
        uint16_t GetThreshold() const { return soundThreshold; }
        uint16_t GetLastSampleCount() const { return lastSampleCount; }

    private:
        uint8_t pin;
        unsigned long sampleTime;
        uint16_t soundThreshold;

        unsigned long lastWindowTime;
        uint16_t currentSampleCount;
        uint16_t lastSampleCount;
        bool soundDetected;
    };
}

#endif
