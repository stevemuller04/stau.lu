#include <Arduino.h>
#include "TrafficAnimation.h"

TrafficAnimation::TrafficAnimation(frameid_t frameCount) :
  frameCount(frameCount)
{
}

void TrafficAnimation::reset()
{
  lastUpdate = millis();
  frameIndex = 0;
}

frameid_t TrafficAnimation::getFrameIndex(unsigned long speed)
{
  if ((unsigned long)(millis() - lastUpdate) > speed)
  {
    lastUpdate = millis();
    frameIndex = (frameIndex + 1) % frameCount;
  }
  return frameIndex;
}
