#include <Arduino.h>
#include "headers/bargraph.h"

// update these pins to match your real wiring
// order is from "first" led to "last" led on the bargraph or LED strip/LEDs
const int ledPins[] = {16, 12, 7, 8, 25, 24, 23, 18, 15, 14};
const int LED_COUNT = sizeof(ledPins) / sizeof(ledPins[0]);

void bargraph_init() {
  for (int i = 0; i < LED_COUNT; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
}

void bargraph_set_level(int level) {
  if (level < 0) level = 0;
  if (level > LED_COUNT) level = LED_COUNT;

  for (int i = 0; i < LED_COUNT; i++) {
    digitalWrite(ledPins[i], (i < level) ? HIGH : LOW);
  }
}

void bargraph_set_dot(int index) {
  for (int i = 0; i < LED_COUNT; i++) {
    digitalWrite(ledPins[i], (i == index) ? HIGH : LOW);
  }
}
