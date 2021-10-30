
#include <Arduino.h>

#ifndef _UTILS_
#define _UTILS_

#define TICK_LENGTH_MS 100
const uint32_t tick_1s = 1000 / TICK_LENGTH_MS;
const uint32_t tick_1m = 60000 / TICK_LENGTH_MS;

void button_led_feedback(uint8_t button, uint8_t led);

#endif
