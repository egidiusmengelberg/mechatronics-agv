#include "tof.h"
#include "stepper.h"

void setup() {
  Serial.begin(9600);

  Serial.println("Starting...");
  initTof();
}

void loop() {
  read_sensors();
  delay(200);
}