// Includes
#include <Arduino.h>
// #include <arduino-timer.h>
#include "configuration.h"
#include "utils.h"
#include "mqtt.h"


void setup() {
  Serial.begin(9600);

  // PIN mode
  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(LED_BUILTIN, HIGH);

  wifi_setup();
  mqtt_setup();

  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  static uint32_t tick_counter = 0;
  // static float temp = 0;
  // static float hum = 0;

  // Reboot board if WIFI is not connected
  if (WiFi.status() != WL_CONNECTED) {
    ESP.restart();
  }
  mqtt_reconnect();

  // Update LCD
  if (! (tick_counter % (tick_1s*5))){
    // temp = az3166ReadTemperature();
    // hum = az3166ReadHumidity();
    // pres = az3166ReadPressure();
  }

  // Send MQTT message
  if (! (tick_counter % (tick_1s*5))){
    char section[] = "section";
    char msg[] = "hola";
    publishMessageData(section, msg);
    Serial.println("MQTT message sent");
  }

  if (! (tick_counter % tick_1s)){
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }

  delay(TICK_LENGTH_MS);
  tick_counter++;
}