#ifndef INCLUDE_STAULU_HORIZONTALTRAFFICANIMATION_H
#define INCLUDE_STAULU_HORIZONTALTRAFFICANIMATION_H

#include "../TrafficAnimation.h"
#include "../../Hardware/LedMatrix.h"

class HorizontalTrafficAnimation: public TrafficAnimation
{
  public:
    HorizontalTrafficAnimation(bool leftToRight);
    void render(LedMatrix &ledMatrix, unsigned long speed);
  private:
    bool leftToRight;
};

#endif // INCLUDE_STAULU_HORIZONTALTRAFFICANIMATION_H
