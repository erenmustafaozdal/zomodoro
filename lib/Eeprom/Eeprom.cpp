#include "Eeprom.hpp"

namespace EMO
{
    Eeprom::Eeprom()
    {
    }

    void Eeprom::Setup()
    {
        EEPROM.begin(512); // ESP32 için EEPROM başlatma (512 bayt)
    }
}
