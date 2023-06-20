#include <Adafruit_VL6180X.h>
#include "RunningAverage.h"
#include "config.h"

Adafruit_VL6180X lox1;
Adafruit_VL6180X lox2;
Adafruit_VL6180X lox3;
Adafruit_VL6180X lox4;

RunningAverage smoother;


void initTof();
void averageTof();