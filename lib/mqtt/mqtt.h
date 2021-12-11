
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "configuration.h"
#include "utils.h"

#ifndef _MQTT_H_
#define _MQTT_H_

#define WIFI_RETRY_MS 5000
#define MQTT_RETRY_MS 5000

void wifi_connect();
void wifi_reconnect();

void mqtt_reconnect();
void mqtt_loop();

void callback(char *led_control, byte *payload, unsigned int length);
void mqtt_publish_message(char *section, char *payload, boolean retain);

#endif
