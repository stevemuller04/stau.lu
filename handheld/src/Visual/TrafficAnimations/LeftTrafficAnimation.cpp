#include "LeftTrafficAnimation.h"

LeftTrafficAnimation::LeftTrafficAnimation(bool towardsTarget) :
  TrafficAnimation(3),
  towardsTarget(towardsTarget)
{
}

void LeftTrafficAnimation::render(LedMatrix &ledMatrix, unsigned long speed)
{
  frameid_t frameIndex = TrafficAnimation::getFrameIndex(speed);
  if (this->towardsTarget) frameIndex = frameCount - 1 - frameIndex;
  for (uint8_t x = 0; x < 3; ++x)
  {
    ledMatrix.setPixel(x + (this->towardsTarget ? 2 : 1), 1, frameIndex == x);
    ledMatrix.setPixel(x + (this->towardsTarget ? 1 : 2), 2, frameIndex == x);
    ledMatrix.setPixel(x + (this->towardsTarget ? 2 : 1), 3, frameIndex == x);
  }
  ledMatrix.setPixel(0, 2, true);
}
