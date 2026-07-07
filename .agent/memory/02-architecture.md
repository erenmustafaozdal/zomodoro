# Mimari

## Genel yaklaşım

Proje, PlatformIO'nun `lib/` yapısını kullanarak her sorumluluğu ayrı bir
kütüphaneye bölmüş durumda. Çoğu sınıf bir **interface (IF) arkasında**
soyutlanmış — bu, donanım (LCD→OLED gibi) veya davranış değiştiğinde
`Pomodoro.cpp` çekirdek mantığına dokunmadan çalışmayı mümkün kılıyor.
**Bu ayrımı bozma** — yeni bir ekran/sensör eklerken önce ilgili IF'e
uyacak şekilde yaz.

## Dosya haritası (`lib/`)

| Kütüphane | Sorumluluk | Interface var mı |
|---|---|---|
| `Pomodoro` | Ana state machine (READY, RUNNING, SOUND_DETECTED, PAUSED, FINISHED) | — (çekirdek sınıf, IF kullanan taraf) |
| `Counter` | Süre sayımı (start/duration/max, kalan süre hesabı) | Hayır, dahili yardımcı sınıf |
| `Timer` | `Counter` üzerine ince bir sarmalayıcı | Hayır |
| `UI` | Ekrana ne yazılacağını belirler (Show_Ready/Running/Paused/Finished) | `UI_IF` |
| `Display` | Fiziksel ekrana yazma (şu an `LiquidCrystal` sarmalayıcısı) | Yok (UI, Display'i doğrudan kullanıyor) |
| `State_IF` | `Pomodoro`'nun `UI`'a verdiği salt-okunur durum bilgisi (kalan süre, pomodoro sayısı vb.) | Kendisi bir interface |
| `Eeprom` | Pomodoro sayısını kalıcı saklama | `Eeprom_IF` |
| `SoundSensor` | Ses eşiği örnekleme | Hayır |
| `Button` / Button_Logic | Buton okuma, basılı tutma süresi tespiti | — |
| `LightSensor` (LDR) | Ortam ışığına göre LCD parlaklığı | Hayır |
| `Const` | Tüm pin tanımları ve sabit süreler tek yerde | — |
| `Utils` | Yardımcı fonksiyonlar (ör. `ms_to_m_s`) | — |

## Durum makinesi (State Machine)

```
READY --(B2 kısa basış)--> RUNNING
RUNNING --(ses algılandı, sadece çalışma periyodunda)--> SOUND_DETECTED
SOUND_DETECTED --(30 sn sonra otomatik)--> RUNNING (kalan süre korunur)
RUNNING --(B2 kısa basış)--> PAUSED
PAUSED --(B2 kısa basış)--> RUNNING
RUNNING/PAUSED --(süre biter)--> FINISHED
FINISHED --(otomatik/buton)--> READY
READY/PAUSED --(B2, 3 sn basılı)--> reset (READY'e dön, ilerleme sıfırlanır)
```

## Veri akışı (her `loop()` çağrısında)

1. `main.cpp` → `Pomodoro::Run()` çağırır.
2. `Pomodoro`, mevcut duruma göre `Button_Logic`'ten girdi okur, `Counter`'ı
   günceller, gerekirse `Eeprom`'a yazar.
3. `Pomodoro`, güncel durumu `State_IF` üzerinden `UI`'a aktarır.
4. `UI`, hangi `Show_*()` metodunun çağrılacağına karar verir, `Display`
   üzerinden fiziksel ekrana yazar.

## OLED geçişinde nelerin değişeceği / değişmeyeceği

- **Değişecek:** `Display` sınıfı (`LiquidCrystal` yerine `Adafruit_SSD1306`
  + `Adafruit_GFX`), `UI.cpp` içindeki `Show_*()` metodlarının çizim mantığı
  (karakter tabanlı → piksel tabanlı, animasyonlu dolum, ikonlar).
- **Değişmeyecek:** `Pomodoro.cpp`, `State_IF`, `Counter`, `Timer`,
  `Button_Logic`, `SoundSensor` mantığı. Bunlara dokunulması gerekiyorsa
  bu, mimarinin bozulduğunun işaretidir — durup nedenini sorgula.
- **Yeni eklenecek:** `Icons.hpp` (bitmap tanımları: domates, duraklatma,
  shush/sessizlik, kalp) — `lib/UI/` altında yeni bir dosya olarak.

## Bilinen kod kusurları (henüz düzeltilmedi, bkz. `06-todo.md`)

- `Pomodoro.hpp` içindeki `the_start_time` üyesi hiç okunmuyor (ölü kod).
- `Pomodoro.cpp`'deki `the_pom25/the_pom5/the_pom15` isimleri gerçek
  sürelerle (20/10/30 dk) uyuşmuyor, kafa karıştırıcı.
- `SoundSensor::IsSoundDetected()` `sampleTime` boyunca busy-wait ile
  bloklanıyor (şu an 10ms, zararsız ama non-blocking'e çevrilebilir).
