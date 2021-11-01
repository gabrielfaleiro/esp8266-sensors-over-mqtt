
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <MqttClient.h>
#include "configuration.h"

#ifndef _MQTT_H_
#define _MQTT_H_

void wifi_setup();
void mqtt_setup();
void mqtt_reconnect();

void processMessage(MqttClient::MessageData& md);
void publishMessageData(char *section, char *msg);

#endif
