#ifndef INCLUDE_STAULU_LEDMATRIX_H
#define INCLUDE_STAULU_LEDMATRIX_H

class LedMatrix
{
  public:
    LedMatrix();
    void init();
    void setBlinkRate(uint8_t mode);
    void setBrightness(uint8_t brightness);
    void setPixel(uint8_t x, uint8_t y, bool on);
    void setPixel(uint8_t index, bool on);
    bool getPixel(uint8_t x, uint8_t y) const;
    bool getPixel(uint8_t index) const;
    void clear();
    void render();

  private:
    uint8_t buffer[8];
    bool needRender;
};

#endif // INCLUDE_STAULU_LEDMATRIX_H
