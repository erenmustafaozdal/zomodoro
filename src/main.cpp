#include <Arduino.h>
#include "Const.hpp"
#include "Button.hpp"
#include "UI.hpp"
#include "Pomodoro.hpp"
#include "Eeprom.hpp"
#include "SoundSensor.hpp"

EMO::Button the_b1(EMO::Const::PIN_B1);
EMO::Button the_b2(EMO::Const::PIN_B2);
EMO::Eeprom the_eeprom;
EMO::UI the_ui(EMO::Const::PIN_LDR);
EMO::SoundSensor soundSensor(
    EMO::Const::PIN_SOUND_SENSOR,
    EMO::Const::SOUND_SAMPLE_TIME,
    EMO::Const::SOUND_THRESHOLD);

EMO::Pomodoro the_pomodoro(&the_ui, &the_b1, &the_b2, &the_eeprom, &soundSensor);
uint32_t the_time = 0;

void setup()
{
  the_b1.Setup();
  the_b2.Setup();
  the_pomodoro.Setup();
  Serial.begin(9600);
}

void loop()
{

  the_time = millis();

  the_ui.UpdateBrightness(the_time);
  the_b1.Update(the_time);
  the_b2.Update(the_time);
  the_pomodoro.Run(the_time);

  delay(100);
}
