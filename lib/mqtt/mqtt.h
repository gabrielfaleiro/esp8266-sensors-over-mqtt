
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <MqttClient.h>
#include "configuration.h"

#ifndef _MQTT_H_
#define _MQTT_H_

extern MqttClient *mqtt = NULL;
extern WiFiClient network;

// ============== Object to supply system functions ============================
class System: public MqttClient::System {
public:

	unsigned long millis() const {
		return ::millis();
	}

	void yield(void) {
		::yield();
	}
};

char mqtt_host[] = MQTT_HOST;
char mqtt_clientid[] = MQTT_CLIENT_ID;
char mqtt_user[] = MQTT_USER;
char mqtt_pass[] = MQTT_PASS;

void setupMqtt();

#endif
