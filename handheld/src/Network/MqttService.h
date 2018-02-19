#ifndef INCLUDE_STAULU_MQTTSERVICE_H
#define INCLUDE_STAULU_MQTTSERVICE_H

#include <MQTTClient.h>
#include <ESP8266WiFi.h>

class MqttService
{
  public:
    MqttService(char const *hostname, int port, char const *username, char const *password);
    MqttService(String const &hostname, int port, String const &username, String const &password);
    bool connect();
    bool loop();
    void onConnect(void (*connectCallback)());
    MQTTClient client;
  private:
    String getMqttId();
    bool _connect();
    WiFiClient wifiClient;
    String hostname, username, password;
    int port;
    void (*connectCallback)();
};

#endif // INCLUDE_STAULU_MQTTSERVICE_H
