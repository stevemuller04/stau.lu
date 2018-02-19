#ifndef INCLUDE_STAULU_TRAFFICVISUALISER_H
#define INCLUDE_STAULU_TRAFFICVISUALISER_H

#include "../types.h"
#include "../Hardware/LedMatrix.h"
#include "../Hardware/RgbLed.h"
#include "../Model/TrafficManager.h"
#include "../Visual/TrafficAnimation.h"

class TrafficVisualiser
{
  public:
    TrafficVisualiser(TrafficManager &trafficMgr);
    void add(trafficid_t trafficId, TrafficAnimation &animation);
    trafficid_t showNext();
    void reset();
    void render(LedMatrix &ledMatrix, RgbLed &statusLed);
  private:
    TrafficManager *trafficMgr;
    trafficid_t current;
    bool matrixNeedsReset;
    TrafficAnimation *animations[LIMIT_TRAFFIC_MAXID];
};

#endif // INCLUDE_STAULU_TRAFFICVISUALISER_H
