#include "headers/buttons.h"
#include "headers/pins.h"

static bool lastState[BTN_COUNT];
static bool pressEdge[BTN_COUNT];

void buttons_init() {
  for (int i = 0; i < BTN_COUNT; i++) {
    pinMode(BTN_PINS[i], INPUT_PULLUP);
    lastState[i] = digitalRead(BTN_PINS[i]);
    pressEdge[i] = false;
  }
}

void buttons_poll() {
  for (int i = 0; i < BTN_COUNT; i++) {
    bool now = digitalRead(BTN_PINS[i]);
    pressEdge[i] = (lastState[i] == HIGH && now == LOW);
    lastState[i] = now;
  }
}

bool button_pressed(ButtonId id) {
  bool v = pressEdge[id];
  pressEdge[id] = false;
  return v;
}
