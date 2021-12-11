#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include "configuration.h"
#include "utils.h"


#ifndef _DTH11_H_
#define _DTH11_H_

void dth11_setup();
void dth11_read(int16_t *temp, int16_t *rh);

#endif
