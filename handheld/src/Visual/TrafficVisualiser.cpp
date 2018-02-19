#include "../types.h"
#include "../constants.h"
#include "TrafficVisualiser.h"

TrafficVisualiser::TrafficVisualiser(TrafficManager &trafficMgr) :
  trafficMgr(&trafficMgr),
  current(-1),
  matrixNeedsReset(false),
  animations { nullptr }
{
}

void TrafficVisualiser::add(trafficid_t trafficId, TrafficAnimation &animation)
{
  if (trafficId >= 0 && trafficId < LIMIT_TRAFFIC_MAXID)
    animations[trafficId] = &animation;
}

trafficid_t TrafficVisualiser::showNext()
{
  // Determine next animation
  trafficid_t const previous = current;
  while ((current = (current + 1) % LIMIT_TRAFFIC_MAXID) != previous && animations[current] == nullptr) ;

  // Reset LED matrix and animation
  reset();

  return current;
}

void TrafficVisualiser::reset()
{
  matrixNeedsReset = true;
  if (current >= 0 && animations[current] != nullptr)
    animations[current]->reset();
}

void TrafficVisualiser::render(LedMatrix &ledMatrix, RgbLed &statusLed)
{
  // Don't render if no animation has been selected
  if (current < 0) return;

  // Determine animation speed
  unsigned long speed;

  // Show status LED
  switch (trafficMgr->getStatus(current))
  {
    case TRAFFIC_STATUS_FLUENT:
      statusLed.setColor(0, 0x44, 0); // green
      speed = TIMING_ANIMATION_SPEED_0;
      break;
    case TRAFFIC_STATUS_JAM1:
      statusLed.setColor(0x44, 0x22, 0); // yellow
      speed = TIMING_ANIMATION_SPEED_1;
      break;
    case TRAFFIC_STATUS_JAM2:
      statusLed.setColor(0x44, 0x11, 0); // orange
      speed = TIMING_ANIMATION_SPEED_2;
      break;
    case TRAFFIC_STATUS_JAM3:
      statusLed.setColor(0x44, 0, 0); // red
      speed = TIMING_ANIMATION_SPEED_3;
      break;
   default:
      statusLed.setColor(0x22, 0x22, 0x22); // white
      speed = TIMING_ANIMATION_SPEED_0;
      break;
  }

  // Clear matrix if necessary
  if (matrixNeedsReset)
  {
    ledMatrix.clear();
    matrixNeedsReset = false;
  }

  // Show animation
  if (animations[current] != nullptr)
    animations[current]->render(ledMatrix, speed);
}
