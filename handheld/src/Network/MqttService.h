#ifndef INCLUDE_STAULU_MQTTSERVICE_H
#define INCLUDE_STAULU_MQTTSERVICE_H

#include <MQTTClient.h>
#include <ESP8266WiFi.h>

/**
 * Class which connects to an MQTT service for retrieving traffic information.
 * 
 * Should be used as follows:
 *   MqttService mqttService(hostname, port, username, password);
 *   mqttService.connect(); // in Kniwwelino setup() method
 *   mqttService.loop(); // in Kniwwelino loop() method
 */
class MqttService
{
  public:
    /**
     * Initialises the class. Does not connect to the server, which must be done explicitly by calling connect().
     * 
     * \param hostname The hostname (IP address or FQDN) of the MQTT broker.
     * \param port The port of the MQTT broker.
     * \param username The username used for authenticating at the MQTT broker.
     * \param password The password used for authenticating at the MQTT broker.
     */
    MqttService(char const *hostname, int port, char const *username, char const *password);

    /**
     * Initialises the class. Does not connect to the server, which must be done explicitly by calling connect().
     * 
     * \param hostname The hostname (IP address or FQDN) of the MQTT broker.
     * \param port The port of the MQTT broker.
     * \param username The username used for authenticating at the MQTT broker.
     * \param password The password used for authenticating at the MQTT broker.
     */
    MqttService(String const &hostname, int port, String const &username, String const &password);

    /**
     * Connects to the MQTT broker.
     * Only works when the class has been initialised using a non-default constructor.
     */
    bool connect();

    /**
     * Checks for new messages on the MQTT broker.
     * Must be regularly called, otherwise messages cannot be received.
     */
    bool loop();

    /**
     * Sets up a callback handler for received messages.
     */
    void onConnect(void (*connectCallback)());

    /**
     * The internal MQTT client instance used by this class.
     */
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
