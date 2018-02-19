#ifndef INCLUDE_STAULU_RGBLED_H
#define INCLUDE_STAULU_RGBLED_H

#include <Adafruit_NeoPixel.h>

class RgbLed
{
  public:
  	RgbLed();
    void init();
    void setColor(uint8_t r, uint8_t g, uint8_t b);
    void render();

  private:
    Adafruit_NeoPixel led;
    uint8_t r, g, b;
    bool needRender;
};

#endif // INCLUDE_STAULU_RGBLED_H
