#pragma once
#include <Arduino.h>

//====== ultrasonic ======

static const unsigned long ECHO_TIMEOUT_US = 30000;
static const int           MEDIAN_SAMPLES  = 5;

//====== distance ======

static const float DEFAULT_MAX_DISTANCE_CM = 100.0f;
static const float DISTANCE_FILTER_ALPHA   = 0.7f; // ema smoothing factor

//====== buzzer timing ======

static const unsigned long BUZZER_PERIOD_MAX_MS = 800; // far
static const unsigned long BUZZER_PERIOD_MIN_MS = 100; // close

//====== buttons ======

static const unsigned long DEBOUNCE_MS = 30;

//====== state machine ======

enum State {
  STATE_NORMAL,
  STATE_CALIBRATING,
  STATE_CALIB_DONE_ANIM
};

//====== runtime globals ======

extern State         currentState;
extern float         maxDistanceCm;
extern float         filteredDistanceCm;
extern float         lastRawDistanceCm;
extern int           currentLevel;
extern unsigned long calibDoneAnimStart;
extern bool          buzzerEnabled;
extern bool          freezeDisplay;
