#include "DiagonalTrafficAnimation.h"

DiagonalTrafficAnimation::DiagonalTrafficAnimation(bool topDown) :
  TrafficAnimation(4),
  topDown(topDown)
{
}

void DiagonalTrafficAnimation::render(LedMatrix &ledMatrix, unsigned long speed)
{
  frameid_t frameIndex = TrafficAnimation::getFrameIndex(speed);
  if (!this->topDown) frameIndex = frameCount - 1 - frameIndex;
  for (uint8_t d = 0; d < 4; ++d)
  {
    ledMatrix.setPixel(3 - d, d, frameIndex == d);
    ledMatrix.setPixel(4 - d, d + 1, frameIndex == d);
    ledMatrix.setPixel(3 - d + (this->topDown ? 0 : 1), d + (this->topDown ? 1 : 0), frameIndex == d);
  }
  ledMatrix.setPixel(0, 0, true);
}
