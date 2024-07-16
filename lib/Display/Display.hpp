#ifndef __DISPLAY_HPP__
#define __DISPLAY_HPP__

#include <stdint.h>
#include <LiquidCrystal.h>

namespace EMO
{
    /** 16x2 LCD ekrana yazmak için sarmalayıcı sınıf.
     *
     * LCD ekrana bir şeyler yazmak için printf(...) gibi herhangi bir sayıda argümanla Write() çağırmayı sağlar.
     * Bir versiyonu x ve y başlangıç konumu alır. Diğeri sadece y (yani satır) alır.
     * Ayrıca belirli bir satıra yazılanları takip eder, böylece yeni içerik öncekiyle aynıysa tekrar yazmaz.
     * Bu, dizeleri karşılaştırırken "x" pozisyonunu dikkate alacak şekilde geliştirilmelidir.
     */
    class Display
    {
    public:
        enum
        {
            MAX_LINES = 2,
            MAX_CHARS = 16,
            BUF_SIZE = MAX_CHARS + 1
        };

        /// Nesneyi başlatır.
        Display();

        /// Bir kez çağrılır.
        void Setup();

        /// 8 boyutundaki nokta matrisiyle a_char karakterini ayarlamayı sağlar.
        void Setup_Char(uint8_t a_char, uint8_t *a_matrix);

        /// (a_x, a_y) konumunda bir dize yazar.
        void Write(uint8_t a_x, uint8_t a_y, const char *a_format, ...);

        /// (0, a_y) konumunda bir dize yazar.
        void Write(uint8_t a_y, const char *a_format, ...);

    private:
        void write(uint8_t a_x, uint8_t a_y, const char *a_format, va_list &a_vl);

        LiquidCrystal the_lcd;
        char the_buf[BUF_SIZE];                 //!< Geçici tampon.
        char the_old_line[MAX_LINES][BUF_SIZE]; //!< Eski dizeler.
    };
}

#endif
