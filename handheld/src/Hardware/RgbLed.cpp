#include "RgbLed.h"

RgbLed::RgbLed() :
  led(1, /* GPIO pin: */ 15, NEO_GRB + NEO_KHZ800),
  r(0),
  g(0),
  b(0),
  needRender(true)
{
}

void RgbLed::init()
{
  led.begin();
}

void RgbLed::setColor(uint8_t r, uint8_t g, uint8_t b)
{
  this->needRender |= this->r != r || this->g != g || this->b != b;
  this->r = r;
  this->g = g;
  this->b = b;
}

void RgbLed::render()
{
  if (needRender) {
    led.setPixelColor(0, r, g, b);
    led.show();
  }
}
