#include "LDR.hpp"

namespace EMO
{
    LDR::LDR(uint8_t pin) : pin(pin)
    {
    }

    void LDR::Setup()
    {
        pinMode(pin, INPUT);
    }

    uint16_t LDR::Read() const
    {
        return analogRead(pin);
    }
}
