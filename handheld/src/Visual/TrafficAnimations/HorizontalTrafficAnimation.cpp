#include "HorizontalTrafficAnimation.h"

HorizontalTrafficAnimation::HorizontalTrafficAnimation(bool leftToRight) :
  TrafficAnimation(4),
  leftToRight(leftToRight)
{
}

void HorizontalTrafficAnimation::render(LedMatrix &ledMatrix, unsigned long speed)
{
  frameid_t frameIndex = TrafficAnimation::getFrameIndex(speed);
  if (!this->leftToRight) frameIndex = frameCount - 1 - frameIndex;
  for (uint8_t x = 0; x < 4; ++x)
  {
    ledMatrix.setPixel(x + (this->leftToRight ? 0 : 1), 2, frameIndex == x);
    ledMatrix.setPixel(x + (this->leftToRight ? 1 : 0), 3, frameIndex == x);
    ledMatrix.setPixel(x + (this->leftToRight ? 0 : 1), 4, frameIndex == x);
  }
  ledMatrix.setPixel(2, 0, true);
}
