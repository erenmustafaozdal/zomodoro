#ifndef __LDR_HPP__
#define __LDR_HPP__

#include <Arduino.h>

namespace EMO
{
    class LDR
    {
    public:
        LDR(uint8_t pin);
        void Setup();
        uint16_t Read() const;

    private:
        uint8_t pin;
    };
}

#endif
