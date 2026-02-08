#include <Arduino.h>
#include "headers/buzzer.h"
#include "headers/config.h"
#include "headers/pins.h"

void buzzer_init() {
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
}

void buzzer_force_off() {
  digitalWrite(BUZZER_PIN, LOW);
}

// closer distance = faster beeping
void buzzer_update_from_distance(float distanceCm, float maxDist, bool enabled) {
  static bool          buzState   = false;
  static unsigned long lastToggle = 0;

  if (!enabled || distanceCm < 0 || distanceCm > maxDist) {
    if (buzState) {
      buzState = false;
      digitalWrite(BUZZER_PIN, LOW);
    }
    return;
  }

  float ratio = 1.0f - (distanceCm / maxDist);
  if (ratio < 0.0f) ratio = 0.0f;
  if (ratio > 1.0f) ratio = 1.0f;

  unsigned long period = BUZZER_PERIOD_MAX_MS
                       - (unsigned long)((BUZZER_PERIOD_MAX_MS - BUZZER_PERIOD_MIN_MS) * ratio);
  unsigned long halfPeriod = period / 2;

  unsigned long now = millis();
  if (now - lastToggle >= halfPeriod) {
    lastToggle = now;
    buzState = !buzState;
    digitalWrite(BUZZER_PIN, buzState ? HIGH : LOW);
  }
}
