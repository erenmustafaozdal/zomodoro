# README.md — Yapılması Gereken Güncellemeler

Mevcut `README.md` tamamen Nano + 16x2 LCD dönemini anlatıyor. OLED geçişi
(bkz. `06-todo.md` madde 1-3, 9-12) tamamlandığında aşağıdaki bölümler
güncellenmeli. Bu dosya, geçiş tamamlanana kadar README.md'ye **dokunma**,
geçiş bittiğinde bu listeyi kullanarak README.md'yi güncelle.

## Bölüm bölüm değişiklik listesi

### Giriş paragrafı
- "Arduino Nano ile ... 16x2 LCD ekran kullanarak" ifadesi → "Deneyap Kart
  1A v2 (ESP32-S3) ile ... 128x64 OLED ekran kullanarak" olarak
  güncellenmeli.

### Özellikler
- "LCD Ekran: Zamanlayıcı durumu..." satırı → OLED'e güncellenmeli, yeni
  eklenen görsel özellikler eklenmeli:
  - Gerçek zamanlı dolan kalp ilerleme çubuğu (artık adım adım değil).
  - İkon tabanlı uyarılar (shush ikonu, duraklatma ikonu).
  - Pomodoro tamamlandığında nabız animasyonu.
- "LDR Işık Sensörü: LCD ekranın parlaklığını..." → OLED kendi kendine ışık
  yaydığı için LDR'nin işlevi değişebilir (kontrast/parlaklık ayarı OLED'de
  farklı çalışır) — bu satır, madde 9 tamamlandıktan sonra gözden geçirilip
  gerçek davranışa göre güncellenmeli, olduğu gibi kopyalanmamalı.

### Donanım Gereksinimleri
Şu an:
```
- Arduino Nano
- 16x2 LCD Ekran
- ...
- 10K Potansiyometre (LCD kontrast ayarı için)
```
Yeni haliyle değişmesi gerekenler:
- `Arduino Nano` → `Deneyap Kart 1A v2 (ESP32-S3)`
- `16x2 LCD Ekran` → `Deneyap OLED (SSD1306, 128x64, I2C)`
- `10K Potansiyometre (LCD kontrast ayarı için)` → **kaldırılmalı** (OLED'de
  kontrast potansiyometresi yok, I2C üzerinden yazılımsal ayarlanıyor).
- LDR, Ses Sensörü, Butonlar, Buzzer aynı kalıyor.

### Yazılım Gereksinimleri
- `LiquidCrystal` kütüphanesi listeden çıkarılmalı.
- Eklenmesi gerekenler: `Adafruit SSD1306`, `Adafruit GFX Library`.

### Kurulum
- Devre şeması (`doc/zomodoro-circuit-view.png`) Deneyap Kart 1A v2 + OLED
  bağlantısına göre **yeniden çizilmeli** — mevcut görsel Nano dönemine ait,
  artık yanlış bilgi verir. Yeni şema hazırlanana kadar bu görsel README'den
  geçici olarak kaldırılabilir veya "güncelleniyor" notu eklenebilir.
- `platformio.ini` ile ilgili adım aynı kalabilir (adım değişmiyor, sadece
  içerik değişiyor — bkz. `03-tech-stack.md`).

### Kullanım
- Buton davranışları (başlatma, mola, sıfırlama vb.) **değişmiyor** —
  bu bölüm olduğu gibi kalabilir, çünkü `Pomodoro.cpp` state machine'i
  dokunulmadan korunuyor (bkz. `02-architecture.md`).

### Demo
- Mevcut video linki Nano+LCD dönemine ait. OLED versiyonu tamamlanınca
  yeni bir demo videosu/GIF ile değiştirilmeli.

## Değişmeyecek bölümler
- Katkıda Bulunma
- Lisans
- İçindekiler yapısı (başlıklar aynı kalabilir, sadece içerik güncellenir)
