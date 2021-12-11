#include <Arduino.h>
//#include <Adafruit_Sensor.h>
#include <DHT.h>
#include "configuration.h"
#include "utils.h"


#ifndef _DHT11_H_
#define _DHT11_H_

void dht11_setup();
void dht11_read(int16_t *temp, int16_t *rh);

#endif
