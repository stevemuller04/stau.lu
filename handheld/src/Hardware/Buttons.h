#ifndef INCLUDE_STAULU_BUTTONS_H
#define INCLUDE_STAULU_BUTTONS_H

/**
 * Class which reads the state of the hardware buttons of the Kniwwelino.
 */
class Buttons
{
  public:
    /**
     * Default constructor.
     * Initialises the class. Does not initialise the hardware, which must be done explicitly by calling init().
     */
    Buttons();

    /**
     * Initialises the drivers for communicating with the hardware.
     * This method must be called before any other method is invoked.
     */
    void init();

    /**
     * Determines if button A is currently pressed.
     */
    bool isButton1Pressed() const;

    /**
     * Determines if button B is currently pressed.
     */
    bool isButton2Pressed() const;

    /**
     * Determines if button A has been clicked (i.e., pressed and released) since the last call of update().
     */
    bool isButton1Clicked() const;

    /**
     * Determines if button B has been clicked (i.e., pressed and released) since the last call of update().
     */
    bool isButton2Clicked() const;

    /**
     * Updates the button state stored in this class, by retrieving the current status from the hardware.
     */
    void update();

  private:
    bool pressed1, pressed2;
    bool previousPressed1, previousPressed2;
    /** Timestamp of the last call to update(). Corresponds to the return value of millis(). */
    unsigned long lastUpdate;
};

#endif // INCLUDE_STAULU_BUTTONS_H
