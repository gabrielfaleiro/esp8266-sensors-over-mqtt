#include "dht22.h"


DHT dht22(DTH22_DATA_PIN, DHT22);


void dht22_setup(){
    dht22.begin();
}


void dht22_read(int16_t *temp, int16_t *rh){
    float temperature = 0;
    float humidity = 0;

    temperature = dht22.readTemperature();
    humidity = dht22.readHumidity();

    DEBUG_SERIAL_PRINT("Read DTH22 temperature=");
    DEBUG_SERIAL_PRINTLN(temperature);
    DEBUG_SERIAL_PRINT("Read DTH22 humidity=");
    DEBUG_SERIAL_PRINTLN(humidity);

    if (isnan(temperature) || isnan(humidity)) {
        DEBUG_SERIAL_PRINTLN("Failed to read from DHT22 sensor");
        temperature = -99.9;
        humidity = -1.0;
    }

    *temp = (int16_t) temperature * 10;
    *rh = (int16_t) humidity * 10;
}
