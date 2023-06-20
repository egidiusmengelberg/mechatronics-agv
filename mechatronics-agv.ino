#include "tof.h"
#include "stepper.h"

void setup() {
  Serial.begin(9600);

  Serial.println("Starting...");
  initTof();
  initStepper();
}

void loop() {
  read_sensors();
  prepareLeftStepper(2000);
  prepareRightStepper(5000);
  runStepper();
  delay(200);
}