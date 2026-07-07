# Zomodoro — AI Hafıza Bankası (Memory Bank)

Bu klasör, Zomodoro projesi üzerinde Antigravity + Gemini/Claude ile çalışırken
kullanılacak kalıcı hafıza dosyalarıdır. Bu araçların oturumlar arası hafızası
yoktur; bu yüzden **her yeni oturuma başlarken bu klasördeki tüm dosyaları
oku**, sonra göreve başla.

## Klasör yapısı (proje kökünde `.agent/`)

Bu dosyaların hepsi üç ayrı klasöre dağılır, her birinin farklı bir görevi
var — karıştırma:

| Klasör | Ne içerir | Kim/ne zaman yazar |
|---|---|---|
| `.agent/memory/` | **Bu dosyalar.** Projenin güncel, kalıcı gerçeği: mimari, kurallar, kararlar, aktif todo. Sürekli güncellenir, geçmiş tutmaz. | Her oturumda güncellenir (görev bitince ilgili dosya değişir) |
| `.agent/docs/` | Memory'ye girmeyen doküman tarzı yazılar — kullanıcının (Eren'in) yapması gereken manuel işler, kurulum kılavuzları, tasarım notları, bir seferlik açıklamalar. "Şu an durum ne" değil "bunu nasıl yapacaksın/yapmalısın" içeriği. | Görev sırasında ihtiyaç oldukça oluşturulur |
| `.agent/sessions/` | Her oturumun sonunda o oturumda ne yapıldığının kaydı — `session-1.md`, `session-2.md` ... şeklinde, **artan numarayla, hiç üzerine yazılmadan**. | Her oturum **sonunda** bir kez yazılır |

Kısaca: `memory/` = "şu an durum ne", `docs/` = "bunu nasıl yapacaksın",
`sessions/` = "geçen sefer ne oldu" (değişmeyen tarihsel kayıt, arşiv).

## Okuma sırası

1. `01-project-brief.md` — Proje ne, kim için, neden var
2. `02-architecture.md` — Kod mimarisi, dosya/kütüphane haritası, veri akışı
3. `03-tech-stack.md` — Donanım (eski/yeni), yazılım, derleme ortamı
4. `04-rules-and-conventions.md` — AI'nın uyması gereken kurallar, kısıtlar
5. `05-decisions-log.md` — Kapanmış kararlar (tekrar tartışılmayacak konular)
6. `06-todo.md` — Aktif görev listesi, öncelik sırası, durum
7. `07-readme-updates.md` — README.md'ye OLED geçişiyle işlenecek değişiklikler

## Bu dosyaları nasıl güncellemeli

- Bir görev bittiğinde `06-todo.md`'de ilgili satırı işaretle, gerekirse
  `05-decisions-log.md`'ye yeni bir karar ekle.
- Mimaride gerçek bir değişiklik olursa (yeni dosya, yeni interface, kaldırılan
  sınıf) `02-architecture.md`'yi güncelle — bu dosya kodun güncel halini
  yansıtmalı, geçmiş tartışmayı değil.
- Yeni bir donanım/kütüphane kararı alınırsa `03-tech-stack.md` ve
  `05-decisions-log.md`'ye ekle.
- Bu dosyalar "sohbet günlüğü" değil, **projenin güncel gerçeği**dir. Eskiyen
  bilgiyi silmekten çekinme, arşiv burada tutulmuyor (git history zaten var).

## Proje sahibi hakkında (AI'nın ton/yaklaşım için bilmesi gereken)

Eren, sınıf öğretmeni ve yazılım geliştirici; bu projeyi kızı Zeynep için
yapıyor. Lehim/donanım tarafında yeni deneyim kazanıyor, yazılım tarafında
deneyimli. Doğrudan, teknik gerekçeli geri bildirim istiyor — kod incelerken
sorunları yumuşatmadan söyle, ama çözüm önerisiyle birlikte söyle. Eğitim/çocuk
kullanımı bağlamını (Zeynep 9 yaşında) her tasarım kararında göz önünde
bulundur.
