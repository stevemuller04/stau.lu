#include "../constants.h"
#include "TrafficManager.h"

TrafficManager::TrafficManager() :
  status { '?' }
{
}

void TrafficManager::update(TrafficMessage const &message)
{
  if (message.id >= 0 && message.id < LIMIT_TRAFFIC_MAXID)
    status[message.id] = message.status;  
}

char TrafficManager::getStatus(trafficid_t trafficId) const
{
  if (trafficId >= 0 && trafficId < LIMIT_TRAFFIC_MAXID)
    return status[trafficId];
  else
    return TRAFFIC_STATUS_UNKNOWN;
}
