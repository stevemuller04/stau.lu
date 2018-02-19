#ifndef INCLUDE_STAULU_TRAFFICMANAGER_H
#define INCLUDE_STAULU_TRAFFICMANAGER_H

#include "../types.h"
#include "../constants.h"
#include "TrafficMessage.h"

class TrafficManager
{
  public:
  	TrafficManager();
    void update(TrafficMessage const &message);
    char getStatus(trafficid_t trafficId) const;
  private:
    char status[LIMIT_TRAFFIC_MAXID];
};

#endif // INCLUDE_STAULU_TRAFFICMANAGER_H
