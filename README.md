# Zomodoro: Zeynep'in Pomodoro Zamanlayıcısı

Zomodoro, kızım Zeynep için özel olarak tasarlanmış modern bir pomodoro zamanlayıcısıdır. Proje, Arduino Nano ve 16x2 LCD altyapısından **Deneyap Kart 1A v2 (ESP32-S3)** ve **SSD1306 OLED** ekran altyapısına yükseltilmiştir. Zaman yönetimi ve odaklanma becerilerini oyunlaştırarak çocuk gelişimine katkıda bulunur.

## İçindekiler

- [Özellikler](#özellikler)
- [Donanım Gereksinimleri](#donanım-gereksinimleri)
- [Yazılım Kütüphaneleri](#yazılım-kütüphaneleri)
- [Kurulum](#kurulum)
- [Kullanım ve Kısayollar](#kullanım-ve-kısayollar)
- [Lisans](#lisans)

---

## Özellikler

- **Pomodoro Tekniği:** 20 dakika çalışma, 10 dakika kısa mola ve her 3 pomodoro seansı sonunda 30 dakika uzun mola düzenini yönetir.
- **OLED Arayüz:** Modern grafikler, 12x12 piksel-art domates ikonu, pürüzsüz iki loblu sıvı kalp göstergesi ve damlama animasyonları.
- **Pil Göstergesi:** Li-Po batarya seviyesini okumak için donanımsal voltaj bölücü pini (`A8`) entegre edilmiştir. Üst barda 3 kademeli (Dolu, Orta, Düşük) batarya göstergesi yer alır.
- **LDR Parlaklık Kontrolü:** Ortam ışık seviyesine göre ekran parlaklığını otomatik olarak kısarak (`dim` modu) pil tasarrufu sağlar ve gözü yormaz.
- **Pedagojik Kalp Ödüllendirmesi:** Tamamlanan her pomodoro seansı (20 dk) = 1 dolu küçük kalp kazanımı olarak oyunlaştırılır. Ekranda maksimum 5 adet kalp biriktirilebilir.
- **Gelişmiş Ses Sensörü:** Donanım kesmesi (hardware interrupt) tabanlı çalışır. Sınıf veya çalışma ortamındaki gürültünün yaklaşık 2-3 saniye (25 ardışık döngü) boyunca limit eşiğini aşması durumunda tetiklenerek çalışmayı duraklatır ve buzzer ile sesli uyarı verip ekranı flaş yaparak **"SESSİZ OLUN!"** uyarısı gösterir.
- **Buton Körlüğü:** Butonların kendi mekanik tıklama seslerinin yanlış tetiklemelere yol açmaması için buton basımlarından sonra 1.5 saniye boyunca ses algılama devre dışı bırakılır.

---

## Donanım Gereksinimleri

- Deneyap Kart 1A v2 (ya da ESP32-S3 geliştirme kartı)
- 128x64 SSD1306 OLED Ekran (I2C)
- LDR (Işık Sensörü)
- Mikrofon/Ses Sensörü (Analog çıkışlı)
- Butonlar (x2)
- Buzzer (Aktif)
- Li-Po Batarya (3.7V)
- Dirençler ve bağlantı kabloları

---

## Yazılım Kütüphaneleri

- [PlatformIO](https://platformio.org/)
- Gerekli Kütüphaneler:
  - [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306) (OLED ekran kontrolü)
  - [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library) (Grafik kütüphanesi)

---

## Kurulum

1. **Platform Projesini Açın:** Bu repo'yu indirin ve PlatformIO IDE üzerinde açın.
2. **Bağlantıları Yapın:** Donanım bileşenlerini aşağıdaki pin haritasına göre bağlayın:
   - **B1 (Sol Buton):** `D0`
   - **B2 (Sağ Buton):** `D1`
   - **LDR (Işık Sensörü):** `A0`
   - **Ses Sensörü (Mikrofon):** `A1`
   - **Buzzer:** `D12`
   - **Batarya Ölçüm:** `A8` (Deneyap Kart dahili batarya okuma pini)
   - **OLED Ekran:** I2C pinleri (`SDA` / `SCL`)
3. **Kodu Yükleyin:** PlatformIO üzerinden projeyi derleyin ve karta yükleyin:
   ```bash
   platformio run --target upload
   ```

---

## Kullanım ve Kısayollar

- **Zamanlayıcıyı Başlatma:** Hazır ekranındayken **B2 (Sağ Buton)** tuşuna basarak geri sayımı başlatın.
- **Zamanlayıcı Modları Arasında Geçiş:** Hazır ekranındayken **B1 (Sol Buton)** tuşuna basarak Çalışma (20 dk), Kısa Mola (10 dk) ve Uzun Mola (30 dk) modları arasında geçiş yapabilirsiniz.
- **Duraklatma (Pause):** Çalışma esnasında **B2** tuşuna basarak zamanlayıcıyı duraklatabilirsiniz. Tekrar basıldığında çalışma devam eder.
- **Zamanlayıcıyı İptal Etme:** Duraklatılmış durumda **B2** tuşuna **3 saniye** basılı tuttuğunuzda oturum iptal edilir ve başlangıç (Hazır) ekranına dönülür.
- **Zomodoro/Kalp Sayısını Sıfırlama (Yeni Gün Ritüeli):** Hazır ekranındayken **B2** tuşuna **3 saniye** basılı tutulduğunda kazanılan tüm kalpler sıfırlanır, EEPROM hafızası temizlenir ve kısa bir onay bipi çalar.
- **Otomatik Ses Eşiği Kalibrasyonu:** Hazır ekranındayken **B1 ve B2** tuşlarına aynı anda **2 saniye** basılı tutulduğunda kalibrasyon modu açılır. Cihaz 3 saniye boyunca ortam gürültüsünü dinler, en yüksek gürültü seviyesini tespit edip yeni eşik limitini otomatik hesaplar ve EEPROM'a kalıcı olarak kaydeder.

---

## Lisans

Bu proje MIT lisansı altında lisanslanmıştır. Daha fazla bilgi için [LICENSE](https://github.com/erenmustafaozdal/zomodoro/blob/master/LICENSE) dosyasına bakın.

## Demo

https://github.com/user-attachments/assets/dc259c37-99fc-435b-b7c4-00ff2f2d4342
