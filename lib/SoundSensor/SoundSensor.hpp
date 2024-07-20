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
        bool IsSoundDetected();

    private:
        uint8_t pin;
        unsigned long sampleTime;
        uint16_t soundThreshold;
    };
}

#endif
