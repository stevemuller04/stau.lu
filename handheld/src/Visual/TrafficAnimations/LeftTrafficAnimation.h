#ifndef INCLUDE_STAULU_LEFTTRAFFICANIMATION_H
#define INCLUDE_STAULU_LEFTTRAFFICANIMATION_H

#include "../TrafficAnimation.h"
#include "../../Hardware/LedMatrix.h"

class LeftTrafficAnimation: public TrafficAnimation
{
  public:
    LeftTrafficAnimation(bool towardsTarget);
    void render(LedMatrix &ledMatrix, unsigned long speed);
  private:
    bool towardsTarget;
};

#endif // INCLUDE_STAULU_LEFTTRAFFICANIMATION_H
