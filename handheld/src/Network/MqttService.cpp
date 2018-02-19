#include "../constants.h"
#include "MqttService.h"

MqttService::MqttService(char const *hostname, int port, char const *username, char const *password) :
  hostname(String(hostname)),
  port(port),
  username(String(username)),
  password(String(password)),
  connectCallback(nullptr)
{
}

MqttService::MqttService(String const &hostname, int port, String const &username, String const &password) :
  hostname(hostname),
  port(port),
  username(username),
  password(password),
  connectCallback(nullptr)
{
}

bool MqttService::connect()
{
  client.begin(hostname.c_str(), port, wifiClient);
  return _connect();
}

bool MqttService::_connect()
{
  String id = getMqttId();
  for (uint8_t trial = 0; trial < LIMIT_MQTT_NUMRECONNECT && !client.connect(id.c_str(), username.c_str(), password.c_str()); ++trial)
    delay(TIMING_MQTT_RECONNECT);

  if (client.connected())
  {
    if (this->connectCallback != nullptr)
      this->connectCallback();
    return true;
  }
  else
  {
    return false;
  }
}

bool MqttService::loop()
{
  return client.loop() && (client.connected() || _connect());
}

void MqttService::onConnect(void (*connectCallback)())
{
  this->connectCallback = connectCallback;
}

String MqttService::getMqttId()
{
  String mac = WiFi.macAddress();
  mac.replace(":", "");
  return "Kniwwelino_" + mac.substring(6);
}
