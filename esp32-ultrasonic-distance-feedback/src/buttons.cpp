#include <Arduino.h>
#include "headers/buttons.h"
#include "headers/pins.h"
#include "headers/config.h"

//====== debounce state ======

static bool          stableCalib     = false;
static bool          prevCalib       = false;
static unsigned long lastChangeCalib = 0;

static bool          stableMute      = false;
static bool          prevMute        = false;
static unsigned long lastChangeMute  = 0;

static bool          stableFreeze     = false;
static bool          prevFreeze       = false;
static unsigned long lastChangeFreeze = 0;

void buttons_init() {
  pinMode(BTN_CALIB_PIN,  INPUT_PULLUP);
  pinMode(BTN_MUTE_PIN,   INPUT_PULLUP);
  pinMode(BTN_FREEZE_PIN, INPUT_PULLUP);
}

// debounce one button, returns true on rising edge
static bool debounce(int pin, bool &stable, bool &prev, unsigned long &lastChange) {
  unsigned long now = millis();
  bool raw = (digitalRead(pin) == LOW); // active low

  if (raw != stable && (now - lastChange) > DEBOUNCE_MS) {
    stable = raw;
    lastChange = now;
    if (stable && !prev) {
      prev = stable;
      return true;
    }
    prev = stable;
  }
  return false;
}

ButtonEvent buttons_poll() {
  if (debounce(BTN_CALIB_PIN, stableCalib, prevCalib, lastChangeCalib))
    return BUTTON_CALIB_PRESS;

  if (debounce(BTN_MUTE_PIN, stableMute, prevMute, lastChangeMute))
    return BUTTON_MUTE_PRESS;

  if (debounce(BTN_FREEZE_PIN, stableFreeze, prevFreeze, lastChangeFreeze))
    return BUTTON_FREEZE_PRESS;

  return BUTTON_NONE;
}
