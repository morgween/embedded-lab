#include <Arduino.h>
#include "headers/config.h"

//====== runtime globals ======

State         currentState       = STATE_NORMAL;
float         maxDistanceCm      = DEFAULT_MAX_DISTANCE_CM;
float         filteredDistanceCm = -1.0f;
float         lastRawDistanceCm  = -1.0f;
int           currentLevel       = 0;
unsigned long calibDoneAnimStart = 0;
bool          buzzerEnabled      = true;
bool          freezeDisplay      = false;
