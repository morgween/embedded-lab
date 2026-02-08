#include "headers/motor.h"
#include "headers/pins.h"
#include "headers/config.h"

static int targetDuty  = 0;
static int currentDuty = 0;

void motor_init() {
  pinMode(MOTOR_PIN, OUTPUT);
  ledcAttach(MOTOR_PIN, MOTOR_FREQ, MOTOR_RES);
  ledcWrite(MOTOR_PIN, 0);
}

void motor_set_target(int duty) {
  if (duty < 0)   duty = 0;
  if (duty > 255) duty = 255;
  targetDuty = duty;
}

int motor_get_target()  { return targetDuty; }
int motor_get_current() { return currentDuty; }

void motor_update() {
  if (currentDuty < targetDuty) {
    currentDuty += RAMP_STEP;
    if (currentDuty > targetDuty) currentDuty = targetDuty;
  } else if (currentDuty > targetDuty) {
    currentDuty -= RAMP_STEP;
    if (currentDuty < targetDuty) currentDuty = targetDuty;
  }

  // avoid tiny useless values
  if (currentDuty > 0 && currentDuty < MIN_DUTY) {
    if (targetDuty == 0) currentDuty = 0;
    else currentDuty = MIN_DUTY;
  }

  ledcWrite(MOTOR_PIN, currentDuty);
}
