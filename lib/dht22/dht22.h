#include <Arduino.h>
//#include <Adafruit_Sensor.h>
#include <DHT.h>
#include "configuration.h"
#include "utils.h"


#ifndef _DHT22_H_
#define _DHT22_H_

void dht22_setup();
void dht22_read(int16_t *temp, int16_t *rh);

#endif
