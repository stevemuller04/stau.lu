#ifndef INCLUDE_STAULU_DIAGONALTRAFFICANIMATION_H
#define INCLUDE_STAULU_DIAGONALTRAFFICANIMATION_H

#include "../TrafficAnimation.h"
#include "../../Hardware/LedMatrix.h"

class DiagonalTrafficAnimation: public TrafficAnimation
{
  public:
    DiagonalTrafficAnimation(bool topDown);
    void render(LedMatrix &ledMatrix, unsigned long speed);
  private:
    bool topDown;
};

#endif // INCLUDE_STAULU_DIAGONALTRAFFICANIMATION_H
