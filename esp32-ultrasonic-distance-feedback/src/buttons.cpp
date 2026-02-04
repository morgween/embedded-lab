#include <Arduino.h>
#include "headers/buttons.h"

// update these pins to match your real wiring
// here: green = mute, red = calibration, yellow = freeze
const int BTN_CALIB_PIN  = 10; // green
const int BTN_MUTE_PIN   = 9;  // yellow
const int BTN_FREEZE_PIN = 11; // red

// debounce state
static bool btnCalibStable      = false;
static bool btnCalibPrevStable  = false;
static unsigned long btnCalibLastChange = 0;

static bool btnMuteStable       = false;
static bool btnMutePrevStable   = false;
static unsigned long btnMuteLastChange = 0;

static bool btnFreezeStable     = false;
static bool btnFreezePrevStable = false;
static unsigned long btnFreezeLastChange = 0;

void buttons_init() {
  pinMode(BTN_CALIB_PIN, INPUT_PULLUP);
  pinMode(BTN_MUTE_PIN, INPUT_PULLUP);
  pinMode(BTN_FREEZE_PIN, INPUT_PULLUP);
}

ButtonEvent buttons_poll() {
  const unsigned long debounceMs = 30;
  unsigned long now = millis();
  ButtonEvent ev = BUTTON_NONE;

  // calibration button (active low)
  {
    bool raw = (digitalRead(BTN_CALIB_PIN) == LOW);
    if (raw != btnCalibStable && (now - btnCalibLastChange) > debounceMs) {
      btnCalibStable = raw;
      btnCalibLastChange = now;

      if (btnCalibStable && !btnCalibPrevStable) {
        ev = BUTTON_CALIB_PRESS;
      }
      btnCalibPrevStable = btnCalibStable;
    }
  }

  // mute button
  {
    bool raw = (digitalRead(BTN_MUTE_PIN) == LOW);
    if (raw != btnMuteStable && (now - btnMuteLastChange) > debounceMs) {
      btnMuteStable = raw;
      btnMuteLastChange = now;

      if (btnMuteStable && !btnMutePrevStable && ev == BUTTON_NONE) {
        ev = BUTTON_MUTE_PRESS;
      }
      btnMutePrevStable = btnMuteStable;
    }
  }

  // freeze button
  {
    bool raw = (digitalRead(BTN_FREEZE_PIN) == LOW);
    if (raw != btnFreezeStable && (now - btnFreezeLastChange) > debounceMs) {
      btnFreezeStable = raw;
      btnFreezeLastChange = now;

      if (btnFreezeStable && !btnFreezePrevStable && ev == BUTTON_NONE) {
        ev = BUTTON_FREEZE_PRESS;
      }
      btnFreezePrevStable = btnFreezeStable;
    }
  }

  return ev;
}
