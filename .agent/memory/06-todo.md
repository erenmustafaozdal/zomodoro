# Görev Listesi (Aktif)

Durum sütunu: `[ ]` yapılmadı, `[~]` devam ediyor, `[x]` tamamlandı.

Önerilen sıra: **2 → 3 → 9 → 4 → 5 → 10 → 11 → 12 → 7 → 6 → 14**

| # | Konu | Karar/Ne yapılacak | Dosya(lar) | Öncelik | Durum |
|---|------|---------------------|-----------|---------|-------|
| 1 | Donanım geçişi | Nano+16x2 LCD → Deneyap Kart 1A v2 + Deneyap OLED | (donanım) | Yüksek | [ ] |
| 2 | PlatformIO ortamı | `platformio.ini`'yi `board = deneyapkart1Av2`, `platform = espressif32` yap, Adafruit SSD1306/GFX ekle | `platformio.ini` | Yüksek | [ ] |
| 3 | EEPROM uyumu | `EEPROM.begin(size)` çağrısını ekle (ESP32 gereksinimi) | `lib/Eeprom/Eeprom.cpp` | Yüksek | [ ] |
| 4 | Ölü kod temizliği | Kullanılmayan `the_start_time` üyesini sil | `lib/Pomodoro/Pomodoro.hpp/.cpp` | Orta | [ ] |
| 5 | İsimlendirme düzeltmesi | `the_pom25/5/15` → gerçek süreleri yansıtan isimlere (`the_pom_work/short/long`) | `lib/Pomodoro/Pomodoro.cpp` | Orta | [ ] |
| 6 | Ses sensörü non-blocking | `SoundSensor::IsSoundDetected()` busy-wait'i millis tabanlı hale getir | `lib/SoundSensor/*` | Düşük | [ ] |
| 7 | Ses eşiği kalibrasyonu | HAZIR durumunda B1+B2 basılı tutma ile ortam gürültüsünü örnekleyip yeni eşik hesaplayan kalibrasyon modu | `lib/SoundSensor/*`, `lib/Pomodoro/*` | Orta | [ ] |
| 8 | PIR/hareket sensörü | Kapandı — bkz. `05-decisions-log.md` | — | — | [x] |
| 9 | Ekran 1 — Çalışma ekranı | Büyük fontla süre + **gerçek zamanlı dolan** kalp bar (adım adım değil), domates+sayı sağ üstte | `lib/UI/UI.cpp`, `lib/Display/*` | Yüksek | [ ] |
| 10 | Ekran 2 — Ses uyarısı | "Sessiz olun!" metni yerine shush ikonu + metin + duraklatma ikonu, ekran flaşı | `lib/UI/UI.cpp` | Orta | [ ] |
| 11 | Ekran 3 — Pomodoro bitti | Statik "Aferin sana!" yerine nabız atan kalp animasyonu + bip senkronlu ekran flaşı | `lib/UI/UI.cpp` | Orta | [ ] |
| 12 | İkon yönetimi | Domates, duraklatma, shush, kalp bitmap'lerini tek dosyada topla | `lib/UI/Icons.hpp` (yeni) | Orta | [ ] |
| 13 | Mimari koruma | `Pomodoro.cpp`'ye dokunulmadığını doğrula (yalnızca UI/Display katmanı değişti) | — | — | (her PR'da kontrol) |
| 14 | Kamera ile odak/varlık tespiti | İleri özellik — kapsam: "yüz kare içinde var mı" (basit varlık tespiti, tam dikkat analizi DEĞİL) | (yeni modül, henüz yok) | Düşük/Backlog | [ ] |
| 15 | Proje adı | Kapandı — Zomodoro kalıyor | — | — | [x] |

## Notlar

- Madde 9, en yüksek görsel/motivasyonel etkiye sahip — önce bu yapılırsa
  ilerlemenin somut karşılığı hemen görülür.
- Madde 4-5 çok küçük (toplam ~10 dk), madde 2-3'ten hemen sonra aynı
  oturumda bitirilebilir.
- Madde 14, mevcut mimariye yeni bir modül olarak eklenecek; kamera + basit
  yüz varlık tespiti ESP32-S3'ün DVP kamera girişi ve TFLite Micro desteğiyle
  mümkün, ama gerçek "dikkat/attention" tespiti bu aşamanın kapsamı DIŞINDA
  tutulmalı (bkz. `04-rules-and-conventions.md` — yanlış pozitif riski).
