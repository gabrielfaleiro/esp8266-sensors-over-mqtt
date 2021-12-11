#include "dht11.h"

DHT dht(DTH11_DATA_PIN, DHT11);


// void dht11_read(int16_t *temp, int16_t *rh){
//     *temp = 236;
//     *rh = 468;
// }


void dht11_setup(){
    dht.begin();
}


void dht11_read(int16_t *temp, int16_t *rh){
    float temperature = 0;
    float humidity = 0;

    temperature = dht.readTemperature();
    humidity = dht.readHumidity();

    DEBUG_SERIAL_PRINT("Read DTH11 temperature=");
    DEBUG_SERIAL_PRINTLN(temperature);
    DEBUG_SERIAL_PRINT("Read DTH11 humidity=");
    DEBUG_SERIAL_PRINTLN(humidity);

    if (isnan(temperature) || isnan(humidity)) {
        DEBUG_SERIAL_PRINTLN("Failed to read from DHT sensor");
        temperature = -99.9;
        humidity = -1.0;
    }

    *temp = (int16_t) temperature * 10;
    *rh = (int16_t) humidity * 10;
}

