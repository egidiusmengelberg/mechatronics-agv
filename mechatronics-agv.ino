#include "tof.h"
#include "stepper.h"

int tofErrorCount = 0;
int cornerDirection = -1;

unsigned long lastTime = 0;

void setup() {
  Serial.begin(9600);

  Serial.println("Starting...");
  initTof();
  initStepper();
  pinMode(11, INPUT);
  pinMode(12, INPUT);
}

void loop() {
  unsigned long currTime = millis();
  float tofDiff = readTofDiff();
  bool tofHasError = tofNoSignal();
  float r = 1;

  if (tofHasError){ 
      tofErrorCount++;
  } else {
    tofErrorCount = 0;  
  }

  if (nothingInFront()) {
    if (tofErrorCount > CORNER_TOF_ERROR_COUNT) {
      runStepper(CORNER_LENGTH, CORNER_SIZE * cornerDirection);
      cornerDirection = cornerDirection * -1;
      tofErrorCount = 0;
    } else {        
      if (tofDiff > 20)
        r = 0.5;
      if (tofDiff < -20)
        r = 1.5;
    
      if (!digitalRead(11) || !digitalRead(12)) {
        delay(FLOWERPOT_WAIT_TIME);
        runStepper(FLOWERPOT_AFTER_LENGTH, r); 
      }else {
        runStepper(NORMAL_STEPS, r); 
      } 
    }
  } else {
    lastTime = millis();

    while((currTime - lastTime > 10000) || nothingInFront()) {
      currTime = millis();
    }

    
  }
}
