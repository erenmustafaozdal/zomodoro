#ifndef __EEPROM_IF_HPP__
#define __EEPROM_IF_HPP__

#include <stdint.h>

namespace EMO
{
    /** EEPROM arayüzü.
     *
     * Bayt yazmak ve okumak için basit işlevler.
     */
    class Eeprom_IF
    {
    public:
        /// Sanal yıkıcı, bu sınıftan türetileceğiz.
        virtual ~Eeprom_IF() {}

        /// Belirtilen EEPROM adresinden bir bayt okur.
        virtual uint8_t Read(int a_addr) const = 0;

        /// Belirtilen EEPROM adresine bir bayt yazar.
        virtual void Write(int a_addr, uint8_t a_value) = 0;
    };
}

#endif
