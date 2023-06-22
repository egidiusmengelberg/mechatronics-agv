#include "stepper.h"

TinyStepper_28BYJ_48 leftStepper;
TinyStepper_28BYJ_48 rightStepper;

void initStepper() {
    leftStepper.connectToPins(STEPPER_L_1_PIN, STEPPER_L_2_PIN, STEPPER_L_3_PIN, STEPPER_L_4_PIN);
    rightStepper.connectToPins(STEPPER_R_1_PIN, STEPPER_R_2_PIN, STEPPER_R_3_PIN, STEPPER_R_4_PIN);

    leftStepper.setSpeedInStepsPerSecond(STEPPER_MAX_V);
    leftStepper.setAccelerationInStepsPerSecondPerSecond(STEPPER_MAX_A);

    rightStepper.setSpeedInStepsPerSecond(STEPPER_MAX_V);
    rightStepper.setAccelerationInStepsPerSecondPerSecond(STEPPER_MAX_A);
}

void runStepper(int dist, float dir) {
    long stepsLeft = dist;
    long stepsRight = dist;

    if (dir > 0.0) {
      stepsLeft = dist * dir;
    }

    if (dir < 0.0) {
      stepsRight = dist * dir * -1;
    }
      
    float v_left;
    float a_left;
    float v_right;
    float a_right;
    long absStepsLeft;
    long absStepsRight;

    v_left = STEPPER_MAX_V;
    a_left = STEPPER_MAX_A;
  
    v_right = STEPPER_MAX_V;
    a_right = STEPPER_MAX_A;
  
    if (stepsLeft >= 0)
      absStepsLeft = stepsLeft;
    else
      absStepsLeft = -stepsLeft;
   
    if (stepsRight >= 0)
      absStepsRight = stepsRight;
    else
      absStepsRight = -stepsRight;


    if ((absStepsLeft > absStepsRight) && (stepsLeft != 0))
    {
      float scaler = (float) absStepsRight / (float) absStepsLeft;
      v_right = v_right * scaler;
      a_right = a_right * scaler;
    }
  
    if ((absStepsRight > absStepsLeft) && (stepsRight != 0))
    {
      float scaler = (float) absStepsLeft / (float) absStepsRight;
      v_left = v_left * scaler;
      a_left = a_left * scaler;
    }


    leftStepper.setSpeedInStepsPerSecond(v_left);
    leftStepper.setAccelerationInStepsPerSecondPerSecond(a_left);
    leftStepper.setupRelativeMoveInSteps(stepsLeft);
  
    rightStepper.setSpeedInStepsPerSecond(v_right);
    rightStepper.setAccelerationInStepsPerSecondPerSecond(a_right);
    rightStepper.setupRelativeMoveInSteps(stepsRight);
  
    while((!leftStepper.motionComplete()) || (!rightStepper.motionComplete()))
    {
      leftStepper.processMovement();
      rightStepper.processMovement();
    }
}
