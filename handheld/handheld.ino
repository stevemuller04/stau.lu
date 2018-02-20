#include <WiFiManager.h>
#include <Kniwwelino.h>
#include "config.h"
#include "src/types.h"
#include "src/Hardware/LedMatrix.h"
#include "src/Hardware/Buttons.h"
#include "src/Network/MqttService.h"
#include "src/Model/TrafficManager.h"
#include "src/Model/TrafficMessage.h"
#include "src/Visual/TrafficVisualiser.h"
#include "src/Visual/TrafficAnimation.h"
#include "src/Visual/TrafficAnimations/RightTrafficAnimation.h"
#include "src/Visual/TrafficAnimations/TopRightTrafficAnimation.h"
#include "src/Visual/TrafficAnimations/HorizontalTrafficAnimation.h"
#include "src/Visual/TrafficAnimations/UpTrafficAnimation.h"
#include "src/Visual/TrafficAnimations/DiagonalTrafficAnimation.h"
#include "src/Visual/TrafficAnimations/LeftTrafficAnimation.h"
#include "src/Visual/TrafficAnimations/DownTrafficAnimation.h"

LedMatrix matrix;
Buttons buttons;
RgbLed statusLed;
MqttService mqtt(CONFIG_MQTT_HOSTNAME, CONFIG_MQTT_PORT, CONFIG_MQTT_USERNAME, CONFIG_MQTT_PASSWORD);
TrafficManager trafficMgr;
uint8_t trafficVisualiserMode = 0; // direction 0 (heaviest traffic in the morning) or direction 1 (heaviest traffic in the evening)
TrafficVisualiser trafficVisualiser0(trafficMgr);
TrafficVisualiser trafficVisualiser1(trafficMgr);
RightTrafficAnimation anim0(true);
RightTrafficAnimation anim1(false);
TopRightTrafficAnimation anim2(true);
TopRightTrafficAnimation anim3(false);
HorizontalTrafficAnimation anim4(true);
HorizontalTrafficAnimation anim5(false);
UpTrafficAnimation anim6(true);
UpTrafficAnimation anim7(false);
DiagonalTrafficAnimation anim8(true);
DiagonalTrafficAnimation anim9(false);
LeftTrafficAnimation anim10(true);
LeftTrafficAnimation anim11(false);
DownTrafficAnimation anim12(true);
DownTrafficAnimation anim13(false);

void setup()
{
  // Initialise hardware components
  buttons.init();
  matrix.init();
  statusLed.init();
  // Reset
  matrix.render();
  statusLed.render();

  // Initialise traffic info related classes
  trafficVisualiser0.add(0, anim0);
  trafficVisualiser1.add(1, anim1);
  trafficVisualiser0.add(2, anim2);
  trafficVisualiser1.add(3, anim3);
  trafficVisualiser0.add(4, anim4);
  trafficVisualiser1.add(5, anim5);
  trafficVisualiser0.add(6, anim6);
  trafficVisualiser1.add(7, anim7);
  trafficVisualiser0.add(8, anim8);
  trafficVisualiser1.add(9, anim9);
  trafficVisualiser0.add(10, anim10);
  trafficVisualiser1.add(11, anim11);
  trafficVisualiser0.add(12, anim12);
  trafficVisualiser1.add(13, anim13);
  trafficVisualiser0.showNext();
  trafficVisualiser1.showNext();

  // Establish WiFi connection, or set up WiFi access point
  // where the user can connect to in order to configure WiFi
  WiFiManager wifiManager;
  wifiManager.setAPCallback(wifiConfigModeCallback);
  wifiManager.setSaveConfigCallback(wifiSaveConfigCallback);
  wifiManager.autoConnect("stau.lu"); // blocks until a connection has been made

  // Set up MQTT client
  mqtt.onConnect(mqttConnected);
  mqtt.client.onMessage(mqttMessageReceived);
  mqtt.connect();
}

void wifiConfigModeCallback(WiFiManager *wiFiManager) {
  statusLed.setColor(0, 0, 0xFF);
  statusLed.render();
}

void wifiSaveConfigCallback() {
  statusLed.setColor(0, 0xFF, 0);
  statusLed.render();
  delay(1500);
  statusLed.setColor(0, 0, 0);
  statusLed.render();
}

void mqttConnected()
{
  mqtt.client.subscribe(CONFIG_MQTT_TOPIC);
}

void mqttMessageReceived(String &topic, String &payload)
{
  TrafficMessage msg;
  if (msg.tryParse(payload))
    trafficMgr.update(msg);
}

void loop()
{
  mqtt.loop();
  buttons.update();

  if (buttons.isButton2Clicked())
  {
    trafficVisualiserMode = (trafficVisualiserMode + 1) % 2;
    trafficVisualiser0.reset();
    trafficVisualiser1.reset();
  }
  if (buttons.isButton1Clicked())
  {
    trafficid_t id0 = trafficVisualiser0.showNext();
    trafficid_t id1 = trafficVisualiser1.showNext();
  }
  (trafficVisualiserMode == 0 ? trafficVisualiser0 : trafficVisualiser1).render(matrix, statusLed);

  matrix.render();
  statusLed.render();
}
