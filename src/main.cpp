// Includes
#include <Arduino.h>
#include "configuration.h"
#include "utils.h"
#include "mqtt.h"

void setup() {
  char ssid[] = WIFI_SSID;
  char pass[] = WIFI_PASS;

  char buffer[40];

  // PIN mode
  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(LED_BUILTIN, HIGH);

  // Connect to Wifi
  WiFi.begin(ssid, pass);
  while ( WiFi.status() != WL_CONNECTED) {
    delay(TICK_LENGTH_MS);
  }
  // IPAddress ip = WiFi.localIP();

  // Connect to MQTT Broker
  // if (!mqttclient.connected()) {
  //   mqttclient.connect();
  // }

  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  static uint32_t tick_counter = 0;
  // static float temp = 0;
  // static float hum = 0;

  // Reboot board if MQTT or WIFI is not connected
  if (!mqtt->isConnected() || WiFi.status() != WL_CONNECTED) {
    ESP.restart();
  }

  // Update LCD
  if (! (tick_counter % (tick_1s*5))){
    // temp = az3166ReadTemperature();
    // hum = az3166ReadHumidity();
    // pres = az3166ReadPressure();
  }

  // Send MQTT message
  if (! (tick_counter % (tick_1s*5))){
  // TODO: send message every minute
  //if (! (tick_counter % tick_1m)){
    // topicSensors.publish("test");
  }

  if (! (tick_counter % tick_1s)){
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }

  delay(TICK_LENGTH_MS);
  tick_counter++;
}