#include <Adafruit_VL6180X.h>
#include "RunningAverage.h"

RunningAverage smoother(10);

// address we will assign if dual sensor is present
#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31
#define LOX3_ADDRESS 0x32
#define LOX4_ADDRESS 0x33

// set the pins to shutdown
#define SHT_LOX1 A0
#define SHT_LOX2 A1
#define SHT_LOX3 A2
#define SHT_LOX4 A3

// objects for the VL6180X
Adafruit_VL6180X lox1 = Adafruit_VL6180X();
Adafruit_VL6180X lox2 = Adafruit_VL6180X();
Adafruit_VL6180X lox3 = Adafruit_VL6180X();
Adafruit_VL6180X lox4 = Adafruit_VL6180X();


void setID() {
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

void readSensor(Adafruit_VL6180X &vl) {
  Serial.print(" Addr: ");
  Serial.print(vl.getAddress(), HEX);

  uint8_t range = vl.readRange();
  uint8_t status = vl.readRangeStatus();

  if (status == VL6180X_ERROR_NONE) {
    Serial.print(" Range: "); Serial.print(range);
  }

  // Some error occurred, print it out!

  if  ((status >= VL6180X_ERROR_SYSERR_1) && (status <= VL6180X_ERROR_SYSERR_5)) {
    Serial.print("(System error)");
  }
  else if (status == VL6180X_ERROR_ECEFAIL) {
    Serial.print("(ECE failure)");
  }
  else if (status == VL6180X_ERROR_NOCONVERGE) {
    Serial.print("(No convergence)");
  }
  else if (status == VL6180X_ERROR_RANGEIGNORE) {
    Serial.print("(Ignoring range)");
  }
  else if (status == VL6180X_ERROR_SNR) {
    Serial.print("Signal/Noise error");
  }
  else if (status == VL6180X_ERROR_RAWUFLOW) {
    Serial.print("Raw reading underflow");
  }
  else if (status == VL6180X_ERROR_RAWOFLOW) {
    Serial.print("Raw reading overflow");
  }
  else if (status == VL6180X_ERROR_RANGEUFLOW) {
    Serial.print("Range reading underflow");
  }
  else if (status == VL6180X_ERROR_RANGEOFLOW) {
    Serial.print("Range reading overflow");
  }
}

void read_sensors() {
  uint8_t range1 = lox1.readRange();
  uint8_t range2 = lox2.readRange();

  uint8_t range3 = lox3.readRange();
  uint8_t range4 = lox4.readRange();

  float gl = (range1 + range2) / 2.0;
  float gr = (range3 + range4) / 2.0;

  float err = gr - gl;

  smoother.addValue(err);

  Serial.println(smoother.getAverage());

  delay(50);
}

//===============================================================
// Setup
//===============================================================
void setup() {
  Serial.begin(115200);

  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }

  pinMode(SHT_LOX1, OUTPUT);
  pinMode(SHT_LOX2, OUTPUT);
  pinMode(SHT_LOX3, OUTPUT);
  pinMode(SHT_LOX4, OUTPUT);

  Serial.println("Shutdown pins inited...");

  digitalWrite(SHT_LOX1, LOW);
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);
  digitalWrite(SHT_LOX4, LOW);
  Serial.println("All in reset mode...(pins are low)");


  Serial.println("Starting...");
  setID();

}

//===============================================================
// Loop
//===============================================================
void loop() {
  read_sensors();
  delay(200);
}