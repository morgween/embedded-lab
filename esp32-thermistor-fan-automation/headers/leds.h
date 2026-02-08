#pragma once
#include <Arduino.h>

//====== led identifiers ======

// order must match LED_PINS[] in pins.h
enum LedId {
  LED_OK,
  LED_AUTO,
  LED_ERR,
  LED_COUNT // keep last
};

void leds_init();
void leds_blink_red_once();    // one-shot red blink (temp down)
void leds_blink_red_triple();  // three red blinks (duty limit hit)
void leds_blink_blue_once();   // one-shot blue blink (temp up)
void leds_update(bool errorFlag, bool autoMode, int currentDuty);
