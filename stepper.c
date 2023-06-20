#include "stepper.h"

AccelStepper leftStepper(AccelStepper::FULL4WIRE, STEPPER_L_1_PIN, STEPPER_L_2_PIN, STEPPER_L_3_PIN, STEPPER_L_4_PIN);
AccelStepper rightStepper(AccelStepper::FULL4WIRE, STEPPER_R_1_PIN, STEPPER_R_2_PIN, STEPPER_R_3_PIN, STEPPER_R_4_PIN);

void initStepper() {
    leftStepper.setMaxSpeed(STEPPER_MAX_V);
    leftStepper.setAcceleration(STEPPER_MAX_A);

    rightStepper.setMaxSpeed(STEPPER_MAX_V);
    rightStepper.setAcceleration(STEPPER_MAX_A);
}

void prepareLeftStepper(int x) {
    leftStepper.moveTo(x);
}

void prepareRightStepper(int x) {
    rightStepper.moveTo(x);
}

void runStepper() {
    leftStepper.run();
    rightStepper.run();
}

void stopStepper() {
    leftStepper.stop();
    rightStepper.stop();
}