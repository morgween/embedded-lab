#include <Arduino.h>
#include "headers/ultrasonic.h"

// update these pins to match your wiring for hc-sr04
const int TRIG_PIN = 27;
const int ECHO_PIN = 17;

// echo timeout in microseconds
const unsigned long ECHO_TIMEOUT_US = 30000;

// number of samples for median
const int MEDIAN_SAMPLES = 5;

// single raw measurement, returns cm or -1 if no echo
static float ultrasonic_measure_once_cm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  unsigned long duration = pulseIn(ECHO_PIN, HIGH, ECHO_TIMEOUT_US);
  if (duration == 0) {
    return -1.0f;
  }

  float distanceCm = (float)duration / 58.0f;
  return distanceCm;
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
    if (d > 0) {
      samples[count++] = d;
    }
    delay(10);
  }

  if (count == 0) {
    return -1.0f;
  }

  // simple bubble sort for small arrays
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
