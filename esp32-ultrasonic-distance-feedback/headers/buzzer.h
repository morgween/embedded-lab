#pragma once
#include <Arduino.h>

void buzzer_init();
void buzzer_update_from_distance(float distanceCm, float maxDistanceCm, bool enabled);
void buzzer_force_off();
