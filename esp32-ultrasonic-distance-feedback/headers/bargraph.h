#pragma once
#include <Arduino.h>

// led count is exposed so main code can use it for animations
extern const int LED_COUNT;

void bargraph_init();
void bargraph_set_level(int level);
void bargraph_set_dot(int index);
