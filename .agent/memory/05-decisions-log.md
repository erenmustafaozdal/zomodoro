# Karar Günlüğü (Kapanmış Konular)

Bu maddeler tartışılmış ve karara bağlanmış. AI bunları **tekrar önermemeli**,
sebep sorulmadıkça yeniden açmamalı.

## Hareket sensörü (PIR) — kaldırıldı, geri gelmeyecek

**Karar:** PIR ile "hareket algılandığında zamanlayıcıyı durdur" fikri
denenmiş, ufak hareketlerde bile yanlış tetiklendiği için sistemden
tamamen çıkarılmış. Bu doğru bir mühendislik kararı olarak değerlendirildi.
**Gerekçe:** PIR "odada hareket var mı" ölçer, "göreve odaklanma" ölçmez —
yanlış sensör sınıfıydı. Kalem tutarken, sayfa çevirirken bile hareket var.
**Gelecekte tekrar gündeme gelebileceği durum:** Kamera tabanlı bir
yaklaşımla (bkz. `06-todo.md` madde 14), gerçek "kişi masada mı" tespiti —
ama bu PIR'ın yerine geçen farklı bir teknik, aynı fikrin tekrarı değil.

## Proje adı — Zomodoro kalıyor

**Karar:** İsim değiştirilmeyecek. "Zeynep + Pomodoro" bağı korunacak.

## Donanım platformu — Deneyap Kart 1A v2 + Deneyap OLED

**Karar:** Nano + 16x2 LCD tamamen terk ediliyor, geri dönüş yok.
**Gerekçe:** LCD'deki "karıncalanma" sorunu muhtemelen paralel bağlantının
çok sayıda lehim noktasından (RS/EN/D4-D7 + kontrast potu) kaynaklanıyordu,
Nano'nun kendisinden değil. I2C OLED (2 veri hattı) bunu yapısal olarak
çözüyor.

## Geliştirme ortamı — PlatformIO'da kalınıyor

**Karar:** Arduino IDE'ye geçilmeyecek, PlatformIO'da devam edilecek.
Deneyap Kart 1A v2 PlatformIO'nun resmi `espressif32` platformunda
destekleniyor, bu yüzden ekstra manuel adım gerekmiyor.

## Ekran kütüphanesi — Adafruit SSD1306 + Adafruit GFX

**Karar:** Deneyap'ın kendi resmi kütüphanesi yerine Adafruit kütüphaneleri
kullanılacak. **Gerekçe:** Animasyonlu ikon/dolum tasarımı için düşük
seviye `drawBitmap`/`fillRect` erişimi gerekiyor, Adafruit bunu doğrudan
sağlıyor ve daha yaygın dokümante edilmiş.
