#ifndef INCLUDE_STAULU_RIGHTTRAFFICANIMATION_H
#define INCLUDE_STAULU_RIGHTTRAFFICANIMATION_H

#include "../TrafficAnimation.h"
#include "../../Hardware/LedMatrix.h"

class RightTrafficAnimation: public TrafficAnimation
{
  public:
    RightTrafficAnimation(bool towardsTarget);
    void render(LedMatrix &ledMatrix, unsigned long speed);
  private:
    bool towardsTarget;
};

#endif // INCLUDE_STAULU_RIGHTTRAFFICANIMATION_H
