#pragma once
#include <Arduino.h>

void buzzer_init();
void buzzer_update_from_distance(float distanceCm, float maxDist, bool enabled);
void buzzer_force_off();
