#include <AccelStepper.h>
#include "config.h"

AccelStepper leftStepper;
AccelStepper rightStepper;

void initStepper();
void prepareLeftStepper();
void prepareRightStepper();

void runStepper();

void stopStepper();