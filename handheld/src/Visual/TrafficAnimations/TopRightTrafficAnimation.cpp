#include "TopRightTrafficAnimation.h"

TopRightTrafficAnimation::TopRightTrafficAnimation(bool towardsTarget) :
  TrafficAnimation(3),
  towardsTarget(towardsTarget)
{
}

void TopRightTrafficAnimation::render(LedMatrix &ledMatrix, unsigned long speed)
{
  frameid_t frameIndex = TrafficAnimation::getFrameIndex(speed);
  if (this->towardsTarget) frameIndex = frameCount - 1 - frameIndex;
  for (uint8_t d = 0; d < 3; ++d)
  {
    ledMatrix.setPixel(2 - d, d + 1, frameIndex == d);
    ledMatrix.setPixel(3 - d, d + 2, frameIndex == d);
    ledMatrix.setPixel(2 - d + (this->towardsTarget ? 1 : 0), d + (this->towardsTarget ? 1 : 2), frameIndex == d);
  }
  ledMatrix.setPixel(4, 0, true);
}
