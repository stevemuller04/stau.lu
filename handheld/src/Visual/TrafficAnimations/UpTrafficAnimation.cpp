#include "UpTrafficAnimation.h"

UpTrafficAnimation::UpTrafficAnimation(bool towardsTarget) :
  TrafficAnimation(3),
  towardsTarget(towardsTarget)
{
}

void UpTrafficAnimation::render(LedMatrix &ledMatrix, unsigned long speed)
{
  frameid_t frameIndex = TrafficAnimation::getFrameIndex(speed);
  if (this->towardsTarget) frameIndex = frameCount - 1 - frameIndex;
  for (uint8_t y = 0; y < 3; ++y)
  {
    ledMatrix.setPixel(1, y + (this->towardsTarget ? 2 : 1), frameIndex == y);
    ledMatrix.setPixel(2, y + (this->towardsTarget ? 1 : 2), frameIndex == y);
    ledMatrix.setPixel(3, y + (this->towardsTarget ? 2 : 1), frameIndex == y);
  }
  ledMatrix.setPixel(2, 0, true);
}
