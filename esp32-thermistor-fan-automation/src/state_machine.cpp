#include "headers/state_machine.h"
#include "headers/buttons.h"
#include "headers/motor.h"
#include "headers/thermistor.h"
#include "headers/leds.h"
#include "headers/logger.h"
#include "headers/config.h"

static Mode     mode         = MODE_MANUAL;
static FanState fanState     = FS_OFF;
static bool     autoMode     = false;   // blue button toggle
static bool     motorEnabled = true;    // green button toggle
static int      manualDuty   = MANUAL_DUTY_DEFAULT;

FanState system_fan_state()      { return fanState; }
Mode     system_mode()           { return mode; }
bool     system_motor_enabled()  { return motorEnabled; }
bool     system_auto_mode()      { return autoMode; }
int      system_manual_duty()    { return manualDuty; }

//====== init ======

void system_init() {
  buttons_init();
  motor_init();
  thermistor_init();
  leds_init();

  motor_set_target(0);
}

//====== compute target duty ======

static void update_logic() {
  int targetDuty = 0;
  fanState = FS_OFF;

  if (thermistor_error()) {
    fanState = FS_ERROR;
    targetDuty = 0;
    motor_set_target(targetDuty);
    return;
  }

  if (mode == MODE_MANUAL) {
    if (motorEnabled) {
      targetDuty = manualDuty;
      fanState = (targetDuty > 0) ? FS_MANUAL : FS_OFF;
    } else {
      targetDuty = 0;
      fanState = FS_OFF;
    }
  } else { // MODE_AUTO
    fanState = FS_AUTO;

    float filtTemp = thermistor_filtered();
    int autoDuty = 0;

    if (filtTemp <= HOT_ADC) {
      autoDuty = MAX_DUTY;
    } else if (filtTemp >= COOL_ADC) {
      autoDuty = 0;
    } else {
      float t = (float)(COOL_ADC - filtTemp) / (float)(COOL_ADC - HOT_ADC);
      if (t < 0) t = 0;
      if (t > 1) t = 1;
      autoDuty = MIN_DUTY + (int)(t * (MAX_DUTY - MIN_DUTY));
    }

    if (!motorEnabled) {
      autoDuty = 0;
    }

    targetDuty = autoDuty;
  }

  motor_set_target(targetDuty);
}

//====== main loop ======

void system_update() {
  buttons_poll();

  // ---------- buttons ----------
  if (button_pressed(BTN_POWER)) {
    motorEnabled = !motorEnabled;
  }

  if (button_pressed(BTN_AUTO)) {
    autoMode = !autoMode;
    mode = autoMode ? MODE_AUTO : MODE_MANUAL;
  }

  if (mode == MODE_MANUAL) {
    if (button_pressed(BTN_SPEED_DOWN)) {
      manualDuty -= MANUAL_DUTY_STEP;
      if (manualDuty < MIN_DUTY) {
        // below minimum -> motor off, triple red blink
        manualDuty = 0;
        leds_blink_red_triple();
        logEvent("duty below min -> OFF");
      }
    }
    if (button_pressed(BTN_SPEED_UP)) {
      manualDuty += MANUAL_DUTY_STEP;
      if (manualDuty > MAX_DUTY) {
        // above maximum -> clamp, triple red blink
        manualDuty = MAX_DUTY;
        leds_blink_red_triple();
        logEvent("duty at max limit");
      }
      // if coming from 0, jump to MIN_DUTY
      if (manualDuty > 0 && manualDuty < MIN_DUTY) {
        manualDuty = MIN_DUTY;
      }
    }
  }

  // ---------- temperature ----------
  thermistor_update();

  // temperature event blinks
  if (!thermistor_error()) {
    if (thermistor_trend_down()) {
      // adc up -> cooler -> temp falling -> red blink
      leds_blink_red_once();
      logEvent("temp_down");
    }
    if (thermistor_trend_up()) {
      // adc down -> hotter -> temp rising -> blue blink only in manual
      if (mode == MODE_MANUAL) {
        leds_blink_blue_once();
      }
      logEvent("temp_up");
    }
  }

  // ---------- core logic ----------
  update_logic();
  motor_update();
  leds_update(thermistor_error(), autoMode, motor_get_current());
  logSample();
}
