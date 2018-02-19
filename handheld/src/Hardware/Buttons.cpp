#include <Wire.h>
#include <Arduino.h>
#include "../constants.h"
#include "Buttons.h"

Buttons::Buttons() :
  pressed1(false),
  pressed2(false),
  previousPressed1(false),
  previousPressed2(false),
  lastUpdate(0)
{
}

void Buttons::init()
{
  #ifndef __INTERNAL__WIRE_INITIALIZED
  #define __INTERNAL__WIRE_INITIALIZED
  Wire.begin();
  Wire.beginTransmission(HT16K33_ADDRESS);
  Wire.write(0x21); // turn on oscillator
  Wire.endTransmission();
  Wire.beginTransmission(HT16K33_ADDRESS);
  Wire.write(0xE0 | 15); // set maximum brightness
  Wire.endTransmission();
  Wire.beginTransmission(HT16K33_ADDRESS);
  Wire.write(0x81); // disable blinking
  Wire.endTransmission();
  #endif
}

bool Buttons::isButton1Pressed() const
{
  return pressed1;
}

bool Buttons::isButton2Pressed() const
{
  return pressed2;
}

bool Buttons::isButton1Clicked() const
{
  return pressed1 && !previousPressed1;
}

bool Buttons::isButton2Clicked() const
{
  return pressed2 && !previousPressed2;
}

void Buttons::update()
{
  previousPressed1 = pressed1;
  previousPressed2 = pressed2;

  // Make sure that the chip is not flooded with requests.
  // Apparently it does not like it that much, and refuses to work properly afterwards.
  if ((unsigned long)(millis() - lastUpdate) > TIMING_BUTTON_UPDATE)
  {
    lastUpdate = millis();

    Wire.beginTransmission(HT16K33_ADDRESS);
    Wire.write(HT16K33_KEYS_REGISTER);
    Wire.endTransmission();
  
    Wire.requestFrom(HT16K33_ADDRESS, 2);
    pressed1 = Wire.read() != 0;
    pressed2 = Wire.read() != 0;
  }
}
