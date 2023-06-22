#include "tof.h"

Adafruit_VL6180X lox1 = Adafruit_VL6180X();
Adafruit_VL6180X lox2 = Adafruit_VL6180X();
Adafruit_VL6180X lox3 = Adafruit_VL6180X();
Adafruit_VL6180X lox4 = Adafruit_VL6180X();
Adafruit_VL6180X lox5 = Adafruit_VL6180X();

void initTof() {
    pinMode(SHT_LOX1, OUTPUT);
    pinMode(SHT_LOX2, OUTPUT);
    pinMode(SHT_LOX3, OUTPUT);
    pinMode(SHT_LOX4, OUTPUT);
    pinMode(SHT_LOX5, OUTPUT);
    
    digitalWrite(SHT_LOX1, LOW);
    digitalWrite(SHT_LOX2, LOW);
    digitalWrite(SHT_LOX3, LOW);
    digitalWrite(SHT_LOX4, LOW);
    digitalWrite(SHT_LOX5, LOW);
    delay(10);

    digitalWrite(SHT_LOX1, HIGH);
    digitalWrite(SHT_LOX2, HIGH);
    digitalWrite(SHT_LOX3, HIGH);
    digitalWrite(SHT_LOX4, HIGH);
    digitalWrite(SHT_LOX5, HIGH);
    delay(10);

    digitalWrite(SHT_LOX1, HIGH);
    digitalWrite(SHT_LOX2, LOW);
    digitalWrite(SHT_LOX3, LOW);
    digitalWrite(SHT_LOX4, LOW);
    digitalWrite(SHT_LOX5, LOW);

    if (!lox1.begin()) {
        Serial.println(F("Failed to boot first VL6180X"));
        while (1);
    }
    lox1.setAddress(LOX1_ADDRESS);
    delay(10);

    digitalWrite(SHT_LOX3, HIGH);
    delay(10);

    if (!lox3.begin()) {
        Serial.println(F("Failed to boot third VL6180X"));
        while (1);
    }
    lox3.setAddress(LOX3_ADDRESS);

    digitalWrite(SHT_LOX5, HIGH);
    delay(10);

    if (!lox5.begin()) {
        Serial.println(F("Failed to boot fourth VL6180X"));
        while (1);
    }
    lox5.setAddress(LOX5_ADDRESS);
}

int readTofDiff() {
  uint8_t l = lox1.readRange();
  uint8_t ls = lox1.readRangeStatus();


  uint8_t r = lox3.readRange();
  uint8_t rs = lox3.readRangeStatus();

  if (ls != VL6180X_ERROR_NONE) {
    return 0;
  }

  if (rs != VL6180X_ERROR_NONE) {
    return 0;
  }

  return r - l;
}

bool nothingInFront() {
  uint8_t f = lox5.readRange();
  uint8_t fs = lox5.readRangeStatus();

  if (f > 100) {
    return true;
  }

  if (fs == VL6180X_ERROR_NONE) {
    return false;
  }

  return false;
}

bool tofNoSignal() {
  uint8_t ls = lox1.readRangeStatus();
  uint8_t rs = lox3.readRangeStatus();

  return !(ls == VL6180X_ERROR_NONE) && !(rs == VL6180X_ERROR_NONE);
}
