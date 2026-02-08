#include <Arduino.h>
#include "headers/state_machine.h"

void setup() {
  Serial.begin(115200);
  delay(500);
  system_init();
  Serial.println("fan controller: leds fixed, temp events & hysteresis");
}

void loop() {
  system_update();
  delay(20);
}
