
#include <Arduino.h>

// Uncomment to activate Serial debugging
#define DEBUG

#ifndef _UTILS_
#define _UTILS_

#ifdef DEBUG
    #define DEBUG_SERIAL_SETUP(bauds)       Serial.begin(bauds)
    #define DEBUG_SERIAL_PRINTLN(string)    Serial.println(string);
    #define DEBUG_SERIAL_PRINT(string)      Serial.print(string);
#else
    #define DEBUG_SERIAL_SETUP(bauds)
    #define DEBUG_SERIAL_PRINTLN(string)
    #define DEBUG_SERIAL_PRINT(string)
#endif

#define TICK_LENGTH_MS 100
const uint32_t tick_1s = 1000 / TICK_LENGTH_MS;
const uint32_t tick_1m = 60000 / TICK_LENGTH_MS;

void button_led_feedback(uint8_t button, uint8_t led);

#endif
