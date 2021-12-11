// Includes
#include <Arduino.h>
#include <arduino-timer.h>
#include "configuration.h"
#include "utils.h"
#include "mqtt.h"


// Global variables
auto timer = timer_create_default();


bool publish_temp(void *) {

  char section[100] = "temperature";
  char payload[10] = "test";

  // TODO: read value and update payload

  mqtt_publish_message(section, payload, false);

  return true; // to repeat the action - false to stop
}


void setup() {  
  DEBUG_SERIAL_SETUP(9600);
  DEBUG_SERIAL_PRINTLN("Setting up device...");

  // Network setup
  wifi_connect();
  mqtt_reconnect();

  // PIN mode
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  // Timer functions
  timer.every(60000, publish_temp);

  DEBUG_SERIAL_PRINTLN("Running main loop...");
}

void loop() {
  // static float temp = 0;
  // static float hum = 0;

  timer.tick();

  // Reboot board if WIFI is not connected
  // TODO: replace with wifi_reconnect();
  if (WiFi.status() != WL_CONNECTED) {
    delay(10000);
    ESP.restart();
  }
  mqtt_reconnect();
  mqtt_loop();
  
}