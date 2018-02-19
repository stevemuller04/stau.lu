#ifndef INCLUDE_STAULU_DOWNTRAFFICANIMATION_H
#define INCLUDE_STAULU_DOWNTRAFFICANIMATION_H

#include "../TrafficAnimation.h"
#include "../../Hardware/LedMatrix.h"

class DownTrafficAnimation: public TrafficAnimation
{
  public:
    DownTrafficAnimation(bool towardsTarget);
    void render(LedMatrix &ledMatrix, unsigned long speed);
  private:
    bool towardsTarget;
};

#endif // INCLUDE_STAULU_DOWNTRAFFICANIMATION_H
