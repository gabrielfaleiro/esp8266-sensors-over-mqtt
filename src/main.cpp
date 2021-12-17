// Includes
#include <Arduino.h>
#include <arduino-timer.h>
#include "configuration.h"
#include "utils.h"
#include "mqtt.h"
#include "dht22.h"


// Global variables
auto timer = timer_create_default();


bool publish_dth22(void *) {

  char topic_temp[20] = "temperature";
  char topic_rh[20] = "relative_humidity";
  char payload_temp[10] = "";
  char payload_rh[10] = "";
  int16_t temp = 0;
  int16_t rh = 0;

  dht22_read(&temp, &rh);

  sprintf(payload_temp, "%d", temp);
  sprintf(payload_rh, "%d", rh);

  mqtt_publish_message(topic_temp, payload_temp, false);
  mqtt_publish_message(topic_rh, payload_rh, false);

  return true; // to repeat the action - false to stop
}


void setup() {
  DEBUG_SERIAL_SETUP(9600);
  DEBUG_SERIAL_PRINTLN("Setting up device...");

  // Network setup
  wifi_connect();
  mqtt_reconnect();
  dht22_setup();

  // PIN mode
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  // Timer functions
  timer.every(DTH_SAMPLING_MS, publish_dth22);

  DEBUG_SERIAL_PRINTLN("Running main loop...");
}

void loop() {
  timer.tick();

  wifi_reconnect();
  mqtt_reconnect();
  mqtt_loop();
  
}