#include <Arduino.h>
#include "headers/buzzer.h"

// update this pin to match your buzzer wiring
const int BUZZER_PIN = 6;

void buzzer_init() {
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
}

void buzzer_force_off() {
  digitalWrite(BUZZER_PIN, LOW);
}

// distance -> beeping rate, closer = faster
void buzzer_update_from_distance(float distanceCm, float maxDistanceCm, bool enabled) {
  static bool buzState = false;
  static unsigned long lastToggle = 0;

  if (!enabled) {
    if (buzState) {
      buzState = false;
      digitalWrite(BUZZER_PIN, LOW);
    }
    return;
  }

  if (distanceCm < 0 || distanceCm > maxDistanceCm) {
    if (buzState) {
      buzState = false;
      digitalWrite(BUZZER_PIN, LOW);
    }
    return;
  }

  float ratio = 1.0f - (distanceCm / maxDistanceCm);
  if (ratio < 0.0f) ratio = 0.0f;
  if (ratio > 1.0f) ratio = 1.0f;

  unsigned long period = (unsigned long)(800 - 700 * ratio); // 800..100 ms
  unsigned long halfPeriod = period / 2;

  unsigned long now = millis();
  if (now - lastToggle >= halfPeriod) {
    lastToggle = now;
    buzState = !buzState;
    digitalWrite(BUZZER_PIN, buzState ? HIGH : LOW);
  }
}
