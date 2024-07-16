#ifndef __EEPROM_HPP__
#define __EEPROM_HPP__

#include <EEPROM.h>
#include "Eeprom_IF.hpp"

namespace EMO
{
    /** Arduino versiyonu EEPROM arayüzü.
     *
     * EEPROM'dan okuma ve EEPROM'a yazma işlemlerini gerçekleştirir.
     */
    class Eeprom : public Eeprom_IF
    {
    public:
        /// Belirtilen EEPROM adresinden bir bayt okur.
        virtual uint8_t Read(int a_addr) const
        {
            return EEPROM.read(a_addr);
        }

        /// Belirtilen EEPROM adresine bir bayt yazar.
        virtual void Write(int a_addr, uint8_t a_value)
        {
            EEPROM.write(a_addr, a_value);
        }
    };
}

#endif
