#ifndef INCLUDE_STAULU_TRAFFICMESSAGE_H
#define INCLUDE_STAULU_TRAFFICMESSAGE_H

#include <Arduino.h>
#include "../types.h"

class TrafficMessage
{
  public:
    trafficid_t id;
    char status;
    uint8_t delay;
    bool tryParse(String const &str);
  private:
    bool tryParseVersion1(String const &str);
};

#endif // INCLUDE_STAULU_TRAFFICMESSAGE_H
