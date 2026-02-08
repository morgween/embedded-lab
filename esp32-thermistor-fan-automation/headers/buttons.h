#pragma once
#include <Arduino.h>

//====== button identifiers ======

// order must match BTN_PINS[] in pins.h
enum ButtonId {
  BTN_POWER,
  BTN_SPEED_DOWN,
  BTN_SPEED_UP,
  BTN_AUTO,
  BTN_COUNT // keep last
};

void buttons_init();
void buttons_poll();
bool button_pressed(ButtonId id); // true once per press (edge)
