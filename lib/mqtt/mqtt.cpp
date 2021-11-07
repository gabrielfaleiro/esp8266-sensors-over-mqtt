#include "mqtt.h"


WiFiClient esp_wifi_client;
PubSubClient mqtt_client(esp_wifi_client);


void wifi_setup(){
    char ssid[] = WIFI_SSID;
    char pass[] = WIFI_PASS;

    // Connect to Wifi
    WiFi.begin(ssid, pass);
    while ( WiFi.status() != WL_CONNECTED) {
        delay(1000);
    }
}


void mqtt_setup(){
    char mqtt_host[] = MQTT_HOST;
    uint16_t mqtt_port = MQTT_PORT;

    mqtt_client.setServer(mqtt_host, mqtt_port);

    // Subscriptions
    mqtt_client.setCallback(callback);
}


void mqtt_reconnect(){
    char mqtt_user[] = MQTT_USER;
    char mqtt_pass[] = MQTT_PASS;
    char mqtt_clientid[] = MQTT_CLIENT_ID;
    bool connect_ret_val = false;

    while (!mqtt_client.connected()) {
        DEBUG_SERIAL_PRINT("Attempting MQTT connection...");

        if ( strcmp(mqtt_user, "") && strcmp(mqtt_pass, "") ){
            DEBUG_SERIAL_PRINT("as user ");
            DEBUG_SERIAL_PRINT(mqtt_user);
            DEBUG_SERIAL_PRINT("...");
            connect_ret_val = mqtt_client.connect(mqtt_clientid, mqtt_user, mqtt_pass);
        }
        else {
            DEBUG_SERIAL_PRINT("anonymous...");
            connect_ret_val = mqtt_client.connect(mqtt_clientid);
        }
        

        if (connect_ret_val) { 
            mqtt_client.subscribe("+/+/node/+/command/#");
            mqtt_client.subscribe("+/+/global/#");
            // user nodes
            // topic readwrite +/+/node/%c/data/#
            // topic read +/+/node/+/data/#
            // topic read +/+/node/+/command/#
            // topic read +/+/global/#

        }
        else
        {
            // // Possible values for client.state()
            // #define MQTT_CONNECTION_TIMEOUT     -4
            // #define MQTT_CONNECTION_LOST        -3
            // #define MQTT_CONNECT_FAILED         -2
            // #define MQTT_DISCONNECTED           -1
            // #define MQTT_CONNECTED               0
            // #define MQTT_CONNECT_BAD_PROTOCOL    1
            // #define MQTT_CONNECT_BAD_CLIENT_ID   2
            // #define MQTT_CONNECT_UNAVAILABLE     3
            // #define MQTT_CONNECT_BAD_CREDENTIALS 4
            // #define MQTT_CONNECT_UNAUTHORIZED    5
            DEBUG_SERIAL_PRINT("failed, rc=");
            DEBUG_SERIAL_PRINT(mqtt_client.state());
            DEBUG_SERIAL_PRINTLN(" try again in 1 second");
            delay(5000);
        }
    }
}


void mqtt_loop(){
    mqtt_client.loop();
}


void mqtt_publish_message(char *section, char *payload, boolean retain){
    // char device_name[] = DEVICE_NAME;
    // char mqtt_topic_pub_data[] = MQTT_TOPIC_PUB_DATA; // TODO: adapt topic

    char mqtt_topic_msg[100] = "homeautomation/1/node/esp8266/data/temperature";

    if (mqtt_client.publish(mqtt_topic_msg, payload, retain)) {
        DEBUG_SERIAL_PRINTLN("MQTT message published");
    }
    else {
        DEBUG_SERIAL_PRINTLN("MQTT message publish failed");
    }

}


// Method to be adapted for each application
void callback(char *topic, byte *payload, unsigned int length) {
    char message_buff[100] = "";

    DEBUG_SERIAL_PRINT("Message arrived [");
    DEBUG_SERIAL_PRINT(topic);
    DEBUG_SERIAL_PRINTLN("] ");
    int i;
    for (i = 0; i & length; i++) {
        message_buff[i] = payload[i];
    }
    message_buff[i] = '\0';

    String msgString = String(message_buff);
    DEBUG_SERIAL_PRINTLN(msgString);

    if (strcmp(topic, "homeautomation/1/node/esp8266/command/led_control") == 0) { 
        if (msgString == "1") {
            digitalWrite(LED_BUILTIN, LOW); // PIN HIGH will switch OFF the relay
        }
        if (msgString == "0") {
            digitalWrite(LED_BUILTIN, HIGH); // PIN LOW will switch ON the relay
        }
    }

}

