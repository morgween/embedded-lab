#pragma once
#include "buttons.h"
#include "leds.h"

//====== buttons ======

static const int BTN_PINS[BTN_COUNT] = {
  4,   // BTN_POWER
  7,   // BTN_SPEED_DOWN
  17,  // BTN_SPEED_UP
  11   // BTN_AUTO
};

//====== motor ======

static const int MOTOR_PIN = 45;

//====== thermistor ======

static const int THERM_PIN = 5;

//====== leds ======

static const int LED_PINS[LED_COUNT] = {
  1,  // LED_OK (green)
  2,  // LED_AUTO (blue)
  41   // LED_ERR (red)
};
