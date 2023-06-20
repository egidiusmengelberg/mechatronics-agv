#include "tof.h"

Adafruit_VL6180X lox1 = Adafruit_VL6180X();
Adafruit_VL6180X lox2 = Adafruit_VL6180X();
Adafruit_VL6180X lox3 = Adafruit_VL6180X();
Adafruit_VL6180X lox4 = Adafruit_VL6180X();

RunningAverage smoother(10);

void initTof() {
    pinMode(SHT_LOX1, OUTPUT);
    pinMode(SHT_LOX2, OUTPUT);
    pinMode(SHT_LOX3, OUTPUT);
    pinMode(SHT_LOX4, OUTPUT);

    // all reset
    digitalWrite(SHT_LOX1, LOW);
    digitalWrite(SHT_LOX2, LOW);
    digitalWrite(SHT_LOX3, LOW);
    digitalWrite(SHT_LOX4, LOW);
    delay(10);

    // all unreset
    digitalWrite(SHT_LOX1, HIGH);
    digitalWrite(SHT_LOX2, HIGH);
    digitalWrite(SHT_LOX3, HIGH);
    digitalWrite(SHT_LOX4, HIGH);
    delay(10);

    // activating LOX1 and reseting LOX2
    digitalWrite(SHT_LOX1, HIGH);
    digitalWrite(SHT_LOX2, LOW);
    digitalWrite(SHT_LOX3, LOW);
    digitalWrite(SHT_LOX4, LOW);

    // initing LOX1
    if (!lox1.begin()) {
        Serial.println(F("Failed to boot first VL6180X"));
        while (1);
    }
    lox1.setAddress(LOX1_ADDRESS);
    delay(10);

    // activating LOX2
    digitalWrite(SHT_LOX2, HIGH);
    delay(10);

    //initing LOX2
    if (!lox2.begin()) {
        Serial.println(F("Failed to boot second VL6180X"));
        while (1);
    }
    lox2.setAddress(LOX2_ADDRESS);

    // activating LOX3
    digitalWrite(SHT_LOX3, HIGH);
    delay(10);

    //initing LOX3
    if (!lox3.begin()) {
        Serial.println(F("Failed to boot third VL6180X"));
        while (1);
    }
    lox3.setAddress(LOX3_ADDRESS);

    // activating LOX4
    digitalWrite(SHT_LOX4, HIGH);
    delay(10);

    //initing LOX3
    if (!lox4.begin()) {
        Serial.println(F("Failed to boot fourth VL6180X"));
        while (1);
    }
    lox4.setAddress(LOX4_ADDRESS);
}

void averageTof() {
  uint8_t range1 = lox1.readRange();
  uint8_t range2 = lox2.readRange();

  uint8_t range3 = lox3.readRange();
  uint8_t range4 = lox4.readRange();

  float gl = (range1 + range2) / 2.0;
  float gr = (range3 + range4) / 2.0;

  float err = gr - gl;

  smoother.addValue(err);

  Serial.println(smoother.getAverage());
}

