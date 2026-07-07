# Kurallar ve Kısıtlar (AI için)

Bu dosya, Zomodoro üzerinde kod üreten herhangi bir AI modelinin (Gemini,
Claude, fark etmez) uyması gereken kurallardır.

## Mimari kuralları

1. `Pomodoro.cpp` çekirdek state machine'ine **sadece** durum makinesi
   mantığı gerçekten değişiyorsa dokun. Ekran/donanım değişikliği için bu
   dosyaya dokunman gerekiyorsa muhtemelen yanlış katmandasın —
   `UI_IF`/`Display` katmanına bak.
2. Yeni bir donanım bileşeni eklerken önce bir interface (`*_IF.hpp`) tanımla,
   somut sınıfı ona göre yaz. Var olan `UI_IF`, `Eeprom_IF`, `State_IF`
   deseni örnek alınacak.
3. Tüm pin numaraları ve sabit süreler `Const.hpp`'de toplanır. Kod içine
   pin numarası veya "sihirli sayı" gömme.
4. Değişken/fonksiyon isimleri gerçek değerlerini yansıtmalı (bkz.
  `the_pom25` hatası — isim ile değer tutarsızlığı tekrar oluşmasın).

## Kod stili

- Yorumlar ve kullanıcıya gösterilen tüm metinler **Türkçe**.
- `delay()` ile bloklayan kod yerine mümkün olduğunca `millis()` tabanlı
  non-blocking desenler tercih et — özellikle buton okuma ve ekran
  güncelleme döngüsü çocuğun buton tepkisini hissetmesi için gecikmesiz
  olmalı.
- Yeni bitmap/ikon eklerken `lib/UI/Icons.hpp` altında topla, `UI.cpp`
  içine gömme.
- EEPROM'a yazma sıklığını artırma (aşınma ömrü sınırlı) — sadece pomodoro
  tamamlandığında veya resette yaz, mevcut davranış korunmalı.

## Ürün/UX kuralları (Zeynep 9 yaşında, unutma)

- Metin yerine ikon + kısa metin birlikte kullan — okuma hızı yetişkin
  değil.
- Ses/uyarı geçişleri ani ve ürkütücü olmamalı (ör. tüm ekranı flaşlarken
  frekansı çok yüksek tutma).
- Yeni özellik eklerken "yanlış pozitif" riskini her zaman sorgula — PIR
  sensörünün kaldırılma sebebi tam olarak buydu (bkz.
  `05-decisions-log.md`), aynı hata ses/kamera tabanlı yeni özelliklerde
  tekrarlanmamalı.

## Şunları yapma

- `Pomodoro.cpp`, `Counter`, `Timer`, `Button_Logic` davranışını "ekranı
  güzelleştirmek" bahanesiyle değiştirme.
- LCD'ye özgü CGRAM/custom-character kısıtlarını OLED tasarımına taşıma —
  OLED serbest piksel çizimi destekliyor, LCD alışkanlıklarını miras alma.
- Yeni bir kütüphane eklerken `platformio.ini`'deki `lib_deps` dışında,
  proje genelinde birden fazla ekran kütüphanesi (ör. hem Adafruit hem
  U8g2) aynı anda kullanma — birini seç (bkz. `03-tech-stack.md`).

## Görev tamamlama protokolü

Bir görevi bitirdiğinde:
1. `.agent/memory/06-todo.md`'de ilgili maddeyi işaretle.
2. Mimaride kalıcı bir değişiklik olduysa `.agent/memory/02-architecture.md`'yi
   güncelle.
3. README.md'yi etkileyen bir değişiklikse `.agent/memory/07-readme-updates.md`'yi
   kontrol et, gerekirse README.md'yi doğrudan güncelle.
4. Bu görev bir manuel işlem, kurulum adımı veya kullanıcının kendisinin
   yapması gereken bir şey içeriyorsa (ör. "devre şemasını böyle bağla",
   "kütüphaneyi manuel indir") bunu memory dosyalarına gömme — ayrı bir
   `.agent/docs/` dosyası olarak yaz. Memory dosyaları "proje ne durumda"
   sorusuna cevap verir, `.agent/docs/` ise "bunu nasıl yaparım" sorusuna.

## Oturum sonu protokolü (session log)

Her oturumun (yani her Antigravity çalışma seansının) **sonunda**, o oturumda
yapılan işleri özetleyen bir dosya yaz: `.agent/sessions/session-N.md`
(N = bir önceki oturumdan bir fazla, hiçbir zaman üzerine yazma — bu bir
tarihsel kayıt, arşiv).

Session dosyası şu bölümleri içermeli:
- **Tarih/bağlam:** Hangi todo maddeleri üzerinde çalışıldı.
- **Yapılanlar:** Değiştirilen/eklenen dosyalar, kısa özetle (ne değişti, neden).
- **Kararlar:** Oturum sırasında alınan yeni kararlar varsa (bunlar ayrıca
  `05-decisions-log.md`'ye de eklenmeli, session dosyası sadece "bu oturumda
  alındı" bilgisini taşır).
- **Yarım kalanlar / sıradaki adım:** Bir sonraki oturumun nereden devam
  edeceği — bu kısım özellikle önemli, çünkü yeni oturumun hafızası yok,
  bu satırlar onun için bir nevi "kaldığın yer" imi.

Session dosyaları **salt kayıttır, geri dönüp düzenlenmez**. Güncel durumu
her zaman `.agent/memory/` dosyaları taşır; session'lar sadece "o gün ne
oldu"yu anlatır, çelişki çıkarsa memory dosyaları esas alınır.
