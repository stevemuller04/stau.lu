#ifndef INCLUDE_STAULU_UPTRAFFICANIMATION_H
#define INCLUDE_STAULU_UPTRAFFICANIMATION_H

#include "../TrafficAnimation.h"
#include "../../Hardware/LedMatrix.h"

class UpTrafficAnimation: public TrafficAnimation
{
  public:
    UpTrafficAnimation(bool towardsTarget);
    void render(LedMatrix &ledMatrix, unsigned long speed);
  private:
    bool towardsTarget;
};

#endif // INCLUDE_STAULU_UPTRAFFICANIMATION_H
