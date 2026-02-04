#pragma once
#include <Arduino.h>

enum ButtonEvent {
  BUTTON_NONE = 0,
  BUTTON_CALIB_PRESS,
  BUTTON_MUTE_PRESS,
  BUTTON_FREEZE_PRESS
};

void buttons_init();
ButtonEvent buttons_poll();
