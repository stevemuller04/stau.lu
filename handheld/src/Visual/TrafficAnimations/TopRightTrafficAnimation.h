#ifndef INCLUDE_STAULU_TOPRIGHTTRAFFICANIMATION_H
#define INCLUDE_STAULU_TOPRIGHTTRAFFICANIMATION_H

#include "../TrafficAnimation.h"
#include "../../Hardware/LedMatrix.h"

class TopRightTrafficAnimation: public TrafficAnimation
{
  public:
    TopRightTrafficAnimation(bool towardsTarget);
    void render(LedMatrix &ledMatrix, unsigned long speed);
  private:
    bool towardsTarget;
};

#endif // INCLUDE_STAULU_TOPRIGHTTRAFFICANIMATION_H
