#pragma once

//====== motor pwm ======

static const int MOTOR_FREQ = 20000; // 20 kHz, above audible range
static const int MOTOR_RES  = 8;     // 8-bit resolution, duty 0..255
static const int RAMP_STEP  = 2;     // duty change per update cycle

static const int MIN_DUTY = 50;      // lowest duty where motor starts
static const int MAX_DUTY = 150;     // comfortable max

//====== thermistor adc ======

static const int   RAW_MIN_OK     = 200;  // below = sensor shorted
static const int   RAW_MAX_OK     = 3900; // above = sensor disconnected
static const float FILTER_ALPHA   = 0.9f; // ema weight, higher = less smoothing
static const int   TEMP_DELTA_EVT = 5;    // adc steps for trend event

//====== auto mode thresholds ======

static const int HOT_ADC  = 2400; // adc value when hot -> full speed
static const int COOL_ADC = 2700; // adc value when cool -> off

//====== manual mode ======

static const int MANUAL_DUTY_STEP    = 5;  // +/- per button press
static const int MANUAL_DUTY_DEFAULT = 90; // starting duty in manual

//====== led timing ======

static const unsigned long BLINK_TIME_MS  = 250; // one-shot blink duration

//====== serial logging ======

static const bool          ENABLE_LOG      = true;
static const unsigned long LOG_INTERVAL_MS = 200;
