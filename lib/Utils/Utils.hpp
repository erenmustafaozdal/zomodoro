#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <stdint.h>

namespace Utils
{
    // ms değerini "mm:ss" formatında bir string'e dönüştürür.
    const char *ms_to_m_s(uint32_t a_ms);

    // Seri konsola bir mesaj yazar - EMO_DEBUG ile etkinleştirilmelidir.
    void debug(const char *a_format, ...);
}

#endif
