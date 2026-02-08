#pragma once

//====== bargraph leds ======

static const int LED_PINS[] = {19, 20, 21, 47, 48, 45, 36, 37, 38, 39};
static const int LED_COUNT  = sizeof(LED_PINS) / sizeof(LED_PINS[0]);

//====== ultrasonic sensor ======

static const int TRIG_PIN = 5;
static const int ECHO_PIN = 4;

//====== buttons ======

static const int BTN_CALIB_PIN  = 11;
static const int BTN_MUTE_PIN   = 12;
static const int BTN_FREEZE_PIN = 13;

//====== buzzer ======

static const int BUZZER_PIN = 14;
