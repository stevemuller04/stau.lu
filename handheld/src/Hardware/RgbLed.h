#ifndef INCLUDE_STAULU_RGBLED_H
#define INCLUDE_STAULU_RGBLED_H

#include <Adafruit_NeoPixel.h>

/**
 * Class which controls the RGB LED of the Kniwwelino.
 */
class RgbLed
{
  public:
    /**
     * Default constructor.
     * Initialises the class. Does not initialise the hardware, which must be done explicitly by calling init().
     */
    RgbLed();

    /**
     * Initialises the drivers for communicating with the hardware.
     * This method must be called before any other method is invoked.
     */
    void init();

    /**
     * Sets the color state of the LED.
     * The color is represented by its red-green-blue parts in the RGB color space,
     * each lying in the interval [0-255].
     */
    void setColor(uint8_t r, uint8_t g, uint8_t b);

    /**
     * Reflects all changes made in this class (setColor()) on the LED hardware.
     * 
     * This method will actually only communicate with the hardware if needed (i.e., if any changes were made).
     * It can thus safely be called in every Kniwwelino::update() loop.
     */
    void render();

  private:
    Adafruit_NeoPixel led;
    uint8_t r, g, b;
    bool needRender;
};

#endif // INCLUDE_STAULU_RGBLED_H
