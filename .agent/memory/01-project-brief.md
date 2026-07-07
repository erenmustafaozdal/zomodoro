# Proje Özeti

## Ne

**Zomodoro** ("Zeynep'in Pomodoro'su"), bir Pomodoro zaman yönetimi tekniği
uygulayan gömülü (embedded) bir cihaz. Fiziksel bir kutuda buton, ekran,
buzzer ve ses sensörü bulunuyor; masaüstü/mobil bir uygulama değil.

## Kim için

Eren'in kızı Zeynep (aktif kullanıcı, ~9 yaş). Ödev/ders çalışma ve okuma
sürelerini yönetmek için evde masasında kullanıyor.

## Neden var

- Zeynep'in odaklanma süresini yönetmesine yardımcı olmak.
- Eren'in yazılım + donanım (Arduino/ESP32) becerilerini birleştirdiği bir
  baba-kız projesi; aynı zamanda TeknoFest tarzı yarışmalara taşınabilecek bir
  temel oluşturuyor (bkz. Eren'in geçmiş TeknoFest projeleri: SenGör, MiniBağ,
  ActiBand).
- Klasik 25/5/15 dakikalık Pomodoro yerine çocuk kullanımına uyarlanmış
  20/10/30 dakikalık süreler kullanılıyor.

## Temel davranış (kullanıcı deneyimi)

1. Cihaz açılır, HAZIR durumunda bekler, süre seçilebilir (1. buton ile
   çalışma/kısa mola/uzun mola arası geçiş).
2. 2. buton ile zamanlayıcı başlar (RUNNING).
3. Çalışma periyodunda ses algılanırsa (konuşma vb.) zamanlayıcı 30 saniye
   duraklar, ekranda uyarı gösterilir (SOUND_DETECTED).
4. Süre bitince buzzer çalar, ekranda tebrik/bilgi mesajı gösterilir
   (FINISHED).
5. Her 5 tamamlanmış pomodoro bir "kalp" doldurur; toplam sayı EEPROM'da
   kalıcı olarak saklanır.

## Şu anki dönüşüm (aktif proje evresi)

Proje **Arduino Nano + 16x2 karakter LCD**'den **Deneyap Kart 1A v2
(ESP32-S3) + Deneyap OLED (SSD1306, 128x64 piksel)**'e taşınıyor. Bu sadece
bir donanım portu değil — piksel tabanlı ekrana geçişle birlikte arayüz
(UI) tamamen yeniden tasarlanıyor (bkz. `06-todo.md` madde 9-12).

Detaylar için `02-architecture.md`, `03-tech-stack.md` ve `06-todo.md`'ye bak.
