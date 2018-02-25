#ifndef INCLUDE_STAULU_TRAFFICVISUALISER_H
#define INCLUDE_STAULU_TRAFFICVISUALISER_H

#include "../types.h"
#include "../Hardware/LedMatrix.h"
#include "../Hardware/RgbLed.h"
#include "../Model/TrafficManager.h"
#include "../Visual/TrafficAnimation.h"

/**
 * Class which visualises the traffic for specific routes, and which permits cycling through the available routes.
 */
class TrafficVisualiser
{
  public:
    /**
     * Initialises the class.
     * \param trafficMgr The traffic manager instance that is used to retrieve the traffic information to display.
     */
    TrafficVisualiser(TrafficManager &trafficMgr);

    /**
     * Adds a route that can be cycled through.
     * \param trafficId The identifier of the route.
     * \param animation The animation that is rendered when the route is selected.
     */
    void add(trafficid_t trafficId, TrafficAnimation &animation);

    /**
     * Shows the traffic of the next route in line.
     */
    trafficid_t showNext();

    /**
     * Resets the animation that is currently displayed.
     */
    void reset();

    /**
     * Renders the traffic status of the currently selected route.
     * This method must be regularly called (such as in the Kniwwelino::loop() function).
     * \param ledMatrix The LED matrix where the traffic is rendered to.
     * \param statusLed The RGB LED where the traffic status is rendered to.
     */
    void render(LedMatrix &ledMatrix, RgbLed &statusLed);

  private:
    TrafficManager *trafficMgr;
    trafficid_t current;
    bool matrixNeedsReset;
    TrafficAnimation *animations[LIMIT_TRAFFIC_MAXID];
};

#endif // INCLUDE_STAULU_TRAFFICVISUALISER_H
