#include "Pomodoro.hpp"
#include "Utils.hpp"
#include "Const.hpp"

namespace EMO
{
    Pomodoro::Pomodoro(
        UI_IF *a_ui,
        Button_Logic *a_b1,
        Button_Logic *a_b2,
        Eeprom_IF *a_eeprom,
        SoundSensor *a_soundSensor) : the_timer_type(T_POM20),
                                      the_state(READY),
                                      the_timer(0),
                                      the_pomodoros(0),

                                      the_ui(a_ui),
                                      the_b1(a_b1),
                                      the_b2(a_b2),
                                      the_eeprom(a_eeprom),
                                      the_soundSensor(a_soundSensor),


                                      the_pause_time(0),
                                      the_duration(0),
                                      the_sound_pause_time(0),
                                      the_calib_start_time(0),
                                      the_max_detected_noise(0),
                                      the_last_button_activity_time(0),
                                      the_sound_trigger_count(0),

                                      the_pom_work(Const::POM_WORK_MIN, Const::POM_WORK_BEEPS),
                                      the_pom_break_short(Const::POM_BREAK_SHORT_MIN, Const::POM_BREAK_SHORT_BEEPS),
                                      the_pom_break_long(Const::POM_BREAK_LONG_MIN, Const::POM_BREAK_LONG_BEEPS)
    {
        the_pom[T_POM20] = &the_pom_work;
        the_pom[T_POM10] = &the_pom_break_short;
        the_pom[T_POM30] = &the_pom_break_long;

        reset_timer();
    }

    // -------------------------------------------------------------------------

    void Pomodoro::Setup()
    {
        the_ui->Setup();
        the_soundSensor->Setup();
        // Pomodoroları EEPROM'dan oku
        the_pomodoros = the_eeprom->Read(Const::POM_SAVE_ADDRESS);
        if (the_pomodoros == 255) {
            the_pomodoros = 0;
            the_eeprom->Write(Const::POM_SAVE_ADDRESS, 0);
        }

        // Kayıtlı ses eşiğini EEPROM'dan oku
        uint8_t threshold_high = the_eeprom->Read(Const::SOUND_THRESHOLD_ADDR_HIGH);
        uint8_t threshold_low = the_eeprom->Read(Const::SOUND_THRESHOLD_ADDR_LOW);
        uint16_t saved_threshold = (threshold_high << 8) | threshold_low;

        // EEPROM boş değilse ve 450'den büyükse eşiği uygula (klavye tıkırtısı > 350 olduğundan min 450 yapıyoruz)
        if (saved_threshold >= 450 && saved_threshold < 65535) {
            the_soundSensor->SetThreshold(saved_threshold);
            Utils::debug("Kayitli ses esigi yuklendi: %u", saved_threshold);
        } else {
            the_soundSensor->SetThreshold(450);
            Utils::debug("Varsayilan guvenli ses esigi kullaniliyor: 450");
        }
    }

    // -------------------------------------------------------------------------

    void Pomodoro::Run(uint32_t a_time)
    {
        if (the_state == READY)
            run_ready(a_time);
        else if (the_state == RUNNING)
            run_running(a_time);
        else if (the_state == FINISHED)
            run_finished();
        else if (the_state == PAUSED)
            run_pause();
        else if (the_state == SOUND_DETECTED)
            handle_sound_detection(a_time);
        else if (the_state == CALIBRATING)
            run_calibrating(a_time);
    }

    // -------------------------------------------------------------------------

    void Pomodoro::run_ready(uint32_t a_time)
    {
        the_ui->Show_Ready(*this);

        // B1 ve B2 butonlarının her ikisi de basılı tutuluyorsa
        if (the_b1->On() && the_b2->On())
        {
            if (the_calib_start_time == 0)
            {
                the_calib_start_time = a_time;
            }
            else if (a_time - the_calib_start_time > 2000) // 2 saniye basılı tutulursa kalibrasyona geç
            {
                the_state = CALIBRATING;
                the_calib_start_time = a_time;
                the_max_detected_noise = 0;
                the_b1->Reset(); // Kalibrasyon geçişinde buton durumlarını temizle
                the_b2->Reset();
                Utils::debug("Kalibrasyon modu tetiklendi");
                return;
            }
        }
        else
        {
            the_calib_start_time = 0;
        }

        // B1 basıldıysa, zamanlayıcıdaki süreler arasında döngü yap
        if (!the_b2->On() && the_b1->Released())
        {
            the_timer_type = (the_timer_type + 1) % T_SIZE;
            reset_timer();
            Utils::debug("sonraki zamanlayıcı indeksi = %u", the_timer_type);
        }

        if (the_b2->On())
        {
            // B2'ye 3 saniyeden uzun süre basıldıysa pomodoroları sıfırla
            if (the_b2->Duration() > 3000)
            {
                the_pomodoros = 0;

                // Pomodoroları EEPROM'a kaydet
                the_eeprom->Write(Const::POM_SAVE_ADDRESS, the_pomodoros);

                the_timer_type = T_POM20;
                reset_timer();
                Utils::debug("pomodorolar sıfırlandı");
            }
        }
        // b2 kapalı
        else if (the_b2->Released())
        {
            if (the_b2->Last_Duration() < 250)
            {
                the_ui->Set_Beeper(p().Get_Beeps());
                reset_timer();
                Utils::debug("çalışma durumuna geçiliyor");

                the_state = RUNNING;
            }
        }
    }

    // -------------------------------------------------------------------------

    void Pomodoro::run_running(uint32_t a_time)
    {
        // Buton aktivitesi varsa algılamayı kör etmek için zamanı kaydet
        if (the_b1->On() || the_b1->Released() || the_b2->On() || the_b2->Released())
        {
            the_last_button_activity_time = a_time;
            the_sound_trigger_count = 0;
        }

        // sayaç güncelleniyor
        the_timer.Update(a_time);

        the_ui->Show_Running(*this);

        if (the_timer.Elapsed())
        {
            the_state = FINISHED;
        }
        else if (the_b2->Released())
        {
            the_state = PAUSED;
        }
        else
        {
            // Butona basıldıktan sonra 1.5 saniye ses kontrolü yapma (klik sesini filtrele)
            if (the_timer_type == T_POM20 && (a_time - the_last_button_activity_time > 1500))
            {
                if (the_soundSensor->IsSoundDetected())
                {
                    if (the_sound_trigger_count < 25)
                        the_sound_trigger_count++;

                    // Her 5 döngüde bir seri porta durum yazdır
                    if (the_sound_trigger_count % 5 == 0)
                    {
                        Serial.print("Gurultu sayaci: ");
                        Serial.print(the_sound_trigger_count);
                        Serial.print("/25, Darbe: ");
                        Serial.print(the_soundSensor->GetLastSampleCount());
                        Serial.print(", Limit: ");
                        Serial.println(the_soundSensor->GetThreshold());
                    }

                    // En az 25 yoğun pencerede gürültü olmalı (gerçek sürede ~2 saniyeye denk gelir)
                    if (the_sound_trigger_count >= 25)
                    {
                        Serial.print("Gurultu dogrulandi! Darbe: ");
                        Serial.print(the_soundSensor->GetLastSampleCount());
                        Serial.print(", Limit: ");
                        Serial.println(the_soundSensor->GetThreshold());

                        the_ui->Set_Beeper(1); // Ses uyarısı başladığında kısa bip sesi çıkar
                        the_state = SOUND_DETECTED;
                        the_sound_pause_time = a_time;
                        the_sound_trigger_count = 0;
                    }
                }
                else
                {
                    if (the_sound_trigger_count > 0)
                        the_sound_trigger_count--;
                }
            }
            else
            {
                the_sound_trigger_count = 0;
            }
        }
    }

    // -------------------------------------------------------------------------

    void Pomodoro::run_finished()
    {
        the_ui->Show_Finished(*this);

        // bip sesi bitene kadar çal
        if (the_ui->Showing() == false)
        {
            if (the_timer_type == T_POM20)
            {
                the_pomodoros += 1;
                // Pomodoroları EEPROM'a kaydet
                the_eeprom->Write(Const::POM_SAVE_ADDRESS, the_pomodoros);

                the_timer_type = T_POM10;
                if (the_pomodoros % 3 == 0)
                {
                    the_timer_type = T_POM30;
                }
            }
            else
            {
                the_timer_type = T_POM20;
            }
            reset_timer();
            the_state = READY;
        }
    }

    // -------------------------------------------------------------------------

    void Pomodoro::run_pause()
    {
        the_ui->Show_Paused(*this);

        if (the_b2->On())
        {
            // B2'ye 3 saniyeden uzun süre basıldıysa pomodoro iptal edilir
            if (the_b2->Duration() > 3000)
            {
                reset_timer();
                the_state = READY;
                the_b2->Reset();
            }
        }
        // b2 kapalı
        else if (the_b2->Released())
        {
            if (the_b2->Last_Duration() < 250)
            {
                continue_timer();
                the_state = RUNNING;
            }
        }
    }

    void Pomodoro::handle_sound_detection(uint32_t a_time)
    {
        the_ui->Show_Paused(*this, true);

        if (a_time - the_sound_pause_time >= 30000) // 30 saniye bekleme
        {
            // Timer'ı devam ettir
            the_state = RUNNING;
            continue_timer();
        }
    }

    void Pomodoro::run_calibrating(uint32_t a_time)
    {
        uint32_t elapsed = a_time - the_calib_start_time;

        the_ui->Show_Calibrating(*this, elapsed);

        // Son 10ms penceresindeki gürültü miktarını takip et
        uint16_t noise = the_soundSensor->GetLastSampleCount();
        if (noise > the_max_detected_noise)
        {
            the_max_detected_noise = noise;
        }

        if (elapsed >= 3000) // 3 saniye örnekleme yap
        {
            // Eşik değerini belirle: daha güvenli olması için maks gürültü * 2 + 15 tolerans
            uint16_t new_threshold = the_max_detected_noise * 2 + 15;
            
            // Yanlış tetiklenmeyi önlemek için minimum sınırı 450 yapalım (klavye tıkırtılarını eler)
            if (new_threshold < 450) {
                new_threshold = 450;
            }

            the_soundSensor->SetThreshold(new_threshold);

            // EEPROM'a 16-bit olarak kaydet
            the_eeprom->Write(Const::SOUND_THRESHOLD_ADDR_HIGH, (new_threshold >> 8) & 0xFF);
            the_eeprom->Write(Const::SOUND_THRESHOLD_ADDR_LOW, new_threshold & 0xFF);

            Utils::debug("Yeni gurultu esigi kaydedildi: %u (max gurultu: %u)", new_threshold, the_max_detected_noise);

            // READY durumuna dön
            the_state = READY;
            the_calib_start_time = 0;
            the_b1->Reset(); // Kalibrasyon bitişinde buton durumlarını temizle
            the_b2->Reset();
            reset_timer();
        }
    }
}
