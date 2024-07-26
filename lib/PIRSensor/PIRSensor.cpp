#include "PIRSensor.hpp"

namespace EMO
{

    PIRSensor::PIRSensor(uint8_t pin) : pin(pin) {}

    void PIRSensor::Setup()
    {
        pinMode(pin, INPUT);
    }

    bool PIRSensor::IsMotionDetected()
    {
        return digitalRead(pin) == HIGH;
    }
}
