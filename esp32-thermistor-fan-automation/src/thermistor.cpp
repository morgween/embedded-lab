#include "headers/thermistor.h"
#include "headers/pins.h"
#include "headers/config.h"

static int   lastRaw      = -1;
static float filt         = -1.0f;
static float prevFilt     = -1.0f;
static bool  errFlag      = false;
static bool  prevErrFlag  = false;
static bool  trendUp      = false;
static bool  trendDown    = false;

void thermistor_init() {
  analogReadResolution(12);
  lastRaw = analogRead(THERM_PIN);
  filt = lastRaw;
  prevFilt = filt;
}

void thermistor_update() {
  prevErrFlag = errFlag;

  int raw = analogRead(THERM_PIN);
  lastRaw = raw;

  // simple fault detection: out of sane range
  if (raw < RAW_MIN_OK || raw > RAW_MAX_OK) {
    errFlag = true;
  } else {
    errFlag = false;
  }

  // handle error transitions: clear all trends
  if (errFlag != prevErrFlag) {
    trendUp   = false;
    trendDown = false;
  }

  if (errFlag) return;

  // first-time init of filter
  if (filt < 0) {
    filt = raw;
    prevFilt = filt;
    return;
  }

  // remember previous filtered value
  prevFilt = filt;

  // low-pass filter
  filt = FILTER_ALPHA * filt + (1.0f - FILTER_ALPHA) * raw;

  int diff = (int)filt - (int)prevFilt;

  // diff > 0: adc up -> cooler -> temp falling
  if (diff > TEMP_DELTA_EVT) {
    trendDown = true;   // temp going down (cooler)
  }
  // diff < 0: adc down -> hotter -> temp rising
  else if (diff < -TEMP_DELTA_EVT) {
    trendUp = true;     // temp going up (hotter)
  }
}

int   thermistor_raw()      { return lastRaw; }
float thermistor_filtered() { return filt; }
bool  thermistor_error()    { return errFlag; }

bool thermistor_trend_up() {
  bool t = trendUp;
  trendUp = false;
  return t;
}

bool thermistor_trend_down() {
  bool t = trendDown;
  trendDown = false;
  return t;
}

void thermistor_clear_trends() {
  trendUp = trendDown = false;
}
