#include "mqtt.h"

MqttClient *mqtt_messager = NULL;
WiFiClient network;

void wifi_setup(){
    char ssid[] = WIFI_SSID;
    char pass[] = WIFI_PASS;

    // Connect to Wifi
    WiFi.begin(ssid, pass);
    while ( WiFi.status() != WL_CONNECTED) {
        delay(1000);
    }
}

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


void mqtt_setup(){
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
    mqtt_messager = new MqttClient(
        mqttOptions, *mqttLogger, *mqttSystem, *mqttNetwork, *mqttSendBuffer,
        *mqttRecvBuffer, *mqttMessageHandlers
    );
}


void mqtt_reconnect(){
    // char mqtt_user[] = MQTT_USER;
    // char mqtt_pass[] = MQTT_PASS;
    char mqtt_host[] = MQTT_HOST;
    uint16_t mqtt_port = MQTT_PORT;
    char mqtt_clientid[] = MQTT_CLIENT_ID;
    char mqtt_topic_pub_config[] = MQTT_TOPIC_SUB_CONFIG;

    // Check connection status
    if (!mqtt_messager->isConnected()) {
        // Close connection if exists
        network.stop();
        // Re-establish TCP connection with MQTT broker
        network.connect(mqtt_host, mqtt_port);
        if (!network.connected()) {
            delay(5000);
            ESP.reset();
        }
        // Start new MQTT connection
        MqttClient::ConnectResult connectResult;
        // Connect
        {
            MQTTPacket_connectData options = MQTTPacket_connectData_initializer;
            options.MQTTVersion = 4;
            options.clientID.cstring = (char*)mqtt_clientid;
            options.cleansession = true;
            options.keepAliveInterval = 15; // 15 seconds
            MqttClient::Error::type rc = mqtt_messager->connect(options, connectResult);
            if (rc != MqttClient::Error::SUCCESS) {
                return;
            }
        }
        {
            // Subscribe
            {
            MqttClient::Error::type rc = mqtt_messager->subscribe(
                mqtt_topic_pub_config, MqttClient::QOS0, processMessage
            );
            if (rc != MqttClient::Error::SUCCESS) {
                mqtt_messager->disconnect();
                return;
            }
        }
        }
        Serial.println("MQTT connected");
    }
    else{
        Serial.println("MQTT not connected");
    }
}


//////////////////// Message handling
void processMessage(MqttClient::MessageData& md) {
    const MqttClient::Message& msg = md.message;
    char payload[msg.payloadLen + 1];
    memcpy(payload, msg.payload, msg.payloadLen);
    payload[msg.payloadLen] = '\0';
}

void publishMessageData(char *section, char *msg){
    char device_name[] = DEVICE_NAME;
    char mqtt_topic_pub_data[] = MQTT_TOPIC_PUB_DATA;

    char mqtt_topic_msg[100] = "esp8266/topictest";
    // sprintf(mqtt_topic_msg, device_name + mqtt_topic_pub_data + *section);
    
    char* buf = msg;
    MqttClient::Message message;
    message.qos = MqttClient::QOS0;
    message.retained = false;
    message.dup = false;
    message.payload = (void*) buf;
    message.payloadLen = strlen(buf);
    mqtt_messager->publish(mqtt_topic_msg, message);
}

//////////////////// Message building
// TODO
