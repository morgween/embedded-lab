#include <Arduino.h>
#include "headers/pins.h"

// ================= button state tracking ===========
static bool btnCalibStable      = false;
static bool btnCalibPrevStable  = false;
static unsigned long btnCalibLastChange = 0;

static bool btnMuteStable       = false;
static bool btnMutePrevStable   = false;
static unsigned long btnMuteLastChange = 0;

static bool btnFreezeStable     = false;
static bool btnFreezePrevStable = false;
static unsigned long btnFreezeLastChange = 0;

// ================= hardware config =================
const int LED_COUNT = sizeof(ledPins) / sizeof(ledPins[0]);

// ================= general config =================
const unsigned long ECHO_TIMEOUT_US = 30000;

// ================= ultrasonic config =================
const int MEDIAN_SAMPLES = 5;

// ================= distance config =================

float maxDistanceCm = 100.0f;               // initial maximum distance in cm
const float DISTANCE_FILTER_ALPHA = 0.7f;    // ema factor for smoothing

// ================= state machine ===================

enum State {
  STATE_NORMAL = 0,        // distance mode: leds + buzzer
  STATE_CALIBRATING,       // calibration mode: dot animation
  STATE_CALIB_DONE_ANIM    // short "happy" fill animation after calibration
};

State currentState = STATE_NORMAL;

// ================= globals =========================

float filteredDistanceCm = -1.0f;
float lastRawDistanceCm  = -1.0f;
int   currentLevel       = 0;

unsigned long calibDoneAnimStart = 0;

bool buzzerEnabled = true;
bool freezeDisplay = false;
