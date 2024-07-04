#include "Utils.hpp"
#include <stdio.h>
#include <stdarg.h>
#ifdef EEMO_DEBUG
// sadece Serial üzerinden yazdırmak istediğimizde gereklidir, bu nedenle gtests için gerekli değildir
#include <Arduino.h>
#endif

namespace Utils
{
    const char *ms_to_m_s(uint32_t a_ms)
    {
        static const uint8_t B_SIZE = 64;
        static char buf[B_SIZE];

        uint32_t s = a_ms / 1000;
        uint32_t m = s / 60;
        s -= m * 60;

        snprintf(buf, B_SIZE, "%02lu:%02lu", m, s);
        return buf;
    }

    // -------------------------------------------------------------------------

    void debug(const char *a_format, ...)
    {
#ifdef EMO_DEBUG
        const unsigned int B_SIZE = 256;
        char buf[B_SIZE];

        va_list vl;

        va_start(vl, a_format);
        int written = vsnprintf(buf, B_SIZE, a_format, vl);
        va_end(vl);

        if (written > 0)
        {
            Serial.println(buf);
        }
#else
        (a_format); // EMO_DEBUG olmadan derlendiğinde kullanılmayan
                    // değişkenle ilgili uyarıyı önlemek için
#endif
    }
}
