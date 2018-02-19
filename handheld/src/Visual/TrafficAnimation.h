#ifndef INCLUDE_STAULU_TRAFFICANIMATION_H
#define INCLUDE_STAULU_TRAFFICANIMATION_H

#include "../types.h"
#include "../Hardware/LedMatrix.h"

class TrafficAnimation
{
  public:
    void reset();
    virtual void render(LedMatrix &ledMatrix, unsigned long speed) = 0;
  protected:
    TrafficAnimation(frameid_t frameCount);
    frameid_t getFrameIndex(unsigned long speed);
    frameid_t frameCount = 1;
  private:
    frameid_t frameIndex = 0;
    unsigned long lastUpdate; // value of millis()
};

#endif // INCLUDE_STAULU_TRAFFICANIMATION_H
