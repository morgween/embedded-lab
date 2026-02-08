#include <Arduino.h>
#include "headers/config.h"
#include "headers/pins.h"
#include "headers/bargraph.h"
#include "headers/ultrasonic.h"
#include "headers/buzzer.h"
#include "headers/buttons.h"

//====== helpers ======

static int distanceToLevel(float distanceCm) {
  if (distanceCm < 0 || distanceCm >= maxDistanceCm) return 0;

  float ratio = 1.0f - (distanceCm / maxDistanceCm);
  if (ratio < 0.0f) ratio = 0.0f;
  if (ratio > 1.0f) ratio = 1.0f;

  int level = (int)(ratio * LED_COUNT + 0.5f);
  if (level < 0) level = 0;
  if (level > LED_COUNT) level = LED_COUNT;
  return level;
}

//====== state handlers ======

static void updateStateNormal() {
  float raw = ultrasonic_measure_median_cm();
  lastRawDistanceCm = raw;

  if (!freezeDisplay) {
    float effectiveRaw = (raw > 0) ? raw : (maxDistanceCm + 20.0f);

    if (filteredDistanceCm < 0) {
      filteredDistanceCm = effectiveRaw;
    } else {
      filteredDistanceCm = DISTANCE_FILTER_ALPHA * filteredDistanceCm
                         + (1.0f - DISTANCE_FILTER_ALPHA) * effectiveRaw;
    }

    int targetLevel = distanceToLevel(filteredDistanceCm);
    if (targetLevel > currentLevel) currentLevel++;
    else if (targetLevel < currentLevel) currentLevel--;

    bargraph_set_level(currentLevel);
  }

  buzzer_update_from_distance(filteredDistanceCm, maxDistanceCm, buzzerEnabled);

  static unsigned long lastPrint = 0;
  unsigned long now = millis();
  if (now - lastPrint > 500) {
    lastPrint = now;
    Serial.print("raw=");     Serial.print(lastRawDistanceCm);
    Serial.print(" filt=");   Serial.print(filteredDistanceCm);
    Serial.print(" max=");    Serial.print(maxDistanceCm);
    Serial.print(" level=");  Serial.print(currentLevel);
    Serial.print(" freeze="); Serial.print(freezeDisplay ? "on" : "off");
    Serial.print(" buzzer="); Serial.println(buzzerEnabled ? "on" : "off");
  }
}

// dot animation while calibrating
static void updateStateCalibrating() {
  static int           index      = 0;
  static int           dir        = 1;
  static unsigned long lastUpdate = 0;

  unsigned long now = millis();
  if (now - lastUpdate < 80) return;
  lastUpdate = now;

  index += dir;
  if (index >= LED_COUNT - 1) { index = LED_COUNT - 1; dir = -1; }
  else if (index <= 0)        { index = 0;              dir =  1; }

  bargraph_set_dot(index);
  buzzer_force_off();
}

// fill animation after successful calibration
static void updateStateCalibDoneAnim() {
  static int           level      = 0;
  static int           dir        = 1;
  static unsigned long lastUpdate = 0;

  unsigned long now = millis();

  if (now - calibDoneAnimStart > 1600) {
    currentState = STATE_NORMAL;
    level = 0;
    dir = 1;
    bargraph_set_level(0);
    buzzer_force_off();
    return;
  }

  if (now - lastUpdate > 60) {
    lastUpdate = now;
    level += dir;
    if (level >= LED_COUNT) { level = LED_COUNT; dir = -1; }
    else if (level <= 0)    { level = 0;         dir =  1; }
    bargraph_set_level(level);
  }

  buzzer_force_off();
}

//====== setup / loop ======

void setup() {
  Serial.begin(115200);
  delay(1000);

  bargraph_init();
  ultrasonic_init();
  buzzer_init();
  buttons_init();

  Serial.println();
  Serial.println("esp32 ultrasonic distance feedback");
}

void loop() {
  ButtonEvent ev = buttons_poll();

  if (ev == BUTTON_CALIB_PRESS) {
    if (currentState == STATE_NORMAL) {
      currentState = STATE_CALIBRATING;
      Serial.println("calibration: place hand at max distance and press again");
    } else if (currentState == STATE_CALIBRATING) {
      if (lastRawDistanceCm > 0) {
        maxDistanceCm = lastRawDistanceCm;
        filteredDistanceCm = -1.0f;
        currentState = STATE_CALIB_DONE_ANIM;
        calibDoneAnimStart = millis();
        Serial.print("calibration ok, max=");
        Serial.print(maxDistanceCm);
        Serial.println(" cm");
      } else {
        Serial.println("calibration failed: no valid distance");
      }
    }
  } else if (ev == BUTTON_MUTE_PRESS) {
    buzzerEnabled = !buzzerEnabled;
    if (!buzzerEnabled) buzzer_force_off();
    Serial.print("buzzer: ");
    Serial.println(buzzerEnabled ? "on" : "off");
  } else if (ev == BUTTON_FREEZE_PRESS) {
    freezeDisplay = !freezeDisplay;
    Serial.print("freeze: ");
    Serial.println(freezeDisplay ? "on" : "off");
  }

  switch (currentState) {
    case STATE_NORMAL:          updateStateNormal();         break;
    case STATE_CALIBRATING:     updateStateCalibrating();    break;
    case STATE_CALIB_DONE_ANIM: updateStateCalibDoneAnim();  break;
  }
}
