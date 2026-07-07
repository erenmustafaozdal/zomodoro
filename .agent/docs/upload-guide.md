# Deneyap Kart 1A v2 Kod Yükleme Kılavuzu

Deneyap Kart 1A v2 (ESP32-S3) üzerindeki kodları derlemek ve karta yüklemek için aşağıdaki adımları uygulayabilirsiniz.

## 1. Bağlantı ve Hazırlık
- Deneyap Kartınızı bir **USB-C** kablosu ile bilgisayarınıza bağlayın.
- Kullandığınız kablonun sadece şarj kablosu olmadığından, **veri transferi (data transfer)** desteklediğinden emin olun.

## 2. PlatformIO Arayüzü ile Yükleme (VS Code)
Eğer projeyi VS Code üzerinde açtıysanız:
1. Alt durum çubuğunda (Status Bar) bulunan **PlatformIO: Upload** (sağa doğru ok simgesi `→`) butonuna tıklayın.
2. PlatformIO projeyi otomatik olarak tekrar derleyecek ve algılanan COM portu üzerinden yükleme işlemini başlatacaktır.

## 3. Komut Satırı (Terminal) ile Yükleme
Eğer terminalden yükleme yapmak isterseniz, proje dizinindeyken aşağıdaki komutu çalıştırabilirsiniz:
```powershell
C:\Users\emozdal\.platformio\penv\Scripts\platformio.exe run --target upload
```

## 4. Bootloader Moduna Alma (Sorun Yaşanırsa)
Kart bazen otomatik yükleme moduna geçmeyebilir ve terminalde `Connecting...` kısmında takılıp hata verebilir. Bu durumda kartı manuel olarak **Bootloader Moduna** almalısınız:
1. Kartın üzerindeki **BOOT** butonuna basın ve basılı tutun.
2. BOOT butonunu bırakmadan **RST (Reset)** butonuna bir kez basıp çekin.
3. Son olarak **BOOT** butonunu bırakın.
4. Karta yükleme yapmayı tekrar deneyin (`Upload`).
5. Yükleme tamamlandıktan sonra kartın üzerindeki **RST (Reset)** butonuna basarak kodu normal modda çalıştırabilirsiniz.
