#include <Arduino.h>
#include "Const.hpp"
#include "Button.hpp"

EMO::Button the_b1(EMO::Const::PIN_B1);
EMO::Button the_b2(EMO::Const::PIN_B2);

uint32_t the_time = 0;

uint8_t the_contrast = 128;
uint8_t the_brightness = 128;

void setup()
{
  the_b1.Setup();
  the_b2.Setup();
  Serial.begin(9600);
}

void loop()
{
  the_time = millis();

  the_b1.Update(the_time);
  the_b2.Update(the_time);

  // kontrast ve parlaklığı ayarlamak için
  if (Serial.available() > 0)
  {
    int b = Serial.read();

    if (b == 'c')
    {
      the_contrast += 8;
      analogWrite(EMO::Const::PIN_LCD_CONTRAST, the_contrast);
      Serial.print("contrast: ");
      Serial.println(the_contrast, DEC);
    }
    else if (b == 'b')
    {
      the_brightness += 8;
      analogWrite(EMO::Const::PIN_LCD_BRIGHTNESS, the_brightness);
      Serial.print("brightness: ");
      Serial.println(the_brightness, DEC);
    }
  }

  delay(100);
}