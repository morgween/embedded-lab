#include <Arduino.h>
#include "headers/ultrasonic.h"
#include "headers/config.h"
#include "headers/pins.h"

// single raw measurement, returns cm or -1 on timeout
static float ultrasonic_measure_once_cm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  unsigned long duration = pulseIn(ECHO_PIN, HIGH, ECHO_TIMEOUT_US);
  if (duration == 0) return -1.0f;

  return (float)duration / 58.0f;
}

void ultrasonic_init() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);
  delay(100);
}

// median of several samples to reject outliers
float ultrasonic_measure_median_cm() {
  float samples[MEDIAN_SAMPLES];
  int count = 0;

  for (int i = 0; i < MEDIAN_SAMPLES; i++) {
    float d = ultrasonic_measure_once_cm();
    if (d > 0) samples[count++] = d;
    delay(10);
  }

  if (count == 0) return -1.0f;

  for (int i = 0; i < count - 1; i++) {
    for (int j = i + 1; j < count; j++) {
      if (samples[j] < samples[i]) {
        float tmp = samples[i];
        samples[i] = samples[j];
        samples[j] = tmp;
      }
    }
  }

  return samples[count / 2];
}
