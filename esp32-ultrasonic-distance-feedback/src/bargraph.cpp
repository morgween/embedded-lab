#include <Arduino.h>
#include "headers/bargraph.h"
#include "headers/pins.h"

void bargraph_init() {
  for (int i = 0; i < LED_COUNT; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    digitalWrite(LED_PINS[i], LOW);
  }
}

void bargraph_set_level(int level) {
  if (level < 0) level = 0;
  if (level > LED_COUNT) level = LED_COUNT;

  for (int i = 0; i < LED_COUNT; i++) {
    digitalWrite(LED_PINS[i], (i < level) ? HIGH : LOW);
  }
}

void bargraph_set_dot(int index) {
  for (int i = 0; i < LED_COUNT; i++) {
    digitalWrite(LED_PINS[i], (i == index) ? HIGH : LOW);
  }
}
