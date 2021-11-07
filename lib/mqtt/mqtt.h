
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "configuration.h"
#include "utils.h"

#ifndef _MQTT_H_
#define _MQTT_H_

void wifi_setup();
// void wifi_reconnect(); // TODO

void mqtt_setup();
void mqtt_reconnect();
void mqtt_loop();

void callback(char *led_control, byte *payload, unsigned int length);
void mqtt_publish_message(char *section, char *payload, boolean retain);

#endif
