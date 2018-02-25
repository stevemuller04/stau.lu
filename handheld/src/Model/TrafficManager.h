#ifndef INCLUDE_STAULU_TRAFFICMANAGER_H
#define INCLUDE_STAULU_TRAFFICMANAGER_H

#include "../types.h"
#include "../constants.h"
#include "TrafficMessage.h"

/**
 * Class which holds the traffic status for all routes.
 */
class TrafficManager
{
  public:
    /**
     * Default constructor.
     * Initialises the class.
     */
    TrafficManager();

    /**
     * Updates the traffic status for a given route by reading it from the given traffic message.
     */
    void update(TrafficMessage const &message);

    /**
     * Gets the traffic status for the route with the given identifier.
     * The returned value will be one of the TRAFFIC_STATUS_* constants.
     */
    char getStatus(trafficid_t trafficId) const;

  private:
    char status[LIMIT_TRAFFIC_MAXID];
};

#endif // INCLUDE_STAULU_TRAFFICMANAGER_H
