#ifndef INCLUDE_STAULU_TRAFFICMESSAGE_H
#define INCLUDE_STAULU_TRAFFICMESSAGE_H

#include <Arduino.h>
#include "../types.h"

/**
 * A traffic message holds information about the traffic situation of a specific route.
 */
class TrafficMessage
{
  public:
    /**
     * The identifier of the route.
     */
    trafficid_t id;

    /**
     * The traffic situation (fluent, traffic jam, etc.) for the route.
     * One of the TRAFFIC_STATUS_* constants.
     */
    char status;

    /**
     * The delay (in minutes) caused by traffic for the route.
     */
    uint8_t delay;

    /**
     * Tries to parse a string as a traffic message.
     * Returns true if and only if the parsing was successful.
     * 
     * This method overwrites the values stored in this class!
     * When successful, the fields of this class will reflect the information stored in the string.
     * If the parsing was not successful, the fields of this class are in an undefined state.
     */
    bool tryParse(String const &str);

  private:
    /**
     * Tries to parse a string as a traffic message, following the Traffic Message Format v1.
     * Returns true if and only if the parsing was successful.
     * 
     * This method overwrites the values stored in this class!
     * When successful, the fields of this class will reflect the information stored in the string.
     * If the parsing was not successful, the fields of this class are in an undefined state.
     */
    bool tryParseVersion1(String const &str);
};

#endif // INCLUDE_STAULU_TRAFFICMESSAGE_H
