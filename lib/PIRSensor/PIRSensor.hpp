#ifndef PIR_SENSOR_HPP
#define PIR_SENSOR_HPP

#include <Arduino.h>

namespace EMO
{
    class PIRSensor
    {
    public:
        PIRSensor(uint8_t pin);
        void Setup();
        bool IsMotionDetected();

    private:
        uint8_t pin;
    };
}

#endif
