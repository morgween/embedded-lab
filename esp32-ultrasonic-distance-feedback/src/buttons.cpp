#include <Arduino.h>
#include "headers/buttons.h"
#include "headers/pins.h"
#include "headers/config.h"

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
