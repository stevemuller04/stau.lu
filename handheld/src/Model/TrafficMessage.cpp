#include "TrafficMessage.h"

bool TrafficMessage::tryParse(String const &str)
{
  if (str.length() < 1)
    return false;
  switch (str.charAt(0)) // version
  {
    default: return false;
    case '$': return tryParseVersion1(str);
  }
}

bool TrafficMessage::tryParseVersion1(String const &str)
{
  if (str.length() < 6)
    return false;
  char id1 = str.charAt(1);
  char id0 = str.charAt(2);
  char delay1 = str.charAt(4);
  char delay0 = str.charAt(5);

  if (id0 < '0' || id0 > '9' || id1 < '0' || id1 > '9')
    return false;
  if (delay0 < '0' || delay0 > '9' || delay1 < '0' || delay1 > '9')
    return false;

  id = (id1 - '0') * 10 + (id0 - '0');
  status = str.charAt(3);
  delay = (delay1 - '0') * 10 + (delay0 - '0');
  return true;
}
