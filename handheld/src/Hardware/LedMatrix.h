#ifndef INCLUDE_STAULU_LEDMATRIX_H
#define INCLUDE_STAULU_LEDMATRIX_H

/**
 * Class which controls the LED matrix of the Kniwwelino.
 */
class LedMatrix
{
  public:
    /**
     * Default constructor.
     * Initialises the class. Does not initialise the hardware, which must be done explicitly by calling init().
     */
    LedMatrix();

    /**
     * Initialises the drivers for communicating with the hardware.
     * This method must be called before any other method is invoked.
     */
    void init();

    /**
     * Sets the blinking mode of all pixels of the LED matrix.
     * The mode must be MATRIX_STATIC (to disable blinking) or one of the MATRIX_BLINK_* constants.
     */
    void setBlinkRate(uint8_t mode);

    /**
     * Sets the brightness of all pixels of the LED matrix.
     * The brightness must be between 0 and 15 (both included).
     * Values less than 2 will turn off the LED matrix.
     */
    void setBrightness(uint8_t brightness);

    /*
     * Turns a pixel of the LED matrix on or off.
     * The render() method must be called for the changes to take effect!
     * 
     * Pixels can be accessed by coordinates (x,y) lying in the range [0-4]×[0-4].
     * The x-direction goes horizontally and starts at the left.
     * The y-direction goes vertically and starts at the top.
     */
    void setPixel(uint8_t x, uint8_t y, bool on);

    /*
     * Turns a pixel of the LED matrix on or off.
     * The render() method must be called for the changes to take effect!
     * 
     * Pixels can be accessed by their index lying in the range [0-24].
     * Indices start at the top left corner and proceed line by line
     * (this, index=5 being the first pixel in the second line).
     */
    void setPixel(uint8_t index, bool on);

    /*
     * Gets the current pixel state of the LED matrix (true = on, false = off).
     * 
     * Pixels can be accessed by coordinates (x,y) lying in the range [0-4]×[0-4].
     * The x-direction goes horizontally and starts at the left.
     * The y-direction goes vertically and starts at the top.
     */
    bool getPixel(uint8_t x, uint8_t y) const;

    /*
     * Gets the current pixel state of the LED matrix (true = on, false = off).
     * 
     * Pixels can be accessed by their index lying in the range [0-24].
     * Indices start at the top left corner and proceed line by line
     * (this, index=5 being the first pixel in the second line).
     */
    bool getPixel(uint8_t index) const;

    /**
     * Turns all LED pixels off.
     * The render() method must be called for the changes to take effect!
     */
    void clear();

    /**
     * Reflects all changes made in this class (setPixel() and clear()) on the LED matrix hardware.
     * 
     * This method will actually only communicate with the hardware if needed (i.e., if any changes were made).
     * It can thus safely be called in every Kniwwelino::update() loop.
     */
    void render();

  private:
    uint8_t buffer[8];
    bool needRender;
};

#endif // INCLUDE_STAULU_LEDMATRIX_H
