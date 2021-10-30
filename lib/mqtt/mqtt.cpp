#include "mqtt.h"

void setupMqtt(){
    // Setup MqttClient
    MqttClient::System *mqttSystem = new System;
    MqttClient::Logger *mqttLogger = new MqttClient::LoggerImpl<HardwareSerial>(Serial);
    MqttClient::Network * mqttNetwork = new MqttClient::NetworkClientImpl<WiFiClient>(network, *mqttSystem);
    //// Make 128 bytes send buffer
    MqttClient::Buffer *mqttSendBuffer = new MqttClient::ArrayBuffer<128>();
    //// Make 128 bytes receive buffer
    MqttClient::Buffer *mqttRecvBuffer = new MqttClient::ArrayBuffer<128>();
    //// Allow up to 2 subscriptions simultaneously
    MqttClient::MessageHandlers *mqttMessageHandlers = new MqttClient::MessageHandlersImpl<2>();
    //// Configure client options
    MqttClient::Options mqttOptions;
    ////// Set command timeout to 10 seconds
    mqttOptions.commandTimeoutMs = 10000;
    //// Make client object
    mqtt = new MqttClient(
        mqttOptions, *mqttLogger, *mqttSystem, *mqttNetwork, *mqttSendBuffer,
        *mqttRecvBuffer, *mqttMessageHandlers
    );
}


// // Check connection status
// 	if (!mqtt->isConnected()) {
// 		// Close connection if exists
// 		network.stop();
// 		// Re-establish TCP connection with MQTT broker
// 		LOG_PRINTFLN("Connecting");
// 		network.connect("test.mosquitto.org", 1883);
// 		if (!network.connected()) {
// 			LOG_PRINTFLN("Can't establish the TCP connection");
// 			delay(5000);
// 			ESP.reset();
// 		}
// 		// Start new MQTT connection
// 		MqttClient::ConnectResult connectResult;
// 		// Connect
// 		{
// 			MQTTPacket_connectData options = MQTTPacket_connectData_initializer;
// 			options.MQTTVersion = 4;
// 			options.clientID.cstring = (char*)MQTT_ID;
// 			options.cleansession = true;
// 			options.keepAliveInterval = 15; // 15 seconds
// 			MqttClient::Error::type rc = mqtt->connect(options, connectResult);
// 			if (rc != MqttClient::Error::SUCCESS) {
// 				LOG_PRINTFLN("Connection error: %i", rc);
// 				return;
// 			}
// 		}
// 		{
// 			// Add subscribe here if required
// 		}
// 	} else {
// 		{
// 			// Add publish here if required
// 		}
// 		// Idle for 30 seconds
// 		mqtt->yield(30000L);
// 	}