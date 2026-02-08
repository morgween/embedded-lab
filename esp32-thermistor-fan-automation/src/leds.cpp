#include "headers/leds.h"
#include "headers/pins.h"
#include "headers/config.h"

// one-shot blink timers: time until which led is on
static unsigned long redBlinkUntil  = 0;
static unsigned long blueBlinkUntil = 0;

// triple blink state
static int  redTripleCount    = 0;    // blinks remaining
static bool redTriplePhase    = false; // true = on, false = off
static unsigned long redTripleNext = 0;

void leds_init() {
  for (int i = 0; i < LED_COUNT; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    digitalWrite(LED_PINS[i], LOW);
  }
}

void leds_blink_red_once() {
  redBlinkUntil = millis() + BLINK_TIME_MS;
}

void leds_blink_red_triple() {
  redTripleCount = 3;
  redTriplePhase = true;
  redTripleNext  = millis() + BLINK_TIME_MS;
  redBlinkUntil  = 0; // override single blink
}

void leds_blink_blue_once() {
  blueBlinkUntil = millis() + BLINK_TIME_MS;
}

void leds_update(bool errorFlag, bool autoMode, int currentDuty) {
  unsigned long now = millis();

  // ------- green: motor actually spinning, no error -------
  bool greenOn = (!errorFlag && currentDuty >= MIN_DUTY);

  // ------- red: solid on error, triple blink, or single blink ---
  bool redOn = false;
  if (errorFlag) {
    redOn = true;
    redBlinkUntil  = 0;
    redTripleCount = 0;
  } else if (redTripleCount > 0) {
    // triple blink in progress
    redOn = redTriplePhase;
    if (now >= redTripleNext) {
      if (redTriplePhase) {
        // was on, switch to off gap
        redTriplePhase = false;
        redTripleNext = now + BLINK_TIME_MS / 2;
      } else {
        // was off gap, start next blink
        redTripleCount--;
        if (redTripleCount > 0) {
          redTriplePhase = true;
          redTripleNext = now + BLINK_TIME_MS;
        }
      }
    }
  } else if (now < redBlinkUntil) {
    redOn = true;
  }

  // ------- blue: auto indicator + temp up blink -----------
  bool blueOn = false;

  // blink has priority
  if (!errorFlag && now < blueBlinkUntil) {
    blueOn = true;
  } else {
    blueBlinkUntil = 0;
    // steady blue when auto mode is active and no error
    if (!errorFlag && autoMode) {
      blueOn = true;
    }
  }

  digitalWrite(LED_PINS[LED_OK],   greenOn ? HIGH : LOW);
  digitalWrite(LED_PINS[LED_ERR],  redOn   ? HIGH : LOW);
  digitalWrite(LED_PINS[LED_AUTO], blueOn  ? HIGH : LOW);
}
