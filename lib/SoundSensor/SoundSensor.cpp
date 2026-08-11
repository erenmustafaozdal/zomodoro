#include "SoundSensor.hpp"

namespace EMO
{

    // Kesme servis rutini (ISR) için global değişken ve fonksiyon
    volatile uint32_t g_sound_pulse_count = 0;
    void IRAM_ATTR soundSensorISR()
    {
        g_sound_pulse_count++;
    }

    SoundSensor::SoundSensor(uint8_t pin, unsigned long sampleTime, uint16_t soundThreshold)
        : pin(pin), sampleTime(sampleTime), soundThreshold(soundThreshold),
          lastWindowTime(0), currentSampleCount(0), lastSampleCount(0), noiseFloor(0), soundDetected(false) {}

    void SoundSensor::Setup()
    {
        // USB beslemesinde açık kollektör / parazit hatlarını kararlı kılmak için PULLUP
        pinMode(pin, INPUT_PULLUP);
        // Düşen kenar (FALLING) kesmesini bağla
        attachInterrupt(digitalPinToInterrupt(pin), soundSensorISR, FALLING);
    }

    void SoundSensor::Update(unsigned long currentTime)
    {
        // Örnekleme süresi dolduğunda pencereyi değerlendir
        if (currentTime - lastWindowTime >= sampleTime)
        {
            // Kesme sayacını güvenli (kesmeleri kapatarak) oku ve sıfırla
            noInterrupts();
            uint32_t pulses = g_sound_pulse_count;
            g_sound_pulse_count = 0;
            interrupts();

            // Parazit Filtresi: 10ms içinde 3000'den fazla darbe imkansız yüksek frekanslı elektrik gürültüsüdür
            if (pulses > 3000)
            {
                pulses = 0;
            }

            lastSampleCount = pulses;

            // Arka Plan Taban Gürültüsü Takibi:
            // Darbe miktarı anlık eşik değerinin altındaysa taban gürültüsünü hareketli ortalama ile güncelle
            if (pulses < soundThreshold)
            {
                noiseFloor = (noiseFloor * 15 + pulses) / 16;
            }

            // Ses tespiti: Anlık darbe eşik değerini aştığında VE taban gürültüsünün belirgin şekilde üzerindeyse
            soundDetected = (pulses > soundThreshold) && (pulses > noiseFloor + 15);
            lastWindowTime = currentTime;
        }
    }

    bool SoundSensor::IsSoundDetected()
    {
        return soundDetected;
    }
}
