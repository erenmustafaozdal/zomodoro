# Teknoloji Yığını

## Donanım — ESKİ (Nano dönemi, artık terk ediliyor)

- Arduino Nano (ATmega328P, 5V lojik)
- 16x2 karakter LCD (HD44780, paralel bağlantı — RS, EN, D4-D7)
- 10K potansiyometre (LCD kontrast ayarı)
- PIR hareket sensörü — **kaldırıldı** (bkz. `05-decisions-log.md`)
- LDR (ışık sensörü, LCD parlaklık ayarı için)
- Ses sensörü (analog eşik karşılaştırmalı modül)
- 2 buton, buzzer

## Donanım — YENİ (aktif geçiş hedefi)

- **Deneyap Kart 1A v2** — ESP32-S3, 240MHz, 4MB flash, 3.3V lojik,
  Wi-Fi/BLE, kamera (DVP) girişi mevcut (ileride kullanılabilir, bkz.
  `06-todo.md` madde 14).
- **Deneyap OLED** — SSD1306 sürücü, 128x64 piksel, I2C arayüz (sadece
  SDA/SCL + güç, 2 veri hattı). 3.3V-5V aralığında çalışır, ESP32-S3'ün
  3.3V lojik seviyesiyle doğrudan uyumlu, level shifter gerekmiyor.
- LDR, ses sensörü, butonlar, buzzer aynı kalıyor (ESP32 GPIO'larına pin
  numaraları güncellenerek bağlanacak, `Const.hpp` üzerinden).

## Yazılım / Derleme ortamı

- **PlatformIO** (Arduino IDE değil — proje baştan beri PlatformIO ile
  kurulu, `platformio.ini` mevcut).
- Deneyap Kart 1A v2, PlatformIO'nun resmi `espressif32` platformunda
  yerleşik olarak destekleniyor. Arduino IDE'deki "boards manager URL ekle"
  adımına gerek YOK.

  ```ini
  [env:deneyapkart1Av2]
  platform = espressif32
  board = deneyapkart1Av2
  framework = arduino
  lib_deps =
      adafruit/Adafruit SSD1306
      adafruit/Adafruit GFX Library
  ```

- Kütüphane değişimi: `LiquidCrystal` (kaldırılacak) →
  `Adafruit_SSD1306` + `Adafruit_GFX` (eklenecek). Alternatif olarak
  Deneyap'ın resmi `deneyap-oled-ekran-arduino-library` kütüphanesi de
  kullanılabilir, ama Adafruit kütüphaneleri daha yaygın dokümante edilmiş
  ve `drawBitmap`/`fillRect` gibi düşük seviye çizim fonksiyonlarına
  doğrudan erişim veriyor — animasyonlu kalp/ikon tasarımı için bu
  gerekli, o yüzden Adafruit tercih edilecek.
- `EEPROM.h` kullanımı ESP32'de `EEPROM.begin(size)` çağrısı gerektiriyor
  (AVR'de gerekmiyordu) — `Eeprom.cpp`'de eksik, eklenmesi gerekiyor.

## AI destekli geliştirme ortamı

- Antigravity üzerinden Gemini ve Claude modelleriyle geliştirme yapılıyor.
- Bu memory-bank klasörü, o modellerin oturum başına context'i olmadığı
  için kalıcı proje hafızası görevi görüyor.
