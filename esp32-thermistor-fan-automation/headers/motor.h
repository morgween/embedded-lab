#pragma once
#include <Arduino.h>

void motor_init();
void motor_set_target(int duty); // 0..255
int  motor_get_target();
int  motor_get_current();        // actual duty after ramping
void motor_update();
