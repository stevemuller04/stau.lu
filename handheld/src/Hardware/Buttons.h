#ifndef INCLUDE_STAULU_BUTTONS_H
#define INCLUDE_STAULU_BUTTONS_H

class Buttons
{
  public:
    Buttons();
    void init();
    bool isButton1Pressed() const;
    bool isButton2Pressed() const;
    bool isButton1Clicked() const;
    bool isButton2Clicked() const;
    void update();

  private:
    bool pressed1, pressed2;
    bool previousPressed1, previousPressed2;
    unsigned long lastUpdate; // value of millis()
};

#endif // INCLUDE_STAULU_BUTTONS_H
