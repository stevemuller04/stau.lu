#ifndef INCLUDE_STAULU_TRAFFICANIMATION_H
#define INCLUDE_STAULU_TRAFFICANIMATION_H

#include "../types.h"
#include "../Hardware/LedMatrix.h"

/**
 * Represents an animation on the Kniwwelino LED matrix that visualises a route.
 */
class TrafficAnimation
{
  public:
    /**
     * Resets the animation to the initial state.
     */
    void reset();

    /**
     * Renders the animation to the given LED matrix.
     * \param speed The duration (in milliseconds) specifying how long a frame will be displayed (e.g., speed=100 will result in 10 frames per second).
     */
    virtual void render(LedMatrix &ledMatrix, unsigned long speed) = 0;

  protected:
    /**
     * Initialises the class.
     * \param frameCount The number of frames that the animation consists of. Will be for determining the current frame index (in getFrameIndex()).
     */
    TrafficAnimation(frameid_t frameCount);

    /**
     * Gets the index of the frame to display.
     */
    frameid_t getFrameIndex(unsigned long speed);

    /** The number of frames that the animation consists of. */
    frameid_t frameCount = 1;

  private:
    frameid_t frameIndex = 0;
    unsigned long lastUpdate; // value of millis()
};

#endif // INCLUDE_STAULU_TRAFFICANIMATION_H
