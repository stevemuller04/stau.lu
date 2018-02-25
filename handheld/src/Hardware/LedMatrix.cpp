#include <Wire.h>
#include "../constants.h"
#include "LedMatrix.h"

LedMatrix::LedMatrix() :
  needRender(true)
{
  clear();
}

void LedMatrix::init()
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

void LedMatrix::setBlinkRate(uint8_t mode)
{
  Wire.beginTransmission(HT16K33_ADDRESS);
  Wire.write(HT16K33_BLINK_CMD | HT16K33_BLINK_DISPLAYON | (mode & 3) << 1);
  Wire.endTransmission();
}

void LedMatrix::setBrightness(uint8_t brightness)
{
  Wire.beginTransmission(HT16K33_ADDRESS);
  Wire.write(HT16K33_CMD_BRIGHTNESS | brightness & 0xF);
  Wire.endTransmission();
}

void LedMatrix::setPixel(uint8_t x, uint8_t y, bool on)
{
  if (on)
    buffer[4 - x % 5] |= 1 << (y % 5);
  else
    buffer[4 - x % 5] &= ~(1 << (y % 5));
  needRender = true;
}

void LedMatrix::setPixel(uint8_t index, bool on)
{
  setPixel(index % 5, index / 5, on);
}

bool LedMatrix::getPixel(uint8_t x, uint8_t y) const
{
  return (buffer[4 - x % 5] & 1 << (y % 5)) != 0;
}

bool LedMatrix::getPixel(uint8_t index) const
{
  return getPixel(index % 5, index / 5);
}

void LedMatrix::clear()
{
  for (uint8_t i = 0; i < 8; i++) {
    needRender |= buffer[i] != 0;
    buffer[i] = 0;
  }
}

void LedMatrix::render()
{
  if (needRender)
  {
    Wire.beginTransmission(HT16K33_ADDRESS);
    Wire.write(HT16K33_DISP_REGISTER);
    for (uint8_t i = 0; i < 8; i++)
    {
      Wire.write(buffer[i]);
      Wire.write(0);
    }
    Wire.endTransmission();
    needRender = false;
  }
}
