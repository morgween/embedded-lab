#include <Arduino.h>
#include "headers/logger.h"
#include "headers/config.h"
#include "headers/state_machine.h"
#include "headers/thermistor.h"
#include "headers/motor.h"

static unsigned long lastLog = 0;

void logSample() {
  if (!ENABLE_LOG) return;

  unsigned long now = millis();
  if (now - lastLog < LOG_INTERVAL_MS) return;
  lastLog = now;

  Serial.print("state=");
  Serial.print((int)system_fan_state());
  Serial.print(" raw=");
  Serial.print(thermistor_raw());
  Serial.print(" filt=");
  Serial.print((int)thermistor_filtered());
  Serial.print(" duty=");
  Serial.print(motor_get_current());
  Serial.print(" tgt=");
  Serial.print(motor_get_target());
  Serial.print(" mode=");
  Serial.print((system_mode() == MODE_MANUAL) ? "M" : "A");
  Serial.print(" auto=");
  Serial.print(system_auto_mode() ? 1 : 0);
  Serial.print(" en=");
  Serial.print(system_motor_enabled() ? 1 : 0);
  Serial.print(" err=");
  Serial.println(thermistor_error() ? 1 : 0);
}

void logEvent(const char* msg) {
  if (!ENABLE_LOG) return;
  Serial.print("event: ");
  Serial.println(msg);
}
