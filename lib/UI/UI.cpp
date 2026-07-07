#include "UI.hpp"
#include "Utils.hpp"
#include "Const.hpp"
#include "Icons.hpp"
#include <Fonts/FreeSans12pt7b.h>

namespace EMO
{
    UI::UI(uint8_t ldrPin) : the_timer(0), the_beeper(Const::PIN_BEEPER, 1), lightSensor(ldrPin), lastBrightnessUpdate(0), brightnessUpdateInterval(1000)
    {
    }

    // -------------------------------------------------------------------------

    void UI::Show_Ready(const State_IF &a_state)
    {
        Adafruit_SSD1306 &lcd = the_display.GetLcd();
        lcd.invertDisplay(false); // Her zaman siyah arka plan
        lcd.clearDisplay();

        // Ortak Başlık ve Domates Sayacı
        drawHeader(a_state);

        // Aktif Mod
        lcd.setCursor(4, 18);
        if (a_state.Is_Pomodoro()) {
            lcd.print("Calisma (20 dk)");
        } else if (a_state.Get_Current_Period_Minutes() == 10) {
            lcd.print("Kisa Mola (10 dk)");
        } else {
            lcd.print("Uzun Mola (30 dk)");
        }

        // Tamamlanan Pomodoro Kalpleri
        lcd.setCursor(4, 34);
        lcd.print("Kalpler:");
        
        uint8_t pomodoros = a_state.Get_Pomodoros();
        // 1 tamamlanan pomodoro = 1 dolu küçük kalp (Zeynep için ödüllendirme odaklı)
        uint8_t hearts_to_show = pomodoros;
        if (hearts_to_show > 5) {
            hearts_to_show = 5;
        }
        
        for (uint8_t i = 0; i < hearts_to_show; ++i) {
            int16_t hx = 56 + (i * 14);
            drawSmallHeart(hx, 33, 5); // Hepsi tam dolu kalp
        }

        lcd.setCursor(4, 52);
        lcd.print("B2'ye basarak baslat");

        lcd.display();
    }

    // -------------------------------------------------------------------------

    void UI::Show_Running(const State_IF &a_state)
    {
        Adafruit_SSD1306 &lcd = the_display.GetLcd();
        lcd.invertDisplay(false); // Her zaman siyah arka plan
        lcd.clearDisplay();

        // Ortak Başlık ve Domates Sayacı
        drawHeader(a_state);

        // 1. Sıvı Dolum Kalp Animasyonu (Sol Taraf)
        uint32_t left = a_state.Get_Time_Left_Ms();
        uint32_t total = a_state.Get_Current_Period_Minutes() * 60 * 1000;
        uint8_t fill_pct = 0;
        if (total > 0 && left <= total)
        {
            fill_pct = 100 - (left * 100 / total);
        }
        drawClippedHeart(6, 18, fill_pct); // Çizgi y=14 olduğu için 18'e kaydırdık

        // 2. Büyük Zamanlayıcı (Sağ Taraf)
        lcd.setFont(&FreeSans12pt7b);
        lcd.setTextSize(1);
        lcd.setTextColor(SSD1306_WHITE);
        // FreeSans baseline kullandığı için y koordinatını biraz daha aşağı (38) çekiyoruz
        lcd.setCursor(48, 38);
        lcd.print(Utils::ms_to_m_s(left));

        // 3. Alt Kısımda Pomodoro Kalplerinin Gösterilmesi
        lcd.setFont(); // Standart fonta geri dön
        lcd.setCursor(4, 52);
        lcd.print("Kalpler:");

        uint8_t pomodoros = a_state.Get_Pomodoros();
        // 1 tamamlanan pomodoro = 1 dolu küçük kalp (Zeynep için ödüllendirme odaklı)
        uint8_t hearts_to_show = pomodoros;
        if (hearts_to_show > 5) {
            hearts_to_show = 5;
        }
        for (uint8_t i = 0; i < hearts_to_show; ++i) {
            int16_t hx = 56 + (i * 14);
            drawSmallHeart(hx, 51, 5); // Hepsi tam dolu kalp
        }

        lcd.display();
    }

    // -------------------------------------------------------------------------

    void UI::Show_Paused(const State_IF &a_state, bool is_sound_detected)
    {
        Adafruit_SSD1306 &lcd = the_display.GetLcd();
        lcd.clearDisplay();

        the_timer += 1;
        if (the_timer >= 10)
            the_timer = 0;

        if (is_sound_detected)
        {
            // Ses uyarısı flaş efekti ve Shush ikonu
            lcd.invertDisplay(the_timer % 2 == 0);

            drawShush(48, 4);
            drawPause(8, 24);
            drawPause(104, 24);

            lcd.setFont();
            lcd.setTextSize(1);
            lcd.setTextColor(SSD1306_WHITE);
            lcd.setCursor(24, 48);
            lcd.print("SESSIZ OLUN!");
        }
        else
        {
            // Normal duraklatma (Ortak başlık sabit kalır, zamanlayıcı blink yapar)
            lcd.invertDisplay(false);
            drawHeader(a_state);

            // Sol taraftaki kalp sabit kalır
            uint32_t left = a_state.Get_Time_Left_Ms();
            uint32_t total = a_state.Get_Current_Period_Minutes() * 60 * 1000;
            uint8_t fill_pct = 0;
            if (total > 0 && left <= total)
            {
                fill_pct = 100 - (left * 100 / total);
            }
            drawClippedHeart(6, 18, fill_pct);

            // Zamanlayıcıyı yanıp söndür
            if (the_timer < 5)
            {
                lcd.setFont(&FreeSans12pt7b);
                lcd.setTextSize(1);
                lcd.setTextColor(SSD1306_WHITE);
                lcd.setCursor(48, 38);
                lcd.print(Utils::ms_to_m_s(left));
            }

            // Alt Kısımda Pomodoro Kalplerinin Gösterilmesi
            lcd.setFont(); // Standart fonta geri dön
            lcd.setCursor(4, 52);
            lcd.print("Kalpler:");

            uint8_t pomodoros = a_state.Get_Pomodoros();
            uint8_t hearts_to_show = pomodoros;
            if (hearts_to_show > 5) {
                hearts_to_show = 5;
            }
            for (uint8_t i = 0; i < hearts_to_show; ++i) {
                int16_t hx = 56 + (i * 14);
                drawSmallHeart(hx, 51, 5); // Hepsi tam dolu kalp
            }
        }

        lcd.display();
        the_beeper.Update();
    }

    // -------------------------------------------------------------------------

    void UI::Show_Finished(const State_IF &a_state)
    {
        Adafruit_SSD1306 &lcd = the_display.GetLcd();
        lcd.clearDisplay();

        the_timer += 1;
        lcd.invertDisplay(the_timer % 2 == 0); // Bip sesi ile senkronize flaş

        // Nabız atan (büyüyüp küçülen) kalp animasyonu
        uint8_t pulse_scale = the_timer % 3; // 0, 1, 2 ölçekleri
        
        lcd.setFont();
        lcd.setTextSize(1);
        lcd.setTextColor(SSD1306_WHITE);

        if (a_state.Is_Pomodoro())
        {
            lcd.setCursor(32, 4);
            lcd.print("POMODORO BITTi!");
            
            // Kalbi çiz
            if (pulse_scale == 0) {
                // Normal kalp
                lcd.drawBitmap(48, 20, Icons::heart_filled, 32, 32, SSD1306_WHITE);
            } else if (pulse_scale == 1) {
                // Biraz daha büyük çizim simülasyonu (çerçeve ile)
                lcd.drawBitmap(48, 20, Icons::heart_filled, 32, 32, SSD1306_WHITE);
                lcd.drawRoundRect(46, 18, 36, 36, 4, SSD1306_WHITE);
            } else {
                // Küçük kalp çizimi (merkezde kalacak şekilde outline)
                lcd.drawBitmap(48, 20, Icons::heart_outline, 32, 32, SSD1306_WHITE);
            }

            lcd.setCursor(24, 54);
            lcd.print("Aferin sana Zeynep!");
        }
        else
        {
            lcd.setCursor(32, 4);
            lcd.print("Mola Bitti!");

            // Domates ikonu göster
            lcd.drawBitmap(56, 20, Icons::tomato, 16, 16, SSD1306_WHITE);

            lcd.setCursor(36, 44);
            lcd.print("Odaklanma zamani");
        }

        lcd.display();
        the_beeper.Update();
    }

    // -------------------------------------------------------------------------

    void UI::Show_Calibrating(const State_IF &a_state, uint32_t elapsed_ms)
    {
        Adafruit_SSD1306 &lcd = the_display.GetLcd();
        lcd.invertDisplay(false); // Her zaman siyah arka plan
        lcd.clearDisplay();
        lcd.setFont();
        lcd.setTextSize(1);
        lcd.setTextColor(SSD1306_WHITE);

        // Başlık
        lcd.setCursor(16, 4);
        lcd.print("SES KALiBRASYONU");

        lcd.drawFastHLine(0, 14, 128, SSD1306_WHITE);

        lcd.setCursor(4, 24);
        lcd.print("Ortam dinleniyor...");

        // İlerleme çubuğu (3 saniyelik kalibrasyon süresine göre dolacak)
        int16_t bar_width = (elapsed_ms * 120) / 3000;
        if (bar_width > 120) bar_width = 120;
        
        lcd.drawRect(4, 40, 120, 10, SSD1306_WHITE);
        lcd.fillRect(6, 42, (bar_width > 4) ? (bar_width - 4) : 0, 6, SSD1306_WHITE);

        lcd.setCursor(4, 54);
        lcd.print("Lutfen sessiz olun");

        lcd.display();
    }

    // -------------------------------------------------------------------------

    void UI::Set_Beeper(uint8_t a_val)
    {
        the_beeper.Reset(a_val);
    }

    // -------------------------------------------------------------------------

    bool UI::Showing() const
    {
        return the_beeper.Done() == false;
    }

    // -------------------------------------------------------------------------

    void UI::Setup()
    {
        delay(100);
        the_display.Setup();
        the_beeper.Setup();
    }

    // -------------------------------------------------------------------------

    void UI::drawSmallHeart(int16_t x, int16_t y, uint8_t fill_level)
    {
        Adafruit_SSD1306 &lcd = the_display.GetLcd();
        
        // 11x9 Kalp Tanımı (Outline ve Filled maskeler)
        static const uint16_t outline[9] = {
            0b00110001100, // Row 0
            0b01001010010, // Row 1
            0b10000100001, // Row 2
            0b10000000001, // Row 3
            0b01000000010, // Row 4
            0b00100000100, // Row 5
            0b00010001000, // Row 6
            0b00001010000, // Row 7
            0b00000100000  // Row 8
        };

        static const uint16_t filled[9] = {
            0b00110001100,
            0b01111011110,
            0b11111111111,
            0b11111111111,
            0b01111111110,
            0b00111111100,
            0b00011111000,
            0b00001110000,
            0b00000100000
        };

        // Doluluk seviyesine göre sütun sınırını belirle (0-5 seviyesi)
        int16_t max_col = -1;
        if (fill_level == 5) {
            max_col = 11;
        } else if (fill_level > 0) {
            max_col = (fill_level * 11) / 5;
        }

        for (int16_t row = 0; row < 9; ++row) {
            for (int16_t col = 0; col < 11; ++col) {
                bool is_outline = (outline[row] & (1 << (10 - col))) != 0;
                bool is_filled = (filled[row] & (1 << (10 - col))) != 0;

                if (fill_level == 5) {
                    if (is_filled) {
                        lcd.drawPixel(x + col, y + row, SSD1306_WHITE);
                    }
                } else {
                    // Dış çerçeveyi her zaman çiz
                    if (is_outline) {
                        lcd.drawPixel(x + col, y + row, SSD1306_WHITE);
                    }
                    // İçini doluluk oranına göre doldur
                    if (fill_level > 0 && col <= max_col && is_filled) {
                        lcd.drawPixel(x + col, y + row, SSD1306_WHITE);
                    }
                }
            }
        }
    }

    bool UI::is_heart_filled_pixel(int16_t col, int16_t row)
    {
        if (col < 0 || col >= 32 || row < 0 || row >= 32)
            return false;
        int16_t byte_idx = row * 4 + col / 8;
        int16_t bit_idx = 7 - (col % 8);
        return (pgm_read_byte(&Icons::heart_filled[byte_idx]) & (1 << bit_idx)) != 0;
    }

    void UI::drawClippedHeart(int16_t x, int16_t y, uint8_t fill_pct)
    {
        Adafruit_SSD1306 &lcd = the_display.GetLcd();
        
        // 1. Dış Çerçeveyi (Outline) Çiz (CPU yükünü azaltmak için statik bitmap kullanıyoruz)
        lcd.drawBitmap(x, y, Icons::heart_outline, 32, 32, SSD1306_WHITE);

        // 2. Doluluk oranına göre (0-100) aşağıdan yukarıya doğru doldur
        if (fill_pct > 100)
            fill_pct = 100;

        int16_t fill_height = (32 * fill_pct) / 100;
        int16_t start_row = 32 - fill_height;

        for (int16_t row = start_row; row < 32; ++row)
        {
            for (int16_t col = 0; col < 32; ++col)
            {
                if (is_heart_filled_pixel(col, row))
                {
                    lcd.drawPixel(x + col, y + row, SSD1306_WHITE);
                }
            }
        }

        // 3. Kum Saati / Damlama Animasyonu
        // Kalbin üst ortasından (col=15, row=4) sıvı seviyesine (start_row) saniyede bir düşen damla
        if (fill_pct < 100 && start_row > 4)
        {
            uint32_t period = 1000;
            uint32_t phase = millis() % period;
            int16_t drop_y = 4 + (phase * (start_row - 4)) / period;
            
            if (drop_y < start_row)
            {
                lcd.drawPixel(x + 15, y + drop_y, SSD1306_WHITE);
                // Bir piksel arkasından iz bırakması için hafif kuyruk ekleyelim
                if (drop_y > 4) {
                    lcd.drawPixel(x + 15, y + drop_y - 1, SSD1306_WHITE);
                }
            }
        }
    }

    void UI::drawTomato(int16_t x, int16_t y)
    {
        the_display.GetLcd().drawBitmap(x, y, Icons::tomato, 12, 12, SSD1306_WHITE);
    }

    void UI::drawPause(int16_t x, int16_t y)
    {
        the_display.GetLcd().drawBitmap(x, y, Icons::pause, 16, 16, SSD1306_WHITE);
    }

    void UI::drawShush(int16_t x, int16_t y)
    {
        the_display.GetLcd().drawBitmap(x, y, Icons::shush, 32, 32, SSD1306_WHITE);
    }

    void UI::Set_Brightness(uint8_t brightness)
    {
        // OLED kontrastını günceller.
        the_display.GetLcd().dim(brightness < 128);
    }

    void UI::UpdateBrightness(unsigned long currentTime)
    {
        if (currentTime - lastBrightnessUpdate >= brightnessUpdateInterval)
        {
            uint16_t ldr_value = lightSensor.Read();
            Set_Brightness(ldr_value < 300 ? 50 : 255);
            lastBrightnessUpdate = currentTime;
        }
    }

    void UI::drawHeader(const State_IF &a_state)
    {
        Adafruit_SSD1306 &lcd = the_display.GetLcd();
        lcd.setFont(); // Standart font
        lcd.setTextSize(1);
        lcd.setTextColor(SSD1306_WHITE);

        // Sol taraf: ZOMODORO Başlığı
        lcd.setCursor(4, 4);
        lcd.print("ZOMODORO");

        // Orta kısım: Pil göstergesi
        drawBattery(76, 4);

        // Sağ taraf: Domates İkonu + Pomodoro Sayısı
        drawTomato(96, 1);
        lcd.setCursor(110, 4);
        lcd.print("x");
        lcd.print(a_state.Get_Pomodoros());

        // Yatay Ayırıcı Çizgi
        lcd.drawFastHLine(0, 14, 128, SSD1306_WHITE);
    }

    void UI::drawBattery(int16_t x, int16_t y)
    {
        Adafruit_SSD1306 &lcd = the_display.GetLcd();
        
        // Pil voltajını oku (A8 batarya voltaj bölücüsüne bağlı)
        uint16_t val = analogRead(A8);
        
        // Pil dış gövdesi (12x7 piksel)
        lcd.drawRect(x, y, 12, 7, SSD1306_WHITE);
        // Pil başı (+ kutbu)
        lcd.drawFastVLine(x + 12, y + 2, 3, SSD1306_WHITE);
        
        // Voltaj seviyesine göre barları doldur (10-bit üzerinden: dolu ~650, kritik ~500)
        if (val >= 600) {
            // Dolu (3 bar)
            lcd.fillRect(x + 2, y + 2, 2, 3, SSD1306_WHITE);
            lcd.fillRect(x + 5, y + 2, 2, 3, SSD1306_WHITE);
            lcd.fillRect(x + 8, y + 2, 2, 3, SSD1306_WHITE);
        } else if (val >= 550) {
            // Orta (2 bar)
            lcd.fillRect(x + 2, y + 2, 2, 3, SSD1306_WHITE);
            lcd.fillRect(x + 5, y + 2, 2, 3, SSD1306_WHITE);
        } else if (val >= 510) {
            // Düşük (1 bar)
            lcd.fillRect(x + 2, y + 2, 2, 3, SSD1306_WHITE);
        }
        // val < 510 ise boş kalacaktır
    }
}
