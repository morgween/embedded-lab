#pragma once
#include <Arduino.h>

void  thermistor_init();
void  thermistor_update();

int   thermistor_raw();
float thermistor_filtered();
bool  thermistor_error();

bool  thermistor_trend_up();   // auto-clear on read
bool  thermistor_trend_down(); // auto-clear on read
void  thermistor_clear_trends();
