#pragma once
#include <Arduino.h>

//====== mode and fan state ======

enum Mode {
  MODE_MANUAL = 0,
  MODE_AUTO   = 1
};

enum FanState {
  FS_ERROR  = 0,
  FS_OFF    = 1,
  FS_MANUAL = 2,
  FS_AUTO   = 3
};

void     system_init();
void     system_update();
FanState system_fan_state();
Mode     system_mode();
bool     system_motor_enabled();
bool     system_auto_mode();
int      system_manual_duty();
